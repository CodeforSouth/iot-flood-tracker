#include "HC_SR04.h"

double cm = 0.0;
double inches = 0.0;

int trigPin = D4;
int echoPin = D5;

/*
Connect an HC-SR04 Range finder as follows:
Spark   HC-SR04
GND     GND
5V      VCC
D4      Trig
D5      Voltage divider output - see below

Echo --|
       >
       < 470 ohm resistor
       >
       ------ D5 on Spark
       >
       < 470 ohm resistor
       >
GND ---|

Test it using curl like this:
curl https://api.spark.io/v1/devices/<deviceid>/cm?access_token=<accesstoken>

The default usable rangefinder is 10cm to 250cm. Outside of that range -1 is returned as the distance.

You can change this range by supplying two extra parameters to the constructor of minCM and maxCM, like this:

HC_SR04 rangefinder = HC_SR04(trigPin, echoPin, 5.0, 300.0);

*/

HC_SR04 rangefinder = HC_SR04(trigPin, echoPin);

void setup() 
{
    Spark.variable("cm", &cm, DOUBLE);
    Spark.variable("inches", &inches, DOUBLE);
}

void loop() 
{
    cm = rangefinder.getDistanceCM();
    inches = rangefinder.getDistanceInch();
    delay(100);
}

