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

    
    // strip2.begin();
    // strip2.clear();
    // strip2.show();
    //strip2.setPixelColor(5, 0xFF0000);

     //strip2.show();
        //bool dir = false;
        // random note: might want to look in to button debouncing, if needed
        // Buttons will now be pulled HIGH when not pushed and LOW when active because it's easier
        // to initialize a button do pinMode(ButtonPin, INPUT_PULLUP)

    
    //SET UP 

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

    //initialize buttons 
    for(int i = 2; i < 13; i = i + 2)
    {
        pinMode(i, INPUT_PULLUP); 
    } 

    //initialize strips
    Adafruit_DotStar strip2 = Adafruit_DotStar(NUMPIXELS, 44, 45, DOTSTAR_BGR);
    Adafruit_DotStar strip = Adafruit_DotStar(NUMPIXELS, 48, 49, DOTSTAR_BGR);
    Adafruit_DotStar strip3 = Adafruit_DotStar(NUMPIXELS, 40, 41, DOTSTAR_BGR);
    Adafruit_DotStar score = Adafruit_DotStar(14, 52, 53, DOTSTAR_BGR);

    strip.setBrightness(80);
    strip2.setBrightness(80);
    strip3.setBrightness(80);
    score.setBrightness(80);


    //initialize gamestrips
    Scoreboard scoreboard = Scoreboard(&score); 
    GameStrip gamestrips[] = {
        GameStrip(&strip), //middle
        GameStrip(&strip2), //top
        GameStrip(&strip3) //bottom
    };

    //initialize button states
    int cur_selection[2] = {1, 1};
    int prev_state_left[2] = {HIGH, HIGH};
    int prev_state_right[2] = {HIGH, HIGH};
    int prev_state_send[2] = {HIGH, HIGH};

    //initialize player position
    gamestrips[1].selectStrip(true, 0); 
    gamestrips[1].selectStrip(true, 1); 

    //Game
    bool isOver = true; 
    while (isOver) {

        for(int i = 0; i < 3; i++)
        {
            if (tickCount % 50 == 0) {
            gamestrips[i].moveBomb();
            }

            if(gamestrips[i].isEnd() == -1) // left
            {
                scoreboard.loseLife(0); 
                gamestrips[i].resetBomb();
            }
            if(gamestrips[i].isEnd() == 1) //right
            {
                scoreboard.loseLife(1); 
                gamestrips[i].resetBomb(); 
            }
            scoreboard.update();

            gamestrips[i].show();

            if(scoreboard.rightDead())
            {
                isOver = false;
                break;
            }
            if(scoreboard.leftDead())
            {
                isOver = false;
                break;
            }
        }

        for(int p = 0; p < 2; p++){

            int temp1 = digitalRead(2 + p * 6);
            if(temp1 == LOW && temp1 != prev_state_left[p] && cur_selection[p] != 0) // move player left
            {
                gamestrips[cur_selection[p]--].selectStrip(false, p);
                gamestrips[cur_selection[p]].selectStrip(true, p);
            }
            prev_state_left[p] = temp1;


            int temp2 = digitalRead(4 + p * 6); 
            if(temp2 == LOW && temp2 != prev_state_right[p] && cur_selection[p] != 2) // move player right
            {
                gamestrips[cur_selection[p]++].selectStrip(false, p);
                gamestrips[cur_selection[p]].selectStrip(true, p);
            }
            prev_state_right[p] = temp2;

            int temp = digitalRead(6 + p *6); 
            if (temp == LOW && temp != prev_state_send[p] && gamestrips[cur_selection[p]].isSelected(p)) {
                gamestrips[cur_selection[p]].setDirection(p);
            }
            prev_state_send[p] = temp;

        }

        delay(TICKLENGTH);
        tickCount = (tickCount + 1) % (1000/TICKLENGTH);
    }
    return 0;
}
