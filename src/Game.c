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

Vector2 MouseVector = { 0 };

#define MAX_NPCS 10
static float textCounter = 0;

static player_t player;
static ground_t *ground;
static npc_t npc[MAX_NPCS];

bool IsNpcsActive(npc_t npc[])
{
  for (int i = 0; i < MAX_NPCS; ++i) {
    if (npc[i].talkin) return true;
  }

  return false;
}

void InitGame(void)
{
  memset(&player, 0, sizeof(player_t));
  InitPlayer(&player);

  memset(&camera, 0, sizeof(Camera2D));
  InitCamera(&camera, &player);

  memset(&ground, 0, sizeof(ground_t) * GroundAmount);
  InitGround(&ground, GroundAmount);

  npc[0] = (npc_t) { (Rectangle){ 200, 570, 20, 20 }, "My friend loves Nietzsche.", false };
  npc[1] = (npc_t) { (Rectangle){ 300, 570, 20, 20 }, "God is dead and we killed him frfr ong.", false };
  npc[2] = (npc_t) { (Rectangle){ 450, 500, 20, 20 }, "HiSegmentation fault (core dumped)", false };
  npc[3] = (npc_t) { (Rectangle){ 560, 500, 20, 20 }, "I hate my thoughtless creator.", false };
  npc[4] = (npc_t) { (Rectangle){ 650, 430, 20, 20 }, "Guess what?", false };
  npc[5] = (npc_t) { (Rectangle){ 750, 430, 20, 20 }, "Chiken butt!", false };
  npc[6] = (npc_t) { (Rectangle){ 820, 430, 20, 20 }, "God those two are insufferable!!", false };
  npc[7] = (npc_t) { (Rectangle){ 900, 311, 40, 40 }, "I am bigger therefore superior.", false };
  npc[8] = (npc_t) { (Rectangle){ 1000, 331, 20, 20 }, "The meaning of life is-wait one sec. Oh yeah 'If you can see this I f---ed up.'", false };
  npc[9] = (npc_t) { (Rectangle){ 1060, 331, 20, 20 }, "Use 'IKJL' for camera movement ig.", false };
}

void UpdateGame(void)
{
  MouseVector = GetScreenToWorld2D(GetMousePosition(), camera);

  CameraUpdate(&camera, &player);

  UpdateDebugToggles();

  UpdateGround(&ground, &GroundAmount);

  UpdatePlayer(&player, ground, GroundAmount, DebugPhysics);

  for (int i = 0; i < MAX_NPCS; ++i) {
    if (CheckCollisionRecs(player.pos, npc[i].pos)) { npc[i].talkin = true; }
    else { npc[i].talkin = false; }
  }

  if (IsNpcsActive(npc)) {
    if ((INPUT_TALK_DOWN)) textCounter += GetFrameTime() * 30;
    else textCounter += GetFrameTime() * 10;
  } else textCounter = 0;
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

                          for (int i = 0; i < MAX_NPCS; ++i) {
                            DrawRectangleRec(npc[i].pos, GREEN);
                          }

                          DrawPlayer(&player);

                          DrawDebugLines(&player, ground, GroundAmount);
          EndMode2D();

          DrawFPS(0, 0);
          DrawDebugInfo(&player, GroundAmount, textCounter);

          for (int i = 0; i < MAX_NPCS; ++i) {
            if (npc[i].talkin) {
              DrawRectangle(0, GetScreenHeight()-100, GetScreenWidth(), 100, Fade(BLACK, 0.3));

              DrawText(TextSubtext(npc[i].msg, 0, textCounter), 10, GetScreenHeight() - 80, 30, WHITE);
            }
          }


  EndDrawing();
}

void DestroyGame(void)
{
  // Free all our allocated memory
  free(ground);
  UnloadTexture(BackgroundSprite);
  UnloadTexture(PlayerSprite);
}
