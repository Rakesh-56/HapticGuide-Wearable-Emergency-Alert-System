# HapticGuide-Wearable-Emergency-Alert-System
An Arduino-based wearable prototype that detects smoke, gas, and flame, transmits emergency alerts wirelessly using 433 MHz RF, and provides directional feedback through vibration motors to support deaf and hard-of-hearing individuals.
# Connection Setup

## Part 1: Transmitter (Arduino Uno)

### 433 MHz Transmitter (3-pin module)
1. Connect the transmitter **VCC** pin to the Uno **5V** pin.
2. Connect the transmitter **GND** pin to the Uno **GND** pin.
3. Connect the transmitter **DATA** pin (may be printed as ATAD) to the Uno **D12** pin.
4. Solder a straight wire of about 17 cm to the **ANT** pad to improve range.

### MQ-2 Smoke Sensor
1. Connect the MQ-2 **VCC** pin to the Uno **5V** pin.
2. Connect the MQ-2 **GND** pin to the Uno **GND** pin.
3. Connect the MQ-2 **AO** pin to the Uno **A0** pin.
4. Leave the MQ-2 **DO** pin unconnected, because the code only uses the analog output.

Note: Pins D10 and D11 are reserved by the RadioHead library in this code. Do not use them for anything else.

---

## Part 2: Receiver (Arduino Nano)

### 433 MHz Receiver (8-pin module)
Going from the ANT end, the pins are: ANT, GND, GND, VCC, VCC, NC, DATA, GND. Check this against the silkscreen on your board, since pin order can vary between manufacturers.

1. Connect either **VCC** pin to the Nano **5V** pin. The two VCC pins are tied together internally.
2. Connect any one **GND** pin to the Nano **GND** pin.
3. Connect the **DATA** pin to the Nano **D12** pin.
4. Solder a straight wire of about 17 cm to the **ANT** pin.
5. Leave the **NC** pin unconnected.

### Left IR Obstacle Sensor
1. Connect the sensor **VCC** pin to the Nano **5V** pin.
2. Connect the sensor **GND** pin to the Nano **GND** pin.
3. Connect the sensor **OUT** pin to the Nano **D2** pin.

### Right IR Obstacle Sensor
1. Connect the sensor **VCC** pin to the Nano **5V** pin.
2. Connect the sensor **GND** pin to the Nano **GND** pin.
3. Connect the sensor **OUT** pin to the Nano **D3** pin.

### Vibration Motor Modules
Each module has three pins: signal, VCC and GND.

**Left motor**
1. Connect the module **signal (IN)** pin to the Nano **D5** pin.
2. Connect the module **VCC** pin to the Nano **5V** pin.
3. Connect the module **GND** pin to the Nano **GND** pin.

**Center motor**
1. Connect the module **signal (IN)** pin to the Nano **D6** pin.
2. Connect the module **VCC** pin to the Nano **5V** pin.
3. Connect the module **GND** pin to the Nano **GND** pin.

**Right motor**
1. Connect the module **signal (IN)** pin to the Nano **D9** pin.
2. Connect the module **VCC** pin to the Nano **5V** pin.
3. Connect the module **GND** pin to the Nano **GND** pin.

Note: Pin D10 is reserved by the RadioHead library. Do not use it for anything else.

---

## Part 3: Power Notes
1. The Uno and the Nano are powered separately (USB, power bank, or battery).
2. All GND connections on each board must be common.
3. Power the Nano from a power bank or a good USB port. The three motor modules, two IR sensors and the RF receiver together draw more current than a weak port may supply.
