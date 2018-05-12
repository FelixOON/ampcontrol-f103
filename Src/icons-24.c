#include "icons.h"

const uint8_t icons_24[] = {
    // Volume
    0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE,
    0xFF, 0xFF, 0x00, 0x00, 0x60, 0xE6, 0xCE, 0x9C, 0x38, 0xF0, 0xE0, 0x80,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x00, 0x66, 0x7E, 0x3C, 0x81, 0xFF, 0x7E, 0x00, 0xFF, 0xFF,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x07, 0x0F, 0x1F, 0x3F, 0x7F,
    0xFF, 0xFF, 0x00, 0x00, 0x06, 0x67, 0x73, 0x39, 0x1C, 0x0F, 0x07, 0x01,
    // Bass
    0xF0, 0x18, 0x0C, 0x04, 0x06, 0x02, 0x02, 0x83, 0xC1, 0xC1, 0xC1, 0xC1,
    0x61, 0x61, 0x31, 0x31, 0x1B, 0x1A, 0x0C, 0x0C, 0x06, 0x06, 0x1B, 0xF3,
    0xFF, 0x03, 0xF6, 0xE4, 0xEC, 0x08, 0x08, 0xD9, 0xD3, 0xD3, 0xD1, 0x10,
    0x10, 0xD0, 0xD0, 0xD0, 0xD8, 0x08, 0x08, 0xE8, 0xE4, 0xF6, 0x03, 0xFF,
    0x0F, 0x18, 0x33, 0x27, 0x6F, 0x40, 0x40, 0xDF, 0x9F, 0xBF, 0xBF, 0x80,
    0x80, 0xBF, 0xBF, 0x9F, 0xDF, 0x40, 0x40, 0x6F, 0x27, 0x33, 0x18, 0x0F,
    // Middle
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80,
    0xC3, 0xEC, 0xF0, 0xE0, 0x60, 0xE0, 0xF0, 0x3A, 0x1D, 0x0E, 0x17, 0x0B,
    0xE0, 0xF0, 0xF8, 0xFC, 0xFC, 0xB8, 0xB8, 0xDC, 0xEC, 0xFD, 0xFF, 0x7F,
    0xF7, 0xFB, 0x3D, 0x7E, 0x3F, 0x0F, 0x37, 0xC0, 0x00, 0x00, 0x00, 0x00,
    0x0F, 0x3F, 0x5F, 0x6F, 0xF3, 0xF1, 0xF9, 0xFF, 0xFF, 0xF9, 0xFE, 0x7F,
    0x3F, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1C, 0x38, 0x00,
    // Treble
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x7F, 0xFF, 0xFF, 0xFF,
    0xF6, 0xF6, 0xEC, 0x6C, 0xD8, 0xB0, 0x60, 0xC0, 0x80, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x87,
    0x8F, 0xDF, 0xFE, 0x40, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xF0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0xFE, 0xFE, 0x03, 0x03, 0x01,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00,
    // Preamp
    0xE0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xB0, 0xD0, 0xF8,
    0xF8, 0xF8, 0x58, 0xE8, 0xFC, 0xFC, 0xFE, 0xFE, 0x7F, 0x7F, 0xBE, 0x80,
    0x3F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x6A, 0x5F, 0xFF,
    0xFF, 0xFF, 0xD5, 0xBF, 0xFF, 0xFF, 0xFD, 0xFA, 0xF7, 0xF7, 0xEF, 0x0F,
    0x00, 0x00, 0x00, 0x03, 0x0F, 0x3F, 0xFF, 0xFC, 0xF0, 0xC0, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x07, 0x07, 0x03, 0x00,
    // Frontrear
    0x10, 0x10, 0x30, 0x30, 0x70, 0x70, 0xF4, 0xF2, 0xF2, 0xF1, 0xF5, 0xF5,
    0xF5, 0xF5, 0xF1, 0xF2, 0xF2, 0xF4, 0x70, 0x70, 0x30, 0x30, 0x10, 0x10,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE7, 0xE7, 0xE7, 0xE7,
    0xE7, 0xE7, 0xE7, 0xE7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x08, 0x0C, 0x0C, 0x0E, 0x0E, 0x2F, 0x4F, 0x4F, 0x8F, 0xAF, 0xAF,
    0xAF, 0xAF, 0x8F, 0x4F, 0x4F, 0x2F, 0x0E, 0x0E, 0x0C, 0x0C, 0x08, 0x08,
    // Balance
    0x00, 0x00, 0x00, 0x00, 0x60, 0xF0, 0x78, 0x38, 0x1C, 0x1C, 0x8C, 0xFF,
    0xFF, 0x8C, 0x1C, 0x1C, 0x38, 0x78, 0xF0, 0x60, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x60, 0x18, 0x06, 0x01, 0x06, 0x18, 0x60, 0x80, 0x03, 0x03,
    0x03, 0x03, 0x80, 0x60, 0x18, 0x06, 0x01, 0x06, 0x18, 0x60, 0x80, 0x00,
    0x1E, 0x3D, 0x64, 0x4C, 0xDC, 0xDC, 0xFC, 0x7C, 0x7C, 0x3D, 0x1E, 0x00,
    0x00, 0x1E, 0x3D, 0x64, 0x4C, 0xDC, 0xDC, 0xFC, 0x7C, 0x7C, 0x3D, 0x1E,
    // Center
    0x80, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xF0, 0xF0, 0xFE, 0xFE, 0xFE, 0xFE,
    0xFE, 0xFE, 0xFE, 0xFE, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x12, 0x14, 0x24, 0x28, 0x2A, 0x2A,
    0x2A, 0x2A, 0x28, 0x24, 0x14, 0x12, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // Subwoofer
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF,
    0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xF0, 0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0,
    0x00, 0x00, 0x0C, 0x1C, 0x38, 0x72, 0x66, 0xEE, 0xCC, 0xD8, 0xD8, 0xD8,
    0xD8, 0xD8, 0xD8, 0xCC, 0xEE, 0x66, 0x72, 0x38, 0x1C, 0x0C, 0x00, 0x00,

    // Tuner
    0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 0x83, 0x83, 0x86, 0x86, 0x8C,
    0x8C, 0x98, 0x98, 0xB0, 0xB0, 0xE0, 0xE0, 0xC0, 0x80, 0x80, 0x80, 0x00,
    0xFF, 0x1F, 0xA7, 0xAB, 0xA9, 0xA9, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA9,
    0xA9, 0xAB, 0xA7, 0x1F, 0xFF, 0xFF, 0xFF, 0xE7, 0xDB, 0xDB, 0xE7, 0xFF,
    0x7F, 0xFC, 0xF2, 0xEA, 0xCA, 0xCA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xCA,
    0xCA, 0xEA, 0xF2, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xCC, 0xCC, 0xFF, 0x7F,
    // PC
    0xFF, 0x01, 0xFD, 0xCD, 0xE5, 0xF5, 0xF5, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD,
    0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0xFD, 0x01, 0xFF,
    0x7F, 0x40, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0xDF, 0xDF, 0xDF, 0xDF,
    0xDF, 0xDF, 0xDF, 0xDF, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x40, 0x7F,
    0xF8, 0xDC, 0x8C, 0xDC, 0xFC, 0xDC, 0x8C, 0xDE, 0xFF, 0xFF, 0xFF, 0x8F,
    0xAF, 0xAF, 0xAF, 0xAF, 0xAE, 0xAC, 0xAC, 0xAC, 0xAC, 0x8C, 0xFC, 0xF8,
    // TV
    0x00, 0x00, 0x00, 0x03, 0x07, 0x0E, 0x1C, 0x38, 0x70, 0xE0, 0xC0, 0x80,
    0x80, 0xC0, 0xE0, 0x70, 0x38, 0x1C, 0x0E, 0x07, 0x03, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0x07, 0x73, 0x1B, 0x0B, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0xFF, 0xFF, 0x93, 0x93, 0xFF,
    0xFF, 0xFF, 0xE0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
    0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    // Bluetooth
    0x00, 0x18, 0x04, 0x62, 0x11, 0x09, 0x04, 0x64, 0xE0, 0xC0, 0x80, 0x00,
    0x00, 0xFF, 0xFF, 0x07, 0x0E, 0x9C, 0xF8, 0xF0, 0x60, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0xC3, 0xE7,
    0x7E, 0xFF, 0xFF, 0x7E, 0xE7, 0xC3, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x18, 0x20, 0x46, 0x88, 0x90, 0x20, 0x26, 0x07, 0x03, 0x01, 0x00,
    0x00, 0xFF, 0xFF, 0xE0, 0x70, 0x39, 0x1F, 0x0F, 0x06, 0x00, 0x00, 0x00,
    // DVD
    0x00, 0xC0, 0xF0, 0xF8, 0xFC, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0x7F, 0x7F,
    0x7F, 0x7F, 0xFF, 0x9F, 0x06, 0x06, 0x0C, 0x1C, 0x38, 0xF0, 0xC0, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0xC3, 0xBD, 0x7E, 0xE7, 0xC3,
    0xC3, 0xE7, 0x7E, 0xBD, 0xC3, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x00, 0x03, 0x0F, 0x1C, 0x38, 0x30, 0x60, 0x60, 0xF9, 0xFF, 0xFE, 0xFE,
    0xFE, 0xFE, 0xFF, 0xFF, 0x7F, 0x7F, 0x3F, 0x3F, 0x1F, 0x0F, 0x03, 0x00,

    // USB
    0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0x30, 0x1C, 0xFF,
    0xFF, 0x1C, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x19, 0x30, 0x60, 0xC0, 0xFF,
    0xFF, 0x00, 0x00, 0x80, 0xCE, 0x7E, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0xFF,
    0xFF, 0xF6, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // CH5.1
    0x06, 0x3F, 0x1F, 0x0E, 0x06, 0x82, 0x80, 0x80, 0x88, 0x8C, 0x8F, 0x0F,
    0x0F, 0x0F, 0x0C, 0x08, 0x80, 0x80, 0x02, 0x06, 0x0E, 0x1F, 0x3F, 0x06,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x6F, 0xEF, 0xCD, 0xCD, 0xFD, 0x79, 0x00,
    0xC0, 0xC0, 0x00, 0xC3, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x60, 0xFC, 0xF8, 0x70, 0x60, 0x40, 0x08, 0x18, 0x38, 0xF8, 0xF8, 0xF8,
    0xF8, 0xF8, 0xF8, 0x38, 0x18, 0x08, 0x40, 0x60, 0x70, 0xF8, 0xFC, 0x60,
    // Guitar
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0x40, 0x00,
    0x00, 0x00, 0x00, 0x80, 0xC0, 0x60, 0x30, 0x1C, 0x0E, 0x0F, 0x03, 0x01,
    0xC0, 0xE0, 0xE0, 0xE0, 0xF0, 0xF0, 0xFC, 0xFE, 0xEF, 0xDF, 0xB8, 0xFC,
    0xFC, 0xDE, 0xC3, 0x41, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x07, 0x0F, 0x1F, 0x3E, 0x3D, 0xFB, 0x7F, 0x1F, 0x07, 0x03, 0x01,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // Turntables
    0xFC, 0xFE, 0x07, 0x13, 0x3B, 0x3B, 0x63, 0xC3, 0x83, 0xC3, 0xE3, 0x63,
    0x33, 0x33, 0x33, 0x33, 0x63, 0xE3, 0xC3, 0x03, 0x03, 0x07, 0xFE, 0xFC,
    0xFF, 0xFF, 0x00, 0x10, 0xFC, 0xFC, 0x10, 0x00, 0x0F, 0x3F, 0x76, 0x6C,
    0xC8, 0xC6, 0xC6, 0xC0, 0x60, 0x70, 0x3F, 0x0F, 0x00, 0x00, 0xFF, 0xFF,
    0x3F, 0x7F, 0xE0, 0xC0, 0xCC, 0xCC, 0xC0, 0xC0, 0xCC, 0xCC, 0xC0, 0xC0,
    0xCC, 0xCC, 0xC0, 0xC0, 0xC0, 0xC0, 0xCC, 0xCC, 0xC0, 0xE0, 0x7F, 0x3F,
    // Microphone
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xD0,
    0x98, 0x3C, 0x7C, 0xF6, 0xFE, 0xF6, 0xEC, 0xFC, 0xF8, 0xF0, 0xE0, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFB, 0xF7,
    0xEF, 0x5F, 0x3E, 0x3C, 0x39, 0x33, 0x07, 0x1F, 0x1F, 0x0F, 0x07, 0x03,
    0x70, 0xF8, 0xFC, 0xFE, 0xFF, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // Projector
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xC0,
    0xC0, 0xE0, 0xE0, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x80, 0x80,
    0xFF, 0xFF, 0xAB, 0xFF, 0xAB, 0xFF, 0xAB, 0xFF, 0xAB, 0xFF, 0xFF, 0xC7,
    0x39, 0x7D, 0xE6, 0xFA, 0xFE, 0x7D, 0x39, 0xC7, 0xFF, 0xFF, 0x3E, 0xFF,
    0x03, 0x03, 0x0F, 0x0F, 0x0F, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x06, 0x06, 0x06, 0x07, 0x07, 0x0F, 0x0F, 0x0F, 0x03, 0x03,
    // Cassette
    0xE0, 0xF0, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
    0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0xF0, 0xE0,
    0xFF, 0xFF, 0x00, 0x00, 0x0E, 0x1B, 0x11, 0x91, 0x9B, 0x9F, 0x9F, 0x9F,
    0x99, 0x99, 0x9F, 0x9B, 0x91, 0x11, 0x1B, 0x0E, 0x00, 0x00, 0xFF, 0xFF,
    0x07, 0x0F, 0x0F, 0x0F, 0x03, 0x0C, 0x0F, 0x0B, 0x0F, 0x0D, 0x0F, 0x0F,
    0x0F, 0x0F, 0x0D, 0x0F, 0x0B, 0x0F, 0x0C, 0x03, 0x0F, 0x0F, 0x0F, 0x07,
    // Mixer
    0xF0, 0xF8, 0x38, 0xF8, 0xF8, 0x38, 0xF8, 0xF8, 0x38, 0xF8, 0xF8, 0x38,
    0xF8, 0xF8, 0x38, 0xF8, 0xF8, 0x38, 0xF8, 0xF8, 0xB8, 0xB8, 0xF8, 0xF0,
    0xFF, 0xFE, 0x00, 0xFE, 0xFB, 0x00, 0xFB, 0xFF, 0x00, 0xFF, 0xDF, 0x00,
    0xDF, 0xFD, 0x00, 0xFD, 0x7F, 0x00, 0x7F, 0xFF, 0xEA, 0xEA, 0xFF, 0xFF,
    0x0F, 0x1F, 0x1C, 0x1F, 0x1F, 0x1C, 0x1F, 0x1E, 0x1C, 0x1E, 0x1F, 0x1C,
    0x1F, 0x1F, 0x1C, 0x1F, 0x1F, 0x1C, 0x1F, 0x1F, 0x1C, 0x1C, 0x1F, 0x0F,
    // Satellite
    0x3E, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 0x20, 0x20, 0xE0,
    0x00, 0x03, 0x1F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0,
    0xE0, 0xC0, 0x80, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
    0x00, 0x00, 0x80, 0xC0, 0xE1, 0xFF, 0xF7, 0xEF, 0xCF, 0x9F, 0x1F, 0x3F,
    0x3F, 0x3F, 0x7F, 0x7F, 0x7E, 0x7C, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0xFF,

    // Brightness
    0x00, 0x00, 0x00, 0x18, 0x38, 0x30, 0x80, 0xC0, 0xC0, 0xE0, 0x60, 0x6F,
    0x6F, 0x60, 0xE0, 0xC0, 0xC0, 0x80, 0x30, 0x38, 0x18, 0x00, 0x00, 0x00,
    0x18, 0x18, 0x18, 0x18, 0x00, 0x7E, 0xFF, 0xC3, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xC3, 0xFF, 0x7E, 0x00, 0x18, 0x18, 0x18, 0x18,
    0x00, 0x00, 0x00, 0x18, 0x1C, 0x0C, 0x01, 0x03, 0x03, 0x07, 0x06, 0xF6,
    0xF6, 0x06, 0x07, 0x03, 0x03, 0x01, 0x0C, 0x1C, 0x18, 0x00, 0x00, 0x00,
    // Threshold
    0x00, 0x60, 0xFE, 0xFE, 0x60, 0x00, 0x0C, 0x12, 0x12, 0x0C, 0x00, 0x00,
    0x00, 0xFE, 0xAB, 0xC3, 0xC3, 0x03, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0F, 0x1F, 0x38, 0x30, 0x38, 0x1C, 0x0C, 0x00, 0x00, 0xC0,
    0xE0, 0x7F, 0x2A, 0xFF, 0xFF, 0x00, 0x7F, 0xE0, 0xC0, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x3F,
    0x70, 0x66, 0xCF, 0xDF, 0xDF, 0xCF, 0x66, 0x70, 0x3F, 0x0F, 0x00, 0x00,
};
