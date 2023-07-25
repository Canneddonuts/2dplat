#ifndef GAME_HEADER
#define GAME_HEADER

#include <stddef.h>

extern Texture2D BackgroundSprite;
extern Texture2D PlayerSprite;
extern Camera2D camera;

typedef struct Player
{
  bool canJump;
  bool is_jumping;
  bool is_walking;
  int dir;
  int rotation;
  float friction;
  Vector2 origin;
  Vector2 velocity;
  Vector2 acceleration;
  Color hbcolor;
  Color scolor;
  Rectangle pos;
  Rectangle sourceRec;
  Rectangle destRec;
} player_t;

typedef struct Npc
{
  Rectangle pos;
  const char *msg;
  bool talkin;
} npc_t;

typedef struct Ground
{
  Rectangle pos;
  Color color;
  int type;
} ground_t;

void InitGame(void);
void UpdateGame(void);
void DrawGame(void);
void DestroyGame(void);
int  TouchingGroundElement(player_t *player, ground_t *ground, int n);
void UpdateGameCamera(Camera2D *camera, float delta, player_t *player, int width, int height);
void UpdateUserCamera(Camera2D *camera);
void InitGround(ground_t **ground, int n);
void DeleteGroundBlock(ground_t **ground, size_t *n);
void AddGroundBlock(ground_t **ground, size_t *n, int GroundType, Vector2 pos);
void UpdateGroundMovement(ground_t *ground, int n);

#endif
