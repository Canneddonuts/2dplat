#include "raylib/raylib.h"

#include "Game.h"

Texture2D BackgroundSprite;
Texture2D PlayerSprite;
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
  SetConfigFlags(FLAG_VSYNC_HINT);

  InitWindow(640, 480, "Platformer Story");

  BackgroundSprite = LoadTexture("assets/gfx/bg.png");
  PlayerSprite = LoadTexture("assets/gfx/cat.png");

  InitGame();

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
