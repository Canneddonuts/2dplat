#include "../include/raylib.h"
#include <math.h>

#include "Game.h"
#include "Controls.h"

void UpdateHorizontalPhysics(player_t *player)
{
  player->acceleration.x = 0;

  if ((INPUT_LEFT_DOWN)) player->acceleration.x -= 2000;
  if ((INPUT_RIGHT_DOWN)) player->acceleration.x += 2000;

  player->acceleration.x += player->velocity.x * player->friction;

  player->velocity.x += player->acceleration.x * GetFrameTime();

  player->velocity.x = max(-700, min(player->velocity.x, 700));
  if (fabsf(player->velocity.x) < 1) player->velocity.x = 0;

  player->pos.x += player->velocity.x * GetFrameTime() + (player->acceleration.x * .5) * (GetFrameTime() * GetFrameTime());
}

int TouchingGroundElement(player_t *player, ground_t *ground, int max)
{
  for (int i = 0; i < max; ++i) {
    if (CheckCollisionRecs(player->pos, (ground + i)->pos)) return i;
  }

  return -1;
}

void UpdateVerticalPhysics(player_t *player, ground_t *ground, int max)
{
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
