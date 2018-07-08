// Modified version of Line_tracking_car sketch from Elegoo 
// Downloaded from https://www.elegoo.com/tutorial/Elegoo%20Smart%20Robot%20Car%20Kit%20V3.0.2018.06.06.zip

//Line Tracking IO define
#define LT_R !digitalRead(10)
#define LT_M !digitalRead(4)
#define LT_L !digitalRead(2)

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

#define CAR_SPEED 150
#define READING_LT_R 1
#define READING_LT_L -1

int previousReading = 0;

void setup(){
  Serial.begin(9600);
  pinMode(LT_R,INPUT);
  pinMode(LT_M,INPUT);
  pinMode(LT_L,INPUT);
}

void loop() {
  if(LT_M){
    forward();
  }
  else if(LT_R) {
    previousReading = READING_LT_R;
    right();
    while(LT_R);                             
  }   
  else if(LT_L) {
    previousReading = READING_LT_L;
    left();
    while(LT_L);  
  } else if (previousReading == READING_LT_R){
    right();
  } else if (previousReading == READING_LT_L){
    left();
  }
}

void forward(){
  analogWrite(ENA, CAR_SPEED);
  analogWrite(ENB, CAR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go forward!");
}

void back(){
  analogWrite(ENA, CAR_SPEED);
  analogWrite(ENB, CAR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("go back!");
}

void left(){
  analogWrite(ENA, CAR_SPEED);
  analogWrite(ENB, CAR_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go left!");
}

void right(){
  analogWrite(ENA, CAR_SPEED);
  analogWrite(ENB, CAR_SPEED);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  Serial.println("go right!");
} 

void stop(){
   digitalWrite(ENA, LOW);
   digitalWrite(ENB, LOW);
   Serial.println("Stop!");
} 

