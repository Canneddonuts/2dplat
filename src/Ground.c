#include "raylib/raylib.h"
#include <stdlib.h>

#include "Game.h"

void InitGround(ground_t **ground, int n)
{
  *ground = malloc(n * sizeof(ground_t));

  (*ground)[0] = (ground_t) { (Rectangle){ 50, 520, 30, 30 }, GRAY, 0 };
  (*ground)[1] = (ground_t) { (Rectangle){ 190, 590, 150, 30 }, GRAY, 0 };
  (*ground)[2] = (ground_t) { (Rectangle){ 450, 520, 30, 30 }, GRAY, 0 };
  (*ground)[3] = (ground_t) { (Rectangle){ 550, 520, 30, 30 }, GRAY, 0 };
  (*ground)[4] = (ground_t) { (Rectangle){ 650, 450, 200, 30 }, GRAY, 0 };
  (*ground)[5] = (ground_t) { (Rectangle){ 880, 351, 200, 20 }, GRAY, 0 };
  (*ground)[6] = (ground_t) { (Rectangle){ -400, 800, 330, 30 }, BLANK, 0 };
}

int TouchingGroundElement(player_t *player, ground_t *ground, int max)
{
  for (int i = 0; i < max; ++i) {
    if (CheckCollisionRecs(player->pos, (ground + i)->pos)) return i;
  }

  return -1;
}

void AddGroundBlock(ground_t **ground, size_t *n, int GroundType, Vector2 pos)
{
  *n += 1;

  ground_t *ngp = realloc(*ground, *n * sizeof(ground_t));

  if (ngp != NULL) *ground = ngp;

  ngp = NULL;

  (*ground)[*n-1] = (ground_t) { (Rectangle){ pos.x, pos.y, 30, 30, }, BLANK, GroundType };

  switch (GroundType) {
	  case 0: (*ground)[*n-1].color = RED; break;
	  case 1: (*ground)[*n-1].color = BLUE; break;
  }
}