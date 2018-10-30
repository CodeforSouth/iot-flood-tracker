// This #include statement was automatically added by the Particle IDE.
#include <HC_SR04.h>

/* defines */
#define SAMPLE_RATE_MILLIS (15 * 1000) // how often program should sample
#define REPORT_RATE_MILLIS (60 * 60 * 1000) // how often program should report if delta is with in REPORT_DELTA_CM
#define REPORT_DELTA_CM 1.0 // if the difference between a sample taken to the previous one is greater then this value program should report the sample

double last_reported_sample = -2.0;
double delta = 0.0; // the difference between last sample and then one before that

unsigned long lastReportTime = 0; // marker for when the last report was taken

int trigPin = D4;
int echoPin = D5;

SYSTEM_MODE(SEMI_AUTOMATIC);

HC_SR04 rangefinder = HC_SR04(trigPin, echoPin);

void setup()
{
    Serial.begin(9600);
    pinMode(D7, OUTPUT);
    Particle.variable("cm", &last_reported_sample, DOUBLE);
    Particle.connect();
}

void publish(double sample, unsigned long timestamp) {
    char publish_buffer[sizeof(sample)];
    double* publish_buffer_ptr = (double*)(void*) &publish_buffer;
    *publish_buffer_ptr = sample;
    Serial.printf("%.2fcm\tat %d\n", sample, timestamp);
    Particle.publish("level_cm", (char*)&publish_buffer, NO_ACK);
}

void loop()
{
    // take a sample
    double current_sample = rangefinder.getDistanceCM();
    // calc and set new delta
    delta = abs(last_reported_sample - current_sample);
    // get time since program started 
    unsigned long now = millis();
    
    // publish if REPORT_RATE_MILLIS has passed or delta is bigger then REPORT_DELTA_CM
    if( ((now - lastReportTime) >= REPORT_RATE_MILLIS) || (delta > REPORT_DELTA_CM) ) {
        publish(last_reported_sample, now);
        lastReportTime = now;
    }
    if (delta > REPORT_DELTA_CM) {
        last_reported_sample = current_sample;
    }
    
    blinkLed();
    delay(SAMPLE_RATE_MILLIS);    
}

void blinkLed() {
    digitalWrite(D7,HIGH);
    delay(150);   
    digitalWrite(D7,LOW);    
}
