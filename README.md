# Sound-Triggered Multi-Channel Controller

A sound-triggered embedded systems project built with an **Arduino Uno R3**, **sound sensor**, **NPN transistor switching**, and **three LED channels** with a buzzer output. The system responds to clap patterns and serial commands to activate different output states in a structured way.

## Overview

This project was designed to explore how embedded systems process real-world input and convert it into controlled hardware output. The system uses:

- a sound sensor for clap detection
- serial commands for testing and manual control
- three independent LED channels: **red**, **blue**, and **green**
- a buzzer for audio feedback
- NPN transistor switching to safely control the output channels

Each LED channel uses **three LEDs in parallel**, with each LED branch containing its own **220 Ω current-limiting resistor**. Each channel is controlled by a transistor base driven through a **1 kΩ resistor** from an Arduino digital pin.

## Features

- Clap-triggered output control
- Serial-command control mode
- Three independent LED channels
- Buzzer feedback
- Transistor-based low-side switching
- Safe current-limited LED driving
- Organized embedded system design with hardware and software integration

## Hardware Used

- Arduino Uno R3
- Sound sensor module
- 3 × NPN transistors (2N2222 / PN2222)
- 9 × LEDs total
- 9 × 220 Ω resistors for LED branches
- 3 × 1 kΩ resistors for transistor bases
- 1 × buzzer
- Breadboards
- Jumper wires
- USB cable

## System Architecture

### Input Stage
The system accepts input from:
- the sound sensor
- serial commands sent from a computer

### Processing Stage
The Arduino reads the input and determines which output pattern should activate.

### Output Stage
The system controls:
- Red channel
- Blue channel
- Green channel
- Buzzer

Each channel is switched using an NPN transistor in a low-side configuration.

## Channel Design

Each LED channel contains:

- 1 transistor switch
- 3 parallel LED branches
- 1 resistor per LED branch
- 5V supply rail
- common ground reference

### Per-branch configuration
`5V → 220Ω resistor → LED → transistor collector → emitter → GND`

## Electrical Notes

The LED current was analyzed using standard circuit relationships.

Typical values used in the design:

- Supply voltage: `5V`
- Transistor saturation voltage: `~0.2V`
- Base-emitter voltage: `~0.7V`
- Red LED forward voltage: `~2.0V`
- Green LED forward voltage: `~2.2V`
- Blue LED forward voltage: `~3.2V`

### Approximate current per LED branch
- Red: `~12.7 mA`
- Green: `~11.8 mA`
- Blue: `~7.3 mA`

### Approximate total current per channel
- Red channel: `~38.1 mA`
- Green channel: `~35.4 mA`
- Blue channel: `~21.9 mA`

## Pin Configuration

### Sound Sensor
- VCC → 5V
- GND → GND
- AO → A0
- DO → not connected

### Buzzer
- Positive → D9
- Negative → GND

### Transistor Control
- Red channel base → D5 through 1 kΩ
- Blue channel base → D3 through 1 kΩ
- Green channel base → D6 through 1 kΩ

## How It Works

1. The Arduino powers on and begins monitoring the sound sensor and serial input.
2. A clap pattern or serial command is detected.
3. The Arduino processes the input and selects the correct output pattern.
4. The selected transistor channel turns on.
5. Current flows through the three parallel LED branches in that channel.
6. The buzzer activates when required.
7. The system resets and returns to monitoring mode.

## Testing

The system was tested using both clap input and serial commands.

### Example test cases
- Single clap → activates one LED channel
- Double clap → activates another LED channel
- Triple clap → activates the third LED channel
- Four claps → activates all channels and buzzer
- Serial commands `1C`, `2C`, `3C`, `4C` → produce matching output behavior

All test cases were successful and the system returned to idle state after each trigger.

## Challenges and Debugging

Some of the main challenges during development were:

- understanding collector/emitter orientation on the transistor
- tuning sound sensor sensitivity
- coordinating multiple outputs with different trigger types
- keeping the circuit organized across three channels

These issues helped strengthen both circuit understanding and debugging skills.

## Future Improvements

Possible upgrades include:

- IR remote control
- ESP32-based wireless control
- LDR light-based activation
- temperature-based control logic
- PWM brightness control
- constant-current LED driving

## Project Goal

This project was built to strengthen understanding of:

- embedded systems
- input/output control
- transistor switching
- current-limited LED design
- circuit analysis
- hardware/software integration

## Author

**Jay**

## Documentation

Full project documentation is available in the PDF report included in this repository.

## Repository Files

- `README.md`
- `Sound-Triggered Multi-Channel Controller.pdf`
- source code
- schematics
- diagrams
- prototype photos

