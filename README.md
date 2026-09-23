# IoT-Based Bangla Smart Notice Board with Real-Time Calendar and Clock

## Overview
This repository contains the hardware design, source code, and web interface for an IoT-based Bangla Smart Notice Board. Developed for the EEE 416 (January 2025) Final Project, this system serves as a modern digital display for educational institutions and public spaces. It utilizes an ESP8266 microcontroller to drive three separate 8x32 LED dot matrix panels, displaying the time, date, and scrolling public announcements entirely in the Bangla language.

The device connects to Wi-Fi to fetch accurate real-time data via the Network Time Protocol (NTP). Authorized users can dynamically update the scrolling notices through a dedicated local web interface.

## Key Features
* **Multi-Panel Display:** Simultaneously drives three distinct display zones for time, date/month/weekday, and scrolling notices.
* **Real-Time Synchronization:** Synchronizes time and date automatically using NTP over Wi-Fi, eliminating the need for manual time-setting.
* **Bangla Typography:** Renders all digits, months, weekdays, and messages in Bangla using custom 8x8 pixel bitmapped graphics manually designed by the team.
* **Gregorian to Bangla Calendar Conversion:** Automatically converts the fetched English date and month into the corresponding Bangla date and month.
* **Web-Controlled Notices:** Features a password-protected HTML web interface (password: "micro416") hosting a local server on port 80. Users can select from five predefined safety and operational messages (e.g., "লাইন মেনে চলুন", "গাড়ি থামবে") or clear the screen.

## Hardware Requirements
* **Microcontroller:** ESP8266 (NodeMCU AMICA V2).
* **Display:** 3x MAX7219 LED Dot Matrix modules (each configured as 4 cascaded 8x8 matrices, resulting in 8x32 resolution per screen).
* **Power Supply:** 5V Power Adapter.
* **Miscellaneous:** Breadboard, Jumper wires. 

### Pin Configuration
All three MAX7219 displays share the CLK and Din pins but require separate Chip Select (CS) pins to function as independent screens.

| Component / Function | NodeMCU Pin |
| :--- | :--- |
| **Clock (CLK) - All Displays** | D5 |
| **Data In (Din) - All Displays** | D7 |
| **CS Pin - Top Display (Time)** | D3 |
| **CS Pin - Middle Display (Date)** | D8 |
| **CS Pin - Bottom Display (Notice)**| D6 |
| **VCC & GND** | 3.3V/5V & GND |

## Software Setup
The project is programmed using the Arduino IDE. Ensure the following libraries are installed before compiling:
* `ESP8266WiFi.h` & `WiFiUdp.h` (Wi-Fi communication).
* `WiFiManager.h`.
* `MD_Parola.h` & `MD_MAX72xx.h` (LED matrix control).
* `SPI.h`.
* `TimeLib.h` (Time synchronization).
* `Adafruit_GFX.h` & `Max72xxPanel.h` (Graphics rendering).

## Future Work
* **Custom Text Input:** Currently, the notice board triggers predefined messages via web buttons; future iterations aim to support dynamic typing of any Bangla text directly from the web interface. 
* **Enhanced Visual Effects:** Programming the board to implement more complex display transition effects for the date and time segments.
