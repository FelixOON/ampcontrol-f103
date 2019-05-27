#include "actions.h"

#include <stddef.h>
#include <string.h>

#include "audio/audio.h"
#include "eemap.h"
#include "gui/canvas.h"
#include "gui/layout.h"
#include "input.h"
#include "menu.h"
#include "pins.h"
#include "rtc.h"
#include "screen.h"
#include "settings.h"
#include "spectrum.h"
#include "swtimers.h"
#include "tuner/stations.h"
#include "tuner/tuner.h"
#include "usb/usbhid.h"

static void actionGetButtons(void);
static void actionGetEncoder(void);
static void actionGetRemote(void);
static void actionGetTimers(void);
static void actionRemapBtnShort(void);
static void actionRemapBtnLong(void);
static void actionRemapRemote(void);
static void actionRemapCommon(void);
static void actionRemapNavigate(void);
static void actionRemapEncoder(void);

static Action action = {ACTION_POWERUP, false, FLAG_ON, SCREEN_STANDBY, {0}, 0, ACTION_POWERUP};
static Action qaction = {ACTION_NONE, false, 0, SCREEN_STANDBY, {0}, 0, ACTION_NONE};

static void actionSet(ActionType type, int16_t value)
{
    action.type = type;
    action.value = value;
}

static void actionSetScreen(Screen screen, int16_t timeout)
{
    action.screen = screen;
    action.timeout = timeout;
}

static void actionDispExpired(Screen screen)
{
    memset(&action.param, 0, sizeof (action.param));
    rtcSetMode(RTC_NOEDIT);

    switch (screen) {
    case SCREEN_STANDBY:
    case SCREEN_MENU:
        actionSetScreen(SCREEN_STANDBY, 1000); // TODO: Return to parent screen caused menu
        break;
    default:
        actionSetScreen(screenGetDefault(), 1000);
        break;
    }
}

static void actionResetSilenceTimer(void)
{
    int16_t silenceTimer = settingsGet(EE_SYSTEM_SIL_TIM);

    if (silenceTimer) {
        swTimSet(SW_TIM_SILENCE_TIMER, 1000 * 60 * silenceTimer + 999);
    }
}

static void actionNavigateMenu(RcCmd cmd)
{
    Menu *menu = menuGet();

    switch (cmd) {
    case RC_CMD_NAV_OK:
    case RC_CMD_NAV_RIGHT:
        actionSet(ACTION_MENU_SELECT, (int16_t)(menuGetFirstChild()));
        break;
    case RC_CMD_NAV_BACK:
    case RC_CMD_NAV_LEFT:
        if (menu->selected) {
            menu->selected = false;
        } else if (menuIsTop()) {
            // TODO: Return to original screen called menu
            actionSet(ACTION_STANDBY, FLAG_ON);
        } else {
            actionSet(ACTION_MENU_SELECT, (int16_t)menu->parent);
        }
        break;
    case RC_CMD_NAV_UP:
    case RC_CMD_CHAN_PREV:
        actionSet(ACTION_MENU_CHANGE, -1);
        break;
    case RC_CMD_NAV_DOWN:
    case RC_CMD_CHAN_NEXT:
        actionSet(ACTION_MENU_CHANGE, +1);
        break;
    }
}

static void actionNavigateTextEdit(RcCmd cmd)
{
    switch (cmd) {
    case RC_CMD_NAV_OK:
        action.type = ACTION_TEXTEDIT_APPLY;
        break;
    case RC_CMD_NAV_BACK:
        action.type = ACTION_TEXTEDIT_CANCEL;
        break;
    case RC_CMD_NAV_RIGHT:
    case RC_CMD_CHAN_NEXT:
        action.type = ACTION_TEXTEDIT_ADD_CHAR;
        break;
    case RC_CMD_NAV_LEFT:
    case RC_CMD_CHAN_PREV:
        action.type = ACTION_TEXTEDIT_DEL_CHAR;
        break;
    case RC_CMD_NAV_UP:
        actionSet(ACTION_ENCODER, -1);
        break;
    case RC_CMD_NAV_DOWN:
        actionSet(ACTION_ENCODER, +1);
        break;
    }
}

static void actionNavigateCommon(RcCmd cmd)
{
    AudioProc *aProc = audioGet();
    InputType inType = aProc->par.inType[aProc->par.input];

    switch (cmd) {
    case RC_CMD_NAV_OK:
        action.type = ACTION_OPEN_MENU;
        break;
    case RC_CMD_NAV_BACK:
        switch (inType) {
        case IN_PC:
            actionSet(ACTION_MEDIA, HIDMEDIAKEY_PLAY);
            break;
        default:
            actionSet(ACTION_DISP_EXPIRED, 0);
            break;
        }
        break;
    case RC_CMD_NAV_RIGHT:
        actionSet(ACTION_MEDIA, HIDMEDIAKEY_FFD);
        break;
    case RC_CMD_NAV_LEFT:
        actionSet(ACTION_MEDIA, HIDMEDIAKEY_REWIND);
        break;
    case RC_CMD_NAV_UP:
    case RC_CMD_CHAN_NEXT:
        actionSet(ACTION_CHAN, +1);
        break;
    case RC_CMD_NAV_DOWN:
    case RC_CMD_CHAN_PREV:
        actionSet(ACTION_CHAN, -1);
        break;
    }
}

static void actionNextAudioParam(AudioProc *aProc)
{
    do {
        action.param.tune++;
        if (action.param.tune >= AUDIO_TUNE_END)
            action.param.tune = AUDIO_TUNE_VOLUME;
    } while (aProc->par.item[action.param.tune].grid == NULL && action.param.tune != AUDIO_TUNE_VOLUME);
}

static void actionNextAudioInput(AudioProc *aProc)
{
    action.param.input++;
    if (action.param.input >= aProc->par.inCnt)
        action.param.input = 0;
}

static void actionGetButtons(void)
{
    CmdBtn cmdBtn = getBtnCmd();

    if (cmdBtn & 0xFF00) {
        actionSet(ACTION_BTN_LONG, cmdBtn >> 8);
    } else if (cmdBtn & 0x00FF) {
        actionSet(ACTION_BTN_SHORT, cmdBtn & 0xFF);
    }
}

static void actionGetEncoder(void)
{
    int8_t encVal = getEncoder();

    if (encVal) {
        actionSet(ACTION_ENCODER, encVal);
    }
}

static bool isRemoteCmdRepeatable(RcCmd cmd)
{
    Screen screen = screenGet();

    switch (cmd) {
    case RC_CMD_VOL_UP:
    case RC_CMD_VOL_DOWN:
        return true;
    case RC_CMD_NAV_UP:
    case RC_CMD_NAV_DOWN:
        switch (screen) {
        case SCREEN_AUDIO_PARAM:
        case SCREEN_AUDIO_INPUT:
            return true;
        }
        break;
    case RC_CMD_NAV_LEFT:
    case RC_CMD_NAV_RIGHT:
        switch (screen) {
        case SCREEN_TUNER:
            return true;
        }
        break;
    }

    return false;
}

static void actionGetRemote(void)
{
    RcData rcData = rcRead(true);
    static RcCmd cmdPrev = RC_CMD_END;

    if (rcData.ready) {
        swTimSet(SW_TIM_RC_NOACION, 200);

        RcCmd cmd = rcGetCmd(&rcData);
        int32_t repTime = swTimGet(SW_TIM_RC_REPEAT);

        if (cmd != cmdPrev) {
            actionSet(ACTION_REMOTE, (int16_t)cmd);
            swTimSet(SW_TIM_RC_REPEAT, 1000);
            cmdPrev = cmd;
        } else {
            if (isRemoteCmdRepeatable(cmd)) {
                if (repTime < 500) {
                    actionSet(ACTION_REMOTE, (int16_t)cmd);
                }
            } else {
                if (repTime == 0) {
                    actionSet(ACTION_REMOTE, (int16_t)cmd);
                    swTimSet(SW_TIM_RC_REPEAT, 1000);
                }
            }
        }
    } else {
        if (swTimGet(SW_TIM_RC_NOACION) == 0) {
            swTimSet(SW_TIM_RC_NOACION, SW_TIM_OFF);
            swTimSet(SW_TIM_RC_REPEAT, 0);
            cmdPrev = RC_CMD_END;
        }
    }
}

static void stbyTimerChange(void)
{
    int32_t stbyTimer = swTimGet(SW_TIM_STBY_TIMER);

    static const uint8_t stbyTimeMin[] = {
        2, 5, 10, 20, 40, 60, 90, 120, 180, 240,
    };

    for (uint8_t i = 0; i < sizeof (stbyTimeMin) / sizeof (stbyTimeMin[0]); i++) {
        int32_t stbyTime = 1000 * 60 * stbyTimeMin[i];
        if (stbyTimer < stbyTime) {
            swTimSet(SW_TIM_STBY_TIMER, stbyTime + 999);
            break;
        }
        if (i == sizeof (stbyTimeMin) / sizeof (stbyTimeMin[0]) - 1) {
            swTimSet(SW_TIM_STBY_TIMER, SW_TIM_OFF);
        }
    }
}

static void spModeChange(Spectrum *sp)
{
    if (++sp->mode >= (sp->peaks ? SP_MODE_END : SP_MODE_WATERFALL)) {
        sp->mode = SP_MODE_STEREO;
        sp->peaks = !sp->peaks;
        eeUpdate(EE_SPECTRUM_PEAKS, sp->peaks);
    }
    screenToClear();
    eeUpdate(EE_SPECTRUM_MODE, sp->mode);
}

static void actionGetTimers(void)
{
    if (swTimGet(SW_TIM_DISPLAY) == 0) {
        actionSet(ACTION_DISP_EXPIRED, 0);
    } else if (swTimGet(SW_TIM_INIT_HW) == 0) {
        actionSet(ACTION_INIT_HW, 0);
    } else if (swTimGet(SW_TIM_INIT_SW) == 0) {
        actionSet(ACTION_INIT_SW, 0);
    } else if (swTimGet(SW_TIM_STBY_TIMER) == 0) {
        actionSet(ACTION_STANDBY, FLAG_ON);
    } else if (swTimGet(SW_TIM_SILENCE_TIMER) == 0) {
        actionSet(ACTION_STANDBY, FLAG_ON);
    } else if (swTimGet(SW_TIM_RTC_INIT) == 0) {
        actionSet(ACTION_INIT_RTC, 0);
    }
}

static void actionRemapBtnShort(void)
{
    switch (action.value) {
    case BTN_D0:
        actionSet(ACTION_STANDBY, FLAG_SWITCH);
        break;
    case BTN_D1:
        actionSet(ACTION_AUDIO_INPUT, FLAG_NEXT);
        break;
    case BTN_D2:
        actionSet(ACTION_NAVIGATE, RC_CMD_NAV_BACK);
        break;
    case BTN_D3:
        actionSet(ACTION_NAVIGATE, RC_CMD_CHAN_PREV);
        break;
    case BTN_D4:
        actionSet(ACTION_NAVIGATE, RC_CMD_CHAN_NEXT);
        break;
    case BTN_D5:
        actionSet(ACTION_NAVIGATE, RC_CMD_NAV_OK);
        break;
    case ENC_A:
        actionSet(ACTION_ENCODER, -1);
        break;
    case ENC_B:
        actionSet(ACTION_ENCODER, +1);
        break;
    default:
        break;
    }
}

static void actionRemapBtnLong(void)
{
    Screen screen = screenGet();
    AudioProc *aProc = audioGet();
    InputType inType = aProc->par.inType[aProc->par.input];

    switch (action.value) {
    case BTN_D0:
        break;
    case BTN_D1:
        actionSet(ACTION_RTC_MODE, 0);
        break;
    case BTN_D2:
        switch (inType) {
        case IN_TUNER:
            if (screen == SCREEN_TEXTEDIT) {
                action.type = ACTION_TUNER_DEL_STATION;
            } else {
                action.type = ACTION_TUNER_EDIT_NAME;
            }
            break;
        default:
            break;
        }
        break;
    case BTN_D3:
        actionSet(ACTION_NAVIGATE, RC_CMD_CHAN_PREV);
        break;
    case BTN_D4:
        actionSet(ACTION_NAVIGATE, RC_CMD_CHAN_NEXT);
        break;
    case BTN_D5:
        switch (screen) {
        case SCREEN_TEXTEDIT:
            action.type = ACTION_OPEN_MENU;
            break;
        case SCREEN_STANDBY:
            actionSet(ACTION_MENU_SELECT, MENU_SETUP_SYSTEM);
            break;
        }
        break;
    case ENC_A:
        actionSet(ACTION_ENCODER, -1);
        break;
    case ENC_B:
        actionSet(ACTION_ENCODER, +1);
        break;
    default:
        break;
    }
}

static void actionRemapRemote(void)
{
    Screen screen = screenGet();

    if (screen == SCREEN_MENU) {
        Menu *menu = menuGet();
        if ((menu->parent == MENU_SETUP_RC) && (menu->selected)) {
            actionSet(ACTION_MENU_CHANGE, 0);
            return;
        }
    }

    if (SCREEN_STANDBY == screen &&
        action.value == RC_CMD_MENU) {
        actionSet(ACTION_MENU_SELECT, MENU_SETUP_SYSTEM);
        return;
    }

    if (SCREEN_STANDBY == screen &&
        action.value != RC_CMD_STBY_SWITCH)
        return;

    switch (action.value) {
    case RC_CMD_STBY_SWITCH:
        actionSet(ACTION_STANDBY, FLAG_SWITCH);
        break;

    case RC_CMD_MUTE:
        actionSet(ACTION_AUDIO_MUTE, FLAG_SWITCH);
        break;
    case RC_CMD_VOL_UP:
        actionSet(ACTION_ENCODER, +1);
        break;
    case RC_CMD_VOL_DOWN:
        actionSet(ACTION_ENCODER, -1);
        break;

    case RC_CMD_MENU:
        action.type = ACTION_OPEN_MENU;
        break;

    case RC_CMD_CHAN_NEXT:
        actionSet(ACTION_CHAN, +1);
        break;
    case RC_CMD_CHAN_PREV:
        actionSet(ACTION_CHAN, -1);
        break;

    case RC_CMD_DIG_0:
    case RC_CMD_DIG_1:
    case RC_CMD_DIG_2:
    case RC_CMD_DIG_3:
    case RC_CMD_DIG_4:
    case RC_CMD_DIG_5:
    case RC_CMD_DIG_6:
    case RC_CMD_DIG_7:
    case RC_CMD_DIG_8:
    case RC_CMD_DIG_9:
        actionSet(ACTION_DIGIT, action.value - RC_CMD_DIG_0);
        break;

    case RC_CMD_IN_NEXT:
        actionSet(ACTION_AUDIO_INPUT, FLAG_NEXT);
        break;

    case RC_CMD_NAV_OK:
    case RC_CMD_NAV_BACK:
    case RC_CMD_NAV_RIGHT:
    case RC_CMD_NAV_UP:
    case RC_CMD_NAV_LEFT:
    case RC_CMD_NAV_DOWN:
        actionSet(ACTION_NAVIGATE, action.value);
        break;

    case RC_CMD_BASS_UP:
        screenSet(SCREEN_AUDIO_PARAM);
        action.param.tune = AUDIO_TUNE_BASS;
        actionSet(ACTION_ENCODER, +1);
        break;
    case RC_CMD_BASS_DOWN:
        screenSet(SCREEN_AUDIO_PARAM);
        action.param.tune = AUDIO_TUNE_BASS;
        actionSet(ACTION_ENCODER, -1);
        break;
    case RC_CMD_MIDDLE_UP:
        screenSet(SCREEN_AUDIO_PARAM);
        action.param.tune = AUDIO_TUNE_MIDDLE;
        actionSet(ACTION_ENCODER, +1);
        break;
    case RC_CMD_MIDDLE_DOWN:
        screenSet(SCREEN_AUDIO_PARAM);
        action.param.tune = AUDIO_TUNE_MIDDLE;
        actionSet(ACTION_ENCODER, -1);
        break;
    case RC_CMD_TREBLE_UP:
        screenSet(SCREEN_AUDIO_PARAM);
        action.param.tune = AUDIO_TUNE_TREBLE;
        actionSet(ACTION_ENCODER, +1);
        break;
    case RC_CMD_TREBLE_DOWN:
        screenSet(SCREEN_AUDIO_PARAM);
        action.param.tune = AUDIO_TUNE_TREBLE;
        actionSet(ACTION_ENCODER, -1);
        break;

    case RC_CMD_LOUDNESS:
        actionSet(ACTION_AUDIO_LOUDNESS, FLAG_SWITCH);
        break;
    case RC_CMD_SURROUND:
        actionSet(ACTION_AUDIO_SURROUND, FLAG_SWITCH);
        break;
    case RC_CMD_EFFECT_3D:
        actionSet(ACTION_AUDIO_EFFECT3D, FLAG_SWITCH);
        break;
    case RC_CMD_TONE_BYPASS:
        actionSet(ACTION_AUDIO_BYPASS, FLAG_SWITCH);
        break;

    case RC_CMD_TIME:
        actionSet(ACTION_RTC_MODE, 0);
        break;

    case RC_CMD_STOP:
        actionSet(ACTION_MEDIA, HIDMEDIAKEY_STOP);
        break;
    case RC_CMD_PLAY:
        actionSet(ACTION_MEDIA, HIDMEDIAKEY_PLAY);
        break;
    case RC_CMD_PAUSE:
        actionSet(ACTION_MEDIA, HIDMEDIAKEY_PAUSE);
        break;
    case RC_CMD_REW:
        actionSet(ACTION_MEDIA, HIDMEDIAKEY_REWIND);
        break;
    case RC_CMD_FWD:
        actionSet(ACTION_MEDIA, HIDMEDIAKEY_FFD);
        break;
    case RC_CMD_TIMER:
        actionSet(ACTION_TIMER, 0);
        break;
    case RC_CMD_SP_MODE:
        actionSet(ACTION_SP_MODE, 0);
        break;
    default:
        break;
    }
}

static void actionRemapNavigate(void)
{
    Screen screen = screenGet();

    switch (screen) {
    case SCREEN_MENU:
        actionNavigateMenu((RcCmd)action.value);
        break;
    case SCREEN_TEXTEDIT:
        actionNavigateTextEdit((RcCmd)action.value);
        break;
    case SCREEN_TIME:
        if (action.value == RC_CMD_NAV_LEFT || action.value == RC_CMD_CHAN_PREV) {
            actionSet(ACTION_RTC_MODE, -1);
        } else if (action.value == RC_CMD_NAV_RIGHT || action.value == RC_CMD_CHAN_NEXT) {
            actionSet(ACTION_RTC_MODE, +1);
        }
        break;
    default:
        actionNavigateCommon((RcCmd)action.value);
        break;
    }
}

static void actionRemapEncoder(void)
{
    Screen screen = screenGet();

    if (SCREEN_STANDBY == screen)
        return;

    int16_t encCnt = action.value;

    switch (screen) {
    case SCREEN_TIME:
        if (rtcGetMode() == RTC_NOEDIT) {
            actionSet(ACTION_AUDIO_PARAM_CHANGE, encCnt);
        } else {
            actionSet(ACTION_RTC_CHANGE, encCnt);
        }
        break;
    case SCREEN_MENU:
        actionSet(ACTION_MENU_CHANGE, encCnt);
        break;
    case SCREEN_TEXTEDIT:
        actionSet(ACTION_TEXTEDIT_CHANGE, encCnt);
        break;
    default:
        actionSet(ACTION_AUDIO_PARAM_CHANGE, encCnt);
        break;
    }

    if (ACTION_AUDIO_PARAM_CHANGE == action.type) {
        screenSet(SCREEN_AUDIO_PARAM);
        switch (screen) {
        case SCREEN_AUDIO_INPUT:
            action.param.tune = AUDIO_TUNE_GAIN;
            break;
        case SCREEN_SPECTRUM:
            action.param.tune = AUDIO_TUNE_VOLUME;
        default:
            break;
        }
    }
}


static void actionRemapCommon(void)
{
    Screen screen = screenGet();
    AudioProc *aProc = audioGet();

    switch (action.type) {
    case ACTION_STANDBY:
        if (FLAG_SWITCH == action.value) {
            action.value = (SCREEN_STANDBY == screen ? FLAG_OFF : FLAG_ON);
        }
        break;
    case ACTION_OPEN_MENU:
        switch (screen) {
        case SCREEN_TEXTEDIT:
            action.type = ACTION_TEXTEDIT_APPLY;
            break;
        case SCREEN_MENU:
            actionSet(ACTION_NAVIGATE, RC_CMD_NAV_OK);
            break;
        }
        break;
    case ACTION_AUDIO_MUTE:
        if (FLAG_SWITCH == action.value) {
            action.value = !aProc->par.mute;
        }
        break;
    default:
        break;
    }

    if (SCREEN_STANDBY == screen &&
        (ACTION_STANDBY != action.type &&
         ACTION_REMOTE != action.type &&
         ACTION_INIT_RTC != action.type &&
         ACTION_MENU_SELECT != action.type)) {
        actionSet(ACTION_NONE, 0);
    }

    if (SCREEN_MENU == screen &&
        (ACTION_STANDBY != action.type &&
         ACTION_NAVIGATE != action.type &&
         ACTION_MENU_CHANGE != action.type &&
         ACTION_MENU_SELECT != action.type &&
         ACTION_ENCODER != action.type)) {
        actionSet(ACTION_NONE, 0);
    }
}

static void actionDequeue(void)
{
    action.type = qaction.type;
    action.value = qaction.value;

    qaction.type = ACTION_NONE;
    qaction.value = 0;
}

void actionQueue(ActionType type, int16_t value)
{
    qaction.type = type;
    qaction.value = value;
}

void actionUserGet(void)
{
    actionSet(ACTION_NONE, 0);

    actionDequeue();

    if (ACTION_NONE == action.type) {
        actionGetButtons();
    }

    if (ACTION_NONE == action.type) {
        actionGetEncoder();
    }

    if (ACTION_NONE == action.type) {
        actionGetRemote();
    }

    if (ACTION_NONE == action.type) {
        Screen screen = screenGet();

        if (screen == SCREEN_STANDBY && rtcCheckAlarm()) {
            actionSet(ACTION_STANDBY, FLAG_OFF);
        }
    }

    if (ACTION_NONE == action.type) {
        actionGetTimers();
    }

    switch (action.type) {
    case ACTION_BTN_SHORT:
        actionRemapBtnShort();
        break;
    case ACTION_BTN_LONG:
        actionRemapBtnLong();
        break;
    case ACTION_REMOTE:
        actionRemapRemote();
        break;
    default:
        break;
    }

    actionRemapCommon();

    if (ACTION_NAVIGATE == action.type) {
        actionRemapNavigate();
    }

    if (ACTION_ENCODER == action.type) {
        actionRemapEncoder();
    }
}


void actionHandle(bool visible)
{
    Screen screen = screenGet();
    AudioProc *aProc = audioGet();
    InputType inType = aProc->par.inType[aProc->par.input];
    Tuner *tuner = tunerGet();
    int8_t stNum = stationGetNum(tuner->status.freq);

    const Layout *lt = layoutGet();
    Canvas *canvas = canvasGet();
    Spectrum *sp = spGet();

    action.visible = visible;
    action.timeout = 0;

    switch (action.type) {
    case ACTION_POWERUP:
        pinsSetMute(true);
        pinsSetStby(true);

        swTimSet(SW_TIM_STBY_TIMER, SW_TIM_OFF);
        swTimSet(SW_TIM_SILENCE_TIMER, SW_TIM_OFF);
        swTimSet(SW_TIM_INIT_HW, SW_TIM_OFF);
        swTimSet(SW_TIM_INIT_SW, SW_TIM_OFF);

        swTimSet(SW_TIM_RTC_INIT, 500);

        audioReadSettings();
        tunerReadSettings();
        break;
    case ACTION_STANDBY:
        if (action.value == FLAG_OFF) {
            audioReadSettings();
            tunerReadSettings();

            pinsSetStby(false);     // ON via relay
            swTimSet(SW_TIM_INIT_HW, 500);

            actionSetScreen(SCREEN_TIME, 800);
        } else {
            screenSaveSettings();

            audioSetMute(true);
            audioSetPower(false);

            tunerSetMute(true);
            tunerSetPower(false);

            pinsDeInitAmpI2c();

            pinsSetStby(true);      // OFF via relay

            swTimSet(SW_TIM_STBY_TIMER, SW_TIM_OFF);
            swTimSet(SW_TIM_SILENCE_TIMER, SW_TIM_OFF);
            swTimSet(SW_TIM_INIT_HW, SW_TIM_OFF);
            swTimSet(SW_TIM_INIT_SW, SW_TIM_OFF);

            actionDispExpired(SCREEN_STANDBY);
        }
        break;
    case ACTION_INIT_HW:
        swTimSet(SW_TIM_INIT_HW, SW_TIM_OFF);

        pinsInitAmpI2c();
        pinsSetStby(false);

        tunerInit();
        audioInit();

        swTimSet(SW_TIM_TUNER_POLL, 400);
        swTimSet(SW_TIM_INIT_SW, 300);
        break;
    case ACTION_INIT_RTC:
        rtcInit();
        break;
    case ACTION_INIT_SW:
        swTimSet(SW_TIM_INIT_SW, SW_TIM_OFF);

        tunerSetPower(true);
        tunerSetVolume(tuner->par.volume);
        tunerSetMute(false);
        tunerSetFreq(tuner->par.freq);

        audioSetPower(true);
        actionResetSilenceTimer();
        break;
    case ACTION_DISP_EXPIRED:
        actionDispExpired(screen);
        break;
    case ACTION_DIGIT:
        if (screen == SCREEN_TIME) {
            rtcEditTime(rtcGetMode(), (int8_t)(action.value));
            actionSetScreen(SCREEN_TIME, 5000);
        }
        break;

    case ACTION_MEDIA:
        switch (inType) {
        case IN_PC:
            usbHidSendMediaKey((HidKey)action.value);
            break;
        }
        break;
    case ACTION_CHAN:
        switch (inType) {
        case IN_TUNER:
            if (action.value > 0) {
                tunerMove(TUNER_DIR_UP);
            } else if (action.value < 0) {
                tunerMove(TUNER_DIR_DOWN);
            }
            actionSetScreen(SCREEN_TUNER, 5000);
            break;
        case IN_PC:
            if (action.value > 0) {
                usbHidSendMediaKey(HIDMEDIAKEY_NEXT_TRACK);
            } else if (action.value < 0) {
                usbHidSendMediaKey(HIDMEDIAKEY_PREV_TRACK);
            }
            break;
        }
        break;

    case ACTION_OPEN_MENU:
        if (screen == SCREEN_AUDIO_PARAM) {
            actionNextAudioParam(aProc);
        } else {
            action.param.tune = AUDIO_TUNE_VOLUME;
        }
        actionSetScreen(SCREEN_AUDIO_PARAM, 5000);
        break;

    case ACTION_RTC_MODE:
        if (screen == SCREEN_TIME) {
            rtcChangeMode((int8_t)action.value);
            actionSetScreen(SCREEN_TIME, 15000);
        } else {
            rtcSetMode(RTC_NOEDIT);
            actionSetScreen(SCREEN_TIME, 5000);
        }
        break;
    case ACTION_RTC_CHANGE:
        rtcChangeTime(rtcGetMode(), (int8_t)(action.value));
        actionSetScreen(screen, 5000);
        break;
    case ACTION_RTC_SET_HOUR:
    case ACTION_RTC_SET_MIN:
    case ACTION_RTC_SET_SEC:
    case ACTION_RTC_SET_DATE:
    case ACTION_RTC_SET_MONTH:
    case ACTION_RTC_SET_YEAR:
        rtcSetTime((RtcMode)(action.type - ACTION_RTC_SET_HOUR), (int8_t)(action.value));
        actionSetScreen(screen, 5000);
        break;

    case ACTION_AUDIO_INPUT:
        if (screen == SCREEN_AUDIO_INPUT) {
            actionNextAudioInput(aProc);
            audioSetInput(action.param.input);
        } else {
            action.param.input = aProc->par.input;
        }
        actionSetScreen(SCREEN_AUDIO_INPUT, 5000);
        break;
    case ACTION_AUDIO_PARAM_CHANGE:
        audioChangeTune(action.param.tune, (int8_t)(action.value));
        actionSetScreen(SCREEN_AUDIO_PARAM, 5000);
        break;

    case ACTION_AUDIO_MUTE:
        audioSetMute(action.value);
        // TODO: handle screen
        break;

    case ACTION_TUNER_EDIT_NAME:
        glcdSetFont(lt->textEdit.editFont);
        texteditSet(stationGetName(stNum), STATION_NAME_MAX_LEN, STATION_NAME_MAX_SYM);
        action.prevScreen = SCREEN_TUNER;
        actionSetScreen(SCREEN_TEXTEDIT, 10000);
        break;
    case ACTION_TUNER_DEL_STATION:
        stationRemove(tuner->status.freq);
        actionSetScreen(action.prevScreen, 2000);
        break;

    case ACTION_TEXTEDIT_CHANGE:
        texteditChange((int8_t)action.value);
        actionSetScreen(SCREEN_TEXTEDIT, 10000);
        break;
    case ACTION_TEXTEDIT_ADD_CHAR:
        texteditAddChar();
        actionSetScreen(SCREEN_TEXTEDIT, 10000);
        break;
    case ACTION_TEXTEDIT_DEL_CHAR:
        texteditDelChar();
        actionSetScreen(SCREEN_TEXTEDIT, 10000);
        break;
    case ACTION_TEXTEDIT_APPLY:
        stationStore(tuner->status.freq, canvas->te.str);
        actionSetScreen(action.prevScreen, 2000);
        break;
    case ACTION_TEXTEDIT_CANCEL:
        actionSetScreen(action.prevScreen, 2000);
        break;

    case ACTION_MENU_SELECT:
        menuSetActive((MenuIdx)action.value);
        action.param.parent = menuGet()->parent;
        actionSetScreen(SCREEN_MENU, 10000);
        break;
    case ACTION_MENU_CHANGE:
        menuChange((int8_t)action.value);
        action.param.parent = menuGet()->parent;
        actionSetScreen(SCREEN_MENU, 10000);
        break;

    case ACTION_TIMER:
        if (screen == SCREEN_STBY_TIMER) {
            stbyTimerChange();
        }
        actionSetScreen(SCREEN_STBY_TIMER, 5000);
        break;
    case ACTION_SP_MODE:
        if (screen == SCREEN_SPECTRUM) {
            spModeChange(sp);
        }
        actionSetScreen(SCREEN_SPECTRUM, 3000);
        break;
    default:
        break;
    }

    // Reset silence timer on any user action
    if (action.type != ACTION_NONE && action.type != ACTION_DISP_EXPIRED) {
        actionResetSilenceTimer();
    }

    // Reset silence timer on signal
    if (screen != SCREEN_STANDBY) {
        Spectrum *spectrum = spGet();
        if (spectrum->data[SP_CHAN_LEFT].max > 128 ||
            spectrum->data[SP_CHAN_RIGHT].max > 128) {
            actionResetSilenceTimer();
        }
    }

    if (action.visible) {
        screenSet(action.screen);
        screenSetParam(action.param);
        if (action.timeout > 0) {
            swTimSet(SW_TIM_DISPLAY, action.timeout);
        }
    }
}
