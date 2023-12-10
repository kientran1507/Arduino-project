#include <RBDdimmer.h>

#define USE_SERIAL Serial

const int STRIP_LED = 3;
const int MOTION_SENSOR = 4;
const int ZEROCROSS = 2;
const int SOUND_SENSOR = A0;
const int sound_threshold = 700;
int power = 0;
int sound_level = 0;
dimmerLamp dimmer(STRIP_LED);

unsigned long previousMillis = 0;
unsigned long interval = 180000;  // Time to wait after the last clap to turn off (milliseconds)
unsigned long currentMillis;

unsigned long motionFlagTime = 0;
unsigned long motionFlagDuration = 3000;  // Time duration for the motion flag to stay on (milliseconds)

bool motionFlag = false;
bool isLightOn = false;
bool clapEnabled = true;
unsigned long minOnTime = 90000;  // Minimum on-time before allowing clap again (milliseconds)
unsigned long lightOnStartTime = 0;

void setup() {
  USE_SERIAL.begin(9600);
  dimmer.begin(NORMAL_MODE, ON);  // Start with the light on
  pinMode(MOTION_SENSOR, INPUT);
  pinMode(STRIP_LED, OUTPUT);
  analogWrite(STRIP_LED, 0);
}

void loop() {
  currentMillis = millis();

  // Check if sound is detected
  sound_level = analogRead(SOUND_SENSOR);

  // Check if motion is detected
  bool motionDetected = digitalRead(MOTION_SENSOR) == HIGH;

  // If motion is detected, set the motionFlag and record the time
  if (motionDetected) {
    motionFlag = true;
    USE_SERIAL.println("Motion flag time started");
    motionFlagTime = currentMillis;
  }

  // If a clap is detected (sound level exceeds the threshold)
  if (sound_level > sound_threshold) {
    USE_SERIAL.println("Clap detected");

    // If the light is off and there is motion, turn on the light
    if (!isLightOn && motionFlag) {
      USE_SERIAL.println("Turning on");
      TurnOn();
      isLightOn = true;
      clapEnabled = false;
      lightOnStartTime = currentMillis;
    } else if (isLightOn) {
      // If the light is on, check if the minimum on-time has passed before allowing clap again
      if (currentMillis - lightOnStartTime >= minOnTime) {
        clapEnabled = true;
        USE_SERIAL.println("Clap enabled");
      }

      // If the light is on and clap is enabled, turn it off
      if (clapEnabled) {
        USE_SERIAL.println("Turning off");
        TurnOff();
        isLightOn = false;
        clapEnabled = false;
      }
    }

    // Check if it's time to turn off the motionFlag
    if (currentMillis - motionFlagTime >= motionFlagDuration) {
      USE_SERIAL.println("Motion flag time finished");
      motionFlag = false;
    }

    // Reset the timer
    previousMillis = currentMillis;
  }

  // Check if it's time to turn off the light when there's no more motion after the clap
  if (isLightOn && !motionDetected && (currentMillis - previousMillis >= interval)) {
    USE_SERIAL.println("Time finished - turning off");
    TurnOff();
    isLightOn = false;
    clapEnabled = false;
  }
}

void TurnOn() {
  for (power = 0; power <= 80; power += 2) {
    dimmer.setPower(power);
    USE_SERIAL.print("lampValue -> ");
    USE_SERIAL.print(dimmer.getPower());
    USE_SERIAL.println("%");
    delay(25);
  }
}

void TurnOff() {
  for (power = 80; power >= 0; power -= 5) {
    dimmer.setPower(power);
    USE_SERIAL.print("lampValue -> ");
    USE_SERIAL.print(dimmer.getPower());
    USE_SERIAL.println("%");
    delay(25);
  }
}
