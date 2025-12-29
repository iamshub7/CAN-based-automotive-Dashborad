CAN-Based Automotive Dashboard

📌 Description

The CAN-Based Automotive Dashboard is an embedded systems project that demonstrates real-time communication between multiple Electronic Control Units (ECUs) using the Controller Area Network (CAN) protocol.
The project simulates an automotive environment where different ECUs exchange data such as vehicle speed, indicators, and system status, which is then displayed on a dashboard unit.

This project was developed as part of the Microcontroller (MC) Module at Emertxe Information Technologies, focusing on CAN protocol implementation, inter-ECU communication, and embedded firmware design.

⚙️ Features
🔹 Multi-ECU Architecture

ECU1 – Sensor ECU

Reads vehicle parameters (speed, indicators, warning signals)

Transmits data over CAN bus

ECU2 – Control ECU

Acts as an intermediate controller

Processes and forwards CAN messages

ECU3 – Dashboard ECU

Receives CAN data

Displays vehicle information on dashboard (LCD / indicators)

🔹 CAN Communication

Implements CAN protocol for inter-ECU messaging

Message-based communication with unique CAN IDs

Reliable data transfer with priority handling

🔹 Real-Time Embedded Operation

Continuous transmission and reception of CAN frames

Low-latency communication suitable for automotive systems

🔹 Modular Firmware Design

Separate firmware for each ECU

Clear separation of:

CAN initialization

Data transmission

Data reception

Peripheral handling

🛠 Technologies Used

Embedded C

CAN Protocol

Microcontrollers (PIC series)

MPLAB X IDE

XC8 Compiler

Embedded peripherals (LCD, switches, indicators)

📦 Installation & Setup

Clone the repository:

git clone https://github.com/iamshub7/CAN-based-automotive-Dashboard.git


Navigate to the project directory:

cd CAN-based-automotive-Dashboard


Each ECU has its own firmware folder:

ECU1/
ECU2/
ECU3/


Open the respective ECU project in MPLAB X IDE, build, and flash the firmware to the corresponding microcontroller.

▶️ Usage

Power all three ECUs

Ensure CAN bus connections between ECUs

ECU1 transmits sensor data

ECU2 processes and relays messages

ECU3 displays real-time vehicle data on the dashboard

📂 Project Structure
.
├── ECU1/        # Sensor ECU firmware
├── ECU2/        # Control ECU firmware
├── ECU3/        # Dashboard ECU firmware
└── README.md

📚 Learning Outcomes

Understanding CAN protocol fundamentals

Designing multi-ECU automotive systems

Inter-microcontroller communication

Embedded firmware modularization

Real-time data handling in automotive applications

🚧 Limitations

Simulated automotive environment

Limited number of vehicle parameters

No CAN error injection or diagnostics support

👨‍💻 Author

Shubham Shinde

📜 License

This project is open-source and available for educational purposes.

🙏 Acknowledgements

Developed as part of the Microcontroller (MC) Module at
Emertxe Information Technologies