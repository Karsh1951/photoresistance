/*
Project 09.2:Light Following Car
*/ 
const int light_L_Pin = A6;   //define the pins of the left photoresistor to A6
const int light_R_Pin = A7;   //define the pins of the right photoresistor to A7
const int left_ctrl = 4;//define direction control pins of the left motor as D4 
const int left_pwm = 6;//define speed control pins of the left motor as D6 
const int right_ctrl = 2;//define the direction control pin of the right motor D2
const int right_pwm = 5;//define the speed control pin of the right motor D5
int left_light; 
int right_light;
const int servopin = 9;//define the pin of the servo asD9
int myangle;
int pulsewidth;

void setup(){
  Serial.begin(9600);
  pinMode(light_L_Pin, INPUT); //Set pins of the left photoresistor to INPUT
  pinMode(light_R_Pin, INPUT); //Set pins of the right photoresistor to INPUT
  pinMode(left_ctrl,OUTPUT);//Set the direction control pin of the left motor to OUTPUT
  pinMode(left_pwm,OUTPUT);//Set the PWM control speed of the left motor to OUTPUT
  pinMode(right_ctrl,OUTPUT);//Set the direction control pin of the right motor to OUTPUT
  pinMode(right_pwm,OUTPUT);//Set the PWM control speed of the right motor to OUTPUT
  servopulse(servopin,90);//set the initial angle of the servo to 90
  delay(300);
}

void loop(){
  left_light = analogRead(light_L_Pin);//read the value of the left photoresistor
  right_light = analogRead(light_R_Pin);//read the value of the right photoresistor
  Serial.print("left_light_value = ");
  Serial.println(left_light);
  Serial.print("right_light_value = ");
  Serial.println(right_light);
  if (left_light > 500 && right_light > 500) //range photoresistors can detect
  {  
    Car_front(); //go forward
  } 
  else if (left_light >500 && right_light <= 500)  //range photoresistors can detect
  {
    Car_left(); //turn left
  } 
  else if (left_light <= 500 && right_light > 500) //range photoresistors can detect
  {
    Car_right(); //turn right
  } 
  else  //if above conditions are not met
  {
    Car_Stop(); //stop
  }
}

void servopulse(int servopin,int myangle)//angles the servo run
{
  for(int i=0; i<20; i++)
  {
    pulsewidth = (myangle*11)+500;
    digitalWrite(servopin,HIGH);
    delayMicroseconds(pulsewidth);
    digitalWrite(servopin,LOW);
    delay(20-pulsewidth/1000);
  }  
}

void Car_front()
{
  digitalWrite(left_ctrl,LOW); //Set direction control pins of the left motor to LOW
  analogWrite(left_pwm,200); //Set the PWM control speed of the left motor to 200
  digitalWrite(right_ctrl,LOW); //set control pins of the right motor to LOW
  analogWrite(right_pwm,200); //Set the PWM control speed of the right motor to 200
}
void Car_left()
{
  digitalWrite(left_ctrl,HIGH); //set control pins of the left motor to HIGH
  analogWrite(left_pwm,200); //Set the PWM control speed of the left motor to 200
  digitalWrite(right_ctrl,LOW); //set control pins of the right motor to LOW
  analogWrite(right_pwm,200); //Set the PWM control speed of the right motor to 200;
}
void Car_right()
{
  digitalWrite(left_ctrl,LOW); //Set direction control pins of the left motor to LOW
  analogWrite(left_pwm,200); //Set the PWM control speed of the left motor to 200
  digitalWrite(right_ctrl,HIGH); //Set direction control pins of the right motor to HIGH
  analogWrite(right_pwm,200); //Set the PWM control speed of the right motor to 200
}
void Car_Stop()
{
  digitalWrite(left_ctrl,LOW);//Set direction control pins of the left motor to LOW
  analogWrite(left_pwm,0);//Set the PWM control speed of the left motor to 0
  digitalWrite(right_ctrl,LOW);//set control pins of the right motor to LOW
  analogWrite(right_pwm,0);//Set the PWM control speed of the right motor to 0
}