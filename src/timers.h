#ifndef TIMERS_H
#define TIMERS_H

#include <stdint.h>

#define OPCODES_PER_SECOND 600
#define TIMER_HZ 60
#define TIMER_MS (1000 / TIMER_HZ)
#define CYCLE_DELAY_MS (1000 / OPCODES_PER_SECOND)

typedef struct Timers {
  uint8_t dt;
  uint8_t st;
} Timers;

void timers_update(Timers *timers);
void timers_init(Timers *timers);
void timers_reset(Timers *timers);

#endif // TIMERS_H
