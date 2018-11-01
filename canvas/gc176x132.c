#include "canvas.h"

// On 176x132 we can draw max 5 menu items + menu header
#define MENU_SIZE_VISIBLE   7

static void showTime(bool clear, RTC_type *rtc);
static void showParam(DispParam *dp);
static void showSpectrum(bool clear, SpectrumData *spData);
static void showTuner(DispTuner *dt);
static void showMenu(void);

static const CanvasParam canvasParam;

static Canvas canvas = {
    .width = 176,
    .height = 132,
    .showTime = showTime,
    .showParam = showParam,
    .showSpectrum = showSpectrum,
    .showTuner = showTuner,
    .showMenu = showMenu,

    .par = &canvasParam,
};

static const CanvasParam canvasParam = {
    .time.hmsFont = &fontterminusdig42,
    .time.dmyFont = &fontterminusdig30,
    .time.wdFont = &fontterminus28,
    .time.hmsY = 8,
    .time.dmyY = 58,
    .time.wdY = 96,

    .bar.sc = 88,
    .bar.sw = 1,
    .bar.pos = 36,
    .bar.half = 6,
    .bar.middle = 2,

    .menu.headFont = &fontterminus16b,
    .menu.menuFont = &fontterminus12,
};

void gc176x132Init(Canvas **value)
{
    *value = &canvas;
    menuGet()->dispSize = MENU_SIZE_VISIBLE;
}

static void showTime(bool clear, RTC_type *rtc)
{
    canvasShowTime(clear, rtc);
}

static void showParam(DispParam *dp)
{
    glcdSetFont(&fontterminus24b);
    glcdSetFontColor(LCD_COLOR_WHITE);

    glcdSetXY(0, 0);
    glcdWriteString((char *)dp->label);

    canvasDrawBar(dp->value, dp->min, dp->max);

    glcdSetXY(canvas.width, 80);
    glcdSetFontAlign(FONT_ALIGN_RIGHT);
    glcdSetFont(&fontterminusdig40);
    glcdWriteNum((dp->value * dp->step) / 8, 3, ' ', 10);
}

static void showSpectrum(bool clear, SpectrumData *spData)
{
    const uint8_t step = 2;     // Step in pixels between spectrum columns
    const uint8_t oft = 0;      // Offset of spectrum column inside step

    const uint8_t width = 1;    // Width of spectrum column

    canvasShowSpectrum(clear, spData, step, oft, width);
}

static void showTuner(DispTuner *dt)
{
    const tFont *fmFont = &fontterminus32;

    canvasShowTuner(dt, fmFont);
}

static void showMenu(void)
{
    canvasShowMenu();
}
