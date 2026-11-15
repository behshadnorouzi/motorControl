# MotorControl

[![Compile examples](https://github.com/behshadnorouzi/motorControl/actions/workflows/compile.yml/badge.svg)](https://github.com/behshadnorouzi/motorControl/actions/workflows/compile.yml)

Arduino library for driving a four-wheel robot with an ESP32 and two L298N
motor drivers. Each side of the robot gets a signed speed (-255..255), which
is enough for straight runs, arcs and in-place turns.

Written for a small 4WD test platform; the default pin map below is the one
used on that robot and can be overridden in the constructor.

## Hardware

- ESP32-WROOM-32 dev board
- 2 x L298N dual H-bridge (ENA/ENB jumpers fitted, speed is set by PWM on the IN pins)
- 4 x DC gear motors
- Separate supply for the motors, common ground with the ESP32

### Default wiring

| Motor       | Driver input | ESP32 GPIO | Forward when PWM on |
|-------------|--------------|-----------:|---------------------|
| Front right | IN1 / IN2    | 2 / 4      | IN2                 |
| Back right  | IN3 / IN4    | 17 / 18    | IN4                 |
| Back left   | IN1 / IN2    | 13 / 14    | IN1                 |
| Front left  | IN3 / IN4    | 15 / 16    | IN3                 |

GPIO 2 and GPIO 15 are ESP32 strapping pins. They work fine as driver inputs,
but if the board refuses to enter download mode with the drivers connected,
move those two signals to other pins.

## Requirements

- [Arduino-ESP32](https://github.com/espressif/arduino-esp32) core **3.x**
  (the library uses `ledcAttach()` / `ledcWrite(pin, duty)`, which do not exist in 2.x)

## Installation

Clone or download this repository into your Arduino `libraries` folder:

```sh
cd ~/Arduino/libraries
git clone https://github.com/behshadnorouzi/motorControl.git MotorControl
```

or use *Sketch → Include Library → Add .ZIP Library* in the Arduino IDE.

## Usage

```cpp
#include <MotorControl.h>

MotorControl motors;

void setup() {
  motors.begin();
  motors.forward();      // default speed (75)
  delay(1000);
  motors.speed(150, 90); // left, right: arc to the right
  delay(1000);
  motors.stop();
}

void loop() {}
```

Custom pins:

```cpp
MotorControl::Pins pins;
pins.frontRightIn1 = 25;
pins.frontRightIn2 = 26;
MotorControl motors(pins);
```

## API

| Method                         | Description                                                                    |
|--------------------------------|--------------------------------------------------------------------------------|
| `bool begin(uint32_t freq = 5000)` | Attach the eight pins to LEDC (8-bit) and stop. Returns `false` if a pin fails. |
| `void stop()`                  | All inputs low (motors coast).                                                 |
| `void forward(uint8_t speed = 75)` | Both sides forward.                                                         |
| `void backward(uint8_t speed = 75)` | Both sides backward.                                                       |
| `void right(uint8_t speed = 75)` | Spin clockwise in place.                                                     |
| `void left(uint8_t speed = 75)`  | Spin counter-clockwise in place.                                             |
| `bool speed(int left, int right)` | Signed speed per side, -255..255. Returns `false` and ignores the command if out of range. |
| `void testFunction()`          | Forward, backward, right, left with pauses (~12 s, blocking).                  |

## Examples

- [`TestFunction`](examples/TestFunction/TestFunction.ino) - runs the motion check once after reset.
- [`DifferentialSpeed`](examples/DifferentialSpeed/DifferentialSpeed.ino) - arcs and range checking.

## License

[MIT](LICENSE)
