#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_DotStar.h>
#include "GameStrip.h"

using namespace std;

const int NUMPIXELS = 26;

int tickCount = 0;

int main()
{
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

	Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, 20, 21, DOTSTAR_BGR);
        pinMode(2, INPUT);
        pinMode(4, INPUT);
        
        GameStrip gamestrip = GameStrip(&strip);
        
        strip.begin();
        strip.clear();
        //strip.setBrightness(0);
        strip.show();
        
        //bool dir = false;
        
        while (true) {
            
            if (tickCount % 10 == 0) {
                gamestrip.moveBomb();
            }
            
            if (digitalRead(2) == HIGH) {
                gamestrip.setDirection(true);
            }
            
            if (digitalRead(4) == HIGH) {
                gamestrip.setDirection(false);
            }
            delay(25);
            
            tickCount = (tickCount + 1) % 40;
        }
        strip.clear();
        
}