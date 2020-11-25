 #include <Servo.h>

#define trig 13
#define echo 12
Servo myservo;
int servoLeft = 10; //angle of microservo rotation to scan on left
int servoForward = 45;
int servoRight = 100; //angle of microservo rotation to scan on right
int a=0;
int enb = 3;
int in3 = 6; 
int in4 = 7;

int czas, dist1, dist2, dist3;

void setup() {
  // servo pin definition
  myservo.attach(9);

  //buzzer
  pinMode(11, OUTPUT);

  //light
  pinMode(10, OUTPUT);

  //ultrasonic sensor
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  //motors
  pinMode(enb, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {

  scanLeft();
  delay(250);
  scanRight();
  delay(250);
  scanForward();
  delay(250);


  if( dist3<30){
    moveBackward();
    digitalWrite(10, HIGH);
    delay(1000);
    digitalWrite(10, LOW);
    moveStop();
  }
  if(dist2>50 && dist1<20){
    myservo.write(servoRight);
    delay(500);
    moveForward();
    delay(1000);
    moveStop();
    a=2;
  }
  if(dist1>50 && dist2<20){
    myservo.write(servoLeft);
    delay(500);
    moveForward();
    delay(1000);
    moveStop();
    a=3;
  }


  if(dist3>dist2 && dist3>dist1 && dist3>50){
    if(a==2)  {
      lamijlocdindreapta();
    }
    if(a==3)  {
      lamijlocdinstanga();
    }
    moveForward();
    delay(1000);
    moveStop();
    a=1;
  }

  if(dist2>dist3 && dist2>dist1 && dist2>50){   
    myservo.write(servoRight);
    delay(500);
    moveForward();
    delay(1000);
    moveStop();
    a=2;
  }

  if(dist1>dist2 && dist1>dist3 && dist1>50){
    myservo.write(servoLeft);
    delay(500);
    moveForward();
    delay(1000);
    moveStop();
    a=3;
  }
}

void scanForward(){
  myservo.write(servoForward);
  digitalWrite(trig, HIGH);
  delay(500);
  digitalWrite(trig, LOW);
  czas = pulseIn(echo, HIGH);
  dist3 = (czas/2)/29.1;
}

void scanRight(){
  myservo.write(servoRight);

  delay(50);
  digitalWrite(trig, HIGH);
  delay(500);
  digitalWrite(trig, LOW);
  czas = pulseIn(echo, HIGH);
  dist2 = (czas/2)/29.1;
}

void scanLeft(){
  myservo.write(servoLeft);

  delay(50);
  digitalWrite(trig, HIGH);
  delay(500);
  digitalWrite(trig, LOW);
  czas = pulseIn(echo, HIGH);
  dist1 = (czas/2)/29.1;
}

void moveForward(){
  motorB(2, 60);
}
void lamijlocdindreapta(){
  myservo.write(servoLeft);
  delay(200);

}
void lamijlocdinstanga(){
  myservo.write(servoRight);
  delay(200);

}

void moveBackward(){
  motorB(1, 80);
}


void moveStop(){
  motorB(0, 0);

}


void buzzerOn(){
  tone(8, 440, 200);
}

void lightOn(){
  digitalWrite(10, HIGH);
  delay(500);
  digitalWrite(10, LOW);
}



//******************   Motor B control   *******************
void motorB(int mode, int percent)
{

  //change the percentage range of 0 -> 100 into the PWM
  //range of 0 -> 255 using the map function
  int duty = map(percent, 0, 100, 0, 255);

  switch(mode)
  {
  case 0:  //disable/coast
    digitalWrite(enb, LOW);  //set enable low to disable B
    break;

  case 1:  //turn clockwise
    //setting IN3 high connects motor lead 1 to +voltage
    digitalWrite(in3, HIGH);   

    //setting IN4 low connects motor lead 2 to ground
    digitalWrite(in4, LOW);  

    //use pwm to control motor speed through enable pin
    analogWrite(enb, duty);  

    break;

  case 2:  //turn counter-clockwise
    //setting IN3 low connects motor lead 1 to ground
    digitalWrite(in3, LOW);   

    //setting IN4 high connects motor lead 2 to +voltage
    digitalWrite(in4, HIGH);  

    //use pwm to control motor speed through enable pin
    analogWrite(enb, duty);  

    break;

  case 3:  //brake motor
    //setting IN3 low connects motor lead 1 to ground
    digitalWrite(in3, LOW);   

    //setting IN4 high connects motor lead 2 to ground
    digitalWrite(in4, LOW);  

    //use pwm to control motor braking power 
    //through enable pin
    analogWrite(enb, duty);  

    break;
  }
}
