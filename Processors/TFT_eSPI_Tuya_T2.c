        ////////////////////////////////////////////////////
        //       TFT_eSPI generic driver functions        //
        ////////////////////////////////////////////////////
#include "SPI.h"

////////////////////////////////////////////////////////////////////////////////////////
// Global variables
////////////////////////////////////////////////////////////////////////////////////////

// Select the SPI port to use
  SPIClassTuyaOpen& spi = SPI;

#if defined (TFT_SDA_READ) && !defined (TFT_PARALLEL_8_BIT)
// TODO: Not supported
#endif

/***************************************************************************************
** Function name:           read byte  - supports class functions
** Description:             Parallel bus only - dummy function - not used
***************************************************************************************/
uint8_t TFT_eSPI::readByte(void)
{
  uint8_t b = 0xAA;
  return b;
}

#if defined (TFT_PARALLEL_8_BIT)
// TODO: Not supported
#elif defined (SPI_18BIT_DRIVER)
// TODO:
#else  // Standard SPI 16-bit colour TFT
void TFT_eSPI::pushBlock(uint16_t color, uint32_t len){
  while ( len-- ) {tft_Write_16(color);}
  return;
}
void TFT_eSPI::pushPixels(const void* data_in, uint32_t len) {
  uint16_t *data = (uint16_t*)data_in;

  if (_swapBytes) while ( len-- ) {tft_Write_16(*data); data++;}
  else while ( len-- ) {tft_Write_16S(*data); data++;}
  return;
}
#endif
