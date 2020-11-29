 #include <Servo.h>
#define line_1 A0
#define line_2 A1
#define line_3 A2
#define line_4 A3
#define line_5 A4
#define SW_CLP 11
#define NEAR_SENSOR 2
int sensor=0; 

#define TRIG 13
#define  ECHO 12
Servo myservo;
//int servoLeft = 40; //angle of microservo rotation to scan on left
//int servoForward = 90;
//int servoRight = 130; //angle of microservo rotation to scan on right
int a=0;
int enb = 3;
int in3 = 6; 
int in4 = 7;
const int loa=2;
int goc;
unsigned long xung;
int distance, khoangcach,kc_trai,kc_phai;

//int czas, dist1, dist2, dist3;

void do_khoang_cach()
{
  digitalWrite(TRIG , LOW);   delayMicroseconds(2);
  digitalWrite(TRIG , HIGH); delayMicroseconds(10);
  digitalWrite(TRIG , LOW);
  xung = pulseIn(ECHO, HIGH, 100000);
  distance = xung / 29.1 / 2;
  if(distance <= 0) {khoangcach = 0;}
  else {khoangcach = distance;}
}



void setup() {
  // servo pin definition
  myservo.attach(9);
  //speaker
  pinMode(loa, OUTPUT);
  //light
  pinMode(10, OUTPUT);

  //ultrasonic sensor
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  //motors
  pinMode(enb, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  lookForward(); 
  Serial.begin(9600);
}



void loop() {
  
  modeAuto();//Che do tu lay


}

void doLine(){
  moveForward();
myservo.write(90);
while((digitalRead(line_2)==0)&&(digitalRead(line_1)==1)&&(digitalRead(line_4)==1)&&(digitalRead(line_5)==1)) // lệch phải một ít
  {
    myservo.write(150);//re trai
  }
while((digitalRead(line_4)==0)&&(digitalRead(line_5)==1)&&(digitalRead(line_1)==1)&&(digitalRead(line_2)==1)) // lệch trái một ít
 {
   myservo.write(30); // rẽ phải
 }
while((digitalRead(line_1)==0)&&(digitalRead(line_4)==1)&&(digitalRead(line_5)==1)) // lệch phải nhiều
  {
    sensor=1;
    while(sensor)
    {
    myservo.write(160); // rẽ trái
    if(digitalRead(line_2)==0) sensor=0;
    }
  }
while((digitalRead(line_5)==0)&&(digitalRead(line_1)==1)&&(digitalRead(line_2)==1)) // lech trai nhiều
{
    sensor=1;
    while(sensor)
    {
    myservo.write(20); // rẽ phải
    if(digitalRead(line_4)==0) sensor=0;
    }
}
while((digitalRead(line_2)==1)&&(digitalRead(line_1)==1)&&(digitalRead(line_4)==1)&&(digitalRead(line_5)==1))
{
  myservo.write(90);
}

}


void moveForward(){
  motorB(2, 60);
}


void lookForward()
{ 
  myservo.write(90); delay(200);
  }

void lookLeft(){
  myservo.write(150);
  delay(200);
}

void lookRight(){
  myservo.write(10);
  delay(200);
}

void scanLookLeft(){
//  myservo.write(20);
//  delay(200);
  for(goc = 90; goc <= 150; goc += 1) 
  {                                  
    myservo.write(goc);              
    delay(1);                       
  } 
  do_khoang_cach(); kc_trai = khoangcach; delay(1000);

}

void scanLookRight(){
// myservo.write(100);
// delay(200);
  for(goc = 90; goc>=20; goc-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(goc);              // tell servo to go to gocition in variable 'goc' 
    delay(1);                       // waits 15ms for the servo to reach the gocition 
  } 
 do_khoang_cach(); kc_phai = khoangcach; delay(1000);
}



void moveBackward(){
  motorB(1, 80);
  delay(1000);
}


void moveStop(){
  motorB(0, 0);

}
void pip_1()
{digitalWrite(loa, HIGH); delay(200);digitalWrite(loa, LOW);

}
void pip_2()
{ digitalWrite(loa, HIGH); delay(50);digitalWrite(loa, LOW);delay(50);
  digitalWrite(loa, HIGH); delay(50);digitalWrite(loa, LOW);delay(50);
}


//void buzzerOn(){
//  tone(8, 440, 200);
//}

void lightOn(){
  digitalWrite(10, HIGH);
//  delay(500);
}

void lightOff(){
  digitalWrite(10, LOW);
}

void modeAuto(){
 
  do_khoang_cach();
if(khoangcach > 30)  {  lightOn(); moveForward();}
if((khoangcach <= 30)&&(khoangcach > 2))
{ pip_2();  
  lightOff(); 
  moveStop(); 
  pip_1();
  scanLookLeft(); 
  lookForward(); 
  pip_1();
  scanLookRight();  
  lookForward(); 
  if((kc_trai<30)&&(kc_phai<30)) {moveBackward(); moveStop();pip_1();scanLookLeft(); lookForward(); pip_1();scanLookRight();  lookForward(); }
  if(kc_trai > kc_phai)  {lookLeft(); moveStop(); lightOn(); moveForward();  }
  if(kc_trai <= kc_phai) {lookRight(); moveStop(); lightOn(); moveForward();  }
}
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




/*

int read_sensor() {
  // put your main code here, to run repeatedly:

 while((digitalRead(line_2)==0)&&(digitalRead(line_1)==1)&&(digitalRead(line_4)==1)&&(digitalRead(line_5)==1)) // lệch phải một ít
  {
    myservo.write(55);// rẽ trái
  }
while((digitalRead(line_4)==0)&&(digitalRead(line_5)==1)&&(digitalRead(line_1)==1)&&(digitalRead(line_2)==1)) // lệch trái một ít
 {
    myservo.write(35);// rẽ phải
 }
while((digitalRead(line_1)==0)&&(digitalRead(line_4)==1)&&(digitalRead(line_5)==1)) // lệch phải nhiều
  {
    sensor=1;
    while(sensor)
    {
     myservo.write(60);// rẽ trái
    if(digitalRead(line_2)==0) sensor=0;
    }
  }
while((digitalRead(line_5)==0)&&(digitalRead(line_1)==1)&&(digitalRead(line_2)==1)) // lech trai nhiều
{
    sensor=1;
    while(sensor)
    {
    myservo.write(30);// rẽ phải
    if(digitalRead(line_4)==0) sensor=0;
    }
}
while((digitalRead(line_2)==1)&&(digitalRead(line_1)==1)&&(digitalRead(line_4)==1)&&(digitalRead(line_5)==1))
{
  myservo.write(45);
}
}
//di thang



 /*
 if((digitalRead(line_4)==1)&&(digitalRead(line_5)==1)&&(digitalRead(line_1)==1)&&(digitalRead(line_2)==1))
  {
    // đi thẳng
  }
  */
