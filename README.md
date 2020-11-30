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
- Module BFD-1000
- x2 switch
## Set up

- GND--->Led--->Servo--->HC-SR04--->L298N--->Arduino
- VCC--->Servo--->HC-SR04--->L298N(+5V)--->Arduino
- 9V battery(GND)--->Arduino(GND)
- 9V battery(VCC)--->L298N(+12V)
- L298N(OUT3-OUT4)--->DC Motor
- HC-SR04 [trig--->pin 13, echo--->pin 12]
- switchMode [vcc-->pinLeft,gnd-->resistor-->pin 5-->pinRight](read state button)
- switch (on/off): Vin(arduino)<-->switch<-->gnd<-->12V+(L298N)

| Arduino         | L298N            | HC-SR04|Servo |Led|BFD-1000  |
| ----------------| ---------------- |--------|------|---|----------| 
| pin 3           | ENB              |        |      |   |          |
| pin 6           | in3              |        |      |   |          |  
| pin 7           | in4              |        |      |   |          |  
| VCC             | +5V              |   x    |  x   |   |  X       |  
| GND             |  x               |   x    |  x   | x |  X       |
| pin 10          |                  |        |      | x |          |
| pin 12          |                  |   ECHO |      |   |          |
| pin 13          |                  |   TRIG |      |   |          |
| pin 9           |                  |        |   x  |   |          |
| A0              |                  |        |      |   |  S1      |
| A1              |                  |        |      |   |  S2      |
| A2              |                  |        |      |   |  S3      |
| A3              |                  |        |      |   |  S4      |
| A4              |                  |        |      |   |  S5      |
| pin 2           |                  |        |      |   | NEAR     |
| pin 11          |                  |        |      |   | CLP      |

### Run
- Arduino IDE(Download [here](https://www.arduino.cc/en/software))
- Complie
- Upload Arduino
- Power on: Arduino and L298N
- Enjoy!
