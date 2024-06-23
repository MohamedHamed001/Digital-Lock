# Digital Safe Project Report

## Introduction
The digital safe project aims to create a secure storage solution using a combination of a keypad, an LCD display, a servo motor, and EEPROM for passcode storage. The safe can be locked and unlocked using a user-defined passcode entered via the keypad. The system is designed to be user-friendly while providing robust security features.

## Key Features
1. **User-Defined Passcode**: Users can set and change the passcode, which is stored in EEPROM to retain it even after power loss.
2. **Passcode Entry**: Users enter the passcode via a keypad, and the system provides real-time feedback on an LCD display.
3. **Servo Motor Lock Mechanism**: A servo motor controls the locking and unlocking of the safe based on the entered passcode.
4. **Error Indication**: A red LED indicates incorrect passcode entries, with the system locking after a specified number of failed attempts.
5. **Reset Functionality**: Users can reset the passcode by entering a special sequence.

## System Components
1. **Keypad**: Used for passcode input.
2. **LCD Display**: Provides user feedback and prompts.
3. **Servo Motor**: Controls the safe's locking mechanism.
4. **Red LED**: Indicates errors and alerts.
5. **EEPROM**: Stores the passcode and system status.

## Process Overview
1. **Initialization**: The system initializes the LCD, keypad, servo motor, and EEPROM.
2. **Set Passcode**: If no passcode is set, the user is prompted to enter a new passcode.
3. **Enter Passcode**: The user enters the passcode to unlock the safe.
4. **Check Passcode**: The entered passcode is compared with the stored passcode.
5. **Unlock Safe**: If the passcode is correct, the servo motor unlocks the safe and locks it again after a delay.
6. **Error Handling**: If the passcode is incorrect, the system decrements the number of allowed attempts and indicates the error using the red LED.
7. **Reset Passcode**: If a specific sequence is entered, the system resets the passcode and prompts the user to set a new one.

By combining these components and features, the digital safe provides a secure and user-friendly way to protect valuable items, with the added benefit of passcode retention through EEPROM. The project emphasizes ease of use, security, and robustness.

## Flowchart
The following flowchart outlines the process flow of the digital safe system.

![Flowchart](assets\flowchart.png)

## Circuit Description
### Components and Connections
1. **Keypad**:
   - Connect keypad rows to pins PD1 to PD4.
   - Connect keypad columns to pins PD5 to PD7.
2. **LCD**:
   - RS pin to PC0.
   - RW pin to Ground (VSS).
   - E pin to PC1.
   - Data pins (D4 to D7) to PC2 to PC5.
3. **Servo Motor**:
   - PWM signal pin to PB6 (OC1A).
4. **Red LED**:
   - Anode of the LED to PB7
   - Cathode of the LED to Ground.
5. **EEPROM**:
   - Used to store the passcode and the status of the safe.

### Circuit Schematic
Below is the circuit schematic illustrating the connections between the microcontroller and mentioned components.

![Circuit Schematic](assets\circuit.jpg)

## Authors
- Mohamed Ahmed Hamed (ID: 1190266)
- Ammar Yasser (ID: 4210206)
- Hanan Tawfik (ID: 4200369)
- Sharif Ehab Sayed (ID: 1200958)
- Mohamed Ehab Souka (ID: 1190517)

---

Cairo University  
Faculty of Engineering  
Embedded Systems in Medical Equipment (SBES162)  
