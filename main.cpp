#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_DotStar.h>
#include "GameStrip.h"
#include "globals.cpp"
#include "scoreboard.h"

using namespace std;

void setup()
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
    
    // init buttons on Digital Pins 2, 4, 6, 8, and 10
    for (Arduino::byte i = 2; i < 11; i += 2)
    {
        pinMode(i, INPUT_PULLUP);
    }
    
    // dotstar for the board init
    Adafruit_DotStar* rawStrips[NUMSTRIPS] = {
        &Adafruit_DotStar(NUMPIXELS, 37, 36, DOTSTAR_BGR), //0
        &Adafruit_DotStar(NUMPIXELS, 41, 40, DOTSTAR_BGR), //1
        &Adafruit_DotStar(NUMPIXELS, 45, 44, DOTSTAR_BGR), //2
        &Adafruit_DotStar(NUMPIXELS, 49, 48, DOTSTAR_BGR), //3
        &Adafruit_DotStar(NUMPIXELS, 53, 52, DOTSTAR_BGR)  //4
    };
}

int main()
{
    // to initialize a button do pinMode(ButtonPin, INPUT_PULLUP)
    // unpushed is HIGH, pressed is LOW
    
    
    // might as well use this to setup the things
    setup();
    
    // dotstar scoreboard
    Adafruit_DotStar score = Adafruit_DotStar(14, 49, 48, DOTSTAR_BGR);

    Scoreboard scoreboard = Scoreboard(&score); 
    
    //GameStrip array of pointers to each strip also tracks position
    GameStrip* board[NUMSTRIPS] = {
        &GameStrip(rawStrips[0]),
        &GameStrip(rawStrips[1]),
        &GameStrip(rawStrips[2]),
        &GameStrip(rawStrips[3]),
        &GameStrip(rawStrips[4])
    };
    
    
    // main game loop
    // might want to work on how we space our ticks. maybe track time instead of raw delays
    while (true) {
        int tickCount = 0;

        // move the bombs
        // adjust movement speed by dividing the desired millis by TICKLENGTH
        // i.e. move every 1/4 sec = 250 millis. so, 250/TICKLENGTH
        if (tickCount % (250/TICKLENGTH) == 0) {
            for (Arduino::byte i = 0; i < NUMSTRIPS; i++)
            {
                board[i]->moveBomb();
            }
        }

        // check for bombs at ends
        for(Arduino::byte i = 0; i < NUMSTRIPS; i++)
        {
            Aruino::Byte endcheck = board[i]->isEnd();
            
            // break out if isEnd() returned 0
            if(!endcheck)
                break;
            
            if(endcheck == -1) // left
            {
                scoreboard.loseLife(false);
            }
            if(endcheck == 1) // right
            {
                scoreboard.loseLife(true);
            }
            
            board->resetBomb();
        }
        
        /* IMPLEMENTED ABOVE
        if(gamestrip.isEnd() == -1) // left
        {
            scoreboard.loseLife(false);
            gamestrip.resetBomb();
        }
        if(gamestrip.isEnd() == 1) //right
        {
            scoreboard.loseLife(true);
            gamestrip.resetBomb(); 
        }
        scoreboard.update();
         */

        if(scoreboard.rightDead())
        {
            break;
        }
        if(scoreboard.leftDead())
        {
            break;
        }

        // code that will compile lel
        if (digitalRead(2) == LOW) {
            board[0].setDirection(true);
        }
        
        if (digitalRead(4) == LOW) {
            board[0].setDirection(false);
        }
            
        delay(TICKLENGTH);
        tickCount = (tickCount + 1) % (1000/TICKLENGTH);
    }
    
    return 0;
}
