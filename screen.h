#ifndef SCREEN_H
#define SCREEN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "audio/audio.h"
#include "menu.h"
#include "spectrum.h"
#include "rtc.h"

typedef uint8_t Screen;
enum {
    SCREEN_STANDBY,

    SCREEN_TIME,
    SCREEN_SPECTRUM,

    SCREEN_AUDIO_PARAM,
    SCREEN_AUDIO_INPUT,

    SCREEN_TUNER,

    SCREEN_MENU,

    SCREEN_TEXTEDIT,

    SCREEN_STBY_TIMER,
    SCREEN_SILENCE_TIMER,

    SCREEN_END
};

typedef enum {
    BR_STBY,
    BR_WORK,

    BR_END
} BrMode;

typedef union {
    AudioTune tune;
    uint8_t input;
    MenuIdx parent;
    SpMode spMode;
} ScreenParam;

void screenReadSettings(void);
void screenSaveSettings(void);

void screenInit(void);

void screenSet(Screen value);
Screen screenGet(void);

void screenSetParam(ScreenParam param);

void screenSetDefault(Screen value);
Screen screenGetDefault(void);

int8_t screenGetBrightness(BrMode mode);
void screenSetBrightness(BrMode mode, int8_t value);
void screenChangeBrighness(BrMode mode, int8_t diff);

void screenToClear(void);
void screenShow(bool clear);

#ifdef __cplusplus
}
#endif

#endif // SCREEN_H
