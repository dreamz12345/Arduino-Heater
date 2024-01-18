#include <EEPROM.h>
#include <OneWire.h>
#include <LiquidCrystal.h>
#include <DallasTemperature.h>

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
OneWire oneWire(A1);

DallasTemperatures sensors(&oneWire);
DeviceAdress airSensor = (0x28, 0xD9, 0xE5, 0x9A, 0x90, 0x21, 0x6, 0x4E);
DeviceAdress floorSensor = (0x28, 0x68, 0x22, 0x7A, 0x95, 0x21, 0x6, 0x71);
DeviceAdress heaterSensor = (0x28, 0xDE, 0x9C, 0x90, 0x90, 0x21, 0x6, 0xA5);
DeviceAdress outsideSensor = (0x28, 0xDC, 0xC1, 0x90, 0x90, 0x21, 0x6, 0xDD);

#define led1 2 //pin2
#define pump 3 //pin3

float airSensorTemp;
float floorSensorTemp;
float heaterSensorTemp;
float outsideSensorTemp;

float airTargetSensorTemp = 27;
float floorTargetSensorTemp = 28;
float heaterTargetSensorTemp = 29;
float outsideTargetSensorTemp = 30;

void setup() {
    sensors.begin();
    sensors.setResolution(airSensor, 9);
    sensors.setResolution(floorSensor, 9);
    sensors.setResolution(heaterSensor, 9);
    sensors.setResolution(outsideSensor, 9);
    pinMode(led1, OUTPUT);
    pinMode(pump, OUTPUT);
    lcd.begin(16, 2);
    printHello();
}

void loop() {
    getTemperatureFromSensors();
    buttons();
    blinkLed();
    setPumpState();
    printDefaultScreen();
}

void getTemperaturesFromSensors() {
    sensors.requestTemperatures();
    airSensorTemp = sensors.GetTempC(airSensor);
    floorSensorTemp = sensors.GetTempC(floorSensor);
    heaterSensorTemp = sensors.GetTempC(heaterSensor);
    outsideSensorTemp = sensors.GetTempC(outsideSensor);
}

void printDefaultScreen() {
    printTempFromSensors();
    printPumpState();
}

void printPumpState() {
    lcd.setCursor(15, 0);
    if (digitalRead(pump) == HIGH) {lcd.print("1");}
    else {lcd.print("0");}
}

void printTempFromSensors() {
    lcd.setCursor(0, 0);  lcd.print("A");
    lcd.setCursor(2, 0);  lcd.print(airSensorTemp, 1);
    lcd.setCursor(8, 0);  lcd.print("F");
    lcd.setCursor(10, 0); lcd.print(floorSensorTemp, 1);
    lcd.setCursor(0, 1);  lcd.print("H");
    lcd.setCursor(2, 1);  lcd.print(heaterSensorTemp, 1);
    lcd.setCursor(8, 1);  lcd.print("O");
    lcd.setCursor(10, 1); lcd.print(outsideSensorTemp, 1);
}

void printHello() {
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("HeaterControler");
    lcd.setCursor(0, 1); lcd.print("24-7-2023");
    delay(2000);
    lcd.clear();
}

bool pumpState = 0;

void setPumpState() {
    pumpState = 1;
    if (airSensorTemp > airTargetSensorTemp) {pumpState = 0;}
    if (floorSensorTemp > floorTargetSensorTemp) {pumpState = 0;}
    if (outsideSensorTemp > outsideTargetSensorTemp) {pumpState = 0;}

    if (pumpState == 1) {digitalWrite(pump, HIGH);}
    else {digitalWrite(pump, LOW);}
}

bool isBlinkOn = 0;

void makeCursorBlink() {
    if (isBlinkOn == 0) {
        lcd.blink();
        isBlinkOn = 1;
    }
    else {
        lcd.noBlink();
        isBlinkOn = 0;
    }
}

bool isLeftButtonPressed = 0;
bool isUpButtonPressed = 0;
bool isRightButtonPressed = 0;
bool isDownButtonPressed = 0;
bool isSelectButtonPressed = 0;

int buttons() {
    double buttonPressed = analogRead(A0);

    if (buttonPressed < 65) {
        isRightButtonPressed = 1;
        return 0;
    }

    if (buttonPressed >= 65 && buttonPressed < 210) {
        isUpButtonPressed = 1;
        return 0;
    }

    if (buttonPressed >= 210 && buttonPressed < 390) {
        isDownButtonPressed = 1;
        return 0;
    }

    if (buttonPressed >= 390 && buttonPressed < 600) {
        isLeftButtonPressed = 1;
        return 0;
    }

    if (buttonPressed >= 600 && buttonPressed < 850) {
        isSelectButtonPressed = 1;
        return 0;
    }

    if (buttonPressed >= 850) {
        isLeftButtonPressed = 0;
        isRightButtonPressed = 0;
        isUpButtonPressed = 0;
        isDownButtonPressed = 0;
        isSelectButtonPressed = 0;
        return 0;
    }
}

unsigned long timeNow = 0;
unsigned long previousTime = 0;
bool ledState1 = LOW;

void blinkLed() {
    timeNow = milis();
    if (timeNow - previousTime >= 700UL) {
        previousTime = timeNow;
        ledState1 = !ledState1;
        digitalWrite(led1, ledState1);
    }
}

