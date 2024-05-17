***Smart Home Automation Project: Controlling Your Home with a Tap!***

I am excited to share with you my recent project experience in developing a smart home automation system using cutting-edge technologies. This project demonstrates the potential of IoT and automation in creating a seamless and intuitive experience for homeowners.

System Overview

The smart home system consists of three zones: bedroom, office, and living room. Each bedroom and office is equipped with a bulb and fan, while the living room features additional sensors for temperature and gas levels. The system enables remote control of lighting, fans, and door operations, as well as real-time monitoring of temperature and gas levels.

# Hardware Connections

I utilized Fritizing to design the hardware connections, which are illustrated in the diagram below:
![connections](https://github.com/Hamaozil/SmartHome_IOT/assets/115914652/1d642cfe-3c6e-49ba-963f-b04a11e2db27)

# Hardware Components

The system employs the following hardware components:

1. NodeMCU
2. Arduino Nano
3. 3 x 12V LED
4. 3 x 12V fan
5. 4-channel relay module (5V input)
6. 2-channel relay module (5V input)
7. Servo motor
8. Gas sensor (MQ2)
9. Booster
10. 5 x LI-ION battery (18650)
11. Jumpers
12. Temperature sensor (LM35)
# Code Architecture

The code is divided into two parts: Arduino and NodeMCU. The Arduino code controls the LEDs, fans, and receives data from the gas and temperature sensors. It then forwards this data to the NodeMCU, which publishes it to the `MQTT` server (HiveMQ). The NodeMCU code connects to WiFi and the `MQTT` broker, listening to specific topics such as bedRoomLed, bedRoomFan, etc.
