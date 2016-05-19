#ifndef __gamestrip_h__
#define __gamestrip_h__

class Adafruit_DotStar;

class GameStrip
{
public:
    GameStrip(Adafruit_DotStar *strip);
    void moveBomb();
    void setDirection(bool right);
    int isEnd(); 
    void resetBomb();
private:
    Adafruit_DotStar *m_strip;
    bool m_direction; //0 left, 1 right
    int m_start;
    int m_end;
    int m_position;
};


#endif /* __gamestrip_h__ */