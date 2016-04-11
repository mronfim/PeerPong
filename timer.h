//
//  timer.h
//  PeerPong
//
//  Created by Matheus Barella Ronfim on 4/11/16.
//  Copyright © 2016 Matheus Barella Ronfim. All rights reserved.
//

#ifndef timer_h
#define timer_h

#include <stdio.h>
#include "core.h"

typedef struct Timer {
    int isStarted;
    int isPaused;
    Uint32 startTicks;
    Uint32 pausedTicks;
} Timer;

Timer* newTimer();
void destroyTimer(Timer** timer);
void startTimer(Timer* timer);
void stopTimer(Timer* timer);
void pauseTimer(Timer* timer);
void unpauseTimer(Timer* timer);
Uint32 getTimerTicks(Timer* timer);

/* Returns an integer in the range [0, n).
 *
 * Uses rand(), and so is affected-by/affects the same seed.
 */
int randint(int n);

#endif /* timer_h */
