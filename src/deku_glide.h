#include "modding.h"
#include "global.h"

// #define CONFIG_UNLIMITED_GLIDING (bool)recomp_get_config_u32("unlimited_gliding")
// #define CONFIG_REDEPLOY (bool)recomp_get_config_u32("redeploy")

bool glideConsumed = false;
bool doActionGlide = false;

extern void Player_Action_94(Player* this, PlayState* play);
extern s32 Player_SetAction(PlayState* play, Player* this, PlayerActionFunc actionFunc, s32 arg3);
extern void func_8082E1F0(Player* this, u16 sfxId);
extern Input* sPlayerControlInput;

void StartGlide(Player* this, PlayState* play);