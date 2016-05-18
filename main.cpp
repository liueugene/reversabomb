#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_DotStar.h>
#include "GameStrip.h"
#include "globals.cpp"
#include "scoreboard.h"
using namespace std;

const int NUMPIXELS = 26;
const int TICKLENGTH = 25;
int tickCount = 0;

void init()
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
}

int main()
{
	Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, 20, 21, DOTSTAR_BGR);
    Adafruit_DotStar scoreboard = Adafruit_DotStar(14, 15, 16, DOTSTAR_BGR);
    pinMode(2, INPUT_PULLUP);
    pinMode(4, INPUT_PULLUP);
    
    GameStrip gamestrip = GameStrip(&strip);
    scoreboard scoreboard = scoreboard(&scoreboard);
    strip.begin();
    strip.clear();
    //strip.setBrightness(0);
    strip.show();
        
        //bool dir = false;
        // random note: might want to look in to button debouncing, if needed
        // Buttons will now be pulled HIGH when not pushed and LOW when active because it's easier
        // to initialize a button do pinMode(ButtonPin, INPUT_PULLUP)
    while (true) {
            
        if (tickCount % 10 == 0) {
            gamestrip.moveBomb();
        }
            
        if (digitalRead(2) == LOW) {
            gamestrip.setDirection(true);
        }
        
        if (digitalRead(4) == LOW) {
            gamestrip.setDirection(false);
        }
        if (scoreboard.leftDead() || scoreboard.rightDead() )
        {
            for(int i = 0; i < NUMPIXELS; i++)
            {
                strip.setPixelColor(i, 0xffffff);
            }
            strip.show();
        }
            
        delay(TICKLENGTH);
        tickCount = (tickCount + 1) % (1000/TICKLENGTH);
    }
    return;
}