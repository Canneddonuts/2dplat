#include "../include/raylib.h"
#include <stdio.h>

#include "Game.h"
#include "Controls.h"

#define MAX_NPCS 10
#define MAX_GND 7

float textCounter = 0;
float rotation = 0;

int catdir = 1;
Vector2 MouseVector = { 0 };

bool Debug = false;
bool CameraEnabled = true;
bool DimedBackground = false;

player_t player = {
  (Rectangle){ 64, 491, 30, 30 },
};

ground_t ground[MAX_GND] = {
  { (Rectangle){ 50, 520, 30, 30 }, GRAY },
  { (Rectangle){ 190, 590, 150, 30 }, GRAY },
  { (Rectangle){ 450, 520, 30, 30 }, GRAY },
  { (Rectangle){ 550, 520, 30, 30 }, GRAY },
  { (Rectangle){ 650, 450, 200, 30 }, GRAY },
  { (Rectangle){ 880, 351, 200, 20 }, GRAY },
  { (Rectangle){ -400, 800, 330, 30 }, BLANK }
};

npc_t npc[MAX_NPCS] = {
  { (Rectangle){ 200, 570, 20, 20 }, "My friend loves Nietzsche.", false },
  { (Rectangle){ 300, 570, 20, 20 }, "God is dead and we killed him frfr ong.", false },
  { (Rectangle){ 450, 500, 20, 20 }, "HiSegmentation fault (core dumped)", false },
  { (Rectangle){ 560, 500, 20, 20 }, "I hate my thoughtless creator.", false },
  { (Rectangle){ 650, 430, 20, 20 }, "Guess what?", false },
  { (Rectangle){ 750, 430, 20, 20 }, "Chiken butt!", false },
  { (Rectangle){ 820, 430, 20, 20 }, "God those two are insufferable!!", false },
  { (Rectangle){ 900, 311, 40, 40 }, "I am bigger therefore superior.", false },
  { (Rectangle){ 1000, 331, 20, 20 }, "The meaning of life is-wait one sec. Oh yeah 'If you can see this I f---ed up.'", false },
  { (Rectangle){ 1060, 331, 20, 20 }, "Use 'IKJL' for camera movement ig.", false }
};

bool IsNpcsActive(npc_t npc[])
{
  for (int i = 0; i < MAX_NPCS; ++i) {
    if (npc[i].talkin) return true;
  }

  return false;
}

void InitGame(void)
{
  camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
  camera.target = (Vector2){ player.pos.x+15, player.pos.y+5 };
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;
  player.friction = -9;
}

void UpdateGame(void)
{
  MouseVector = GetScreenToWorld2D(GetMousePosition(), camera);

  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) printf("%f, %f\n", MouseVector.x, MouseVector.y );

  UpdatePlayerPhysics(&player, ground, MAX_GND);

  player.sourceRec = (Rectangle){ 0, 0, cat.width*catdir, cat.height };
  player.destRec = (Rectangle){ player.pos.x+10, player.pos.y+15, cat.width, cat.height };
  player.origin = (Vector2){ player.destRec.width/2, player.destRec.height/2 };

  if ((INPUT_RIGHT_DOWN) && !(INPUT_LEFT_DOWN)) catdir = 1;
  if ((INPUT_LEFT_DOWN) && !(INPUT_RIGHT_DOWN)) catdir = -1;

  for (int i = 0; i < MAX_NPCS; ++i) {
    if (CheckCollisionRecs(player.pos, npc[i].pos)) { npc[i].talkin = true; }
    else { npc[i].talkin = false; }
  }

  if (IsNpcsActive(npc)) {
    if ((INPUT_TALK_DOWN)) textCounter += GetFrameTime() * 30;
    else textCounter += GetFrameTime() * 10;
  } else textCounter = 0;

  if (IsKeyPressed(KEY_D)) Debug = !Debug;
  if (IsKeyPressed(KEY_C)) CameraEnabled = !CameraEnabled;
  if (IsKeyPressed(KEY_G)) DimedBackground = !DimedBackground;

  if (CameraEnabled) UpdateGameCamera(&camera, GetFrameTime(), &player, GetScreenWidth(), GetScreenHeight());

  UpdateUserCamera(&camera);

  if (player.pos.y > 1000 || IsKeyPressed(KEY_R)) { player.pos.x = 64; player.pos.y = 491; player.velocity.y = 0; player.velocity.x = 0; }

  if (!player.canJump && catdir == 1) rotation += GetFrameTime()*500;
  else if (!player.canJump && catdir == -1) rotation -= GetFrameTime()*500;
  else rotation = 0;
}

void DrawGame(void)
{
  BeginDrawing();

          ClearBackground(RAYWHITE);

          if (DimedBackground) DrawTexture(bg, -20, -20, GRAY);
          else DrawTexture(bg, -20, -20, RAYWHITE);

          BeginMode2D(camera);

                          DrawText("Welcome to Macaroon's Misadventure", -220, 380, 30, RED);



                          for (int i = 0; i < MAX_GND; ++i) {
                            DrawRectangleRec(ground[i].pos, ground[i].color);
                          }

                          DrawText("We ran out of blocks", ground[6].pos.x, ground[6].pos.y, 30, WHITE);

                          for (int i = 0; i < MAX_NPCS; ++i) {
                            DrawRectangleRec(npc[i].pos, GREEN);
                          }

                          DrawTexturePro(cat, player.sourceRec, player.destRec, player.origin, rotation*!player.canJump, RAYWHITE);

                          if (Debug) {
                            DrawRectangleLinesEx(player.pos, 1, RED);
                            DrawCircleLines(player.origin.x, player.origin.y, 10, PURPLE);
                            DrawRectangleLinesEx(player.sourceRec, 1, YELLOW);
                            DrawRectangleLinesEx(player.destRec, 1, BLUE);
                            for (int i = 0; i < MAX_GND; ++i) {
                                DrawRectangleLinesEx(ground[i].pos, 2, PINK);
                            }
                          }

          EndMode2D();

          DrawFPS(0, 0);
           if (Debug) {
              DrawText("--DEBUG--", GetScreenWidth()/2 - 100, 80, 20, LIME);
              DrawText(TextFormat("X VELOCITY: %f", player.velocity.x), GetScreenWidth()/2 - 150, 100, 20, WHITE);
              DrawText(TextFormat("X POS: %f", player.pos.x), GetScreenWidth()/2 - 150, 120, 20, WHITE);
              DrawText(TextFormat("X ACCELERATION: %f", player.acceleration.x), GetScreenWidth()/2 - 150, 140, 20, WHITE);
              DrawText(TextFormat("Y VELOCITY: %f", player.velocity.y), GetScreenWidth()/2 - 150, 160, 20, WHITE);
              DrawText(TextFormat("Y POS: %f", player.pos.y), GetScreenWidth()/2 - 150, 180, 20, WHITE);
              DrawText(TextFormat("Y ACCELERATION: %f", player.acceleration.y), GetScreenWidth()/2 - 150, 200, 20, WHITE);
              DrawText(TextFormat("TEXTCOUNTER: , %f", textCounter), GetScreenWidth()/2 - 150, 220, 20, WHITE);
          }

          for (int i = 0; i < MAX_NPCS; ++i) {
            if (npc[i].talkin) {
              DrawRectangle(0, GetScreenHeight()-70, GetScreenWidth(), 80, BLACK);

              DrawText(TextSubtext(npc[i].msg, 0, textCounter), 10, GetScreenHeight() - 60, 30, WHITE);
            }
          }


  EndDrawing();
}
