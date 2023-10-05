#ifndef HC_SR04_h
#define HC_SR04_h

class HC_SR04_sensor
{
public:
    HC_SR04_sensor(int trig, int echo);  // Constructor to initialize pins
    int readDistance(); // Read the distance
private:
    int trigPin; // Trigger pin
    int echoPin; // Echo pin
    long soundDuration; // Duration of sound wave travel
    int soundDistance;  // Distance measurement
};

#endif