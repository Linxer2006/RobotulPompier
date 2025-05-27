#include <IRremote.h>
#include <Servo.h>
int motor1pin1 =2;
int motor1pin2 =3;
int motor2pin1 =4;
int motor2pin2 =5;
int control1=9;
int control2=10;
int flacara=6;
int dht11=8;
int viteza=100;
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0; 
IRrecv IR(11); // Im using the pin 7
decode_results results;
int buton=12;//0 apasat|| 1 liber
int k=0;
void setup(){
  Serial.begin(9600);
  IR.enableIRIn();
  pinMode(buton,INPUT_PULLUP);
  myservo.attach(13);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(control1, OUTPUT);
  pinMode(control2, OUTPUT);
  pinMode(flacara, INPUT);
  pinMode(dht11, INPUT);
}
void fata(int x){
  Serial.println("fata");
  analogWrite(control1, x);
  analogWrite(control2, x);
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  
}
void spate(int x){
  Serial.println("spate");
  analogWrite(control1, x);
  analogWrite(control2, x);
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  
}
void stanga(int x){
  Serial.println("stanga");
  analogWrite(control1, x);
  analogWrite(control2, x);
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  
}
void dreapta(int x){
  Serial.println("dreapta");
  analogWrite(control1, x);
  analogWrite(control2, x);
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  
}
void stop(){
  Serial.println("stop");
  analogWrite(control1, 0);
  analogWrite(control2, 0);
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
  
}
void extinctor()
{
  for(int i=0;i<=20;i++)
  {
      myservo.write(98);
      delay(100);
    while(digitalRead(buton)==1)
    {
      myservo.write(82);
    }
  }
  if(digitalRead(buton)==0)
    myservo.write(90);  
}
void loop(){
  if(digitalRead(buton)==1&&k==0)
  { 
    myservo.write(82); 
  }
  if(digitalRead(buton)==0)
    {
      myservo.write(90);
      k=1;
    }
  if (IR.decode()){
        if(IR.decodedIRData.decodedRawData==0xBA45FF00)
        {
          extinctor();
        }
        if(IR.decodedIRData.decodedRawData==0xE718FF00)
        {
          fata(viteza);
        }
        if(IR.decodedIRData.decodedRawData==0xAD52FF00)
        {
          spate(viteza);
        }
        if(IR.decodedIRData.decodedRawData==0xF708FF00)
        {
          stanga(viteza);
        }
        if(IR.decodedIRData.decodedRawData==0xA55AFF00)
        {
          dreapta(viteza);
        }
        if(IR.decodedIRData.decodedRawData==0xE31CFF00)
        {
          stop();
        }
        IR.resume();
  }
}
