# GPIO Driver - Bare Metal Arduino UNO (ATmega328P)

**Assignment**: Firmware Intern - Unbox Robotics
**Hardware**: Arduino UNO (ATmega328P)
**Branch**: `GPIO_dev`

---

## 📌 Overview

A bare-metal GPIO driver written for the ATmega328P microcontroller.
Directly manipulates hardware registers to toggle the onboard LED (Pin 13)
every 500ms — without using any Arduino libraries or functions.

---

## 🎯 What It Does

- Configures **Pin 13 (PB5)** as a digital output
- Toggles the **onboard LED** every **500ms** in an infinite loop
- Uses direct register access (no `digitalWrite`, no `pinMode`)

---

## 🔧 Hardware

| Item | Detail |
|------|--------|
| Board | Arduino UNO |
| Microcontroller | ATmega328P |
| Clock Speed | 16 MHz |
| Target Pin | Pin 13 → PB5 (Port B, bit 5) |

---

## 📝 Code Explanation

### 1. GPIO Initialization
```cpp
void setup_gpio()
{
    DDRB = DDRB | (1 << 5);  // Set PB5 as output
}
```
- `DDRB` is the **Data Direction Register** for Port B
- Setting bit 5 to `1` configures Pin 13 as **OUTPUT**
- OR operation ensures other pins are not affected

---

### 2. LED Toggle
```cpp
void toggle_led()
{
    PORTB = PORTB ^ (1 << 5);  // XOR to toggle
}
```
- `PORTB` is the **Port B Data Register**
- XOR (`^`) with bit 5 flips the pin state
- HIGH → LOW → HIGH on every call

---

### 3. Delay Function
```cpp
void delay_500ms(void) {
    for (volatile unsigned long i = 0; i < 200000; i++);
}
```
- Simple busy-wait loop (~500ms at 16MHz)
- `volatile` prevents compiler from optimizing the loop away

---

### 4. Main Loop
```cpp
int main(void)
{
    setup_gpio();

    while (1)
    {
        toggle_led();
        delay_500ms();
    }
    return 0;
}
```
- Initializes GPIO once
- Continuously toggles LED with 500ms delay

---

## 📊 Register Reference

| Register | Address | Purpose |
|----------|---------|---------|
| `DDRB` | 0x24 | Data Direction - Port B (1=Output, 0=Input) |
| `PORTB` | 0x25 | Port B Data Register (controls pin state) |
| `PINB` | 0x23 | Port B Input Register (read pin state) |

---

## ⚙️ How to Run

1. Open **Arduino IDE**
2. Open `GPIO_Driver.ino`
3. Connect Arduino UNO via USB
4. Select board: **Arduino UNO**
5. Upload the code
6. Observe onboard LED blinking every **500ms**

> 💡 No hardware setup needed — uses the onboard LED


## 📚 Reference

- [ATmega328P Datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf)
  - Section 13: I/O Ports
  - Section 13.4: DDRB, PORTB Register Description