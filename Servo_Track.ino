 #include <Servo.h>

Servo myServo;
int potPin = A0;
int buttonPin = 2;

int potValue;
int angle;
int lockedAngle = 0;
bool isLocked = false;
bool lastButtonState = HIGH;

void setup() {
  myServo.attach(9);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);

  // Detect the moment the button is pressed (transition from HIGH to LOW)
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    isLocked = !isLocked;      // toggle: unlocked -> locked, or locked -> unlocked
    if (isLocked) {
      lockedAngle = angle;     // save current angle only when newly locking
    }
    delay(50);                 // simple debounce
  }

  lastButtonState = currentButtonState;

  if (isLocked) {
    myServo.write(lockedAngle);
    Serial.print("LOCKED at angle: ");
    Serial.println(lockedAngle);
  } else {
    potValue = analogRead(potPin);
    angle = map(potValue, 0, 1023, 0, 180);
    myServo.write(angle);
    Serial.print("Manual mode -> angle: ");
    Serial.println(angle);
  }

  delay(15);
}