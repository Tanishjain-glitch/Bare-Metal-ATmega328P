
# UART Driver - Bare Metal Arduino UNO (ATmega328P)

**Hardware**: Arduino UNO (ATmega328P)  
**Branch**: `UART_dev`

---

## 📌 Overview

Bare-metal UART driver for ATmega328P — directly manipulates
hardware registers to transmit "Hello from UART\r\n" every 1000ms.
No Arduino libraries used.

Two implementations provided based on different timing approaches.

---

## 📂 Folder Structure
```
UART_dev/
├── UART_Loop/
│   └── UART_Driver_Loop.ino     ← Simple delay loop version
└── UART_Timer/
    └── UART_Driver_Timer.ino    ← Timer1 interrupt version
```

---

## ⚙️ UART Configuration

| Parameter | Value |
|-----------|-------|
| Baud Rate | 9600 |
| Data Bits | 8 |
| Parity | None |
| Stop Bits | 1 |
| Mode | Asynchronous (8-N-1) |

### Baud Rate Calculation
```
UBRR = (F_CPU / (16 × BAUD)) - 1
     = (16000000 / (16 × 9600)) - 1
     = 103
```
> Reference: ATmega328P Datasheet Page 165

---

## 📁 Version 1 — UART_Loop

### How it works
- Initializes UART at 9600 baud
- Transmits string using busy-wait delay (~1 second)
- Simple and easy to understand



https://github.com/user-attachments/assets/2bda6928-6518-4ed6-ae3e-665c4359e8a6


### Key Code
```cpp
void uart_init() {
    UBRR0L = 103;                              // 9600 baud
    UCSR0B = (1 << TXEN0);                     // Enable TX
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   // 8-N-1
}

void loop() {
    uart_string("Hello from UART\r\n");
    delay_sec();   // ~1 second busy wait
}
```

### Registers Used
| Register | Purpose |
|----------|---------|
| `UBRR0L` | Baud rate low byte (103 for 9600) |
| `UCSR0B` | Enable transmitter via TXEN0 |
| `UCSR0C` | Frame format — 8 data, no parity, 1 stop |
| `UCSR0A` | UDRE0 flag — buffer empty check |
| `UDR0` | Data register — write char to transmit |

---

## 📁 Version 2 — UART_Timer

### How it works
- Same UART configuration as Loop version
- Uses **Timer1 in CTC mode** for accurate 1ms interrupts
- ISR increments counter — sets flag every 1000ms
- Main loop sends string only when flag is set

### Key Code
```cpp
ISR(TIMER1_COMPA_vect) {
    timer_count++;
    if (timer_count >= 1000) {
        send_flag = 1;     // Set every 1000ms
        timer_count = 0;
    }
}

void timer_init() {
    TCCR1B |= (1 << WGM12);           // CTC mode
    TCCR1B |= (1 << CS11) | (1 << CS10); // Prescaler 64
    OCR1A = 249;                       // 1ms tick
    TIMSK1 |= (1 << OCIE1A);          // Enable interrupt
    sei();                             // Global interrupts ON
}
```

### Timer Calculation
```
Timer Freq  = 16MHz / 64 = 250,000 Hz
OCR1A       = (250,000 / 1000) - 1 = 249
Interrupt   → every 1ms
Flag set    → every 1000 interrupts = 1 second
```
> Reference: ATmega328P Datasheet Page 132

### Registers Used
| Register | Purpose |
|----------|---------|
| `TCCR1B` | Timer1 control — CTC mode + prescaler |
| `OCR1A` | Compare value (249 for 1ms) |
| `TIMSK1` | Enable compare match interrupt |
| `UBRR0` | Full baud rate register (103) |
| `UCSR0B` | Enable TX + UCSZ02 = 0 |
| `UCSR0C` | 8-bit frame format |

---

## 📊 Loop vs Timer Comparison

| Aspect | UART_Loop | UART_Timer |
|--------|-----------|------------|
| **Timing** | Approximate | Precise |
| **CPU** | Busy waiting | Free for other tasks |
| **Complexity** | Simple | ISR + flag based |
| **Real-world use** | Prototyping | Production |

---

## 🚀 How to Test

1. Open folder (`UART_Loop` or `UART_Timer`)
2. Open `.ino` file in Arduino IDE
3. Upload to Arduino UNO
4. Open **Serial Monitor**
5. Set baud rate to **9600**
6. See `Hello from UART` every **1000ms**

---

## 📚 Reference

- ATmega328P Datasheet
  - Page 165 — Baud Rate Table
  - Page 162 — UCSR0C Frame Format
  - Page 132 — Timer1 CTC Mode
