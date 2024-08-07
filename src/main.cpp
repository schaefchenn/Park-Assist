#include <Arduino.h>
#include <CANBUS.h>

// Core definitions (assuming you have dual-core ESP32)
static const BaseType_t pro_cpu = 0; // protocol core
static const BaseType_t app_cpu = 1; // application core

// Initialize CPU cores
TaskHandle_t Task1;
TaskHandle_t Task2;

// Set CAN ID
#define CANBUS_ID 0x12    // put your CAN ID here

// CAN send values
int8_t driveMode = 1;
int16_t throttle;
int8_t steeringAngle;
int16_t voltage;
int8_t velocity;
int8_t acknowledged;

// CAN recieve values
uint8_t canDMODE;
int16_t canTHROTTLE;
int8_t canSTEERING;
int16_t canVOLTAGE;
int8_t canVELOCITY;
int8_t canACKNOWLEDGED;

//==================================================================================//

void CANBUS (void * pvParameters) {
  while (1){
    CANRECIEVER msg = canReceiver();

    if (msg.recieved) {
      Serial.print("recieved");
      Serial.print("\tid: 0x");
      Serial.print(msg.id, HEX);

      if (msg.extended) {
        Serial.print("\textended");
      }

      if (CAN.packetRtr()) {
        Serial.print("\trtr");
        Serial.print("\trequested length: ");
        Serial.print(msg.reqLength);

      } else {
        Serial.print("\tlength: ");
        Serial.print(msg.length);
        Serial.print("\tdrive mode: ");
        Serial.print(msg.driveMode);
        Serial.print("\tthrottle: ");
        Serial.print(msg.throttle);
        Serial.print("\tsteering angle: ");
        Serial.print(msg.steeringAngle);
        Serial.print("\tvoltage: ");
        Serial.print(msg.voltage);
        Serial.print("\tvelocity: ");
        Serial.print(msg.velocity);
        Serial.print("\tacknowledged: ");
        Serial.print(msg.acknowledged);
        Serial.println();
      }
    }

    // yield
    vTaskDelay(5 / portTICK_PERIOD_MS);
  }
}


//==================================================================================//

void ECU (void * pvParameters){
  while(1){

    vTaskDelay(10000 / portTICK_PERIOD_MS);

    driveMode = 0;
    throttle = 2000;
    steeringAngle = 60;
    voltage = 1085; 
    velocity = 60;
    acknowledged = 1;

    canSender(CANBUS_ID, driveMode, throttle, steeringAngle, voltage, velocity, acknowledged);

    // yield
    vTaskDelay(5000 / portTICK_PERIOD_MS);

    driveMode = 1;
    canSender(CANBUS_ID, driveMode, throttle, steeringAngle, voltage, velocity, acknowledged);
  }
}


//==================================================================================//

void setup() {
  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);
  while (!Serial);

  // Setup CAN communication and ECU Components
  setupCANBUS();


  // Wait a moment to start (so we don't miss Serial output)
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  xTaskCreatePinnedToCore(CANBUS,                                       // Function to be called
                          "Controller Area Network Message Recieving",  // Name of task
                          4096,                                         // Increased stack size
                          NULL,                                         // Parameter to pass to function
                          2,                                            // Increased priority
                          NULL,                                         // Task handle
                          pro_cpu);                                     // Assign to protocol core

  // Start CANcommunication (priority set to 1, 0 is the lowest priority)
  xTaskCreatePinnedToCore(ECU,                            // Function to be called
                          "Electromic Controll Uni",      // Name of task
                          8192,                           // Increased stack size
                          NULL,                           // Parameter to pass to function
                          2,                              // Increased priority
                          NULL,                           // Task handle
                          app_cpu);                       // Assign to protocol core  
}

void loop() {
  // put your main code here, to run repeatedly:
}
