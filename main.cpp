#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_DotStar.h>
#include "GameStrip.h"
#include "globals.cpp"
#include "scoreboard.h"

using namespace std;

const int NUMPIXELS = 19;
const int TICKLENGTH = 25;
int tickCount = 0;

int main()
{
        // might as well use this to setup the things
    //initialize timer registers
    cli();
    TCCR0A = B00000011;
    TCCR0B = B00000011;
    TIMSK0 = B00000001;
    TCCR1A = B10100001;
    TCCR1B = B00000011;
    TCCR2A = B00000001;
    TCCR2B = B00000100;
    TIMSK1 = B00000000;
    sei();

	Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, 45, 44, DOTSTAR_BGR);
    Adafruit_DotStar strip2 = Adafruit_DotStar(NUMPIXELS, 53, 52, DOTSTAR_BGR);
    Adafruit_DotStar score = Adafruit_DotStar(14, 49, 48, DOTSTAR_BGR);

    pinMode(2, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    
    strip2.begin();
    strip2.clear();
    strip2.show();

    Scoreboard scoreboard = Scoreboard(&score); 
    GameStrip gamestrip = GameStrip(&strip);
        
    strip2.setPixelColor(5, 0xFF0000); 
    strip2.show();
        //bool dir = false;
        // random note: might want to look in to button debouncing, if needed
        // Buttons will now be pulled HIGH when not pushed and LOW when active because it's easier
        // to initialize a button do pinMode(ButtonPin, INPUT_PULLUP)
    
    while (true) {


        if (tickCount % 10 == 0) {
            gamestrip.moveBomb();
        }

        if(gamestrip.isEnd() == -1) // left
        {
            scoreboard.loseLife(0); 
            gamestrip.resetBomb();
        }
        if(gamestrip.isEnd() == 1) //right
        {
            scoreboard.loseLife(1); 
            gamestrip.resetBomb(); 
        }
        scoreboard.update();

        if(scoreboard.rightDead())
        {
            break;
        }
        if(scoreboard.leftDead())
        {
            break;
        }

        if (digitalRead(2) == LOW) {
            gamestrip.setDirection(true);
        }
        
        if (digitalRead(4) == LOW) {
            gamestrip.setDirection(false);
        }
            
        delay(TICKLENGTH);
        tickCount = (tickCount + 1) % (1000/TICKLENGTH);
    }
    return 0;
}
