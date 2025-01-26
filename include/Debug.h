#ifndef DEBUG_HEADER
#define DEBUG_HEADER

extern bool DebugInfo;
extern bool CameraEnabled;
extern bool HitboxLines;
extern bool DebugPhysics;

void UpdateDebugToggles(void);
void DrawDebugInfo(const player_t *player, int GroundAmount, float textCounter);
void DrawDebugLines(const player_t *player, const ground_t *ground, int GroundAmount);

#endif
