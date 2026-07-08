# STM32 Custom PWM Generator with Keypad & LCD

A custom PWM signal generator built on the **STM32F103C8T6 (Sparrow Board)** using STM32CubeIDE. The user enters a two-digit duty cycle percentage via a 4×3 matrix keypad. The PWM signal is generated on PA0 via TIM2 Channel 1, and the result is displayed on a 16×2 LCD as `DUTY CYCLE:XX%`. The onboard LED blinks to confirm each keypress.

---

## Features

- Two-digit duty cycle input (00% to 100%) via 4×3 matrix keypad
- PWM output on PA0 using TIM2 CH1
- 16×2 LCD display in 8-bit mode driven via direct ODR register manipulation
- Onboard LED (PC13) blinks on each key detection
- No external LCD libraries — pure HAL + bare register access

---

## Hardware

| Component | Details |
|---|---|
| Microcontroller | STM32F103C8T6 (Sparrow Board) |
| Keypad | 4×3 Matrix Keypad |
| Display | 16×2 LCD (HD44780, 8-bit mode) |
| PWM Output | LED connected to PA0 via 330Ω resistor |
| Status LED | Onboard LED on PC13 (Active LOW) |

---

## Pin Configuration

| Pin | Function | Mode |
|---|---|---|
| PA0 | TIM2 CH1 — PWM Output | Alternate Function Push-Pull |
| PA1 | Keypad ROW1 | Output Push-Pull |
| PA2 | Keypad ROW2 | Output Push-Pull |
| PA3 | Keypad ROW3 | Output Push-Pull |
| PA4 | Keypad ROW4 | Output Push-Pull |
| PA5 | Keypad COL1 | Input Pull-up |
| PA6 | Keypad COL2 | Input Pull-up |
| PA7 | Keypad COL3 | Input Pull-up |
| PA11 | LCD RS | Output Push-Pull |
| PA12 | LCD E (Enable) | Output Push-Pull |
| PB3 | LCD D0 | Output Push-Pull |
| PB4 | LCD D1 | Output Push-Pull |
| PB5 | LCD D2 | Output Push-Pull |
| PB6 | LCD D3 | Output Push-Pull |
| PB7 | LCD D4 | Output Push-Pull |
| PB8 | LCD D5 | Output Push-Pull |
| PB9 | LCD D6 | Output Push-Pull |
| PB10 | LCD D7 | Output Push-Pull |
| PC13 | Onboard Status LED | Output Push-Pull |

> **Note:** LCD RW pin is hardwired to GND (write mode only). LCD contrast is set via a 10kΩ potentiometer on V0 pin.

---

## Timer Configuration (TIM2)

| Parameter | Value |
|---|---|
| Prescaler | 1999 |
| ARR (Period) | 35999 |
| PWM Frequency | 1 Hz |
| CCR Formula | `CCR = Duty% × 360` |

PWM frequency is calculated as:

```
f = 72MHz / (Prescaler+1) / (ARR+1)
  = 72,000,000 / 2000 / 36000
  = 1 Hz
```

---

## Keypad Matrix Map

```
[ 1 ][ 2 ][ 3 ]   ← ROW1 (PA1)
[ 4 ][ 5 ][ 6 ]   ← ROW2 (PA2)
[ 7 ][ 8 ][ 9 ]   ← ROW3 (PA3)
[ * ][ 0 ][ # ]   ← ROW4 (PA4)
  ↑    ↑    ↑
COL1 COL2 COL3
(PA5)(PA6)(PA7)
```

---

## LCD Wiring

```
LCD Pin 1  (VSS)  → GND
LCD Pin 2  (VDD)  → 5V
LCD Pin 3  (V0)   → Potentiometer wiper (contrast)
LCD Pin 4  (RS)   → PA11
LCD Pin 5  (RW)   → GND (hardwired)
LCD Pin 6  (E)    → PA12
LCD Pin 7  (D0)   → PB3
LCD Pin 8  (D1)   → PB4
LCD Pin 9  (D2)   → PB5
LCD Pin 10 (D3)   → PB6
LCD Pin 11 (D4)   → PB7
LCD Pin 12 (D5)   → PB8
LCD Pin 13 (D6)   → PB9
LCD Pin 14 (D7)   → PB10
LCD Pin 15 (LED+) → 5V via 100Ω resistor
LCD Pin 16 (LED-) → GND
```

---

## How It Works

1. On power up, LCD initializes and TIM2 PWM starts with CCR = 0
2. Program waits in a blocking loop for the first digit keypress
3. Onboard LED blinks once to confirm first digit received
4. Program waits for the second digit keypress
5. Onboard LED blinks again to confirm second digit received
6. Duty cycle is computed as `(d1 × 10) + d2`, clamped to 100
7. CCR is updated as `CCR = duty × 360`
8. LCD displays `DUTY CYCLE:XX%`
9. Loop repeats for new input after delay

---

## ODR Bit Shift Explanation

Since LCD data pins start at PB3 instead of PB0, the data byte is left shifted by 3 before writing to ODR:

```c
GPIOB->ODR &= ~(0xFF << 3);   // clear bits 3-10
GPIOB->ODR |=  (data << 3);   // write data shifted to PB3-PB10
```

This ensures each bit of the data byte lands on the correct physical pin without disturbing other GPIOB pins.

---

## Project Structure

```
stm32-pwm-keypad/
│
├── Core/
│   ├── Src/
│   │   └── main.c
│   └── Inc/
│       └── main.h
│
├── Docs/
│   └── project_report.pdf
│
├── README.md
└── stm32-pwm-keypad.ioc
```

---

## Tools Used

| Tool | Purpose |
|---|---|
| STM32CubeIDE | Development and flashing |
| STM32CubeMX (IOC) | Pin and peripheral configuration |
| ST-Link V2 | Flashing and debugging |

---

## Author

Niswanth B
ECE Undergraduate — SASTRA Deemed University
RCS (Robotics Club of SASTRA) — Embedded Systems & PCB Design
Stellaria (Space Club of SASTRA) — PCB Designer, CanSat Project
