//
//  timer.c
//  PeerPong
//
//  Created by Matheus Barella Ronfim on 4/11/16.
//  Copyright © 2016 Matheus Barella Ronfim. All rights reserved.
//

#include "timer.h"

Timer* newTimer()
{
    Timer* timer = (Timer *)malloc(sizeof(Timer));
    
    timer->isStarted = 0;
    timer->isPaused = 0;
    timer->startTicks = 0;
    timer->pausedTicks = 0;
    
    return timer;
}


void destroyTimer(Timer** timer)
{
    free(*timer);
    *timer = NULL;
}


void startTimer(Timer* timer)
{
    // start the timer
    timer->isStarted = 1;
    
    // unpause the timer
    timer->isPaused = 0;
    
    // get the current clock time
    timer->startTicks = SDL_GetTicks();
    timer->pausedTicks = 0;
}


void stopTimer(Timer* timer)
{
    // stop the timer
    timer->isStarted = 0;
    
    // unpause the timer
    timer->isPaused = 0;
    
    // clear tick variables
    timer->startTicks = 0;
    timer->pausedTicks = 0;
}


void pauseTimer(Timer* timer)
{
    // if the timer is running and isn't already paused
    if (timer->isStarted && !timer->isPaused)
    {
        // Pause the timer
        timer->isPaused = 1;
        
        // calculate the paused ticks
        timer->pausedTicks = SDL_GetTicks() - timer->startTicks;
        timer->startTicks = 0;
    }
}


void unpauseTimer(Timer* timer)
{
    // if the timer is running and paused
    if (timer->isStarted && timer->isPaused)
    {
        // unpause the timer
        timer->isPaused = 0;
        
        // reset the starting ticks
        timer->startTicks = SDL_GetTicks() - timer->pausedTicks;
        
        // reset the paused ticks
        timer->pausedTicks = 0;
    }
}

Uint32 getTimerTicks(Timer* timer)
{
    // The actual timer time
    Uint32 time = 0;
    
    // if the timer is running
    if (timer->isStarted)
    {
        // if the timer is paused
        if (timer->isPaused)
        {
            // return the number of ticks when the timer was paused
            time = timer->pausedTicks;
        }
        else
        {
            // return the current time minus the start time
            time = SDL_GetTicks() - timer->startTicks;
        }
    }
    
    return time;
}

int randint(int n) {
    if ((n - 1) == RAND_MAX) {
        return rand();
    } else {
        // Chop off all of the values that would cause skew...
        long end = RAND_MAX / n; // truncate skew
        assert (end > 0L);
        end *= n;
        
        // ... and ignore results from rand() that fall above that limit.
        // (Worst case the loop condition should succeed 50% of the time,
        // so we can expect to bail out of this loop pretty quickly.)
        int r;
        while ((r = rand()) >= end);
        
        return r % n;
    }
}
