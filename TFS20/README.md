# TFS20-L Arduino Driver (UART)

A simple and clean Arduino driver for the **TFS20-L single-point LiDAR module** using **UART communication**.  
This project is tested on **Arduino Uno R4** and focuses on reliability, readability, and ease of integration.

---

## ✨ Features

- UART communication at **115200 baud**
- Compatible with **Arduino Uno R4**
- Frame-based data parsing
- Checksum verification
- Signal strength validation
- Modular structure (`.h / .cpp / .ino`)
- No external libraries required

---

## 📡 About TFS20-L

**TFS20-L** is a miniaturized single-point LiDAR module based on **direct Time of Flight (dToF)** technology.

It emits a pulsed laser signal and measures distance by calculating the time difference between transmitted and reflected signals using the speed of light.

### Working Principle (Simplified)

1. VCSEL laser emits a pulse
2. Pulse reflects from the target
3. SPAD detector receives the echo
4. Time difference is measured
5. Distance is calculated

---

## 📊 Technical Specifications

### Performance

- **Detection Range**
  - 0.2–20 m @ 90% reflectivity, 0 Klux
  - 0.2–15 m @ 90% reflectivity, 100 Klux
  - 0.2–12 m @ 10% reflectivity, 0 Klux
  - 0.2–9 m @ 10% reflectivity, 100 Klux

- **Accuracy**
  - ±6 cm (0.2–6 m)
  - 1% (≥6 m)

- **Repeatability**
  - 2 cm (0.2–6 m) @ 1σ

- **Frame Rate**
  - 0 / 20 / 50 / 100 (default) / 250 Hz

- **Ambient Light Resistance**
  - Up to 100 KLux

---

### Laser Parameters

- Light Source: VCSEL  
- Wavelength: 905 nm  
- Field of View: < 2°  
- Eye Safety: Class 1 (EN60825)

---

### Electrical & Mechanical

- Average Power Consumption: ≤ 0.43 W
- Peak Current: 130 mA @ 3.3 V
- Power Supply: DC 3.3 V ±9%
- Communication Level: LVTTL (3.3 V)
- Interfaces: UART / I²C
- Operating Temperature: -20 °C to +60 °C
- Storage Temperature: -20 °C to +85 °C
- Dimensions: 21.0 × 15 × 7.87 mm
- Weight: 1.35 g
- Connector: 0.8 mm, 6-pin (WF08006-01207)

---

## 🔌 Hardware Connection (UART)

| TFS20-L | Arduino Uno R4 |
|-------|----------------|
| TX    | RX (Pin 0)     |
| RX    | TX (Pin 1)     |
| VCC   | 3.3V           |
| GND   | GND            |

> ⚠️ **Important:** TFS20-L is a 3.3V device. Do NOT connect to 5V.

---

## 📦 Data Frame Format

The module continuously outputs a 9-byte frame:

| Byte | Description |
|-----|------------|
| 0   | 0x59 (Header) |
| 1   | 0x59 (Header) |
| 2   | Distance Low Byte |
| 3   | Distance High Byte |
| 4   | Signal Strength Low |
| 5   | Signal Strength High |
| 6   | Temperature Low |
| 7   | Temperature High |
| 8   | Checksum (sum of bytes 0–7, LSB) |

---

## ✅ Data Validation Rules

- Header must be `0x59 0x59`
- Checksum must be valid
- Signal Strength:
  - ❌ Invalid if `< 100`
  - ❌ Invalid if `>= 65535`

---

## 🧪 Example Output

Distance: 135 cm | Strength: 482 | Temp raw: 2310


---

## 📁 Project Structure



TFS20-L/
├── TFS20.ino
├── TFS20.h
└── TFS20.cpp


---

## 🚀 Getting Started

1. Clone the repository
2. Open `TFS20.ino` in Arduino IDE
3. Select **Arduino Uno R4**
4. Upload the code
5. Open Serial Monitor at **115200 baud**

---

## 📌 Notes

- Accuracy depends on temperature, reflectivity, and ambient light
- Peak current may reach 130 mA — ensure power stability
- This project currently supports **UART mode**

---

## 📜 License

MIT License © 2024 EiCUT

---

## 🙌 Acknowledgments

- Benewake (Beijing) Co., Ltd.
- TFS20-L Hardware Documentation

---

Happy hacking! 🚀