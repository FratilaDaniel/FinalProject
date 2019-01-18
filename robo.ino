#include <Servo.h>
// Pins of motor 1
#define mpin00 5
#define mpin01 6
// Pins of motor 2
#define mpin10 3
#define mpin11 11
Servo srv;
bool motorsStarted;
int angle;
void setup() {
 // configuration of motor pins as output, initially 0
    digitalWrite(mpin00, 0);
    digitalWrite(mpin01, 0);
    digitalWrite(mpin10, 0);
    digitalWrite(mpin11, 0);
    pinMode (mpin00, OUTPUT);
    pinMode (mpin01, OUTPUT);
    pinMode (mpin10, OUTPUT);
    pinMode (mpin11, OUTPUT);
    motorsStarted = false;
 // LED pin
    pinMode(13, OUTPUT);
  Serial.begin(9600); // implicit serial frame formats
  angle = 90;
}


// Function to control a motor
// Input: pins m1 and m2, direction and speed
void StartMotor (int m1, int m2, int forward, int speed)
{
    if (speed==0) // stop
    {
      digitalWrite(m1, 0);
      digitalWrite(m2, 0);
    }
    else
    {
      if (forward)
      {
        digitalWrite(m2, 0);
        analogWrite (m1, speed); // use PWM
      }
      else
      {
        digitalWrite(m1, 0);
        analogWrite(m2, speed);
      }
    }
    motorsStarted = true;
}

// Safety function
// Commands motors to stop, then delays
void delayStopped(int ms)
{
    StartMotor (mpin00, mpin01, 0, 0);
    StartMotor (mpin10, mpin11, 0, 0);
    delay(ms);
}


//---- servo specific angle



// Use of servo
// Set three angles
// When finished, the servo remains in the middle (90 degrees)
void playWithServo(int pin)
{
       
        angle = Serial.read();
     
    srv.attach(pin);
    srv.write(angle);//(int)angle
    Serial.println(angle);
    delay(1000);
    srv.write(90);
    delay(1000);
    srv.detach();
}


void loop() {  
//// Start the servo motor
if (Serial.available()) {
    playWithServo(8);
}
// Now start the DC motors

    StartMotor (mpin00, mpin01, 1, 128);
    StartMotor (mpin10, mpin11, 1, 128);
    delay (500); // How long the motors are on
    delayStopped(500); // How long the motors are off
//    
//    StartMotor (mpin00, mpin01, 1, 50);
//    StartMotor (mpin10, mpin11, 1, 50);
    
//    delay (500);
//    delayStopped(500);
//    StartMotor (mpin00, mpin01, 0, 128);
//    StartMotor (mpin10, mpin11, 1, 128);
//    
//    delay (500);
//    delayStopped(500);
//    
//    StartMotor (mpin00, mpin01, 1, 128);
//    StartMotor (mpin10, mpin11, 0, 128);
//    
//    delay (500);
//    delayStopped(500);
     
}





