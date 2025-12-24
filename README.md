# Dual-Axis Solar Tracking System using Arduino Nano (PID Control)

This project implements a **dual-axis solar tracking system** using an **Arduino Nano**, **LDR sensors**, and **servo motors**, controlled through a **PID (Proportional–Integral–Derivative) control loop**.  
The system continuously adjusts the panel orientation to maximize solar exposure in both horizontal and vertical directions.

---

## 📌 Project Overview

Solar panels generate maximum power when aligned perpendicular to sunlight.  
This project uses **four LDR sensors** to detect light intensity differences and applies **PID control** to precisely rotate the panel using two servo motors:

- **Left–Right axis (Azimuth control)**
- **Top–Bottom axis (Elevation control)**

PID control ensures **smooth, stable, and accurate tracking**, avoiding oscillations and sudden movements.

---

## 🧠 Key Features

- Dual-axis solar tracking (horizontal + vertical)
- PID-based closed-loop control
- Smooth servo motion with output limiting
- Real-time sensor feedback via Serial Monitor
- LED indicators for movement direction
- Buzzer-based system status indication
- Low-power operation using a 3.7V battery

---

## 🛠️ Hardware Requirements

| Component                         | Quantity    |
|-----------------------------------|-------------|
| Arduino Nano                      | 1           |
| Servo Motor (SG90 or equivalent)  | 2           |
| LDR Sensors                       | 3–4         |
| LEDs                              | 4           |
| Resistors (for LDRs & LEDs)       | As required |
| Breadboard                        | 1           |
| Jumper Wires                      | As required |
| 3.7V Li-ion Battery / Power Cable | 1           |
| Buzzer                            | 1           |

---

## 🔌 Pin Connections (Summary)

### Servos
- Left–Right Servo → Digital Pin **10**
- Top–Bottom Servo → Digital Pin **11**

### LDR Sensors
- Left LDR → **A1**
- Bottom LDR → **A2**
- Right LDR → **A3**

### Indicators
- LEDs → Digital Pins **3, 4, 5, 6, 7**
- Buzzer → Digital Pin **2**

---

## ⚙️ Control Logic

### Sensor Processing
- Horizontal error = `Right LDR − Left LDR`
- Vertical error = `Top LDR − Bottom LDR`

### PID Control
For each axis:
- **Proportional (P):** Reacts to current light difference  
- **Integral (I):** Eliminates steady-state error  
- **Derivative (D):** Reduces overshoot and oscillation  

PID output is limited to prevent abrupt servo movements.

---

## ▶️ How to Run the Project

1. Assemble the hardware as per connections
2. Open the Arduino IDE
3. Select:
   - Board: **Arduino Nano**
   - Processor: **ATmega328P**
4. Upload the provided code
5. Place the setup under a light source
6. Observe automatic tracking and LED indicators

---

## 📈 Applications

- Solar panel efficiency enhancement
- Renewable energy systems
- Embedded control systems learning
- PID control demonstration
- IoT and automation projects

---

## 📄 Notes

- PID gains (`Kp`, `Ki`, `Kd`) may be tuned based on lighting conditions and servo response.
- Build stability improves with proper LDR placement and shielding.
- Debug information is available via Serial Monitor.

---

## 🎓 Academic Context

This project demonstrates practical implementation of:
- Feedback control systems
- PID algorithms
- Sensor-based automation
- Embedded system integration

---

## 📜 License

This project is developed for **academic and educational purposes**.
