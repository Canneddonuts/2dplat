#ifndef GAME_HEADER
#define GAME_HEADER

extern Texture2D bg;
extern Camera2D camera;
extern Texture2D cat;

#define max(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})

#define min(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})

typedef struct
{
  Rectangle pos;
  Rectangle sourceRec;
  Rectangle destRec;
  Vector2 origin;
  Vector2 velocity;
  Vector2 acceleration;
  float friction;
  bool canJump;
  bool is_jumping;
} player_t;

typedef struct
{
  Rectangle pos;
  char *msg;
  bool talkin;
} npc_t;

typedef struct
{
  Rectangle pos;
  Color color;
} ground_t;

void InitGame(void);
void UpdateGame(void);
void DrawGame(void);
void DestroyGame(void);
void UpdatePlayerPhysics(player_t *player, ground_t *ground, int max);
int  TouchingGroundElement(player_t *player, ground_t *ground, int max);
void UpdateGameCamera(Camera2D *camera, float delta, player_t *player, int width, int height);
void UpdateUserCamera(Camera2D *camera);

#endif
