# AUTOMOTIVE-PARAMETER-MONITORING-SYSTEM-USING-CAN
This project simulates a real-time vehicle monitoring system where multiple embedded nodes communicate over CAN bus to display important vehicle parameters such as:  
* 🌡️ Engine Temperature 
* ⛽ Fuel Level 
* 🔄 Turn Indicators (Left / Right)

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
🧩 Block Diagram

Add your block diagram image here

![Block Diagram](images/block_diagram.png)
🔌 CAN Network

Add CAN network image here

![CAN Network](images/can_network.png)
📟 LCD Output

Add LCD output image here

![LCD Output](images/lcd_output.png)
⚙️ Hardware Components
LPC2129 ARM7 Microcontroller
MCP2551 CAN Transceiver
DS18B20 Temperature Sensor
20×4 LCD Display
Fuel Sensor
LEDs
Push Buttons / Switches
Power Supply Circuit
🛠️ Software & Tools
Embedded C
Keil µVision IDE
Flash Magic
CAN Protocol (ISO 11898)

Hardware Required:

LPC2129 Development Boards
MCP2551 CAN Modules
Sensors and LCD
🔹 Build & Flash
Step 1

Open the project in Keil µVision

Step 2

Compile the project

Step 3

Generate .hex file

Step 4

Flash firmware using Flash Magic

🔹 CAN Bus Connections

Connect all nodes using:

CANH ↔ CANH
CANL ↔ CANL

Add:

120Ω termination resistor

at both ends of the CAN bus.

🔹 LPC2129 Pin Configuration
Peripheral	LPC2129 Pins
CAN TX	P0.0
CAN RX	P0.1
LCD	GPIO
ADC	AD0.x
Switches	GPIO
LEDs	GPIO
📊 System Working
Fuel Node
Reads fuel sensor using ADC
Converts value into percentage
Sends fuel data via CAN
Indicator Node
Receives CAN commands
Controls LED blinking patterns
Main Node
Reads temperature sensor
Receives fuel level data
Sends indicator control commands
Displays all parameters on LCD

🧠 Features

✅ Multi-node CAN communication
✅ Real-time parameter monitoring
✅ Distributed embedded architecture
✅ 20×4 LCD live dashboard display
✅ Sensor interfacing with LPC2129
✅ Indicator control using switches and LEDs
✅ CAN-based reliable data transmission
💡 Advantages
Reliable automotive communication
Modular node-based architecture
Easy scalability
Real-time monitoring
Reduced wiring complexity
📚 Concepts Learned
CAN Protocol Implementation
ARM7 LPC2129 Programming
Embedded C Development
Sensor Interfacing
Real-Time Embedded Systems
ADC and GPIO Programming
🔮 Future Enhancements
🚘 Speed sensor integration
📡 IoT-based cloud monitoring
📱 Mobile application dashboard
⚠️ Vehicle fault detection
📍 GPS tracking system
🔋 Battery health monitoring
