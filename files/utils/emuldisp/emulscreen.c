#include "emulscreen.h"

#include <stdlib.h>
#include <time.h>

#include "../../../canvas/layout.h"
#include "../../../display/dispdefs.h"
#include "../../../eemul.h"
#include "../../../menu.h"
#include "../../../rc.h"
#include "../../../spectrum.h"


static Spectrum spectrum;
static RcData rcData;
static DispDriver drv;

void emulDrawPixel(int16_t x, int16_t y, uint16_t color);
void emulDrawRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

void dispdrvInit(DispDriver **driver)
{
    drv.width = EMUL_DISP_WIDTH;
    drv.height = EMUL_DISP_HEIGHT;
    drv.drawPixel = emulDrawPixel;
    drv.drawRectangle = emulDrawRectangle;

    *driver = &drv;
}

const Layout *ltEmulGet(void)
{
    const Layout *lt;

#if EMUL_DISP_WIDTH == 160 && EMUL_DISP_HEIGHT == 128
    lt = lt160x128Get();
#elif EMUL_DISP_WIDTH == 176 && EMUL_DISP_HEIGHT == 132
    lt = lt176x132Get();
#elif EMUL_DISP_WIDTH == 220 && EMUL_DISP_HEIGHT == 176
    lt = lt220x176Get();
#elif EMUL_DISP_WIDTH == 320 && EMUL_DISP_HEIGHT == 240
    lt = lt320x240Get();
#elif EMUL_DISP_WIDTH == 400 && EMUL_DISP_HEIGHT == 240
    lt = lt400x240Get();
#elif EMUL_DISP_WIDTH == 480 && EMUL_DISP_HEIGHT == 320
    lt = lt480x320Get();
#else
#error "No such layout"
#endif

    return lt;
}

uint16_t eeReadU(EE_Param param, uint16_t def)
{
    switch (param) {
    default:
        return def;
    }
}

int16_t eeReadI(EE_Param param, int16_t def)
{
    switch (param) {
    case EE_AUDIO_IN0:
        return 1;
    case EE_AUDIO_PARAM_VOLUME:
        return -30;
    default:
        return def;
    }
}

bool eeReadB(EE_Param param, bool def)
{
    switch (param) {
    default:
        return def;
    }
}

void eeUpdate(EE_Param param, int16_t data)
{
    (void)param;
    (void)data;
}

void inputSetEncRes(int8_t value)
{
    (void)value;
}

uint16_t rcGetCode(RcCmd cmd)
{
    (void)cmd;
    return 0;
}

void rcSaveCode(uint16_t cmd, uint16_t value)
{
    (void)cmd, (void)value;
}

RcData rcRead(bool clear)
{
    (void)clear;
    return rcData;
}

void dispdrvSetBrightness(int8_t value)
{
    (void) value;
}

void rtcGetTime(RTC_type *rtc)
{
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);

    rtc->hour = (int8_t)lt->tm_hour;
    rtc->min = (int8_t)lt->tm_min;
    rtc->sec = (int8_t)lt->tm_sec;

    rtc->date = (int8_t)lt->tm_mday;
    rtc->month = (int8_t)lt->tm_mon;
    rtc->year = (int8_t)lt->tm_year - 100;

    rtc->wday = (int8_t)lt->tm_wday;
}

int8_t rtcGetMode(void)
{
    return RTC_HOUR;
}

Spectrum *spGet(void)
{
    return &spectrum;
}

void spGetADC(uint8_t *dataL, uint8_t *dataR)
{
    srand((unsigned int)time(NULL));

    for (uint8_t i = 0; i < SPECTRUM_SIZE; i++) {
        dataL[i] = rand() & 0xFF;
        dataR[i] = rand() & 0xFF;
    }
}


void swTimSetTunerPoll(int16_t value)
{
    (void) value;
}
int16_t swTimGetTunerPoll(void)
{
    return 0;
}

void swTimSetSpConvert(int16_t value)
{
    (void) value;
}
int16_t swTimGetSpConvert(void)
{
    return 0;
}
