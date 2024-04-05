#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include <stdio.h>
#include <stdlib.h>

#include "Game.h"
#include "Ground.h"

bool PlaceMode = false;
size_t GroundAmount = 7;

static int NextGroundType = 0;

static void AddGroundBlock(ground_t **ground, size_t *n, int GroundType, Vector2 pos);
static void DeleteGroundBlock(ground_t **ground, size_t *n);
static void UpdateGroundMovement(ground_t *ground, size_t n);

ground_t *TouchingGroundElement(player_t *player, ground_t *ground, int n)
{
  for (int i = 0; i < n; ++i) {
    if (CheckCollisionRecs(player->pos, ground[i].pos)) {
        player->hbcolor = YELLOW;
        return &ground[i];
    } else player->hbcolor = RED;
  }

  return NULL;
}

void InitGround(ground_t **ground, int n)
{
  *ground = malloc(n * sizeof(ground_t));

  (*ground)[0] = (ground_t) { 0, GRAY, (Rectangle){ 50, 520, 30, 30 } };
  (*ground)[1] = (ground_t) { 0, GRAY, (Rectangle){ 190, 590, 150, 30 } };
  (*ground)[2] = (ground_t) { 0, GRAY, (Rectangle){ 450, 520, 30, 30 } };
  (*ground)[3] = (ground_t) { 0, GRAY, (Rectangle){ 550, 520, 30, 30 } };
  (*ground)[4] = (ground_t) { 0, GRAY, (Rectangle){ 650, 450, 200, 30 } };
  (*ground)[5] = (ground_t) { 0, GRAY, (Rectangle){ 880, 351, 200, 20 } };
  (*ground)[6] = (ground_t) { 0, BLANK,(Rectangle){ -400, 800, 330, 30 } };
}

void UpdateGround(ground_t **ground, size_t *GroundAmount)
{
  if (IsKeyPressed(KEY_P))
      PlaceMode = !PlaceMode;

  if (IsKeyPressed(KEY_ZERO))
      NextGroundType = 0;

  if (IsKeyPressed(KEY_ONE))
      NextGroundType = 1;

  if (PlaceMode) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
      AddGroundBlock(ground, GroundAmount, NextGroundType, MouseVector);

    if (IsKeyPressed(KEY_BACKSPACE) && *GroundAmount > 7)
      DeleteGroundBlock(ground, GroundAmount);
  }

  UpdateGroundMovement(*ground, *GroundAmount);
}

void DrawGround(ground_t *ground, int n)
{
  for (int i = 0; i < n; ++i) {
    DrawRectangleRec(ground[i].pos, ground[i].color);
  }
}

static void AddGroundBlock(ground_t **ground, size_t *n, int GroundType, Vector2 pos)
{
  *n += 1;

  ground_t *ngp = realloc(*ground, *n * sizeof(ground_t));

  if (ngp == NULL)
      return;

  *ground = ngp;

  ngp = NULL;

  (*ground)[*n-1] = (ground_t) { GroundType, BLANK, (Rectangle){ pos.x, pos.y, 30, 30, } };

  switch (GroundType) {
	  case 0: (*ground)[*n-1].color = RED; break;
	  case 1: (*ground)[*n-1].color = BLUE; break;
  }

  printf("INFO: GAME: ground[%zu] dynamicly spawned at pos %f, %f\n", *n, pos.x, pos.y );
}

static void DeleteGroundBlock(ground_t **ground, size_t *n)
{
  if (*n < 8)
      return;

  printf("INFO: GAME: ground[%zu] deleted\n", *n);

  *n -= 1;

  ground_t *ngp = realloc(*ground, *n * sizeof(ground_t));

  *ground = ngp;

  ngp = NULL;
}

static void UpdateGroundMovement(ground_t *ground, size_t n)
{
  for (int i = 0; i < n; ++i) {
    if (ground[i].type == 1) ground[i].pos.y +=  sin(GetTime()*2) * GetFrameTime()*40;
  }
}
