const int soundPin = A0;
const int ldrPin = A1;

const int ch1 = 3;
const int ch2 = 5;
const int ch3 = 6;

const int buzzer = 9;

int clapCount = 0;
unsigned long lastClapTime = 0;

const int clapGap = 250;
const int windowTime = 1500;

int threshold = 550;
int lightThreshold = 500;

unsigned long lastLightToggle = 0;
const unsigned long lightBlinkInterval = 250;
bool lightState = false;

void setup() {
  pinMode(ch1, OUTPUT);
  pinMode(ch2, OUTPUT);
  pinMode(ch3, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  // ---------------- SERIAL COMMANDS ----------------
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd == "c") blink(ch1);
    else if (cmd == "cc") blink(ch2);
    else if (cmd == "ccc") blink(ch3);
    else if (cmd == "cccc") fastBlinkAll();
  }

  // ---------------- LIGHT SENSOR ----------------
  int lightValue = analogRead(ldrPin);
  bool isLight = (lightValue > lightThreshold);

  // ---------------- LIGHT BLINK MODE ----------------
  if (isLight) {
    if (millis() - lastLightToggle >= lightBlinkInterval) {
      lastLightToggle = millis();
      lightState = !lightState;

      digitalWrite(ch1, lightState);
      digitalWrite(ch2, lightState);
      digitalWrite(ch3, lightState);
      digitalWrite(buzzer, lightState);
    }
  } else {
    lightState = false;
    digitalWrite(ch1, LOW);
    digitalWrite(ch2, LOW);
    digitalWrite(ch3, LOW);
    digitalWrite(buzzer, LOW);
  }

  // ---------------- SOUND INPUT (IMPROVED) ----------------
  int soundValue = analogRead(soundPin);

  static int peakValue = 0;
  peakValue = max(peakValue, soundValue);

  if (peakValue > threshold) {

    if (millis() - lastClapTime > clapGap) {
      clapCount++;
      lastClapTime = millis();

      Serial.print("CLAP VALUE: ");
      Serial.println(peakValue);

      beep(40);
    }

    peakValue = 0;
  }

  // ---------------- AUTO ACTION ----------------
  if (millis() - lastClapTime > windowTime && clapCount > 0) {

    if (clapCount == 1) blink(ch1);
    else if (clapCount == 2) blink(ch2);
    else if (clapCount == 3) blink(ch3);
    else if (clapCount >= 4) fastBlinkAll();

    clapCount = 0;
  }
}

// ---------------- FUNCTIONS ----------------

void blink(int pin) {
  for (int i = 0; i < 5; i++) {
    digitalWrite(pin, HIGH);
    beep(80);
    delay(150);

    digitalWrite(pin, LOW);
    delay(150);
  }
}

void fastBlinkAll() {
  for (int i = 0; i < 10; i++) {
    digitalWrite(ch1, HIGH);
    digitalWrite(ch2, HIGH);
    digitalWrite(ch3, HIGH);

    beep(40);
    delay(60);

    digitalWrite(ch1, LOW);
    digitalWrite(ch2, LOW);
    digitalWrite(ch3, LOW);

    delay(60);
  }
}

void beep(int duration) {
  digitalWrite(buzzer, HIGH);
  delay(duration);
  digitalWrite(buzzer, LOW);
}