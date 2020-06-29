
#include <IRremote.h> //Bu kütüphaneyi indirmeyi unutmayın. - Don't forget to download this library
#include <Servo.h>

const int MotorB1 = 3; //B = Sol Motor - B = Left Motor
const int MotorB2 = 4;
const int MotorA1 = 5; //A = Sağ Motor - A = Right Motor
const int MotorA2 = 6;

int servoPin = 7; //Servo Motor bağlantısı-connection
int RECV_PIN = 2; //IR Alıcı sinyal pini - IR Receiver Signal Pin
int ledpin = 8; //Bu değişken şimdilik gereksiz. - This variable is useless for now

IRrecv irrecv(RECV_PIN);
decode_results results;

int servocount; //Servonun dönmesi için değerler - Values for the servo to rotate

#define SAG 256914 //Kumandaya göre değişecektir, burayı değiştirin. - These will vary according to the remote control, please change these
#define SOL 912274
#define ILERI 650130
#define GERI 387986
#define TARETSAG 166726
#define TARETSOL 240530
#define ISIKLAR 117650

Servo taretmotor; //The servo motor

int seciliyon; //Tankın ilerleyeceği yolu belirler - Determines the way that the tank will move

int taretyon = 0; //Taretin ilerleyeceği yönü belirler - Determines the way that the turret will rotate

bool isikdurum; //Şimdilik gereksiz - Useless for now

void setup() {
  // put your setup code here, to run once:
  pinMode(MotorB1, OUTPUT);
  pinMode(MotorB2, OUTPUT);
  pinMode(MotorA1, OUTPUT);
  pinMode(MotorA2, OUTPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(ledpin, OUTPUT);
  taretmotor.attach(servoPin);
irrecv.enableIRIn();
Serial.begin(9600);
taretmotor.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
if(irrecv.decode(&results))
{
  if(results.value == SAG) //right
  {
    seciliyon = 2;
  }else if(results.value == SOL) //left
  {
   seciliyon = 3;
    
  }else if(results.value == ILERI) //forward
  {
    seciliyon = 1;
  }else if(results.value == GERI)  //back
  {
    seciliyon = 4;
  }else if(results.value == TARETSAG) //turret-right
  {
    taretyon = 1;
  }else if(results.value == TARETSOL) //turret-left
  {
    taretyon = 2;
  }else if(results.value == ISIKLAR) //useless for now - şimdilik gereksiz
  {
   if(isikdurum == true)
   {
    isikdurum = false; 
   }else if(isikdurum == false)
   {
    isikdurum = true;
   }
  }
 
  irrecv.resume();
}else
{
  seciliyon = 5;
  taretyon = 0;
}

motorHareket(seciliyon);
ServoHareket(taretyon);
isikDurum(isikdurum);

delay(200);
}

void isikDurum(bool durum)
{
 if(durum == true)
 {
   
 }
}
void motorHareket(int yon)
{
  if(yon == 1) //ileri - forwards
  {
    Serial.println("ileri");
    digitalWrite(MotorB1, LOW);
    digitalWrite(MotorB2, HIGH);
    digitalWrite(MotorA1, LOW);
    digitalWrite(MotorA2, HIGH);
  }else if(yon == 2) //sağ - right
  {
    Serial.println("sağ");
    digitalWrite(MotorB1, LOW);
    digitalWrite(MotorB2, HIGH); 
    digitalWrite(MotorA1, HIGH);
    digitalWrite(MotorA2, LOW);

  }else if(yon == 3)
  {
       Serial.println("sol"); //left
    digitalWrite(MotorB1, HIGH);
    digitalWrite(MotorB2, LOW);
    digitalWrite(MotorA1, LOW);
    digitalWrite(MotorA2, HIGH); 

  }else if(yon == 4) //Geri
  {
       Serial.println("geri"); //backward
    digitalWrite(MotorB1, HIGH);
    digitalWrite(MotorB2, LOW);
    digitalWrite(MotorA1, HIGH);
    digitalWrite(MotorA2, LOW);
   
  }else
  {
       Serial.println("boş"); //idle
   digitalWrite(MotorB1, LOW);
    digitalWrite(MotorB2, LOW);
    digitalWrite(MotorA1, LOW);
    digitalWrite(MotorA2, LOW);
  }
}

void ServoHareket(int yon)
{
  if(yon == 1) //sağ - right
  {
   
      servocount = 0;
    
    taretmotor.write(servocount);
  }else if(yon == 2) //left - sol
  {
     servocount = 180;
     
    taretmotor.write(servocount);
  }else
  {
    taretmotor.write(90);
  }
  
  Serial.println(servocount);
}
