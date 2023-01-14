#include "../include/raylib.h"
#include "../include/raymath.h"
#include <stdio.h>
#include <stdlib.h>

#include "Game.h"
#include "Controls.h"

#define MAX_NPCS 10
size_t GroundAmount = 7;

float textCounter = 0;
float rotation = 0;

int catdir = 1;
int NextGroundType = 0;
Vector2 MouseVector = { 0 };

bool DebugInfo = false;
bool CameraEnabled = true;
bool DimedBackground = false;
bool PlaceMode = false;
bool HitboxLines = false;

player_t player;
ground_t *ground;
npc_t npc[MAX_NPCS];  

bool IsNpcsActive(npc_t npc[])
{
  for (int i = 0; i < MAX_NPCS; ++i) {
    if (npc[i].talkin) return true;
  }

  return false;
}

void InitGame(void)
{
  player = (player_t){ (Rectangle){ 64, 491, 30, 30 } };
  player.friction = -9;

  camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
  camera.target = (Vector2){ player.pos.x+15, player.pos.y+5 };
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  // Allocate space in RAM for the blocks
  ground = malloc(GroundAmount * sizeof(*ground));

  ground[0] = (ground_t){ (Rectangle){ 50, 520, 30, 30 }, GRAY, 0 };
  ground[1] = (ground_t){ (Rectangle){ 190, 590, 150, 30 }, GRAY, 0 };
  ground[2] = (ground_t){ (Rectangle){ 450, 520, 30, 30 }, GRAY, 0 };
  ground[3] = (ground_t){ (Rectangle){ 550, 520, 30, 30 }, GRAY, 0 };
  ground[4] = (ground_t){ (Rectangle){ 650, 450, 200, 30 }, GRAY, 0 };
  ground[5] = (ground_t){ (Rectangle){ 880, 351, 200, 20 }, GRAY, 0 };
  ground[6] = (ground_t){ (Rectangle){ -400, 800, 330, 30 }, BLANK, 0 };
  
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

  // add new blocks with realloc
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && PlaceMode) {
    GroundAmount++;

    ground = (ground_t*)realloc(ground, GroundAmount * sizeof(*ground));
     
    ground[GroundAmount-1] = (ground_t){ (Rectangle){ MouseVector.x, MouseVector.y, 30, 30, }, BLANK, NextGroundType };

    switch (NextGroundType) {
	case 0: ground[GroundAmount-1].color = RED; break;
	case 1: ground[GroundAmount-1].color = BLUE; break;
    }

    printf("INFO: GAME: ground[%zu] dynamicly spawned at pos %f, %f\n", GroundAmount, MouseVector.x, MouseVector.y );
  }

  for (int i = 0; i < GroundAmount; ++i) {
     if (ground[i].type == 1) ground[i].pos.y +=  sin(GetTime()*2) * GetFrameTime()*60;
  } 

  UpdatePlayerPhysics(&player, ground, GroundAmount);

  player.sourceRec = (Rectangle){ 0, 0, cat.width*catdir, cat.height };
  player.destRec = (Rectangle){ player.pos.x+10, player.pos.y+15, cat.width, cat.height };
  player.origin = (Vector2){ player.destRec.width/2, player.destRec.height/2 };

  player.is_walking = (INPUT_RIGHT_DOWN) || (INPUT_LEFT_DOWN);

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

  if (IsKeyPressed(KEY_D)) DebugInfo = !DebugInfo;
  if (IsKeyPressed(KEY_H)) HitboxLines = !HitboxLines;
  if (IsKeyPressed(KEY_C)) CameraEnabled = !CameraEnabled;
  if (IsKeyPressed(KEY_G)) DimedBackground = !DimedBackground;
  if (IsKeyPressed(KEY_P)) PlaceMode = !PlaceMode;
  if (IsKeyPressed(KEY_ZERO)) NextGroundType = 0;
  if (IsKeyPressed(KEY_ONE)) NextGroundType = 1;

  if (CameraEnabled) UpdateGameCamera(&camera, GetFrameTime(), &player, GetScreenWidth(), GetScreenHeight());

  UpdateUserCamera(&camera);

  if (player.pos.y > 1000 || IsKeyPressed(KEY_R)) { player.pos.x = 64; player.pos.y = 491; player.velocity.y = 0; player.velocity.x = 0; }

  if (!player.canJump && catdir == 1) rotation += GetFrameTime()*500;
  else if (!player.canJump && catdir == -1) rotation -= GetFrameTime()*500;
  else if (player.is_walking) rotation = 10*sin(GetTime()*10);
  else rotation = 0;
}

void DrawGame(void)
{
  BeginDrawing();

          ClearBackground(RAYWHITE);

          if (DimedBackground) DrawTexture(bg, -20, -20, GRAY);
          else DrawTexture(bg, -20, -20, RAYWHITE);

          BeginMode2D(camera);

                          DrawText("Welcome to Macaroon's Misadventure", -220, 380, 30, Fade(RED,fabsf(sin(GetTime()))));
                         
                          for (int i = 0; i < GroundAmount; ++i) {
                            DrawRectangleRec(ground[i].pos, ground[i].color);
                          }

                          DrawText("We ran out of blocks", ground[6].pos.x, ground[6].pos.y, 30, WHITE);

                          for (int i = 0; i < MAX_NPCS; ++i) {
                            DrawRectangleRec(npc[i].pos, GREEN);
                          }

                          DrawTexturePro(cat, player.sourceRec, player.destRec, player.origin, rotation, RAYWHITE);

                          if (HitboxLines) {
                            DrawRectangleLinesEx(player.pos, 1, RED);
                            DrawCircleLines(player.origin.x, player.origin.y, 10, PURPLE);
                            DrawRectangleLinesEx(player.sourceRec, 1, YELLOW);
                            DrawRectangleLinesEx(player.destRec, 1, BLUE);
                            DrawLineV((Vector2){ -9000, 1000 },(Vector2){ 9000, 1000 }, BLACK);
                            for (int i = 0; i < GroundAmount; ++i) {
                                DrawRectangleLinesEx(ground[i].pos, 2, PINK);
                            }
                          }

          EndMode2D();

          DrawFPS(0, 0);
          if (DebugInfo) {
              DrawRectangle(GetScreenWidth()/2 - 160, 80, 320, 250, Fade(BLACK, 0.3));    
              DrawText("--DEBUG--", GetScreenWidth()/2 - 80, 80, 20, GREEN);
              DrawText(TextFormat("X VELOCITY: %f", player.velocity.x), GetScreenWidth()/2 - 150, 100, 20, WHITE);
              DrawText(TextFormat("X POS: %f", player.pos.x), GetScreenWidth()/2 - 150, 120, 20, WHITE);
              DrawText(TextFormat("X ACCELERATION: %f", player.acceleration.x), GetScreenWidth()/2 - 150, 140, 20, WHITE);
              DrawText(TextFormat("Y VELOCITY: %f", player.velocity.y), GetScreenWidth()/2 - 150, 160, 20, WHITE);
              DrawText(TextFormat("Y POS: %f", player.pos.y), GetScreenWidth()/2 - 150, 180, 20, WHITE);
              DrawText(TextFormat("Y ACCELERATION: %f", player.acceleration.y), GetScreenWidth()/2 - 150, 200, 20, WHITE);
              DrawText(TextFormat("TEXTCOUNTER: , %f", textCounter), GetScreenWidth()/2 - 150, 220, 20, WHITE);
              DrawText(TextFormat("PLACE MODE: , %d", PlaceMode), GetScreenWidth()/2 - 150, 240, 20, WHITE);
              DrawText(TextFormat("sin(GetTime()*2): , %f", sin(GetTime()*2)), GetScreenWidth()/2 - 150, 260, 20, WHITE);
          }

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
}
