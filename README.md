# Arduino-robot-car
<a href='https://postimg.cc/nCcvRvcR' target='_blank'><img src='https://i.postimg.cc/nCcvRvcR/IMG-2020-11-25-22-40-15-930.jpg' border='0' alt='IMG-2020-11-25-22-40-15-930'/></a>
## Prepare
- Arudino(Mega, Uno,...)
- Module L298N motor drive
- HC-SR04 Ultrasonic sensor
- Servo motor
- 9V battery and External power (example: power bank)
- Jumper Wire
- Car chassis and wheels
- Breadboard
- 1 x DC motor (12V)

## Set up

- GND--->Led--->Servo--->HC-SR04--->L298N--->Arduino
- VCC--->Servo--->HC-SR04--->L298N(+5V)--->Arduino
- 9V battery(GND)--->Arduino(GND)
- 9V battery(VCC)--->L298N(+12V)
- L298N(OUT3-OUT4)--->DC Motor
- HC-SR04[trig--->pin 13, echo--->pin 12]

| Arduino         | L298N            | HC-SR04|Servo |Led|
| ----------------| ---------------- |--------|------|---|          
| pin 3           | ENB              |        |      |   |          
| pin 6           | in3              |        |      |   |          
| pin 7           | in4              |        |      |   |          
| VCC             | +5V              |   x    |  x   |   |          
| GND             |  x               |   x    |  x   | x | 
| pin 10          |                  |        |      | x |
| pin 12          |                  |   x    |      |   | 
| pin 13          |                  |   x    |      |   |
| pin 9           |                  |        |   x  |   |

### Run
- Arduino IDE(Download [here](https://www.arduino.cc/en/software))
- Complie
- Upload Arduino
- Power on: Arduino and L298N
- Enjoy!
