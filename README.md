# 🚦 Smart Traffic Light System using STM32 (Nucleo-L432KC)

---

## 📌 Project Overview

This project implements a **Smart Traffic Light System** using an STM32 microcontroller.
The system controls traffic LEDs (Red, Yellow, Green), handles pedestrian input via a push button, and displays the current state on a TFT display.

The project demonstrates key embedded system concepts:

* GPIO control
* SysTick timer
* SPI communication
* Hardware Abstraction Layer (HAL)
* Interrupt-driven timing

---

## 🎯 Objectives

* Design a working embedded traffic system
* Implement timing using SysTick
* Interface TFT display using SPI
* Handle user input (push button)
* Develop modular and reusable embedded code

---

## 🧠 System Architecture

### Block Diagram

👉 *(Insert your block diagram image here)*

---

## 🔌 Hardware Components

| Component           | Quantity |
| ------------------- | -------- |
| STM32 Nucleo-L432KC | 1        |
| Red LED             | 1        |
| Yellow LED          | 1        |
| Green LED           | 1        |
| 220Ω Resistors      | 3        |
| Push Button         | 1        |
| ST7735 TFT Display  | 1        |
| Breadboard          | 1        |
| Jumper Wires        | Multiple |

---

## ⚙️ Peripherals Used

### GPIO

Used to:

* Control LEDs (output)
* Read push button (input)

### SysTick Timer

* Generates interrupt every 1 ms
* Used for delay and timing control
* Drives traffic light timing logic

### SPI (Serial Peripheral Interface)

* Used to communicate with TFT display
* Sends pixel and text data

---

## ⏱️ SysTick Timer Working

The SysTick timer provides system timing:

1. Timer configured for 1 ms interrupt
2. Counter counts down
3. Interrupt triggered at 0
4. Global time variable increments
5. Used by delay function

---

## 🔁 System Flow

### Normal Operation

* Green → Yellow → Red → repeat

### Pedestrian Mode

* Button pressed
* System switches to pedestrian state
* Display shows **"WAIT"**
* Returns to normal cycle

---

## 🖥️ Display Functionality

The TFT display shows:

* GREEN
* YELLOW
* RED
* PEDESTRIAN WAIT

---

## 🔧 Software Structure

```
src/
 ├── main.c
 ├── display.c
 ├── spi.c
 ├── eeng1030_lib.c

include/
 ├── display.h
 ├── spi.h
 ├── eeng1030_lib.h
 ├── font5x7.h
```

---

## ▶️ How to Run the Project

1. Clone repository:

```bash
git clone https://github.com/YOUR_USERNAME/REPO_NAME.git
```

2. Open in PlatformIO

3. Build and upload:

```bash
pio run --target upload
```

4. Connect hardware according to schematic

---

## 🔬 Testing and Debugging

* Verified LED switching using GPIO outputs
* Verified SysTick timing using delay functions
* Verified SPI communication via display output
* Debugged using:

  * LED indicators
  * Display messages

---

## 📊 Results

* LEDs switch correctly with timing
* Button triggers pedestrian mode
* Display updates in real time
* System operates reliably

---

## 📷 Project Images

### Circuit Setup

👉 *(Insert breadboard image here)*

### Schematic

![sche](https://github.com/user-attachments/assets/c78c6582-43c4-4bfd-9338-26a3836846c0)


### Working Output

👉 *(Insert LED + display image here)*

---

## 📚 References

1. STM32L4 Reference Manual
2. STM32Cube HAL Documentation
3. ST7735 TFT Datasheet
4. PlatformIO Documentation
5. ARM Cortex-M SysTick Documentation

---

## 🎥 Demonstration

👉 *(Insert YouTube link here)*

---

## 👨‍💻 Author

SAI VIDYA CHAITANYA PENTA
Embedded Systems Project

---
