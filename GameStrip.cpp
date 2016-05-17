#include "GameStrip.h"
#include <SPI.h>
#include <Adafruit_DotStar.h>

GameStrip::GameStrip(Adafruit_DotStar *strip)
: m_strip(strip), m_position(9), m_direction(true)
{
}

void GameStrip::moveBomb()
{
    if ((m_position == 1 && m_direction) || (m_position == 24 && !m_direction))
        return;
    
    if (m_direction) {//    R iGhT//
        m_strip->setPixelColor(m_position, 0);
        m_strip->setPixelColor(m_position - 1, 0x0000FF);
        m_position--;
        
    } else {
        m_strip->setPixelColor(m_position, 0);
        m_strip->setPixelColor(m_position + 1, 0xFF0000);
        m_position++;
        
    }
    m_strip->show();
}

void GameStrip::setDirection(bool right)
{
    m_direction = right;
}