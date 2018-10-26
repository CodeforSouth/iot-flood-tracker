
/* defines */
#define SAMPLE_RATE_MILLIS 850 // how often program should sample
#define REPORT_RATE_MILLIS 60000 // how often program should report if delta is with in REPORT_DELTA_CM
#define REPORT_DELTA_CM 1.0 // if the difference between a sample taken to the previous one is greater then this value program should report the sample

double cm = 0.0;
double delta = 0.0; // the difference between last sample and then one before that

unsigned long lastReportTime = 0; // marker for when the last report was taken

int trigPin = D4;
int echoPin = D5;


HC_SR04 rangefinder = HC_SR04(trigPin, echoPin);

void setup()
{
    Serial.begin(9600);
    pinMode(D7, OUTPUT);
    Particle.variable("cm", &cm, DOUBLE);
}

void loop()
{
    // take a sample
    double sample = rangefinder.getDistanceCM();
    // calc and set new delta
    delta = abs(sample - cm);
    // set cm to sample
    cm = sample;
    // get time since program started 
    unsigned long now = millis();
    
    // publish if REPORT_RATE_MILLIS has passed or delta is bigger then REPORT_DELTA_CM
    if( (now - lastReportTime) >= REPORT_RATE_MILLIS || delta > REPORT_DELTA_CM ) {
        // print sample to serial
        Serial.printf("Report: %.2f cm\n", cm);
        // set last report time
        lastReportTime = now;
    }
    blinkLed();
    delay(SAMPLE_RATE_MILLIS);    
}

void blinkLed() {
    digitalWrite(D7,HIGH);
    delay(150);   
    digitalWrite(D7,LOW);    
}
