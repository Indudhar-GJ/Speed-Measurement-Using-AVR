# Speed Detector Using AVR Microcontroller

## Introduction

This is a simple speed detector project using an AVR microcontroller. It uses two IR sensors to measure the speed of a moving object between the two sensors and displays the speed on an LCD screen. If the speed exceeds a certain threshold, it alerts the user about over-speeding.

## Hardware Requirements

- AVR Microcontroller (e.g., ATmega series)
- IR Sensors (IR1 and IR2)
- LCD Display
- Potentiometer
- Various passive electronic components

## Software Requirements

- AVR-GCC (GNU Compiler Collection for AVR)
- AVRDUDE (Programmer's tool for AVR microcontrollers)

## Project Structure

- `main.c`: The main C code for the AVR microcontroller.
- `Makefile`: A Makefile for compiling and uploading the code.
- `README.md`: This file.

## Setup and Usage

1. **Compile the Code:**
   - Make sure you have AVR-GCC and AVRDUDE installed.
   - Connect your AVR microcontroller and configure the Makefile as needed (e.g., programmer, microcontroller type).
   - Compile the code by running `make`.

2. **Upload to Microcontroller:**
   - After compilation, upload the compiled code to your AVR microcontroller using AVRDUDE.

3. **Hardware Setup:**
   - Connect the IR sensors and LCD display to the microcontroller as per the wiring instructions in the code.

4. **Running the Project:**
   - The microcontroller will detect and measure the speed of objects passing between IR1 and IR2.
   - The speed will be displayed on the LCD screen.
   - If the speed exceeds 130 km/hr, it will display an over-speeding warning.

## Circuit Diagram

![image](https://github.com/Indudhar-GJ/Speed-Measurement-Using-AVR/assets/125132962/dedcfc8e-5611-412b-909a-3e66ea027413)


## Author

- Indudhar G J

## License

This project is open-source and available under the [MIT License](LICENSE.md). You are free to use and modify the code for your own projects.


