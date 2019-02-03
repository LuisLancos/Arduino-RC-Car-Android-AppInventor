# Arduino-RC-Car-Android-AppInventor

This project uses an uses an Android phone to control an Arduino RC Car via phone gestures. 

I used a 1/10 Turnigy Truck from HobbyKing. I like big cars and anyway just it has enough space for electronics.

Decide to have Arduino controlling the ESC and the Servo. Used the QuicRUn 10BL60 Hobbywing in forward/reverse mode as it’s a liner ESC to use with Arduino, have experienced some ESC that are quite strange with the starting sequence, but this one is really straightforward so an excellent choice. It also a good choice to power a 1/10 car. 

The only think I had to do was to program the ESC to the Forward/reverse mode as it’s the most adequate for this project and allows a seamless switch between forward and reverse. 

For the steering servo used DIGITAL 1/10 SCALE STEERING SERVO 25T 11.2KG / 0.09SEC. Its powerful enough for this scale and it’s a smooth servo, but of course I could use any digital standard servo same size. 

I used a HC-06 Bluetooth module on Arduino to establish a serial communication with the Android app.  Basically, the Android App sends the Accelerometer Y and X value to the Arduino. I’m using the Z axis as speed axis and the Y axis for steering. The Arduino code receives the values as integers and then uses the function map to convert the Y values to angles, 0 to 180, and the Z value for the steering servo from 1000 to 2000 ms. 

The Android application was developed in MIT App Inventor. I decided to use this project to try App Inventor as it becoming quite common between Arduino Hobbyists.   

The Mobile app, first connects to the Bluetooth device, HC-06, and once established the connection, every 100 milliseconds sends to the Arduino the X and Y values from the phone Accelerometer I used the timer block for this instead of accelerometer event “AccelarationChanger” event. This is because the Accelerometer change value constantly and that would cloth the buffer with the Arduino, while the servo and ESC are responding. This way allowing 100 milliseconds will give time for ESC and Servo to respond before next reading. I tested various values for the timer and it seemed to me that this is an ideal value, allowing smooth responses. 

The application shows the values of the Accelerometer that is sending to Arduino and implements a Start/Stop button, allowing to stop the car is required. 

The biggest problems on this project where about sending more than one integer from the App to Arduino and the synchronization and timing between both components.  Is worth to notice that debug of the Bluetooth communication between Android App and Arduino its not easy, especially if the problems are because of buffer synchronization as the App Inventor does not provide easy debug functionality. 

Using MIT App inventor is easy and straightforward and allows to build an app really fast. Problems arises when you need to do something no covered by the standard blocks or you need to do some deep debugging. 

The result however is very positive and I will definitely be using MIT App Inventor for other projects as it allows an expedite way to build the mobile App. 

I add the .aia – MIT App Inventor code and the Arduino code file. 

Components used: 

•    1/10 Turnigy Truck 
•    ESC :QuicRUn 10BL60 Hobbywing  ( http://www.hobbywing.com/products/enpdf/quicrunwp10bl30-10bl60-8bl150.pdf )
•    Servo : TRACKSTAR TS-411MG DIGITAL 1/10 STEERING SERVO 25T 11.2KG / 0.09SEC / 57G
•    Brushless engine : Turngy F540 3300KV Brushless Motor Waterproof ( https://bit.ly/2HnMCVg  )
•    Arduino Nano ( https://store.arduino.cc/arduino-nano )
•    HC-06  ( https://www.olimex.com/Products/Components/RF/BLUETOOTH-SERIAL-HC-06/resources/hc06.pdf )



Enjoy 








