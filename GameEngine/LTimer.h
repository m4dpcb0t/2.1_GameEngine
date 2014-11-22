#ifndef LTIMER_H
#define LTIMER_H

#include <stdint.h>
#include <SDL.h>
//The application time based timer
class LTimer
{
    public:
        LTimer();
        virtual ~LTimer();

        //The various clock actions
        void start();
        void stop();
        void pause();
        void unpause();
        uint32_t g;
        //Gets the timer's time
        uint32_t getTicks();

        //Checks the status of the timer
        bool isStarted();
        bool isPaused();

    private:
        //The clock time when the timer started
        uint32_t m_StartTicks;

        //The ticks stored when the timer was paused
        uint32_t m_pauseTicks;

        //The timer status
        bool m_Paused;
        bool m_Started;
};

#endif // LTIMER_H
