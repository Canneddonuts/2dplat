#ifndef NPC_HEADER
#define NPC_HEADER

#define MAX_NPCS 10

extern float textCounter;

void InitNpcs(npc_t npc[]);
void UpdateNpcs(npc_t npc[], const player_t *player);
void DrawNpcs(npc_t npc[]);
void DrawNpcTextBox(npc_t npc[]);

#endif
