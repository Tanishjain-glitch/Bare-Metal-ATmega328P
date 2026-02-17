# Bare-Metal ATmega328P — Firmware

![Platform](https://img.shields.io/badge/Platform-Arduino%20UNO-blue)
![MCU](https://img.shields.io/badge/MCU-ATmega328P-green)
![Language](https://img.shields.io/badge/Language-C-orange)

---

## 👤 Author

| | |
|--|--|
| **Name** | Tanish Jain |
| **GitHub** | [@Tanishjain-glitch](https://github.com/Tanishjain-glitch) |
| **Repo** | [Bare-Metal-ATmega328P](https://github.com/Tanishjain-glitch/Bare-Metal-ATmega328P) |

---

## 📌 Overview

Bare-metal device drivers written for the **Arduino UNO (ATmega328P)**
by directly manipulating hardware registers — no Arduino libraries or
built-in functions used.

Two drivers implemented:
- **GPIO** — Toggles onboard LED every 500ms
- **UART** — Transmits `Hello from UART\r\n` every 1000ms

Each driver has two versions:
- **Loop version** — Simple busy-wait delay
- **Timer version** — Hardware Timer1 with interrupts

---

## 📂 Repository Structure
```
Bare-Metal-ATmega328P/
│
├── GPIO_dev/
│   ├── GPIO_Driver.ino         ← Simple delay loop version
│   └── README.md               ← GPIO documentation
│   
│
├── UART_dev/
│   ├── UART_Loop/
│   │   └── UART_Driver_Loop.ino    ← Simple delay loop version
│   ├── UART_Timer/
│   │   └── UART_Driver_Timer.ino   ← Timer1 interrupt version
│   └── README.md                   ← UART documentation
│
└── README.md                   ← You are here
```

---

## 🔧 Drivers at a Glance

### GPIO Driver — `GPIO_dev/`
- Configures **Pin 13 (PB5)** as output
- Toggles onboard LED every **500ms**
- Direct `DDRB` and `PORTB` register manipulation

### UART Driver — `UART_dev/`
- Initializes UART at **9600 baud, 8-N-1**
- Transmits `Hello from UART\r\n` every **1000ms**
- Direct `UCSR0B`, `UCSR0C`, `UBRR0` register manipulation

---

## 📊 Versions Comparison

| Feature | Loop Version | Timer Version |
|---------|-------------|---------------|
| **Timing** | Busy-wait (~approx) | Timer1 CTC (precise) |
| **CPU Usage** | 100% blocked | Free for other tasks |
| **Complexity** | Simple | ISR + flag based |
| **Best For** | Learning | Production |

---

## ⚙️ Hardware

| Detail | Value |
|--------|-------|
| Board | Arduino UNO R3 |
| Microcontroller | ATmega328P |
| Clock | 16 MHz |
| IDE | Arduino IDE |

---

> ⚠️ **Note**: No Arduino libraries used throughout this project.
> Only `setup()` and `loop()` structure used where needed.
