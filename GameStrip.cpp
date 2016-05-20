#include "GameStrip.h"
#include <SPI.h>
#include <Adafruit_DotStar.h>

GameStrip::GameStrip(Adafruit_DotStar *strip)
: m_strip(strip), m_position(10), m_direction(rand() % 2)
{
    m_strip->begin();
    m_strip->clear();
    m_strip->show();
}

void GameStrip::moveBomb()
{
    if ((m_position == 1 && m_direction) || (m_position == 17 && !m_direction))
        return;
    
    if (m_direction) {//    R iGhT//
        m_strip->setPixelColor(m_position, 0);
        m_strip->setPixelColor(m_position--, 0x0000FF);
        
    } else {
        m_strip->setPixelColor(m_position, 0);
        m_strip->setPixelColor(m_position++, 0xFF0000);
        
    }
    m_strip->show();
}

void GameStrip::setDirection(bool right)
{
    m_direction = right;
}

Arduino::byte GameStrip::isEnd()
{
    if(m_position == 1 && m_direction)
    {
        return 1; 
    }
    else if(m_position == 17 && !m_direction)
    {
        return -1; 
    }
    else{
        return 0; 
    }
}

void GameStrip::resetBomb()
{
    m_direction = !m_direction; 
    m_strip->setPixelColor(m_position, 0); 
    m_position = 10;
}