#include "raylib/raylib.h"
#include "raylib/raymath.h"

#include "Game.h"
#include "Camera.h"
#include "Debug.h"

static void UpdateGameCamera(Camera2D *camera, float delta, const player_t *player, int width, int height);
static void UpdateUserCamera(Camera2D *camera);

void InitCamera(Camera2D *camera, const player_t *player)
{
  camera->offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };

  camera->target = (Vector2){ player->pos.x+15, player->pos.y+5 };

  camera->rotation = 0.0f;

  camera->zoom = 1.0f;
}

void CameraUpdate(Camera2D *camera, const player_t *player)
{
  if (CameraEnabled)
      UpdateGameCamera(camera, GetFrameTime(), player, GetScreenWidth(), GetScreenHeight());

  UpdateUserCamera(camera);
}

static void UpdateGameCamera(Camera2D *camera, float delta, const player_t *player, int width, int height)
{
    static float minSpeed = 30;
    static float minEffectLength = 10;
    static float fractionSpeed = 0.8f;

    camera->offset = (Vector2){ width/2.0f, height/2.0f };
    Vector2 diff = Vector2Subtract((Vector2){ player->pos.x, player->pos.y }, camera->target);
    float length = Vector2Length(diff);

    if (length > minEffectLength) {
        float speed = fmaxf(fractionSpeed*length, minSpeed);
        camera->target = Vector2Add(camera->target, Vector2Scale(diff, speed*delta/length));
    }
}

static void UpdateUserCamera(Camera2D *camera)
{
  if (IsKeyDown(KEY_EQUAL))
      camera->zoom += GetFrameTime()/2;
  else if (IsKeyDown(KEY_MINUS) && camera->zoom > 0)
      camera->zoom -= GetFrameTime()/2;

  if (IsKeyDown(KEY_I))
      camera->target.y -= GetFrameTime()*250;
  else if (IsKeyDown(KEY_K))
      camera->target.y += GetFrameTime()*250;

  if (IsKeyDown(KEY_J))
      camera->target.x -= GetFrameTime()*250;
  else if (IsKeyDown(KEY_L))
      camera->target.x += GetFrameTime()*250;
}
