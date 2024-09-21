        ////////////////////////////////////////////////////
        //       TFT_eSPI generic driver functions        //
        ////////////////////////////////////////////////////

// This is a generic driver for Arduino boards, it supports SPI interface displays
// 8-bit parallel interface to TFT is not supported for generic processors

#ifndef _TFT_eSPI_TUYA_T2_
#define _TFT_eSPI_TUYA_T2_

#include <api/itoa.h>

// Processor ID reported by getSetup()
#define PROCESSOR_ID 0x6602

// Include processor specific header
// None

// Processor specific code used by SPI bus transaction startWrite and endWrite functions
#define SET_BUS_WRITE_MODE // Not used
#define SET_BUS_READ_MODE  // Not used

// Code to check if DMA is busy, used by SPI bus transaction startWrite and endWrite functions
#define DMA_BUSY_CHECK // Not used so leave blank

// To be safe, SUPPORT_TRANSACTIONS is assumed mandatory
#if !defined (SUPPORT_TRANSACTIONS)
  #define SUPPORT_TRANSACTIONS
#endif

// Initialise processor specific SPI functions, used by init()
#define INIT_TFT_DATA_BUS

// If smooth fonts are enabled the filing system may need to be loaded
#ifdef SMOOTH_FONT
  // TODO
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Define the DC (TFT Data/Command or Register Select (RS))pin drive code
////////////////////////////////////////////////////////////////////////////////////////
#ifndef TFT_DC
  #define DC_C // No macro allocated so it generates no code
  #define DC_D // No macro allocated so it generates no code
#else
  #define DC_C digitalWrite(TFT_DC, LOW)
  #define DC_D digitalWrite(TFT_DC, HIGH)
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Define the CS (TFT chip select) pin drive code
////////////////////////////////////////////////////////////////////////////////////////
#ifndef TFT_CS
  #define CS_L // No macro allocated so it generates no code
  #define CS_H // No macro allocated so it generates no code
#else
  #define CS_L digitalWrite(TFT_CS, LOW)
  #define CS_H digitalWrite(TFT_CS, HIGH)
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Make sure TFT_RD is defined if not used to avoid an error message
////////////////////////////////////////////////////////////////////////////////////////
#ifndef TFT_RD
  #define TFT_RD -1
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Define the WR (TFT Write) pin drive code
////////////////////////////////////////////////////////////////////////////////////////
#ifdef TFT_WR
  // TODO:
  // #define WR_L digitalWrite(TFT_WR, LOW)
  // #define WR_H digitalWrite(TFT_WR, HIGH)
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Define the touch screen chip select pin drive code
////////////////////////////////////////////////////////////////////////////////////////
#if !defined TOUCH_CS || (TOUCH_CS < 0)
  #define T_CS_L // No macro allocated so it generates no code
  #define T_CS_H // No macro allocated so it generates no code
#else
  #define T_CS_L digitalWrite(TOUCH_CS, LOW)
  #define T_CS_H digitalWrite(TOUCH_CS, HIGH)
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Make sure TFT_MISO is defined if not used to avoid an error message
////////////////////////////////////////////////////////////////////////////////////////
#ifndef TFT_MISO
  #define TFT_MISO -1
#endif

#if 0
#define tft_Write_8(C)   { uint8_t data = C; spi.transfer(&data, 1);}
#define tft_Write_16(C)           \
{                                 \
  uint8_t tft_Write_16_data[2] = {0};          \
                                  \
  tft_Write_16_data[0] = (uint8_t)(((C)>>8));  \
  tft_Write_16_data[1] = (uint8_t)(C);         \
                                  \
  spi.transfer(tft_Write_16_data, 2);          \
}
// #define tft_Write_16S(C) { uint8_t data[2] = {(uint8_t)((C)>>0), (uint8_t)((C)>>8)}; spi.transfer(data, 2); }
#define tft_Write_16S(C)  \
{
  uint8_t data[2] = {0};

  data[0] = (uint8_t)(((C)>>8));
  data[1] = (uint8_t)(C);

  spi.transfer(data, 2);
}

#define tft_Write_32(C)  { uint8_t data[4] = {(uint8_t)((C)>>24), (uint8_t)((C)>>16), (uint8_t)((C)>>8), (uint8_t)((C)>>0)}; spi.transfer(data, 4); }

#define tft_Write_32C(C,D) \
  { uint8_t data[4] = {(uint8_t)((C)>>8), (uint8_t)((C)>>0), (uint8_t)((D)>>8), (uint8_t)((D)>>0)}; spi.transfer(data, 4); }

#define tft_Write_32D(C) \
  { uint8_t data[4] = {(uint8_t)((C)>>8), (uint8_t)((C)>>0), (uint8_t)((C)>>8), (uint8_t)((C)>>0)}; spi.transfer(data, 4); }

#else
  #define tft_Write_8(C)   spi.send8(C)
  // #define tft_Write_16(C)  spi.send16(C)
  // #define tft_Write_16S(C) spi.send16(((C)>>8) | ((C)<<8))
  #define tft_Write_16(C)  tft_Write_8((uint8_t)((C)>>8));tft_Write_8((uint8_t)((C)>>0))
  #define tft_Write_16S(C) tft_Write_8((uint8_t)((C)>>0));tft_Write_8((uint8_t)((C)>>8))

  #define tft_Write_32(C) \
  tft_Write_16((uint16_t) ((C)>>16)); \
  tft_Write_16((uint16_t) ((C)>>0))

  #define tft_Write_32C(C,D) \
  tft_Write_16((uint16_t) (C)); \
  tft_Write_16((uint16_t) (D))

  #define tft_Write_32D(C) \
  tft_Write_16((uint16_t) (C)); \
  tft_Write_16((uint16_t) (C))
#endif

#ifndef tft_Write_16N
  #define tft_Write_16N tft_Write_16
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Macros to read from display using SPI or software SPI
////////////////////////////////////////////////////////////////////////////////////////
#define tft_Read_8() spi.transfer(0)

#endif // _TFT_eSPI_TUYA_T2_
