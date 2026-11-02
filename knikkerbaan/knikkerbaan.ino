#include "src/PCA9685/PCA9685.h"

// globale variabelen
int geteldeKnikkers = 0;
unsigned long huidigeTijd = 0;
unsigned long laatsteSerialPrintTijd = 0;

// toestand(en)
const int TOESTAND_SERIAL_PRINT_NU = 1;
const int TOESTAND_SERIAL_PRINT_WACHT = 0;
int toestandSerial = TOESTAND_SERIAL_PRINT_WACHT;


// constanten voor pinnen
const int TELLERPIN = 3;

// overige constanten
const int SERIAL_PRINT_INTERVAL = 1000;

// servodriver stuurt de servo's aan
ServoDriver servodriver;

void setup() {
  // maak servodriver klaar voor gebruik
  Wire.begin();
  servodriver.init(0x7f);

  // initieer seriële poort voor berichtjes
  Serial.begin(9600);

  // stel de digitale pin voor de teller in als input
  pinMode(TELLERPIN, INPUT);
}

void loop() {
  // lees sensoren uit
  huidigeTijd = millis();

  // verander toestanden op basis van sensoren
  if (huidigeTijd - laatsteSerialPrintTijd > SERIAL_PRINT_INTERVAL) {
    toestandSerial = TOESTAND_SERIAL_PRINT_NU;
    laatsteSerialPrintTijd = millis();
  }

  // pas actuatoren aan
  if (toestandSerial == TOESTAND_SERIAL_PRINT_NU) {
    Serial.print("getelde knikkers: ");
    Serial.println(geteldeKnikkers);
  }

  // verander toestand indien een actuator maar eenmalig iets moet doen
  if (toestandSerial == TOESTAND_SERIAL_PRINT_NU) {
    toestandSerial = TOESTAND_SERIAL_PRINT_WACHT;
  }
}