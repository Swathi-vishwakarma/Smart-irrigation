# Smart Irrigation System

This project implements an advanced **Smart Irrigation System** using an Arduino, soil moisture sensor, relay module, water pump, LCD display, and RTC (Real-Time Clock) module. The system automatically irrigates the plants based on soil moisture levels and provides real-time feedback through an LCD and buzzer alarm.

## Features
- **Soil Moisture Detection**: Automatically triggers the irrigation process when the soil moisture level falls below a defined threshold.
- **Watering Duration**: The water pump runs for a fixed duration to ensure optimal water supply.
- **Scheduling**: Allows for irrigation during a specific time range (e.g., 6 AM to 8 AM).
- **Real-time Monitoring**: Displays soil moisture levels and pump status on a 16x2 LCD screen.
- **Buzzer Alarm**: Alerts when the soil remains dry for too long, indicating potential issues.
- **RTC (Real-Time Clock)**: Keeps track of time for scheduled irrigation.

## Components Required
- **Arduino Board** (e.g., Arduino Uno)
- **Soil Moisture Sensor**
- **Relay Module**
- **Water Pump**
- **16x2 LCD Display**
- **RTC Module** (DS3231)
- **Buzzer**
- **Jumper Wires**

## Circuit Connections
1. **Soil Moisture Sensor**: Connect the VCC and GND to 5V and GND on the Arduino, and the analog output (A0) to the A0 pin on Arduino.
2. **Relay Module**: Connect the IN pin to pin 7 of the Arduino. Connect the VCC and GND to 5V and GND on Arduino.
3. **LCD (16x2)**: Use I2C for communication, connecting SDA (A4) and SCL (A5) pins to the Arduino.
4. **Buzzer**: Connect the buzzer to pin 8 of the Arduino.
5. **RTC Module**: Connect SDA (A4) and SCL (A5) pins of the RTC to the Arduino.

## Software Setup
1. **Install Arduino IDE**: Make sure you have the Arduino IDE installed on your system.
2. **Install Libraries**:
   - `LiquidCrystal_I2C` for LCD display control.
   - `RTClib` for Real-Time Clock functionality.
   
   You can install these libraries from the Arduino Library Manager.

3. **Upload the Code**:
   - Open the Arduino IDE.
   - Copy and paste the code from the `smart_irrigation_system.ino` file.
   - Upload it to your Arduino board.

## How It Works
- The soil moisture sensor continuously monitors the soil moisture levels.
- If the moisture level drops below the set threshold, the relay is activated, turning on the water pump.
- The pump runs for a predefined duration (e.g., 5 seconds).
- The system will only irrigate between 6 AM and 8 AM.
- The LCD displays the current moisture level, pump status, and real-time clock.
- If the soil remains dry for an extended period, a buzzer is activated to alert the user.

## Customization
- You can adjust the **moistureThreshold** to suit different soil types.
- Modify the **wateringDuration** to change how long the pump runs.
- The **scheduling** can be updated in the code to irrigate at different times of the day.

## Contributing
Feel free to fork the repository, create a pull request, or submit issues for improvements.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgements
- Arduino and its community for providing an easy-to-use platform for embedded systems.
- The creators of the LiquidCrystal_I2C and RTClib libraries.
