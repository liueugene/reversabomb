//
//  scoreboard.cpp
//  
//
//  Created by Josh Camarena on 5/17/16.
//
//

#include "scoreboard.hpp"
#include <SPI.h>
#include <Adafruit_DotStar.h>

scoreboard::scoreboard(Adafruit_DotStar *strip)
: m_strip(strip), m_leftLife(7), m_rightLife(7), m_rightBegin(7), m_rightEnd(15), m_leftBegin(0), m_leftEnd(7), update(true)
{
    this->update();
}

void scoreboard::loseLife(bool TEAM) //0 left, 1 right
{
    if(TEAM)
        m_rightLife--;
    
    else
        m_leftLife--;
 
    m_update = true;
    
    return;
}


void scoreboard::update()
{
    if (!m_update)
        return;
    
    for (int i = 0; i < MAXLIVES; i++)
    {
        if (i < m_rightLife)
            strip->setPixelColor(i + m_rightBegin, 0x0000FF);
        else
            strip->setPixelColor(i + m_rightBegin, 0);
        
        if (i < m_leftLife)
            strip->setPixelColor(i + m_leftBegin, 0xFF0000);
        else
            strip->setPixelColor(i + m_leftBegin, 0);
    }
    m_update = false;
    return;
}

bool scoreboard::rightDead()
{
    return m_rightLife < 1;
}

bool scoreboard::leftDead()
{
    return m_leftLife < 1;
}