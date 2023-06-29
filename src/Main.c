#include "raylib/raylib.h"
#include "raylib/raymath.h"

#include "Game.h"

Texture2D bg;
Texture2D cat;
Camera2D camera;

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

void UpdateDrawFrame(void)
{
  UpdateGame();
  DrawGame();
}

int main(void)
{
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);

  InitWindow(640, 480, "Platformer Story");
  InitGame();

  bg = LoadTexture("assets/gfx/bg.png");
  cat = LoadTexture("assets/gfx/cat.png");

  #if defined(PLATFORM_WEB)
      emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
  #else
      SetTargetFPS(60);

      while (!WindowShouldClose()) UpdateDrawFrame();
  #endif

  DestroyGame();
  CloseWindow();

  return 0;
}
