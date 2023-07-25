#ifndef PLAYER_HEADER
#define PLAYER_HEADER

void InitPlayer(player_t *player);
void UpdatePlayer(player_t *player, ground_t *ground, int max, bool DebugPhysics);
void DrawPlayer(player_t *player);

#endif
