#include "raylib/raylib.h"
#include "raylib/raymath.h"

#include "Game.h"
#include "Macros.h"
#include "Controls.h"

int TouchingGroundElement(player_t *player, ground_t *ground, int max)
{
  for (int i = 0; i < max; ++i) {
    if (CheckCollisionRecs(player->pos, (ground + i)->pos)) return i;
  }

  return -1;
}

int IsPlayerOffScreen(player_t *player, float DeathPosY)
{
  return (player->pos.y > DeathPosY);
}

void ResetPlayer(player_t *player)
{
  player->pos.x = 64;
  player->pos.y = 491;

  player->velocity = (Vector2) { 0, 0 };
}

void UpdatePlayerSpritePos(player_t *player)
{
  player->sourceRec = (Rectangle) { 0, 0, cat.width*player->dir, cat.height };

  player->destRec = (Rectangle) { player->pos.x+10, player->pos.y+15, cat.width, cat.height };

  player->origin = (Vector2) { player->destRec.width/2, player->destRec.height/2 };
}

void UpdatePlayerDir(player_t *player)
{
  if ((INPUT_RIGHT_DOWN) && !(INPUT_LEFT_DOWN)) player->dir = 1;
  if ((INPUT_LEFT_DOWN) && !(INPUT_RIGHT_DOWN)) player->dir = -1;
}

void UpdatePlayerAnimation(player_t *player)
{
  player->is_walking = (INPUT_RIGHT_DOWN) || (INPUT_LEFT_DOWN);

  if (!player->canJump && player->dir == 1)
    player->rotation += GetFrameTime()*500;
  else if (!player->canJump && player->dir == -1)
    player->rotation -= GetFrameTime()*500;
  else if (player->is_walking)
    player->rotation = 10*sin(GetTime()*10);
  else
    player->rotation = 0;
}

void UpdatePlayerPhysics(player_t *player, ground_t *ground, int max)
{
  player->acceleration.x = 0;

  if ((INPUT_LEFT_DOWN)) player->acceleration.x -= 2000;
  if ((INPUT_RIGHT_DOWN)) player->acceleration.x += 2000;

  player->acceleration.x += player->velocity.x * player->friction;

  player->velocity.x += player->acceleration.x * GetFrameTime();

  player->velocity.x = clamp(-700, player->velocity.x, 700);
  if (fabsf(player->velocity.x) < 1) player->velocity.x = 0;

  player->pos.x += player->velocity.x * GetFrameTime() + (player->acceleration.x * .5) * (GetFrameTime() * GetFrameTime());

  if (TouchingGroundElement(player, ground, max) > -1) { player->canJump = true; player->is_jumping = false; }
  else player->canJump = false;

  if (TouchingGroundElement(player, ground, max) == -1) player->velocity.y -= 1000.0f * GetFrameTime();
  else if (player->canJump && !player->is_jumping) {
    player->velocity.y = 0;
    player->pos.y = (ground + TouchingGroundElement(player, ground, max))->pos.y - 29;
  }

  if (player->canJump) {
    if ((INPUT_JUMP_PRESSED)) { player->is_jumping = true; player->velocity.y += 430.0f; }
  }

  player->pos.y -= player->velocity.y * GetFrameTime();
}
