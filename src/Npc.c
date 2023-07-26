#include "raylib/raylib.h"

#include "Game.h"
#include "Npc.h"
#include "Controls.h"

float textCounter = 0;

static bool IsNpcsActive(npc_t npc[]);

void InitNpcs(npc_t npc[])
{
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

void UpdateNpcs(npc_t npc[], const player_t *player)
{
  for (int i = 0; i < MAX_NPCS; ++i) {
    if (CheckCollisionRecs(player->pos, npc[i].pos))
        npc[i].talkin = true;
    else
        npc[i].talkin = false;
  }

  if (IsNpcsActive(npc)) {
    if ((INPUT_TALK_DOWN))
        textCounter += GetFrameTime() * 30;
    else
        textCounter += GetFrameTime() * 10;
  } else {
    textCounter = 0;
  }
}

void DrawNpcs(npc_t npc[])
{
  for (int i = 0; i < MAX_NPCS; ++i) {
    DrawRectangleRec(npc[i].pos, GREEN);
  }
}

void DrawNpcTextBox(npc_t npc[])
{
  for (int i = 0; i < MAX_NPCS; ++i) {
    if (npc[i].talkin) {
      DrawRectangle(0, GetScreenHeight()-100, GetScreenWidth(), 100, Fade(BLACK, 0.3));

      DrawText(TextSubtext(npc[i].msg, 0, textCounter), 10, GetScreenHeight() - 80, 30, WHITE);
    }
  }
}

static bool IsNpcsActive(npc_t npc[])
{
  for (int i = 0; i < MAX_NPCS; ++i) {
    if (npc[i].talkin) return true;
  }

  return false;
}
