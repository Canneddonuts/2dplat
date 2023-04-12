#ifndef GAME_HEADER
#define GAME_HEADER

#include <stddef.h>

extern Texture2D bg;
extern Camera2D camera;
extern Texture2D cat;

typedef struct 
{
  Rectangle pos;
  Rectangle sourceRec;
  Rectangle destRec;
  Vector2 origin;
  Vector2 velocity;
  Vector2 acceleration;
  float friction;
  int rotation;
  int dir;
  bool canJump;
  bool is_jumping;
  bool is_walking;
} player_t;

typedef struct
{
  Rectangle pos;
  const char *msg;
  bool talkin;
} npc_t;

typedef struct
{
  Rectangle pos;
  Color color;
  int type;
} ground_t;

void InitGame(void);
void UpdateGame(void);
void DrawGame(void);
void DestroyGame(void);
void UpdatePlayerPhysics(player_t *player, ground_t *ground, int max);
int  TouchingGroundElement(player_t *player, ground_t *ground, int max);
int  IsPlayerOffScreen(player_t *player, float DeathPosY);
void InitPlayer(player_t *player);
void UpdatePlayerAnimation(player_t *player);
void UpdatePlayerSpritePos(player_t *player);
void UpdatePlayerDir(player_t *player);
void ResetPlayer(player_t *player);
void UpdateGameCamera(Camera2D *camera, float delta, player_t *player, int width, int height);
void UpdateUserCamera(Camera2D *camera);
void InitGround(ground_t **ground, int n);
void AddGroundBlock(ground_t **ground, size_t *n, int GroundType, Vector2 pos);
void UpdateGroundMovement(ground_t *ground, int n);

#endif
