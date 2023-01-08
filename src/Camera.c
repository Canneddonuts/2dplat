#include "../include/raylib.h"
#include "../include/raymath.h"

#include "Game.h"

void UpdateGameCamera(Camera2D *camera, float delta, player_t *player, int width, int height)
{
    static float minSpeed = 30;
    static float minEffectLength = 10;
    static float fractionSpeed = 0.8f;

    camera->offset = (Vector2){ width/2.0f, height/2.0f };
    Vector2 diff = Vector2Subtract((Vector2){ player->pos.x, player->pos.y }, camera->target);
    float length = Vector2Length(diff);

    if (length > minEffectLength)
    {
        float speed = fmaxf(fractionSpeed*length, minSpeed);
        camera->target = Vector2Add(camera->target, Vector2Scale(diff, speed*delta/length));
    }
}

void UpdateUserCamera(Camera2D *camera)
{
  if (IsKeyDown(KEY_EQUAL)) camera->zoom += GetFrameTime()/2;
  else if (IsKeyDown(KEY_MINUS)) camera->zoom -= GetFrameTime()/2;

  if (IsKeyDown(KEY_I)) camera->target.y -= GetFrameTime()*250;
  else if (IsKeyDown(KEY_K)) camera->target.y += GetFrameTime()*250;

  if (IsKeyDown(KEY_J)) camera->target.x -= GetFrameTime()*250;
  else if (IsKeyDown(KEY_L)) camera->target.x += GetFrameTime()*250;
}
