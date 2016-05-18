//
//  scoreboard.hpp
//  
//
//  Created by Josh Camarena on 5/17/16.
//
//

#ifndef scoreboard_hpp
#define scoreboard_hpp

class Adafruit_DotStar;

class scoreboard
{
public:
    scoreboard(Adafruit_DotStar *strip);
    void loseLife(bool TEAM); //0 left, 1 right
    void update();
    bool rightDead();
    bool leftDead();
    
private:
    Adafruit_DotStar *m_strip;
    int m_rightLife;
    int m_leftLife;
    
    bool m_update;
    
    int m_leftBegin;
    int m_leftEnd;
    int m_rightBegin;
    int m_rightEnd;
};


#endif /* scoreboard_hpp */
