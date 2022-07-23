 #include <Braccio.h>
#include <Servo.h>
#include <modbus.h>
#include <modbusDevice.h>
#include <modbusRegBank.h>
#include <modbusSlave.h>

modbusDevice regBank;
modbusSlave slave;

#define YellowPin 13

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

void setup() {
  regBank.setId(1);

  regBank.add(1);//Yellow
  pinMode(YellowPin,OUTPUT);//Yellow Light
  
  regBank.add(40001);
  regBank.add(40002);
  regBank.add(40003);
  regBank.add(40004);
  regBank.add(40005);
  regBank.add(40006);

  regBank.set(40001, 90);
  regBank.set(40002, 90);
  regBank.set(40003, 90);
  regBank.set(40004, 90);
  regBank.set(40005, 90);
  regBank.set(40006, 73);

  Braccio.begin();
  
  slave._device = &regBank;
  slave.setBaud(9600);
}

void loop() {
  /*
   Step Delay: a milliseconds delay between the movement of each servo.  Allowed values from 10 to 30 msec.
   M1=base degrees.              Allowed values from 0  to 180 degrees
   M2=shoulder degrees.          Allowed values from 15 to 165 degrees
   M3=elbow degrees.             Allowed values from 0  to 180 degrees
   M4=wrist vertical degrees.    Allowed values from 0  to 180 degrees
   M5=wrist rotation degrees.    Allowed values from 0  to 180 degrees
   M6=gripper degrees. Allowed values from 10 to 73 degrees. 10: the toungue is open, 73: the gripper is closed.
  */
  
  // the arm is aligned upwards  and the gripper is closed
                     //(step delay, M1,                 M2,                 M3,                 M4    ,M5, M6);
    Braccio.ServoMovement(20,         regBank.get(40001), regBank.get(40002), regBank.get(40003), regBank.get(40004), regBank.get(40005),  regBank.get(40006));  

    int YellowLED = regBank.get(1);//Controls the 
    if (YellowLED <= 0 && digitalRead(YellowPin) == HIGH)digitalWrite(YellowPin,LOW);
    if (YellowLED >= 1 && digitalRead(YellowPin) == LOW)digitalWrite(YellowPin,HIGH);

    delay(5);
    
    slave.run();
}
