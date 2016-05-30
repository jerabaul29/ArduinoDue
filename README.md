# ArduinoDue

This repository contains a modified version of the core and variant of the code for the Arduino Due. The IDE version used is 1.6.8. The aim of this repository is to be able to:

- Get a 20kHz PWM frequency on all PWM pins instead of 1kHz. This is done by modifying the relevant parts of variant.h
- Make it possible to use the 12 bits resolution PWM on the pins that support it (6 included to 9 included) using *analogWriteResolution()*, which seems broken in Arduino IDE 1.6.8. This is done by modifying the relevant parts of variant.h
- Get independantly control of the size of the RX and TX buffers for the programming port (Serial). This is done by creating new classes *UARTClass_1*, *RingBuffer_1_TX*, *RingBuffer_1_RX* and adapting all files impacted by those changes.
 

## Installing the board

To install the new board version (make it available from the Arduino IDE):

- Install the Due board. On Arduino 1.6.8, it seems the Due must be installed from the library manager (not present by default)
- Locate where the Due board code is installed on your computer. This can be tricky to find. For my part (Ubuntu 14.04LTS), it was located in: /home/[username]/.arduino15/packages/arduino/hardware/sam/1.6.7/
- Add the content of the **cores** folder of the repository in the **cores**, i.e. add **sam/1.6.7/cores/arduino_UART_1**
- Add the content of the **variants** folder of the repository in the **variants**, i.e. add **sam/1.6.7/variants/arduino_due_paddle**
- Add the definition of the new board, contained in boards.txt, at the end of boards.txt that is located in **sam/1.6.7/**
 
The board will appear in your IDE as *Arduino Due paddle version (Programming Port)*. The reason why it is called paddle version is that I developped it for building the control system of a paddle.

## Testing the ADC, PWM and buffers

The sketches contained in **Sketches** allow to test the ADC, PWM and the RX buffer.
