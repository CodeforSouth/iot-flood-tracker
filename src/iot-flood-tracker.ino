// This #include statement was automatically added by the Particle IDE.
#include <HC_SR04.h>

#define QUIP "oodles and oodles"

#define SAMPLE_RATE_MILLIS (5 * 60 * 1000) // how often program should sample
#define REPORT_RATE_SEC (15 * 60)
#define REPORT_RATE_MILLIS (REPORT_RATE_SEC * 1000) // how often program should report if delta is with in REPORT_DELTA_CM
#define REPORT_DELTA_CM 1.0 // if the difference between a sample taken to the previous one is greater then this value program should report the sample

#define SAMPLE_COUNT 5
#define SAMPLE_PAUSE_MILLIS 5*1000

#define SLEEP_ROUTINE_MILLIS 5*1000

#define RECONNECT_SPIN_MILLIS 1000

double last_reported_sample = -3.0;
double delta = 0.0; // the difference between last sample and then one before that

unsigned long lastReportTime = 0; // marker for when the last report was taken

int trigPin = D4;
int echoPin = D5;

SYSTEM_MODE(SEMI_AUTOMATIC);

HC_SR04 rangefinder = HC_SR04(trigPin, echoPin);
FuelGauge battery;

int compare_ints(const void* a, const void* b)
{
    double arg1 = *(const double*)a;
    double arg2 = *(const double*)b;
 
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

double median_sample() {
    double samples[SAMPLE_COUNT];
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        samples[i] = rangefinder.getDistanceCM();
        Particle.process();
        delay(SAMPLE_PAUSE_MILLIS);
    }

    qsort(samples, SAMPLE_COUNT, sizeof(double), compare_ints);

    return samples[SAMPLE_COUNT/2];
}

void setup()
{
    Serial.begin(9600);
    pinMode(D7, OUTPUT);
    Particle.variable("cm", &last_reported_sample, DOUBLE);
    Particle.connect();
    Particle.publish("spark/floodtracker-quip", QUIP);
    Serial.println(QUIP);
}

void publish(double sample, unsigned long timestamp) {
    Serial.printf("%.2fcm\tat %d\n", sample, timestamp);
    Particle.publish("level_mm", String::format("%d", (int)(sample * 10.0)), PUBLIC | NO_ACK);
}

void loop()
{
    Particle.process();
    // take a sample
    double current_sample = median_sample();
    
    unsigned long now = millis();
    
    Serial.printf("%.2fcm\tat %d\treport in %ds\n", 
                  current_sample,
                  now,
                  (REPORT_RATE_MILLIS - (now - lastReportTime)) / 1000);
    
    // calc and set new delta
    delta = abs(last_reported_sample - current_sample);
    // get time since program started 
    
    bool been_a_while = ((now - lastReportTime) >= REPORT_RATE_MILLIS);
    bool big_change = (delta > REPORT_DELTA_CM);
    
    // publish if REPORT_RATE_MILLIS has passed or delta is bigger then REPORT_DELTA_CM
    if( been_a_while || big_change ) {
        publish(current_sample, now);
        Particle.publish("spark/battery", String::format("%f", battery.getSoC()));
        Serial.printf("published\n");
        lastReportTime = now;

    }
    if (big_change) {
        last_reported_sample = current_sample;
    }
    
    blinkLed();
    if (been_a_while) {
        Particle.process();
        delay(SLEEP_ROUTINE_MILLIS);
        Particle.process();
        System.sleep(SLEEP_MODE_DEEP, REPORT_RATE_SEC);
    } else {
        delay(SAMPLE_RATE_MILLIS);    
    }
}

void blinkLed() {
    digitalWrite(D7,HIGH);
    delay(150);   
    digitalWrite(D7,LOW);    
}
