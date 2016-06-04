#ifndef __gamestrip_h__
#define __gamestrip_h__

class Adafruit_DotStar;

class GameStrip
{
public:
    GameStrip(Adafruit_DotStar *strip, bool startDir);
    void moveBomb();
    void show();
    void setDirection(int playerNum);
    int isEnd(); 
    void resetBomb();
    int get_position(); 
    void selectStrip(bool select, int playerNum); 
    bool isSelected(int playerNum); 
    bool get_dir();
private:
    Adafruit_DotStar *m_strip;
    bool m_direction; //0 left, 1 right
    int m_start;
    int m_end;
    int m_position;
    bool m_select[2];
};


#endif /* __gamestrip_h__ */