#include <Servo.h>
Servo servo;

int time = 90;

//Servo Limits
int minimum = 1000;
int mid = 1500;
int maximum = 2000;

//Logic and Loop Control Variabls
boolean goTimer = 0;
boolean repeatStop = 0;

//Pin Assignment
int servopin = 9; //Servo control pin
int sevSeg_1 = 10; //E
int sevSeg_2 = 11; //D
int sevSeg_3 = 12; //DP
int sevSeg_4 = 13; //C
int sevSeg_5 = 7;/ /G
int sevSeg_7 = A1; //B
int sevSeg_8 = A2; //Char 2
int sevSeg_9 = A3; //Char 3
int sevSeg_10 = A4; //F
int sevSeg_11 = A5; //A

void setup(){
  sei();                    // Enable global interrupts
  EIMSK |= (1 << INT0);     // Enable external interrupt INT0
  EICRA |= (1 << ISC01);
   
  //Initialize seven segment pins
  pinMode(sevSeg_1, OUTPUT);
  pinMode(sevSeg_2, OUTPUT);
  pinMode(sevSeg_3, OUTPUT); 
  pinMode(sevSeg_4, OUTPUT); 
  pinMode(sevSeg_5, OUTPUT); 
  pinMode(sevSeg_7, OUTPUT); 
  pinMode(sevSeg_8, OUTPUT); 
  pinMode(sevSeg_9, OUTPUT); 
  pinMode(sevSeg_10, OUTPUT); 
  pinMode(sevSeg_11, OUTPUT);  
   
  //Initialize Button Interrupt
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  attachInterrupt(0, activateTimer, FALLING);
  
  //Initialize Servo
  servo.attach(servopin);
  
  //Start State
  sevSeg_Off();
  middleClaw();
  delay(3000);
  closeClaw();
}

void loop(){
  if(goTimer == 1 && repeatStop == 0){
    for(int i = time; i >= 0; i--){
      int dig3 = floor(i/10);
      int dig2 = i%10;
      
      for(int j = 250; j >= 0; j--){
        if(dig3 != 0){
        sevSeg_Write(dig3, 3);}
        else{digitalWrite(sevSeg_9, HIGH);} //else write zero
        delay(2);
       
        sevSeg_Write(dig2, 2);  
        delay(2);
      }
    
      if(i == 0){
        openClaw();
        repeatStop = 1;
      }
    }
  }
  if(repeatStop == 1){
    sevSeg_Write(0,3);
    delay(100);
    sevSeg_Write(0,2);
    delay(100);
  }  
}
void sevSeg_Write(int num, int dig){
  if(num == 0){
    digitalWrite(sevSeg_1, HIGH); //E
    digitalWrite(sevSeg_2, HIGH); //D
    digitalWrite(sevSeg_3, LOW); //DP
    digitalWrite(sevSeg_4, HIGH); //C
    digitalWrite(sevSeg_5, LOW); //G
    digitalWrite(sevSeg_7, HIGH); //B
    if(dig == 2){
      digitalWrite(sevSeg_8, LOW);
      digitalWrite(sevSeg_9, HIGH);} //Char 2
    if(dig ==3){
      digitalWrite(sevSeg_8, HIGH);
      digitalWrite(sevSeg_9, LOW);} //Char 3
    digitalWrite(sevSeg_10,HIGH); //F
    digitalWrite(sevSeg_11,HIGH); //A 
  } 
  else if(num == 1){
    digitalWrite(sevSeg_1, LOW); //E
    digitalWrite(sevSeg_2, LOW); //D
    digitalWrite(sevSeg_3, LOW); //DP
    digitalWrite(sevSeg_4, HIGH); //C
    digitalWrite(sevSeg_5, LOW); //G
    digitalWrite(sevSeg_7, HIGH); //B
    if(dig == 2){
      digitalWrite(sevSeg_8, LOW);
      digitalWrite(sevSeg_9, HIGH);} //Char 2
    if(dig ==3){
      digitalWrite(sevSeg_8, HIGH);
      digitalWrite(sevSeg_9, LOW);} //Char 3
    digitalWrite(sevSeg_10,LOW); //F
    digitalWrite(sevSeg_11,LOW); //A 
  } 
  else if(num == 2){
    digitalWrite(sevSeg_1, HIGH); //E
    digitalWrite(sevSeg_2, HIGH); //D
    digitalWrite(sevSeg_3, LOW); //DP
    digitalWrite(sevSeg_4, LOW); //C
    digitalWrite(sevSeg_5, HIGH); //G
    digitalWrite(sevSeg_7, HIGH); //B
    if(dig == 2){
      digitalWrite(sevSeg_8, LOW);
      digitalWrite(sevSeg_9, HIGH);} //Char 2
    if(dig ==3){
      digitalWrite(sevSeg_8, HIGH);
      digitalWrite(sevSeg_9, LOW);} //Char 3
    digitalWrite(sevSeg_10, LOW); //F
    digitalWrite(sevSeg_11, HIGH); //A 
  }
  else if(num == 3){
    digitalWrite(sevSeg_1, LOW); //E
    digitalWrite(sevSeg_2, HIGH); //D
    digitalWrite(sevSeg_3, LOW); //DP
    digitalWrite(sevSeg_4, HIGH); //C
    digitalWrite(sevSeg_5, HIGH); //G
    digitalWrite(sevSeg_7, HIGH); //B
    if(dig == 2){
      digitalWrite(sevSeg_8, LOW);
      digitalWrite(sevSeg_9, HIGH);} //Char 2
    if(dig ==3){
      digitalWrite(sevSeg_8, HIGH);
      digitalWrite(sevSeg_9, LOW);} //Char 3
    digitalWrite(sevSeg_10,LOW); //F
    digitalWrite(sevSeg_11,HIGH); //A 
  } 
  else if(num == 4){
    digitalWrite(sevSeg_1, LOW); //E
    digitalWrite(sevSeg_2, LOW); //D
    digitalWrite(sevSeg_3, LOW); //DP
    digitalWrite(sevSeg_4, HIGH); //C
    digitalWrite(sevSeg_5, HIGH); //G
    digitalWrite(sevSeg_7, HIGH); //B
    if(dig == 2){
      digitalWrite(sevSeg_8, LOW);
      digitalWrite(sevSeg_9, HIGH);} //Char 2
    if(dig ==3){
      digitalWrite(sevSeg_8, HIGH);
      digitalWrite(sevSeg_9, LOW);} //Char 3
    digitalWrite(sevSeg_10,HIGH); //F
    digitalWrite(sevSeg_11,LOW); //A
  } 
  else if(num == 5){
    digitalWrite(sevSeg_1, LOW); //E
    digitalWrite(sevSeg_2, HIGH); //D
    digitalWrite(sevSeg_3, LOW); //DP
    digitalWrite(sevSeg_4, HIGH); //C
    digitalWrite(sevSeg_5, HIGH); //G
    digitalWrite(sevSeg_7, LOW); //B
    if(dig == 2){
      digitalWrite(sevSeg_8, LOW);
      digitalWrite(sevSeg_9, HIGH);} //Char 2
    if(dig ==3){
      digitalWrite(sevSeg_8, HIGH);
      digitalWrite(sevSeg_9, LOW);} //Char 3
    digitalWrite(sevSeg_10,HIGH); //F
    digitalWrite(sevSeg_11,HIGH); //A
  } 
  else if(num == 6){
    digitalWrite(sevSeg_1, HIGH); //E
    digitalWrite(sevSeg_2, HIGH); //D
    digitalWrite(sevSeg_3, LOW); //DP
    digitalWrite(sevSeg_4, HIGH); //C
    digitalWrite(sevSeg_5, HIGH); //G
    digitalWrite(sevSeg_7, LOW); //B
    if(dig == 2){
      digitalWrite(sevSeg_8, LOW);
      digitalWrite(sevSeg_9, HIGH);} //Char 2
    if(dig ==3){
      digitalWrite(sevSeg_8, HIGH);
      digitalWrite(sevSeg_9, LOW);} //Char 3
    digitalWrite(sevSeg_10,HIGH); //F
    digitalWrite(sevSeg_11,HIGH); //A
  } 
  else if(num == 7){
    digitalWrite(sevSeg_1, LOW); //E
    digitalWrite(sevSeg_2, LOW); //D
    digitalWrite(sevSeg_3, LOW); //DP
    digitalWrite(sevSeg_4, HIGH); //C
    digitalWrite(sevSeg_5, LOW); //G
    digitalWrite(sevSeg_7, HIGH); //B
    if(dig == 2){
      digitalWrite(sevSeg_8, LOW);
      digitalWrite(sevSeg_9, HIGH);} //Char 2
    if(dig ==3){
      digitalWrite(sevSeg_8, HIGH);
      digitalWrite(sevSeg_9, LOW);} //Char 3
    digitalWrite(sevSeg_10, LOW); //F
    digitalWrite(sevSeg_11, HIGH); //A
  } 
  else if(num == 8){
        digitalWrite(sevSeg_1, HIGH); //E
    digitalWrite(sevSeg_2, HIGH); //D
    digitalWrite(sevSeg_3, LOW); //DP
    digitalWrite(sevSeg_4, HIGH); //C
    digitalWrite(sevSeg_5, HIGH); //G
    digitalWrite(sevSeg_7, HIGH); //B
    if(dig == 2){
      digitalWrite(sevSeg_8, LOW);
      digitalWrite(sevSeg_9, HIGH);} //Char 2
    if(dig ==3){
      digitalWrite(sevSeg_8, HIGH);
      digitalWrite(sevSeg_9, LOW);} //Char 3
    digitalWrite(sevSeg_10,HIGH); //F
    digitalWrite(sevSeg_11,HIGH); //A
  } 
  else if(num == 9){
    digitalWrite(sevSeg_1, LOW); //E
    digitalWrite(sevSeg_2, HIGH); //D
    digitalWrite(sevSeg_3, LOW); //DP
    digitalWrite(sevSeg_4, HIGH); //C
    digitalWrite(sevSeg_5, HIGH); //G
    digitalWrite(sevSeg_7, HIGH); //B
    if(dig == 2){
      digitalWrite(sevSeg_8, LOW);
      digitalWrite(sevSeg_9, HIGH);} //Char 2
    if(dig ==3){
      digitalWrite(sevSeg_8, HIGH);
      digitalWrite(sevSeg_9, LOW);} //Char 3
    digitalWrite(sevSeg_10,HIGH); //F
    digitalWrite(sevSeg_11,HIGH); //A
  }   
}

void sevSeg_On(){
  digitalWrite(sevSeg_1, HIGH); //E
  digitalWrite(sevSeg_2, HIGH); //D
  digitalWrite(sevSeg_3, HIGH); //DP
  digitalWrite(sevSeg_4, HIGH); //C
  digitalWrite(sevSeg_5, HIGH); //G
  digitalWrite(sevSeg_7, HIGH); //B
  digitalWrite(sevSeg_8, LOW); //Char 2
  digitalWrite(sevSeg_9, LOW); //Char 3
  digitalWrite(sevSeg_10,HIGH); //F
  digitalWrite(sevSeg_11,HIGH); //A   
}

void sevSeg_Off(){
  digitalWrite(sevSeg_1, HIGH); //E
  digitalWrite(sevSeg_2, HIGH); //D
  digitalWrite(sevSeg_3, HIGH); //DP
  digitalWrite(sevSeg_4, HIGH); //C
  digitalWrite(sevSeg_5, HIGH); //G
  digitalWrite(sevSeg_7, HIGH); //B
  digitalWrite(sevSeg_8, HIGH); //Char 2
  digitalWrite(sevSeg_9, HIGH); //Char 3
  digitalWrite(sevSeg_10,HIGH); //F
  digitalWrite(sevSeg_11,HIGH); //A   
}

void closeClaw(){
  servo.writeMicroseconds(maximum-150);
}

void middleClaw(){
  servo.writeMicroseconds(mid);
}

void openClaw(){
  servo.writeMicroseconds(minimum+200);
}

void activateTimer(){
  goTimer = 1;
}

ISR(EXT_INT0_vect){
    goTimer = 1;
} A       AAAQX
