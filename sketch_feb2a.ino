/* =====================================
   SMART CAR USING 3 ULTRASONIC
   KELOMPOK 5
   ===================================== */

// ===== ULTRASONIC SENSOR =====
#define trigFront 2
#define echoFront 4
 
#define trigLeft 9
#define echoLeft 8

#define trigRight 6
#define echoRight 7

// ===== MOTOR DRIVER =====
#define motorA1 12   // Motor kiri
#define motorA2 13
#define motorB1 10   // Motor kanan
#define motorB2 11

#define enableA 3
#define enableB 5

/* =====================================
   VARIABLE
   ===================================== */
int distanceFront;
int distanceLeft;
int distanceRight;

const int safeDistance = 10; // cm
const int speedMotor = 110;

/* =====================================
   SETUP
   ===================================== */
void setup() {
  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);

  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);

  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);

  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);

  Serial.begin(9600);
}

/* =====================================
   MAIN LOOP
   ===================================== */
void loop() {

  distanceFront = readUltrasonic(trigFront, echoFront);
  distanceLeft  = readUltrasonic(trigLeft, echoLeft);
  distanceRight = readUltrasonic(trigRight, echoRight);

  Serial.print("F: "); Serial.print(distanceFront);
  Serial.print(" | L: "); Serial.print(distanceLeft);
  Serial.print(" | R: "); Serial.println(distanceRight);

  // ===== SMART AVOIDANCE LOGIC =====
  if (distanceFront > safeDistance && distanceRight > safeDistance && distanceLeft > safeDistance) {
    moveForward();
  } 
  else {
  
     if (distanceRight < safeDistance) {
      turnRight();
      
    }
    else if (distanceLeft < safeDistance) {
      turnLeft();
    }
    else {
      stopMotor();
    }
  }
}

/* =====================================
   ULTRASONIC FUNCTION
   ===================================== */
int readUltrasonic(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return 300;

  return duration * 0.034 / 2;
}

/* =====================================
   MOTOR CONTROL
   ===================================== */
void moveForward() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  analogWrite(enableA, speedMotor);
  analogWrite(enableB, speedMotor);
}

void turnLeft() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  analogWrite(enableA, speedMotor);
  analogWrite(enableB, speedMotor);
  delay(300);
}

void turnRight() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  analogWrite(enableA, speedMotor);
  analogWrite(enableB, speedMotor);
  delay(300);
}

void stopMotor() {
  analogWrite(enableA, 0);
  analogWrite(enableB, 0);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}