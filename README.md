# CAN Based Automotive Dashboard

## Project Overview

The **CAN Based Automotive Dashboard** is an embedded systems project developed using the **PIC18F4580 microcontroller**. The project demonstrates communication between multiple Electronic Control Units (ECUs) using the **Controller Area Network (CAN) protocol**.

The system consists of three ECUs that communicate with each other through the CAN bus. Each ECU performs a specific function, and the collected vehicle information is displayed on the dashboard.

## System Architecture

```text
                       CAN BUS
                          │
        ┌─────────────────┼─────────────────┐
        │                 │                 │
      ECU 1             ECU 2             ECU 3
        │                 │                 │
   Speed & Gear       RPM & Indicators    Dashboard
        │                 │                 │
   Potentiometer          │              CLCD Display
   + DKP                  │
                          │
                    Potentiometer
                       + DKP
```

## ECU Functions

### ECU 1 — Speed and Gear Control

ECU 1 is responsible for controlling:

* **Vehicle speed** using a potentiometer
* **Gear selection** using a Digital Keypad (DKP)

The speed and gear information is transmitted through the CAN bus to the dashboard ECU.

### ECU 2 — RPM and Indicators

ECU 2 is responsible for controlling:

* **RPM** using a potentiometer
* **Vehicle indicators** using a Digital Keypad (DKP)
* Indicator LEDs for left/right indication

The RPM and indicator information is transmitted through the CAN bus.

### ECU 3 — Dashboard Display

ECU 3 acts as the **dashboard ECU**.

It receives information from ECU 1 and ECU 2 through CAN communication and displays the vehicle parameters on the **Character LCD (CLCD)**.

The dashboard displays:

* Speed
* Gear
* RPM
* Indicator status

## Features

* CAN communication between multiple ECUs
* Speed control using potentiometer
* RPM control using potentiometer
* Gear selection using DKP
* Indicator control using DKP
* LED indication
* CLCD-based dashboard
* Real-time communication between ECUs

## Technologies Used

| Category             | Technology                    |
| -------------------- | ----------------------------- |
| Microcontroller      | PIC18F4580                    |
| Programming Language | Embedded C                    |
| Communication        | CAN Protocol                  |
| IDE                  | MPLAB X IDE 5.35              |
| Compiler             | XC8                           |
| Display              | CLCD                          |
| Input                | Potentiometer, Digital Keypad |

## Hardware Components

* PIC18F4580 Microcontroller
* CAN Controller / Transceiver
* Character LCD (CLCD)
* Potentiometer
* Digital Keypad (DKP)
* LEDs
* Other supporting components

## Software

The firmware was developed using **Embedded C** in **MPLAB X IDE 5.35** and compiled using the **XC8 compiler**.

## Applications

This project demonstrates the fundamentals of **automotive ECU communication using CAN** and provides a basic model of how different vehicle control units communicate and share information in an automotive network.
