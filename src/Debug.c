#include "raylib/raylib.h"
#include "raylib/raymath.h"
#include <stdlib.h>

#include "Game.h"
#include "Debug.h"
#include "Ground.h"

bool DebugInfo = false;
bool CameraEnabled = true;
bool DimedBackground = false;
bool HitboxLines = false;
bool DebugPhysics = false;

void UpdateDebugToggles(void)
{
  if (IsKeyPressed(KEY_D))
      DebugInfo = !DebugInfo;

  if (IsKeyPressed(KEY_H))
      HitboxLines = !HitboxLines;

  if (IsKeyPressed(KEY_C))
      CameraEnabled = !CameraEnabled;

  if (IsKeyPressed(KEY_G))
      DimedBackground = !DimedBackground;

  if (IsKeyPressed(KEY_Q))
      DebugPhysics = !DebugPhysics;
}

void DrawDebugInfo(const player_t *player, int GroundAmount, float textCounter)
{
  if (DebugInfo) {
      DrawRectangle(GetScreenWidth()/2 - 160, 80, 320, 250, Fade(BLACK, 0.3));
      DrawText("--DEBUG--", GetScreenWidth()/2 - 80, 80, 20, GREEN);
      DrawText(TextFormat("X VELOCITY: %f", player->velocity.x), GetScreenWidth()/2 - 150, 100, 20, WHITE);
      DrawText(TextFormat("X POS: %f", player->pos.x), GetScreenWidth()/2 - 150, 120, 20, WHITE);
      DrawText(TextFormat("X ACCELERATION: %f", player->acceleration.x), GetScreenWidth()/2 - 150, 140, 20, WHITE);
      DrawText(TextFormat("Y VELOCITY: %f", player->velocity.y), GetScreenWidth()/2 - 150, 160, 20, WHITE);
      DrawText(TextFormat("Y POS: %f", player->pos.y), GetScreenWidth()/2 - 150, 180, 20, WHITE);
      DrawText(TextFormat("Y ACCELERATION: %f", player->acceleration.y), GetScreenWidth()/2 - 150, 200, 20, WHITE);
      DrawText(TextFormat("TEXTCOUNTER: , %f", textCounter), GetScreenWidth()/2 - 150, 220, 20, WHITE);
      DrawText(TextFormat("PLACE MODE: , %d", PlaceMode), GetScreenWidth()/2 - 150, 240, 20, WHITE);
      DrawText(TextFormat("sin(GetTime()*2): , %f", sin(GetTime()*2)), GetScreenWidth()/2 - 150, 260, 20, WHITE);
      DrawText(TextFormat("GROUNDAMOUNT: , %zu", GroundAmount), GetScreenWidth()/2 - 150, 280, 20, WHITE);
  }
}

void DrawDebugLines(const player_t *player, const ground_t *ground, int GroundAmount)
{
  if (HitboxLines) {
    DrawRectangleLinesEx(player->pos, 1, player->hbcolor);
    DrawCircleLines(player->origin.x, player->origin.y, 10, PURPLE);
    DrawRectangleLinesEx(player->sourceRec, 1, YELLOW);
    DrawRectangleLinesEx(player->destRec, 1, BLUE);
    DrawLineV((Vector2){ -9000, 1000 },(Vector2){ 9000, 1000 }, BLACK);
    for (int i = 0; i < GroundAmount; ++i) {
        DrawRectangleLinesEx(ground[i].pos, 2, PINK);
    }
  }
}
