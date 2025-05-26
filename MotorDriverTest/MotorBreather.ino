// Motor A control pins
#define ENA PA0
#define IN1 PA2
#define IN2 PA3

// Motor B control pins
#define ENB PA1
#define IN3 PA4
#define IN4 PA5

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Stop motors initially
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  // Move FORWARD
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  // Ramp speed up
  for (int speed = 0; speed <= 255; speed += 5) {
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    delay(20); // adjust for smoothness
  }

  delay(500); // hold at full speed

  // Ramp speed down
  for (int speed = 255; speed >= 0; speed -= 5) {
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    delay(20);
  }

  delay(500);

  // Move REVERSE
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  // Ramp speed up
  for (int speed = 0; speed <= 255; speed += 5) {
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    delay(20);
  }

  delay(500); // hold at full reverse speed

  // Ramp speed down
  for (int speed = 255; speed >= 0; speed -= 5) {
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    delay(20);
  }

  delay(500);
}
