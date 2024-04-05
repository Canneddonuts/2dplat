#ifndef GAME_HEADER
#define GAME_HEADER

extern Texture2D BackgroundSprite;
extern Texture2D PlayerSprite;
extern Camera2D camera;
extern Vector2 MouseVector;

typedef struct Player
{
  bool canJump;
  bool is_jumping;
  bool is_walking;
  int dir;
  int rotation;
  float friction;
  float jumpBufferCounter;
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
  int type;
  Color color;
  Rectangle pos;
} ground_t;

void InitGame(void);
void UpdateGame(void);
void DrawGame(void);
void DestroyGame(void);
ground_t *TouchingGroundElement(player_t *player, ground_t *ground, int n);

#endif
