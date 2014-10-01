#include <Servo.h> 

const int baanEenLed = 11;
const int baanEenButton = 12;
const int baanTweeLed = 8;
const int baanTweeButton = 13;

Servo winnaarVlag; // variable om de servo te besturen
const int vlagPos = 90; // startpositie servo
const int servoPin = 9; // pin waar de servo aanhangt

const int startPin = 10;

const int groenPin = 3;
const int geel1Pin = 4;
const int geel2Pin = 5;
const int geel3Pin = 6;
const int roodPin = 7; 

int state = 0; // 0 = klaar voor aftellen, 1 = aftellen, 2 = rijden, 3 = winnaar bepaald

void setup() 
{ 
  pinMode(baanEenLed, OUTPUT); 
  pinMode(baanEenButton, INPUT); 
  pinMode(baanTweeLed, OUTPUT);
  pinMode(baanTweeButton, INPUT);
  
  winnaarVlag.attach(servoPin);

  pinMode(startPin, INPUT); 
  pinMode(groenPin, OUTPUT); 
  pinMode(geel1Pin, OUTPUT); 
  pinMode(geel2Pin, OUTPUT); 
  pinMode(geel3Pin, OUTPUT); 
  pinMode(roodPin, OUTPUT);

  reset();
}
 
void loop() 
{ 
  if (digitalRead(startPin) == HIGH) {
    if (state == 0) {
      countdown();
    } else {
      reset();
    }
  }
  
  if (state == 2) {
    if (digitalRead(baanEenButton) == HIGH) {
      allesUit();
      digitalWrite(baanEenLed, HIGH);
      winnaarVlag.write(180);
      state = 3;
    } else if (digitalRead(baanTweeButton) == HIGH) {
      allesUit();
      digitalWrite(baanTweeLed, HIGH);
      winnaarVlag.write(0);
      state = 3;
    }
  }
}

void reset() {
  allesUit();
  state = 0;
  winnaarVlag.write(vlagPos);
  
  digitalWrite(groenPin, HIGH);
  delay(300);
  digitalWrite(geel1Pin, HIGH);
  delay(300);
  digitalWrite(geel2Pin, HIGH);
  delay(300);
  digitalWrite(geel3Pin, HIGH);
  delay(300);
  digitalWrite(roodPin, HIGH);
  delay(300);
  
  allesUit();
  digitalWrite(groenPin, HIGH); // groene led laten branden: klaar voor startknop
} 

void countdown() {
  allesUit();
  
  state = 1;
  digitalWrite(roodPin, HIGH);
  delay(1000);
  digitalWrite(geel3Pin, HIGH);
  delay(1000);
  digitalWrite(geel2Pin, HIGH);
  delay(1000);
  digitalWrite(geel1Pin, HIGH);
  delay(1000);
  digitalWrite(groenPin, HIGH);
  state = 2;  
}

void allesUit() {
  digitalWrite(groenPin, LOW);
  digitalWrite(geel1Pin, LOW);
  digitalWrite(geel2Pin, LOW);
  digitalWrite(geel3Pin, LOW);
  digitalWrite(roodPin, LOW);
  digitalWrite(baanEenLed, LOW);
  digitalWrite(baanTweeLed, LOW);
}
