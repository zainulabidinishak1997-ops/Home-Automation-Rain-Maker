ESP32 Remote Relay Control using ESP RainMaker


1. Project Objective


This project demonstrates a cloud-connected IoT system using ESP32 and ESP RainMaker. Users
can remotely control multiple relays from a mobile application without building a custom backend
server.


• Control relays remotely via smartphone

• Operate ESP32 GPIO from anywhere (internet access)

• Use ESP RainMaker cloud for secure device communication

• No port forwarding or custom server required

GPIO Mapping:

Relay 1 ® GPIO12,

Relay 2 ® GPIO13,

Relay 3 ® GPIO14,

Relay 4 ® GPIO15,

Logic: Active LOW (ON = LOW, OFF = HIGH)

---

2. Required Components


• ESP32 development board

• 4-channel relay module

• USB data cable

• Arduino IDE

• Smartphone with ESP RainMaker app

• 2.4GHz Wi-Fi network

• Jumper wires

---

3. Important Notes


• GPIO12 and GPIO15 are strapping pins and may affect boot behavior

• Do not connect relay during firmware upload

• Ensure stable power supply during flashing

---

4. Arduino IDE Setup


Install ESP32 board support and configure the following:

• Board: ESP32 Dev Module

• Flash Size: 4MB

• Partition Scheme: RainMaker 4MB No OTA

• Upload Speed: 115200

---

5. Upload Firmware


• Paste firmware code into Arduino IDE

• Connect ESP32 and select correct COM port

• Click Upload and press BOOT if needed

• Open Serial Monitor at 115200 baud

---

6. Mobile App Setup


• Install ESP RainMaker app

• Add device via BLE provisioning

• Enter PoP and Wi-Fi credentials

---

7. Operation


• Toggle switches in app to control relays

• ON ® relay activates (LOW)

• OFF ® relay deactivates (HIGH)

---

8. Hardware Wiring


ESP32 to Relay connections:

• GPIO12 ® IN1

• GPIO13 ® IN2

• GPIO14 ® IN3

• GPIO15 ® IN4

• GND ® GND

• 5V ® VCC

---

9. Safety Guidelines

---

• Do not connect high voltage directly to ESP32

• Use relay module for isolation

• Test with LED before actual load

---

10. Troubleshooting


• No COM port ® check cable/driver

• Upload failed ® press BOOT, disconnect relay

• Device not found ® enable Bluetooth

• Device offline ® check Wi-Fi/internet

---

11. Project Features

---

• Cloud-based remote control

• Multi-channel relay control

• BLE provisioning

• Secure IoT communication

---

12. Future Improvements

• Add scheduling/timer

• Integrate sensors (PIR, LDR)

• Add manual buttons

• Expand to multi-device system
