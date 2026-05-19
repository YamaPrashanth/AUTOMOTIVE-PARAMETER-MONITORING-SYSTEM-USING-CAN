# AUTOMOTIVE-PARAMETER-MONITORING-SYSTEM-USING-CAN
This project simulates a real-time vehicle monitoring system where multiple embedded nodes communicate over CAN bus to display important vehicle parameters such as:  
*  Engine Temperature 
*  Fuel Level 
*  Turn Indicators (Left / Right)

# Project Overview

This project is designed using three independent CAN nodes:

## > Node	Function
* Main Node	Central controller + LCD dashboard
* Fuel Node	Reads fuel sensor and transmits data
* Indicator Node	Controls left/right indicators

The nodes communicate through the CAN bus using the MCP2551 CAN transceiver.

# Parameters Monitored
## > Engine Temperature
* Measured using DS18B20 digital temperature sensor
* Uses 1-Wire communication protocol
* Displayed continuously on LCD
## > Fuel Level
* Read through ADC
* Converted into percentage (0–100%)
* Transmitted from Fuel Node via CAN
## > Turn Indicators
* Left and Right indicators controlled through switches
* Indicator Node performs LED blinking operations

# System Architecture
## The project follows a distributed CAN-based architecture.

* Main Node (Master Controller)
  * Reads temperature sensor
  * Receives fuel data from Fuel Node
  * Sends indicator commands
  * Updates LCD dashboard
* Fuel Node
  * Reads analog fuel sensor
  * Converts ADC value into percentage
  * Sends data over CAN bus
* Indicator Node
  * Receives commands through CAN
  * Controls left/right indicator LEDs

# Block Diagram
<img width="658" height="471" alt="image" src="https://github.com/user-attachments/assets/316ab1cc-ce05-45c0-a126-d4aa985789f7" />

# CAN Network
<img width="3264" height="1501" alt="can" src="https://github.com/user-attachments/assets/f21c05c2-aa8c-425c-95f3-f99c432b452b" />

# LCD Output
<img width="1280" height="960" alt="can1" src="https://github.com/user-attachments/assets/4e7e31c9-d47f-4875-9fb5-90b078c0c72c" />

# Hardware Components
* LPC2129 ARM7 Microcontroller(inbuilt CAN)
* DS18B20 Temperature Sensor
* 20×4 LCD Display
* Fuel Sensor
* LEDs
* CAN Bus
* Push Buttons / Switches
* Power Supply Circuit

# Softwares Required
* Keil µVision IDE
* Flash Magic

# CAN Bus Connections

* Connect all nodes using:
 * CANH ↔ CANH
 * CANL ↔ CANL

# System Working
* Fuel Node Reads fuel value using ADC, Converts value into percentage and Sends fuel data via CAN to the Main Node.
* Indicator Node Receives CAN commands which Controls LED blinking patterns.
* Main Node
 * Reads temperature sensor
 * Receives fuel level data
 * Sends indicator control commands
 * Displays all parameters on LCD

# Features
* Multi-node CAN communication
* Real-time parameter monitoring
* Distributed embedded architecture
* 20×4 LCD live dashboard display
* Sensor interfacing with LPC2129
* Indicator control using switches and LEDs
* CAN-based reliable data transmission
  
# Advantages
* Reliable automotive communication
* Modular node-based architecture
* Easy scalability
* Real-time monitoring
* Reduced wiring complexity

# Future Enhancements
* Speed sensor integration
* IoT-based cloud monitoring
* Mobile application dashboard
* Vehicle fault detection
* GPS tracking system
* Battery health monitoring
