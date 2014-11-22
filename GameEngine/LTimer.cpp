#include "LTimer.h"

LTimer::LTimer()
{
    //ctor
    m_StartTicks = 0;
    m_pauseTicks = 0;

    m_Paused = false;
    m_Started = false;
}

LTimer::~LTimer()
{
    //dtor
}

void LTimer::start()
{
    //Start the timer
    m_Started = true;

    //Unpause the timer
    m_Paused = false;

    //Gets the current clock time
    m_StartTicks = SDL_GetTicks();
    m_pauseTicks = 0;
}

void LTimer::stop()
{
    //Stop the timer
    m_Started = false;

    //Unpause the timer
    m_Paused = false;

    //Clear tick variables
    m_StartTicks = 0;
    m_pauseTicks = 0;
}

void LTimer::pause()
{
    //If the timer is running and isn't already paused
    if(m_Started && !m_Paused)
    {
        //Pause the timer
        m_Paused = true;

        //Calculate the paused ticks
        m_pauseTicks = SDL_GetTicks() - m_StartTicks;
        m_StartTicks = 0;
    }
}

void LTimer::unpause()
{
    //If the timer is running and paused
    if( m_Started && m_Paused)
    {
        //Unpause the timer
        m_Paused = false;

        //Reset the starting ticks
        m_StartTicks = SDL_GetTicks() - m_pauseTicks;

        //Reset the paused ticks
        m_pauseTicks = 0;

    }

}

uint32_t LTimer::getTicks()
{
    //The actual timer time
    uint32_t time = 0;

    //If the timer is running
    if(m_Started)
    {
        //If the timer is paused
        if(m_Paused)
        {
            //Return the number of ticks when the timer was paused
            time = m_pauseTicks;
        }
        else
        {
            //Return the current time minus the start time
            time = SDL_GetTicks() - m_StartTicks;
        }
    }

    return time;
}
