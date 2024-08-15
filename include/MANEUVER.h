#include <Arduino.h>

struct MANEUVER {
    int8_t driveMode;
    int16_t throttle;
    uint8_t steeringAngle;
    int8_t velocity;
    int16_t voltage;
    int8_t acknowledged;
};


//==================================================================================//

MANEUVER fullLockRight () {
  MANEUVER maneuver;

  maneuver.driveMode = 0;
  maneuver.throttle = 1500;
  maneuver.steeringAngle = 150;
  maneuver.velocity = 0;
  maneuver.voltage = 0;
  maneuver.acknowledged = 0;

  return maneuver;

}

MANEUVER fullLockLeft () {
  MANEUVER maneuver;    

  maneuver.driveMode = 0;
  maneuver.throttle = 1500;
  maneuver.steeringAngle = 30;
  maneuver.velocity = 0;
  maneuver.voltage = 0;
  maneuver.acknowledged = 0; 

  return maneuver;

}

MANEUVER reverse (uint8_t steeringAngle) {
  MANEUVER maneuver;
  
  maneuver.driveMode = 0;
  maneuver.throttle = 1475;
  maneuver.steeringAngle = steeringAngle;
  maneuver.velocity = 0;
  maneuver.voltage = 0;
  maneuver.acknowledged = 0;

  return maneuver;
}

MANEUVER halt () {
  MANEUVER maneuver;
    
  maneuver.driveMode = 0;
  maneuver.throttle = 1500;
  maneuver.steeringAngle = 90;
  maneuver.velocity = 0;
  maneuver.voltage = 0;
  maneuver.acknowledged = 0;

  return maneuver;
}

MANEUVER release () {
  MANEUVER maneuver;
    
  maneuver.driveMode = 1;
  maneuver.throttle = 1500;
  maneuver.steeringAngle = 90;
  maneuver.velocity = 0;
  maneuver.voltage = 0;
  maneuver.acknowledged = 0;

  return maneuver;
}