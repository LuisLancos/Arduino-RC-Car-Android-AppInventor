
// Luis Lancos
// This sketch will allow to control an ESC and a Servo via Bluetooth
// Using app Inventor on Android phone as a remote
// Using HC-05 as the bluetooth device to connect to Android

// For the ESC using the ESC.h library with 1000/2000 mics as endpoints and an arm speed of 1560 
// pins : Tx 10 and Rx 12  HC-05 , ESC 9 , SERVO 7 for turning

#include "ESC.h"
#include  <SoftwareSerial.h>
#include <Servo.h> 

// Servo defintions 

Servo TurnServo;

// Bluetooth for HC-05 connected to 7/8 pins
int bluetoothTx = 10;
int bluetoothRx = 11;
SoftwareSerial bt(bluetoothTx, bluetoothRx); // Rx, Tx 
// https://kychem.wordpress.com/2018/01/21/hc-05-bluetooth-full-document/

// ESC Defintions - PIN 9 
#define LED_PIN (13)                                      // Pin for the LED 
#define SPEED_MIN (1000)                                  // Set the Minimum Speed in microseconds
#define SPEED_MAX (2000)                                  // Set the Minimum Speed in microseconds
#define ARM_VAL (1500)                                    // ESC arm value
#define GENTLY_MAX_SPEED  (1650)                          // mainly for testing, limiting the max speed
#define GENTLY_MAX_REVERSE  (1400)                        // mainly for testing, limiting the max speed

#define ACEL_MIN (1000)                                  // we did use 2 variables : Acelaration with 1001 till 1100 and Turn 2001 till 2100
#define ACEL_MAX (1100)                                  // We will receive numbers in this range via Blueetoth from Android.
#define TURN (2000)
#define TURN_MAX (2500)
#define TURN_MIN (1200)
#define TURN_SERVO_PIN (7)           

ESC myESC (9, SPEED_MIN, SPEED_MAX, ARM_VAL);                 // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Default Speed, Arm Value)

int oESC;                                                 // Variable for the speed sent to the ESC
 //int ServoValue = 0;
 //int TurningValue =0;
 int AcelarationValue=0;
 int Ready = 0;
 char s=",";

void setup() {

  Serial.begin(9600);
  bt.begin(9600);                                         //Setup Bluetooth serial connection to android
  TurnServo.attach(TURN_SERVO_PIN);
  myESC.arm();                                            // Send the Arm value so the ESC will be ready to take commands
  delay(5000);                                            // Wait for a while
}

void loop() {
  //Read from bluetooth and write to usb serial, 2 bytes. The Android is sending 2 bytes at time
  if (bt.available()>0 )
  {
    int TurningValue = bt.parseInt();
    int AcelarationValue = bt.parseInt(); 

         if ((AcelarationValue <= 100 ) && (AcelarationValue >=0 )){                          // foward
           AcelarationValue = map(AcelarationValue,0,100,ARM_VAL,GENTLY_MAX_SPEED);           // 0 - stop , 100 max acel // 0 till -100 reverse ( temporarly -100 min and 100 max )
           Serial.print("Foward: ");
           Serial.println(AcelarationValue);
           myESC.speed(AcelarationValue);                                                      // tell ESC to go to the oESC speed value
           delay(10); 
        }

        if ((AcelarationValue >=-100 ) && (AcelarationValue <0 )){                            // reverse
           AcelarationValue = map(AcelarationValue,-100,0,GENTLY_MAX_REVERSE, ARM_VAL);      // 0 - stop , 100 max acel // 0 till -100 reverse ( temporarly -100 min and 100 max )
             Serial.print("reverse: ");
           Serial.println(AcelarationValue);
           myESC.speed(AcelarationValue);                                                     // tell ESC to go to the oESC speed value
           delay(10); 
        }

     if (TurningValue <= 100  ) {
            TurningValue = map(TurningValue,-100,100,0,180);             
              Serial.println(TurningValue);
            TurnServo.write(TurningValue);
           delay(10);
      }
      
  //      delay(10);
        bt.print('d');   
  
  }
}
