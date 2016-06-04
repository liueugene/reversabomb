//
//  scoreboard.cpp
//  
//
//  Created by Josh Camarena on 5/17/16.
//
//

#include "scoreboard.h"
#include <SPI.h>
#include <Adafruit_DotStar.h>
#include "globals.cpp"

Scoreboard::Scoreboard(Adafruit_DotStar *strip)
: m_strip(strip), m_leftLife(7), m_rightLife(7), m_rightBegin(7), m_rightEnd(15), m_leftBegin(0), m_leftEnd(7), m_update(true)
{
	m_strip->begin();
	m_strip->clear();
	m_strip->setBrightness(50);
    this->update();
}

void Scoreboard::loseLife(bool TEAM) //0 left, 1 right
{
    if(TEAM)
        m_leftLife--;
    
    else
        m_rightLife--;
 
    m_update = true;
    
    return;
}


void Scoreboard::update()
{
    if (!m_update)
        return;
    
    for (int i = 0; i < MAXLIVES; i++)
    {
        if (i < m_rightLife)
            m_strip->setPixelColor(i + m_rightBegin, 0x0000FF);
        else
            m_strip->setPixelColor(i + m_rightBegin, 0);
        
        if (i < m_leftLife)
            m_strip->setPixelColor(i + m_leftBegin, 0xFF0000);
        else
            m_strip->setPixelColor(i + m_leftBegin, 0);
    }
    m_update = false;
    m_strip->show(); 
    return;
}

bool Scoreboard::rightDead()
{
    return m_rightLife < 1;
}

bool Scoreboard::leftDead()
{
    return m_leftLife < 1;
}