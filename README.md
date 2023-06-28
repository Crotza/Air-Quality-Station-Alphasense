# Air Quality Station using Alphasense Sensors

This code is designed to read data from multiple gas sensors and provide measurements for various gases such as Hydrogen Sulfide (H2S), Carbon Monoxide (CO), Volatile Organic Compounds (VOC), Nitrogen Dioxide (NO2), and Oxidising gases (Ozone + Nitrogen Dioxide).

## Requirements
- Arduino Mega 2560
- Gas sensors: H2S-B4, CO-B4, VOC-B4, NO2-B43F, OX-B431 (All the sensors are integrated with the ISB board, from Alphasense)
- DHT 11 sensor for temperature and humidity measurement

## Setup
1. Connect the gas sensors to the appropriate analog pins on your Arduino Board, in this case, they're connected like:
   - H2S-B4:
     - WE pin (analog output) -> A0
     - AE pin (auxiliary output) -> A1
   - CO-B4:
     - WE pin (analog output) -> A3
     - AE pin (auxiliary output) -> A4
   - VOC-B4:
     - WE pin (analog output) -> A6
     - AE pin (auxiliary output) -> A7
   - NO2-B43F:
     - WE pin (analog output) -> A8
     - AE pin (auxiliary output) -> A9
   - OX-B431:
     - WE pin (analog output) -> A11
     - AE pin (auxiliary output) -> A12

2. Connect the DHT sensor for temperature and humidity measurement.

3. Upload the code to your Arduino board.

4. Open the serial monitor at a baud rate of 9600 to view the gas measurements.

## Functionality
The code reads analog values from the gas sensors and performs calculations to determine the gas concentrations in parts per billion (ppb) and parts per million (ppm) for each sensor.

The gas concentrations are calculated based on the sensor's sensitivity and various correction factors, including temperature and auxiliary electrode readings.

The code also reads temperature and humidity values from the DHT sensor and uses them to apply temperature correction factors to the gas sensor measurements.

## Output
The code provides the following information in the serial monitor:
- Temperature and humidity readings from the DHT sensor.
- Gas measurements for each gas sensor, including raw analog values, corrected WE output, and gas concentrations in ppb and ppm.

## Notes
- Make sure to adjust the pin assignments in the code according to your actual hardware setup.
- Ensure that you have installed the necessary libraries for the DHT sensor and any other required dependencies.
- It is important to know that each sensor has a differnt value of sensitivity, WEo, WEe, AEo, AEe, Nt, Kt, Ktt, Kttt. You should contact Alphasens for more information about these values.
- Each Sensor has a differnt equation to calculate the WEc. In this case, I'm using just one of the four equations that are provided by a datasheet. Adjust it for a better measument.
