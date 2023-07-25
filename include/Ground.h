#ifndef GROUND_HEADER
#define GROUND_HEADER

extern bool PlaceMode;
extern size_t GroundAmount;

void InitGround(ground_t **ground, int n);
void UpdateGround(ground_t **ground, size_t *GroundAmount);
void DrawGround(ground_t *ground, int n);

#endif
