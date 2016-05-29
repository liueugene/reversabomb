#include "GameStrip.h"
#include <SPI.h>
#include <Adafruit_DotStar.h>

GameStrip::GameStrip(Adafruit_DotStar *strip)
: m_strip(strip), m_position(9), m_direction(rand() % 2)
{
    m_select[0] = false;
    m_select[1] = false;
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
        m_strip->setPixelColor(m_position - 1, 0x0000FF);
        m_position--;
        
    } else {
        m_strip->setPixelColor(m_position, 0);
        m_strip->setPixelColor(m_position + 1, 0xFF0000);
        m_position++;
        
    }
}

void GameStrip::show()
{
    m_strip->show();
}

void GameStrip::setDirection(int playerNum)
{
    if(playerNum) {
        m_direction = true;
        m_strip->setPixelColor(m_position, 0x0000FF);
    } else {
        m_direction = false;
        m_strip->setPixelColor(m_position, 0xFF0000);
    }
}

int GameStrip::isEnd()
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
    m_position = 9; 
}

void GameStrip::selectStrip(bool select, int playerNum)
{
    int pixelNum = (playerNum == 1) ? 18 : 0;

    if(select){
        m_strip->setPixelColor(pixelNum, 0x00FF00);
        m_select[playerNum] = true;
    }
    else{
        m_strip->setPixelColor(pixelNum, 0x000000); 
        m_select[playerNum] = false;
    }


}

bool GameStrip::get_dir()
{
    return m_direction; 
}

bool GameStrip::isSelected(int playerNum)
{
    return m_select[playerNum]; 
}