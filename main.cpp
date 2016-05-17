#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_DotStar.h>
using namespace std;

int main()
{
	Adafruit_DotStar strip = Adafruit_DotStar(5, 4, 5, DOTSTAR_BRG);
	Serial.begin(9600);
	Serial.print("asdftest");
}