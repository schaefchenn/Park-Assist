#include <CAN.h>

#define TX_GPIO_NUM   17  // Connects to CTX
#define RX_GPIO_NUM   16  // Connects to CRX

// Define CAN ID for the message you expect to receive
const uint32_t CAN_ID = 0x11;

struct CanMessage {
  uint8_t driveMode;
  uint8_t throttleValue;
  uint8_t steeringAngle;
  uint8_t driverSignalRecieved;
};

struct CanRecieveMessage {
  bool extended;
  bool rtr;
  uint32_t id;
  uint8_t length;
  uint8_t data[8];
  uint8_t driverReady;
  uint8_t throttleValue;
};


void canSetup(){
    Serial.println("Initialize CAN...");
    // Set the pins for CAN communication
    CAN.setPins(RX_GPIO_NUM, TX_GPIO_NUM);
    
    // Start the CAN bus at 1 Mbps (adjust as needed)
    if (!CAN.begin(1E6)) {
        Serial.println("CAN initialisation failed!");
        while (1);
    } else {
        Serial.println("CAN Initialized");
    }
}

/*
int sniffCAN(){
    return 1;
}
*/