#include "deku_glide.h"
#include "recomputils.h"
#include "recompconfig.h"
#include "DAH_header.h"

// ============================================== //
//                MOD INTERACTIONS                //
// ============================================== //

// If when optional dependencies are added, this mod may contain additional options
RECOMP_EXPORT bool IsCheatingEnabled() {
    return false;
}

// Only triggers when performing a modded glide
RECOMP_DECLARE_EVENT(onDekuGlide(Player* this, PlayState* play));



// ============================================== //
//                  DEKU GLIDING                  //
// ============================================== //

void StartGlide(Player* this, PlayState* play) {
    onDekuGlide(this, play);
    glideConsumed = true;

    // Consume button press to avoid immediate cancellation
    sPlayerControlInput->press.button &= ~BTN_A;

    //Set the glide action and associated flags
    if (Player_SetAction(play, this, Player_Action_94, 1)) {
        this->stateFlags3 |= PLAYER_STATE3_2000 | PLAYER_STATE3_1000000;
        func_8082E1F0(this, NA_SE_IT_DEKUNUTS_FLOWER_OPEN);
        Audio_SetSfxTimerLerpInterval(4, 2);
    }
    this->av2.actionVar2 = 9999;
    Math_Vec3f_Copy(this->unk_AF0, &this->actor.world.pos);
}

RECOMP_HOOK("func_8083827C") void PlayerFallCheck_Hook(Player* this, PlayState* play) {
    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        glideConsumed = false;
    }

    // Check if the player is in the air
    if (!(this->stateFlags1 & (PLAYER_STATE1_8000000 | PLAYER_STATE1_20000000)) &&
        ((this->stateFlags1 & PLAYER_STATE1_80000000) ||
         !(this->stateFlags3 & (PLAYER_STATE3_200 | PLAYER_STATE3_2000))) &&
        !(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
        
        // If the player is falling as a Deku Scrub, allow them to glide
        if (!glideConsumed && this->transformation == PLAYER_FORM_DEKU && (this->fallDistance > 2)) {
            doActionGlide = true;
            if (CHECK_BTN_ALL(play->state.input->press.button, BTN_A)) {
                StartGlide(this, play);
            }
        }
        else {
            doActionGlide = false;
        }
    }
    else {
        doActionGlide = false;
    }
}



// ============================================== //
//                DO ACTION HELPER                //
// ============================================== //

bool Action_OpenGlider(CONDITION_PARAMETERS) {
    if (doActionGlide) {
        *doAction = DO_ACTION_OPEN;
        return true;
    }
    return false;
}

DAH_ON_INIT void DAH_on_init() {
    DoActionHelper_RegisterAction(ACTION, Action_OpenGlider, 147, "Deku Glide");
}