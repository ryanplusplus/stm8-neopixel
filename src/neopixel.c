/*!
 * @file
 * @brief
 */

#include "neopixel.h"

static void send_byte(uint8_t byte)
{
  (void)byte;

  // clang-format off
  __asm
    disable_interrupts$:
      ld    a, #0
      jrnm  save_interrupt_state$
      ld    a, #1
    save_interrupt_state$:
      push  a
      sim

    send_byte$:
      ld    a, (0x04, sp)   ; a <- byte
      ldw   y, #8           ; y <- 8

    send_bit$:
      bset  0x5014, #7
      sll   a               ; roll left, setting carry if msb(a) == 1
      jrc   send_1$         ; if carry not set

    send_0$:
      nop
      nop
      nop
      nop
      bres  0x5014, #7
      nop
      nop
      nop
      nop
      nop
      nop
      nop
      nop
      nop
      decw  y
      jrne  send_bit$
      jra   done$

    send_1$:
      nop
      nop
      nop
      nop
      nop
      nop
      nop
      nop
      nop
      bres  0x5014, #7
      nop
      nop
      decw  y
      jrne  send_bit$

    done$:
    restore_interrupt_state$:
      pop a
      tnz a
      jreq exit$
      rim

    exit$:
  __endasm;
  // clang-format on
}

void neopixel_write(const uint8_t* data, uint16_t count)
{
  for(uint16_t i = 0; i < count; i++) {
    send_byte(data[i]);
  }
}

void neopixel_reset(void)
{
  // clang-format off
  __asm
    reset_neopixel$:
      ldw   y, #400

    loop$:
      decw  y
      jrne  loop$
  __endasm;
  // clang-format on
}
