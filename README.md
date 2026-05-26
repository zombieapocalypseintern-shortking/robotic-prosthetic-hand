# 🤖 Flex Sensor Controlled Robotic Hand

A gesture-controlled robotic hand that mirrors real finger movements in real-time using flex sensors, servo motors, and 3D-printed parts. The glove worn by the user captures finger bend data which is translated into servo positions on the robotic hand.

---

## 📸 Overview

Two configurations are supported:

| Mode | Description |
|------|-------------|
| **Wired** | Direct flex sensor → Arduino → Servo connection (included code) |
| **Wireless** | NRF 2.4GHz transmitter/receiver pair for remote operation |

## images/videos

<img width="1599" height="722" alt="WhatsApp Image 2026-05-26 at 9 12 53 PM (1)" src="https://github.com/user-attachments/assets/a80ca3cd-5122-45d8-a9ad-4f0e6bc6178b" />
<img width="722" height="1599" alt="WhatsApp Image 2026-05-26 at 9 12 53 PM" src="https://github.com/user-attachments/assets/5b0e1eb9-09ff-49b4-ac59-7b69e918b305" />

https://github.com/user-attachments/assets/14f002f2-9833-4b17-a101-523b07bd2e68



https://github.com/user-attachments/assets/278ec46d-460a-46ab-a117-5d6abe657836



## 🔧 Hardware Components

### Wired Version
| Component | Qty |
|-----------|-----|
| Arduino UNO | 1 |
| Flex Sensor (2.2 inch) | 5 |
| Servo Motor (SG90 or similar) | 5 |
| Resistor 10kΩ | 5 |
| Breadboard | 1 |
| Jumper Wires | — |
| Glove | 1 |
| Transparent/Fishing String | — |
| 2–3mm Elastic Rope | — |
| Adhesive Glue | — |

### Wireless Version (NRF)
| Component | Qty |
|-----------|-----|
| Arduino Nano | 2 |
| NRF 2.4GHz Module | 2 |
| Servo Motor | 6 |
| Flex / Bend Sensor | 1 |
| Accelerometer (MPU-6050 or similar) | 1 |
| 7805 Voltage Regulator | 1 |
| Zero PCB | 1 |
| Battery + Power Supply | 2 |
| Jumper Wires | — |

---

## 🗂️ Repository Structure

```
robotic-hand-project/
├── arduino/
│   └── servoarm_wired.ino       # Main Arduino sketch (wired mode)
├── 3d-files/
│   ├── Left_Hand.stl            # Full left hand base
│   ├── Right_Hand.stl           # Full right hand base
│   ├── Arm.stl                  # Forearm/arm chassis
│   ├── Arm_Cover.stl            # Arm enclosure cover
│   ├── Finger_Index.stl         # Index finger assembly
│   ├── Finger_Middle.stl        # Middle finger assembly
│   ├── Finger_Ring.stl          # Ring finger assembly
│   ├── Finger_Pinky.stl         # Pinky finger assembly
│   └── Finger_Thumb.stl         # Thumb assembly
├── docs/
│   └── block-diagrams/          # System block diagrams
└── README.md
```

---

## ⚙️ How It Works

### System Architecture

**Wired Mode**
```
Flex Sensors (A1–A5)
        ↓
  Arduino UNO
        ↓
  Servo Motors (1–5)
```

**Wireless Mode — Transmitter Side**
```
Flex Sensor + Accelerometer
        ↓
  Arduino Nano (Transmitter)
        ↓
  NRF 2.4GHz (TX)
```

**Wireless Mode — Receiver Side**
```
  NRF 2.4GHz (RX)
        ↓
  Arduino Nano (Receiver)
        ↓
  Servo Motors x6
```

### Flex Sensor Logic

Each flex sensor is connected as a voltage divider with a 10kΩ pull-down resistor. When a finger bends, resistance increases, changing the analog voltage read by the Arduino. The analog value is mapped to a 0–180° servo angle:

```cpp
flex1_pos = analogRead(A1);
servo1_pos = map(flex1_pos, 840, 900, 180, 0);
servo1_pos = constrain(servo1_pos, 0, 180);
servo1.write(servo1_pos);
```

> **Note:** The `map()` values (e.g., `840, 900`) are calibrated for a specific sensor. You will need to calibrate these for your own sensors using the Serial Monitor.

---

## 🛠️ Wiring Guide

### Flex Sensor to Arduino (per finger)

```
3.3V ──────────┬──── Flex Sensor ────┬──── A1 (analog pin)
               │                     │
              GND               10kΩ resistor
                                     │
                                    GND
```
you can refer the attached image of circuit for easy understanding

### Servo to Arduino

| Servo | Signal Pin |
|-------|-----------|
| Servo 1 (Index) | D2 |
| Servo 2 (Middle) | D3 |
| Servo 3 (Ring) | D4 |
| Servo 4 (Pinky) | D5 |
| Servo 5 (Thumb) | D6 |

> Power servos from an external 5V supply, not from the Arduino's 5V pin, to avoid brownouts.

---

## 📦 3D Printing Guide

All STL files are in the `3d-files/` folder. Recommended print settings:

| Setting | Value |
|---------|-------|
| Material | PLA |
| Infill | 20–30% |
| Layer Height | 0.2mm |
| Supports | Yes (for finger joints) |
| Print Bed Temp | 60°C |
| Nozzle Temp | 200–210°C |

**Print Order:**
1. `Left_Hand.stl` or `Right_Hand.stl` (choose your dominant hand)
2. `Arm.stl` + `Arm_Cover.stl`
3. All 5 finger STL files

---

## 🚀 Getting Started

1. **Clone this repository**
   ```bash
   git clone https://github.com/YOUR_USERNAME/robotic-hand-project.git
   ```

2. **3D Print** the parts from `3d-files/`

3. **Wire up** the circuit following the wiring guide above

4. **Calibrate** your flex sensors:
   - Open `servoarm_wired.ino` in Arduino IDE
   - Uncomment the `Serial.print(flex1_pos)` block
   - Open Serial Monitor at 9600 baud
   - Note resting and fully-bent analog values per finger
   - Update the `map()` values accordingly

5. **Upload** the sketch to Arduino UNO

6. **Assemble** the robotic hand with fishing string threaded through finger joints

---

## 📋 Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software) (v1.8+ or v2.x)
- Arduino `Servo.h` library (built-in)

---

## 🔌 Pin Reference (Quick Summary)

| Pin | Connected To |
|-----|-------------|
| A1 | Flex Sensor 1 (Index) |
| A2 | Flex Sensor 2 (Middle) |
| A3 | Flex Sensor 3 (Ring) |
| A4 | Flex Sensor 4 (Pinky) |
| A5 | Flex Sensor 5 (Thumb) |
| D2 | Servo 1 |
| D3 | Servo 2 |
| D4 | Servo 3 |
| D5 | Servo 4 |
| D6 | Servo 5 |

---

## 💡 Tips & Troubleshooting

- **Servo jitter?** Use a dedicated external 5V power supply for servos
- **Wrong finger mapping?** Recalibrate the `map()` idle/close values using Serial Monitor
- **Finger not fully closing?** Increase the upper bound of the `map()` range
- **NRF not pairing?** Ensure both modules share the same channel and address in code
- **STL files won't slice?** Open in [Microsoft 3D Builder](https://apps.microsoft.com/detail/9wzdncrfj3t6) to auto-repair

---

## 📄 License

## License
This project is licensed under the MIT License.
