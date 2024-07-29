#include <Arduino.h>
#include "CANBUS.h"

// Core definitions (assuming you have dual-core ESP32)
static const BaseType_t pro_cpu = 0; // protocol core
static const BaseType_t app_cpu = 1; // application core

// Initialize CPU cores
TaskHandle_t Task1;
TaskHandle_t Task2;

void CANBUS (void * pvParameters) {

  sniffCAN();

  // yield
  vTaskDelay(1 / portTICK_PERIOD_MS);
}

void ECU (void * pvParameters){


  // yield
  vTaskDelay(1 / portTICK_PERIOD_MS);
}

void setup() {
  // Initialize serial communication at 115200 baud rate
  Serial.begin(115200);

  // Wait a moment to start (so we don't miss Serial output)
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  // Start CANcommunication (priority set to 1, 0 is the lowest priority)
  xTaskCreatePinnedToCore(CANBUS,                         // Function to be called
                          "Controller Area Network",      // Name of task
                          8192,                           // Increased stack size
                          NULL,                           // Parameter to pass to function
                          2,                              // Increased priority
                          NULL,                           // Task handle
                          pro_cpu);                       // Assign to protocol core

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