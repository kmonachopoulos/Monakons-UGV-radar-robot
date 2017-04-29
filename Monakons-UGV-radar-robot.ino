/*
-------------------------------------------------------------------------------------------------------------------------------
Technological Educational Institute of Athens - Xbee mini-project  
-------------------------------------------------------------------------------------------------------------------------------
*/
/*
-------------------------------------------------------------------------------------------------------------------------------
Project       : Monakons UGV_Autonomus_Robot
File          : Monakons-UGV-radar-robot.ino
Description   : This code implements UGV basic Code
Author        : Monachopoulos Konstantinos
-------------------------------------------------------------------------------------------------------------------------------
*/

#define sensorPin 0
#include <Servo.h>
#include <LiquidCrystal.h>

// Initialize LCD Pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Servo myservo;  // Create an instance of Class Servo

// Initialize motor pins to Arduino
int motor_pin1 = 8;
int motor_pin2 = 9;
int motor_pin3 = 6;
int motor_pin4 = 7;
int SensorValue;
int distanceleft;
int distance;
int distanceright;
String DataACquisition;
String SpaceIt=" ";
int i;

void setup()
{
//  Initialize lcd screen
lcd.begin(16, 2);
Serial.begin (9600);
pinMode(sensorPin, INPUT);
    
// Initialize Servo Pin and Position
myservo.attach(10);
myservo.write(74);
    
// Initialize motor Pins
pinMode(motor_pin1,OUTPUT);
pinMode(motor_pin2,OUTPUT);
pinMode(motor_pin3,OUTPUT);
pinMode(motor_pin4,OUTPUT);
lcd.setCursor(0, 0);
lcd.clear();
lcd.print("arduino ZIGBEE");
lcd.setCursor(0, 1);
lcd.print("wireless robot");
delay(10000);
}

void loop()
{
DataACquisition="";
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("scanning for obj");
lcd.setCursor(0, 1);
lcd.print("ect ");
digitalWrite(motor_pin1,HIGH);
digitalWrite(motor_pin2,LOW);
SensorValue = analogRead(sensorPin);
distance= 9462/(SensorValue - 16.92);

// Move straight until you find an object
if(distance<25 && distance>0)
{
    digitalWrite(motor_pin1,LOW);
    digitalWrite(motor_pin2,HIGH);
    delay(1000); // Breaks, this depends on the space that the robot moves.
    digitalWrite(motor_pin1,LOW);
    digitalWrite(motor_pin2,LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("avoiding it...");
    lcd.setCursor(0, 1);
lcd.print("");
delay(1000);

// Scan from -90 to 90 degrees and detect the distances
for (i=20;i<=130;i=i+4)
    {

    myservo.write(i);
    delay(100);
    SensorValue = analogRead(sensorPin);
    if (i == 20)
    {
        distanceright= 9462/(SensorValue - 16.92);
        }
    if  (i == 128)
        {
            distanceleft= 9462/(SensorValue - 16.92);
            }
        distance= 9462/(SensorValue - 16.92);
        DataACquisition = DataACquisition+SpaceIt;
        DataACquisition=DataACquisition+distance;
        }
        // Send the data to Serial port while MatlabRobotCommunication.m is Running
        Serial.println(DataACquisition);
        myservo.write(74);

        // Make a decision of the new path that the robot will move
        if (distanceright<distanceleft)
            {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("the object detec");
                lcd.setCursor(0, 1);
                lcd.print("ted at the right");
                // Reverse
                digitalWrite(motor_pin3,LOW);
                digitalWrite(motor_pin4,HIGH);
                digitalWrite(motor_pin1,LOW);
                digitalWrite(motor_pin2,HIGH);
                delay(1200);
                // Stop reverse
                digitalWrite(motor_pin1,HIGH);
                digitalWrite(motor_pin2,LOW);
                delay(500);
                digitalWrite(motor_pin1,LOW);
                digitalWrite(motor_pin2,LOW);
                digitalWrite(motor_pin3,LOW);
                digitalWrite(motor_pin4,LOW);
                delay(1000);
                }
        else
            {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("the object detec");
                lcd.setCursor(0, 1);
                lcd.print("ted at the left");
                // Reverse
                digitalWrite(motor_pin3,HIGH);
                digitalWrite(motor_pin4,LOW);
                digitalWrite(motor_pin1,LOW);
                digitalWrite(motor_pin2,HIGH);
                delay(1200);
                // Stop reverse
                digitalWrite(motor_pin1,HIGH);
                digitalWrite(motor_pin2,LOW);
                delay(500);
                digitalWrite(motor_pin1,LOW);
                digitalWrite(motor_pin2,LOW);
                digitalWrite(motor_pin3,LOW);
                digitalWrite(motor_pin4,LOW);
                delay(1000);
                }
}
}


