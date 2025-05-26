// Motor A control pins
#define ENA PA0
#define IN1 PA2
#define IN2 PA3

// Motor B control pins
#define ENB PA1
#define IN3 PA4
#define IN4 PA5

void setup() {
  // Set motor control pins as output
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Initialize motors to stop
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  // Move both motors forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  // Set motor speeds (0 - 255)
  analogWrite(ENA, 200); // Motor A speed
  analogWrite(ENB, 140); // Motor B speed

  delay(3000); // run for 3 seconds

  // Stop motors
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  delay(2000); // wait for 2 seconds
}
