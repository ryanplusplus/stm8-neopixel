/*!
 * @file
 * @brief
 */

#include <stdbool.h>
#include <stddef.h>
#include "interrupts.h"
#include "clock.h"
#include "tim4_system_tick.h"
#include "tiny_timer.h"
#include "watchdog.h"
#include "neopixel_pa2.h"
#include "pb5_heartbeat.h"
#include "tiny_utils.h"

static tiny_timer_group_t timer_group;
static tiny_timer_t timer;

static void kick_watchdog(tiny_timer_group_t* timer_group, void* context)
{
  (void)timer_group;
  (void)context;
  watchdog_kick();
}

static const neopixel_pa2_color_t leds[] = {
  { .r = 0x01, .g = 0x01, .b = 0x00 },
  { .r = 0x00, .g = 0x01, .b = 0x01 },
  { .r = 0x01, .g = 0x00, .b = 0x01 },

  { .r = 0x01, .g = 0x00, .b = 0x00 },
  { .r = 0x00, .g = 0x01, .b = 0x00 },
  { .r = 0x00, .g = 0x00, .b = 0x01 },

  { .r = 0x00, .g = 0x00, .b = 0x00 },
  { .r = 0x01, .g = 0x01, .b = 0x01 },
};

void main(void)
{
  interrupts_disable();
  {
    watchdog_init();
    clock_init();
    tiny_timer_group_init(&timer_group, tim4_system_tick_init());
    pb5_heartbeat_init(&timer_group);
  }
  interrupts_enable();

  neopixel_pa2_init();

  tiny_timer_start_periodic(&timer_group, &timer, 10, kick_watchdog, NULL);

  while(true) {
    tiny_timer_group_run(&timer_group);
    neopixel_pa2_write(leds, element_count(leds));
    wfi();
  }
}
