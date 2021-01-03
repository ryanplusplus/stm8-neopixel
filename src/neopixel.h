/*!
 * @file
 * @brief
 */

#ifndef neopixel_h
#define neopixel_h

#include <stdint.h>

void neopixel_write(const uint8_t* data, uint16_t count);
void neopixel_reset(void);

#endif
