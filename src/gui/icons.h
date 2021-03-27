#ifndef ICONS_H
#define ICONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "fonts.h"

typedef uint8_t Icon;
enum {
    ICON_EMPTY = 0x00,

    // Various icons
    ICON_RDS,
    ICON_STEREO,
    ICON_FMONO,

    ICON_REPEAT = 0x10,
    ICON_RANDOM,
    ICON_SINGLE,
    ICON_CONSUME,

    // Audio tune icons
    ICON_VOLUME = 0x20,
    ICON_BASS,
    ICON_MIDDLE,
    ICON_TREBLE,
    ICON_BALANCE,
    ICON_FRONTREAR,
    ICON_CENTER,
    ICON_SUBWOOFER,
    ICON_PREAMP,
    ICON_LOUDNESS,

    // Input icons
    ICON_TUNER = 0x40,
    ICON_PC,
    ICON_TV,
    ICON_BLUETOOTH,
    ICON_DVD,
    ICON_USB,
    ICON_MICROPHONE,
    ICON_GUITAR,
    ICON_TURNTABLES,
    ICON_SDCARD,
    ICON_PROJECTOR,
    ICON_SATELLITE,
    ICON_MPD,
    ICON_KARADIO,

    // On/off icons
    ICON_MUTE_ON = 0x60,
    ICON_MUTE_OFF,
    ICON_LOUDNESS_ON,
    ICON_LOUDNESS_OFF,
    ICON_SURROUND_ON,
    ICON_SURROUND_OFF,
    ICON_EFFECT_3D_ON,
    ICON_EFFECT_3D_OFF,
    ICON_TONE_BYPASS_ON,
    ICON_TONE_BYPASS_OFF,

    // Media keys
    ICON_PREV_TRACK = 0x80,
    ICON_NEXT_TRACK,
    ICON_STOP,
    ICON_PLAY_PAUSE,
    ICON_REWIND,
    ICON_FFWD,
};

extern const tFont iconsamp24;
extern const tFont iconsamp32;
extern const tFont iconsamp48;
extern const tFont iconsamp64;

#ifdef __cplusplus
}
#endif

#endif // ICONS_H
