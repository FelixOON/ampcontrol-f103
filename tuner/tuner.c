#include "tuner.h"

#include "../eemul.h"

static Tuner tuner;

static void tunerReadSettings(void)
{
    uint16_t eeData;

    eeData = eeRead(EE_TUNER_IC);
    tuner.ic = (eeData == EE_EMPTY ? TUNER_IC_RDA5807 : eeData);

    eeData = eeRead(EE_TUNER_FREQ);
    tuner.freq = (eeData == EE_EMPTY ? 9950 : eeData);

    eeData = eeRead(EE_TUNER_FLAG);
    tuner.flag = (eeData == EE_EMPTY ? TUNER_FLAG_INIT : eeData);

    tuner.freqMin = 8700;
    tuner.freqMax = 10800;
    tuner.ic = TUNER_IC_RDA5807;
}

static void tunerSaveSettings(void)
{
    eeUpdate(EE_TUNER_FREQ, tuner.freq);
    eeUpdate(EE_TUNER_FLAG, tuner.flag);
}

void tunerInit()
{
    tunerReadSettings();

    switch (tuner.ic) {
#ifdef _RDA580X
    case TUNER_IC_RDA5807:
        tuner.setFreq = rda580xSetFreq;
        rda580xInit();
        break;
#endif
#ifdef _SI470X
    case TUNER_IC_SI4703:
        si470xInit();
        break;
#endif
    default:
        break;
    }
}

Tuner *tunerGet()
{
    return &tuner;
}

void tunerPowerOn(void)
{

}

void tunerPowerOff(void)
{
    tunerSaveSettings();
}

void tunerSetFreq(uint16_t value)
{
    if (value < tuner.freqMin)
        value = tuner.freqMin;
    else if (value > tuner.freqMax)
        value = tuner.freqMax;

    tuner.freq = value;

    if (tuner.setFreq) {
        tuner.setFreq(value);
    }
}

void tunerSetFlag(TunerFlag flag, uint8_t value)
{
    if (value)
        tuner.flag |= flag;
    else
        tuner.flag &= ~flag;

    if (tuner.setFlag) {
        tuner.setFlag();
    }
}

void tunerNextStation(int8_t direction)
{
    tunerSetFreq(tuner.freq + 10 * direction);
}
