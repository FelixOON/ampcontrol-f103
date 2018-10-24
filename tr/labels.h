#ifndef TR_H
#define TR_H

#include "../menu.h"

#include "../tuner/tuner.h"
#include "../audio/audio.h"

typedef enum {
    LANG_BY,
    LANG_RU,

    LANG_END
} Lang;

typedef enum {
    LABEL_SUNDAY,
    LABEL_MONDAY,
    LABEL_TUESDAY,
    LABEL_WEDNESDAY,
    LABEL_THURSDAY,
    LABEL_FRIDAY,
    LABEL_SATURDAY,

    LABEL_BRIGNTNESS,

    LABEL_VOLUME,
    LABEL_BASS,
    LABEL_MIDDLE,
    LABEL_TREBLE,
    LABEL_FRONTREAR,
    LABEL_BALANCE,
    LABEL_CENTER,
    LABEL_SUBWOOFER,
    LABEL_PREAMP,

    LABEL_BOOL_OFF,
    LABEL_BOOL_ON,

    LABEL_TUNER_IC,
    LABEL_TUNER_END = LABEL_TUNER_IC + (TUNER_IC_END - TUNER_IC_NO),

    LABEL_AUDIO_IC = LABEL_TUNER_END,
    LABEL_AUDIO_IC_END = LABEL_AUDIO_IC + (AUDIO_IC_END - AUDIO_IC_NO),

    LABEL_GAIN0 = LABEL_AUDIO_IC_END,
    LABEL_GAIN1,
    LABEL_GAIN2,
    LABEL_GAIN3,
    LABEL_GAIN4,
    LABEL_GAIN5,
    LABEL_GAIN6,
    LABEL_GAIN7,

    // Menu
    LABEL_MENU,
    LABEL_MENU_END = LABEL_MENU + (MENU_END - MENU_NULL),

    LABEL_END = LABEL_MENU_END,
} Label;

void labelsSetLang(Lang value);
const char **labelsGet(void);

void labelsInit(void);

#endif // TR_H
