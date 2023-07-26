#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Game.h"
#include "Player.h"
#include "Camera.h"
#include "Controls.h"
#include "Debug.h"
#include "Ground.h"
#include "Npc.h"

Vector2 MouseVector = { 0 };

static player_t player;
static ground_t *ground;
static npc_t npc[MAX_NPCS];

void InitGame(void)
{
  memset(&player, 0, sizeof(player_t));
  InitPlayer(&player);

  memset(&camera, 0, sizeof(Camera2D));
  InitCamera(&camera, &player);

  memset(&ground, 0, sizeof(ground_t) * GroundAmount);
  InitGround(&ground, GroundAmount);

  memset(npc, 0, sizeof(npc_t) * MAX_NPCS);
  InitNpcs(npc);
}

void UpdateGame(void)
{
  MouseVector = GetScreenToWorld2D(GetMousePosition(), camera);

  CameraUpdate(&camera, &player);

  UpdateDebugToggles();

  UpdateGround(&ground, &GroundAmount);

  UpdatePlayer(&player, ground, GroundAmount, DebugPhysics);

  UpdateNpcs(npc, &player);
}

void DrawGame(void)
{
  BeginDrawing();

          ClearBackground(RAYWHITE);

          if (DimedBackground)
              DrawTexture(BackgroundSprite, -20, -20, GRAY);
          else
              DrawTexture(BackgroundSprite, -20, -20, RAYWHITE);

          BeginMode2D(camera);
                          DrawText("Welcome to Macaroon's Misadventure", -220, 380, 30, Fade(RED,fabs(sin(GetTime()))));

                          DrawGround(ground, GroundAmount);

                          DrawText("We ran out of blocks", ground[6].pos.x, ground[6].pos.y, 30, WHITE);

                          DrawNpcs(npc);

                          DrawPlayer(&player);

                          DrawDebugLines(&player, ground, GroundAmount);
          EndMode2D();

          DrawFPS(0, 0);
          DrawDebugInfo(&player, GroundAmount, textCounter);

          DrawNpcTextBox(npc);

  EndDrawing();
}

void DestroyGame(void)
{
  // Free all our allocated memory
  free(ground);
  UnloadTexture(BackgroundSprite);
  UnloadTexture(PlayerSprite);
}
