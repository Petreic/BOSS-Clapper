# BOSS Clapper

Wireless ESP32-based trigger system for the BOSS / airsoft clapper project.

## Current Hardware

Final hardware:

- 2x Seeed Studio XIAO ESP32-C6
- Detector C6 reads the Kytech trigger signal
- Controller C6 receives the trigger wirelessly
- Controller activates the clapper/RDX system

Basic flow:

```text
Kytech
   ↓
Detector ESP32-C6
   ↓
Wireless
   ↓
Controller ESP32-C6
   ↓
Clapper / RDX
```

## Setup

### 1. Clone the repository

```bash
git clone https://github.com/Petreic/BOSS-Clapper.git
cd BOSS-Clapper
```

### 2. Create the Python environment

```bash
python3 -m venv .venv
source .venv/bin/activate
```

### 3. Install required tools

```bash
pip install -r requirements.txt
```

Verify PlatformIO:

```bash
pio --version
```

Expected version:

```text
PlatformIO Core, version 6.1.19
```

## Build Firmware

### Detector

```bash
pio run -e xiao_c6_detector
```

### Controller

```bash
pio run -e xiao_c6_controller
```

## Flash Firmware

Connect the appropriate XIAO ESP32-C6 by USB.

### Detector

```bash
pio run -e xiao_c6_detector -t upload
```

### Controller

```bash
pio run -e xiao_c6_controller -t upload
```

## Current Testing

The first hardware test is:

```text
Kytech trigger
      ↓
Voltage divider
      ↓
Detector C6
      ↓
TRIGGER DETECTED
```

The Kytech signal must be reduced to an ESP32-safe logic voltage before reaching the GPIO input.

## Development Status

This project is currently under active development and hardware testing.

The repository contains both development/bench configurations and the XIAO ESP32-C6 deployment configurations.
