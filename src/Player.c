#include "raylib/raylib.h"
#include "raylib/raymath.h"

#include "Game.h"
#include "Player.h"
#include "Macros.h"
#include "Controls.h"

static int IsPlayerOffScreen(const player_t *player, float DeathPosY);
static void ResetPlayer(player_t *player);
static void UpdatePlayerSpritePos(player_t *player);
static void UpdatePlayerDir(player_t *player);
static void UpdatePlayerAnimation(player_t *player);
static void UpdatePlayerPhysics(player_t *player, ground_t *ground, int max);
static void UpdateDebugPlayerMovement(player_t *player, ground_t *ground, int max);

void InitPlayer(player_t *player)
{
  player->pos = (Rectangle) { 64, 491, 30, 30 };

  player->rotation = 0;

  player->dir = 1;

  player->friction = -9.0f;

  player->hbcolor = RED;

  player->scolor = RAYWHITE;

  player->origin = (Vector2) { PlayerSprite.width/2, PlayerSprite.height/2 };
  player->sourceRec = (Rectangle) { 0, 0, PlayerSprite.width*player->dir, PlayerSprite.height };
  player->destRec = (Rectangle) { player->pos.x+10, player->pos.y+15, PlayerSprite.width, PlayerSprite.height };
}

void UpdatePlayer(player_t *player, ground_t *ground, int max, bool DebugPhysics)
{
  if (DebugPhysics)
    UpdateDebugPlayerMovement(player, ground, max);
  else
    UpdatePlayerPhysics(player, ground, max);

  UpdatePlayerSpritePos(player);

  UpdatePlayerDir(player);

  if (IsPlayerOffScreen(player, 1000) || IsKeyPressed(KEY_R))
      ResetPlayer(player);

  UpdatePlayerAnimation(player);
}

void DrawPlayer(player_t *player)
{
  DrawTexturePro
  (
    PlayerSprite,
    player->sourceRec,
    player->destRec,
    player->origin,
    player->rotation,
    player->scolor
  );
}

static int IsPlayerOffScreen(const player_t *player, float DeathPosY)
{
  return (player->pos.y > DeathPosY);
}

static void ResetPlayer(player_t *player)
{
  player->pos.x = 64;
  player->pos.y = 491;

  player->velocity = (Vector2) { 0, 0 };
}

static void UpdatePlayerSpritePos(player_t *player)
{
  player->sourceRec.width = PlayerSprite.width * player->dir;

  player->destRec.x = player->pos.x + 10;
  player->destRec.y = player->pos.y + 15;
}

static void UpdatePlayerDir(player_t *player)
{
  if ((INPUT_RIGHT_DOWN) && !(INPUT_LEFT_DOWN))
      player->dir = 1;

  if ((INPUT_LEFT_DOWN) && !(INPUT_RIGHT_DOWN))
      player->dir = -1;
}

static void UpdatePlayerAnimation(player_t *player)
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

static void UpdatePlayerPhysics(player_t *player, ground_t *ground, int max)
{
  if ((INPUT_LEFT_DOWN))
      player->acceleration.x -= 2000;

  if ((INPUT_RIGHT_DOWN))
      player->acceleration.x += 2000;

  player->acceleration.x += player->velocity.x * player->friction;
  player->velocity.x += player->acceleration.x * GetFrameTime();
  if (fabsf(player->velocity.x) < 1)
      player->velocity.x = 0;

  if (TouchingGroundElement(player, ground, max) > -1) {
    player->canJump = true;
    player->is_jumping = false;
  } else {
    player->canJump = false;
  }

  if (TouchingGroundElement(player, ground, max) == -1) {
    player->velocity.y -= 1000.0f * GetFrameTime();
  } else if (player->canJump && !player->is_jumping) {
    player->velocity.y = 0;
    player->pos.y = (ground + TouchingGroundElement(player, ground, max))->pos.y - 29;
  }

  if (player->canJump && (INPUT_JUMP_PRESSED)) {
      player->is_jumping = true;
      player->velocity.y += 430.0f;
  }

  player->velocity.y = max(-800, player->velocity.y);

  player->acceleration.x = 0;

  player->pos.y -= player->velocity.y * GetFrameTime();
  player->pos.x += player->velocity.x * GetFrameTime() + (player->acceleration.x * .5) * (GetFrameTime() * GetFrameTime());
}

static void UpdateDebugPlayerMovement(player_t *player, ground_t *ground, int max)
{
  if ((INPUT_LEFT_DOWN))
      player->pos.x -= 300 * GetFrameTime();

  if ((INPUT_UP_DOWN))
      player->pos.y -= 300 * GetFrameTime();

  if ((INPUT_RIGHT_DOWN))
      player->pos.x += 300 * GetFrameTime();

  if ((INPUT_DOWN_DOWN))
      player->pos.y += 300 * GetFrameTime();

  if (IsKeyDown(KEY_B))
      player->velocity.y += 500.0f * GetFrameTime();

  if (IsKeyDown(KEY_V))
      player->velocity.y -= 500.0f * GetFrameTime();

  TouchingGroundElement(player, ground, max);
}
