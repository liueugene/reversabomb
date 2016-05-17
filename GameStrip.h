class Adafruit_DotStar;

class GameStrip
{
public:
    GameStrip(Adafruit_DotStar *strip);
    void moveBomb();
    void setDirection(bool right);
private:
    Adafruit_DotStar *m_strip;
    bool m_direction; //0 left, 1 right
    int m_start;
    int m_end;
    int m_position;
};
