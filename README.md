# 🏠 Smart Home Security System

An ESP32 and Flask-based smart home security prototype that detects motion using an ultrasonic sensor and displays real-time alerts through a local web interface.

This project demonstrates the integration of embedded hardware, sensor-based detection, and a lightweight Flask web application for real-time monitoring.

## 🚀 Project Overview

The system uses an ESP32 microcontroller connected to an HC-SR04 ultrasonic sensor to measure distance and detect movement. Sensor readings are transmitted to a Flask-based web interface, where users can monitor the latest distance values and receive visual alerts.

## ⚙️ Tech Stack

* ESP32
* Arduino IDE
* C++
* HC-SR04 Ultrasonic Sensor
* Python
* Flask
* HTML / CSS / JavaScript
* SQLite

## 💡 Features

* Ultrasonic distance measurement using ESP32
* Motion/distance detection through HC-SR04 sensor
* Local web interface built with Flask
* Real-time sensor data updates
* Visual alert interface for monitoring
* Simple hardware-software integration prototype

## 🧩 System Architecture

The project consists of two main parts:

1. **Arduino / ESP32 Layer**
   Reads ultrasonic sensor data and sends measurements to the Flask server.

2. **Flask Web Layer**
   Receives distance data and displays the latest values through a local web interface.

## 📁 Project Structure

```text
SmartHomeSecuritySystem/
├── Arduino_Smart_Home_Security_System/
│   └── Arduino_Smart_Home_Security_System.ino
├── Flask_Security_System_Simple_Project/
│   ├── main.py
│   ├── static/
│   └── templates/
└── README.md
```

## 🛠️ Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/Busrwa/SmartHomeSecuritySystem.git
cd SmartHomeSecuritySystem
```

### 2. Run the Flask application

```bash
cd Flask_Security_System_Simple_Project
pip install flask
python main.py
```

The Flask interface runs locally.

### 3. Upload the ESP32 code

Open the Arduino project in Arduino IDE and update the Wi-Fi and Flask server placeholders:

```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* flask_server_ip = "http://YOUR_FLASK_SERVER_IP:5000";
```

Then upload the code to the ESP32.

## 🔐 Security Note

This repository is an educational prototype. Real Wi-Fi credentials, API keys, private server addresses, or production secrets should never be committed to the repository.

## 📌 Project Type

IoT / Embedded Systems / Smart Home Security Prototype

## 📄 License

This project is for academic and portfolio purposes.
