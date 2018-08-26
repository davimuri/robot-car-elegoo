//Line Tracking IO define
#define LT_R !digitalRead(10)
#define LT_M !digitalRead(4)
#define LT_L !digitalRead(2)

//motors
#define ENA 5 // controls left velocity
#define ENB 6 // controls right velocity
#define IN1 7 // left motor going forward
#define IN2 8 // left motor going backward
#define IN3 9 // right motor going backward
#define IN4 11 // right motor going forward

// logical (not actual) velocity defined to be as [MIN_SPEED, MAX_SPEED]
// actual velocity used in motors is [0, MAX_SPEED]
// motors support [0, 255] range but for PID we don't want 255 max speed
#define MAX_SPEED 150
#define MIN_SPEED -150
#define INITIAL_SPEED 100
#define LOGS_ON true

int currentSpeedRight;
int currentSpeedLeft;
float previousError;
float integral;
int previousLineTrackerPos;

// Kd > Kp > Ki because derivative < error < integral
float kd = 100;
float kp = 20;
float ki = 0.25;

void setup() {
  setupLineTracker();
  //setupMotors();
  initVariables();
}

void setupLineTracker() {
  Serial.begin(9600);
  pinMode(LT_R,INPUT);
  pinMode(LT_M,INPUT);
  pinMode(LT_L,INPUT);  
}

void setupMotors() {
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
}

void initVariables() {
  integral = 0;
  previousError = 0;
  currentSpeedRight = INITIAL_SPEED;
  currentSpeedLeft = INITIAL_SPEED;
}

void loop() {
  float pos = getLineTrackerPosition();
  float pid = calculatePID(pos, 0);
  calculateSpeed(pid);
  moveMotors(currentSpeedLeft, currentSpeedRight);
}

int getLineTrackerPosition() {
  int leftReading = LT_L;
  int centerReading = LT_M;
  int rightReading = LT_R;

  if (leftReading == LOW && centerReading == HIGH && rightReading == LOW) {
    previousLineTrackerPos = 0;
    return 0;
  } else if (leftReading == HIGH && centerReading == HIGH && rightReading == LOW) {
    previousLineTrackerPos = -1;
    return -1;
  } else if (leftReading == HIGH && centerReading == LOW && rightReading == LOW) {
    previousLineTrackerPos = -2;
    return -2;
  } else if (leftReading == LOW && centerReading == HIGH && rightReading == HIGH) {
    previousLineTrackerPos = 1;
    return 1;
  } else if (leftReading == LOW && centerReading == LOW && rightReading == HIGH) {
    previousLineTrackerPos = 2;
    return 2;
  } else {
    return previousLineTrackerPos;
  }
}

float calculatePID(float pos, float setValue) {
  float error = pos - setValue;
  float derivative = error - previousError;
  integral += error;
  previousError = error;

  if (error == 0 && derivative == 0) {
    //means output signal of PID converged to target signal
    //resets integral to zero and other control variables
    initVariables();
  }

  float pid = (error * kp) + (integral * ki) + (derivative * kd);

  if (LOGS_ON) {
    //Serial.println(error);
    //Serial.println(integral);
    char toPrint[43] = "";
    char value[10] = "";
    //error value to char array
    dtostrf(error, 10, 2, value);
    strcat(toPrint, value);
    strcat(toPrint, "|");
    dtostrf(integral, 10, 2, value);
    strcat(toPrint, value);
    strcat(toPrint, "|");
    dtostrf(derivative, 10, 2, value);
    strcat(toPrint, value);
    strcat(toPrint, "|");
    dtostrf(pid, 10, 2, value);
    strcat(toPrint, value);
    
    Serial.println(toPrint);
  }
  return pid;
}

void calculateSpeed(float delta) {
  int deltaInt = round(delta);

  //if car is at right (delta < 0), we need to turn left
  //increase right speed, decrease left speed
  //or if car is at left (delta > 0), we need to turn right
  //increase left speed, decrease right speed
  currentSpeedRight -= deltaInt;
  currentSpeedLeft += deltaInt;

  currentSpeedRight = constrain(currentSpeedRight, MIN_SPEED, MAX_SPEED);
  currentSpeedLeft = constrain(currentSpeedLeft, MIN_SPEED, MAX_SPEED);
}

void moveMotors(int leftSpeed, int rightSpeed) {
  int in1Signal, in2Signal, in3Signal, in4Signal;
  
  if (leftSpeed >= 0) {
    //left motors turning forwards
    in1Signal = HIGH;
    in2Signal = LOW;
  } else {
    //left motors turning backwards
    in1Signal = LOW;
    in2Signal = HIGH;
  }
  if (rightSpeed >= 0) {
    //right motors turning forwards
    in3Signal = LOW;
    in4Signal = HIGH;
  } else {
    //right motors turning backwards
    in3Signal = HIGH;
    in4Signal = LOW;
  }

  leftSpeed = abs(leftSpeed);
  rightSpeed = abs(rightSpeed);
  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);
  digitalWrite(IN1, in1Signal);
  digitalWrite(IN2, in2Signal);
  digitalWrite(IN3, in3Signal);
  digitalWrite(IN4, in4Signal);
}
