//
// Created by isfanazha on 01/01/20.
//

#include "Arduino.h"
#include "Wire.h"
#include "SparkFun_MMA8452Q.h" // Library for MMA84520 sensor

#define SENSOR_1 1
#define SENSOR_2 2
#define SENSOR_3 3
#define SENSOR_4 4
#define SENSOR_5 5
#define SENSOR_6 6

void initSensor();

byte readRegister(uint8_t addr);

void multiplexerSelector(char x);

void getBMAData();

MMA8452Q mmaAccelero;

byte bmaAccelero[3];
int8_t xBMAData;
int8_t yBMAData;
int8_t zBMAData;


// input from multiplexer
int S0 = 5;
int S1 = 6;
int S2 = 7;

byte MMAData;

void setup() {
    Serial.begin(9600);
    Serial.println("Initializing program");

    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);

    Wire.begin();
    initSensor();

    Serial.println("Initialization has been completed");
}

void loop() {
    multiplexerSelector(SENSOR_1);

    Serial.print(mmaAccelero.getCalculatedX(), 3);
    Serial.print("   ");
    Serial.print(mmaAccelero.getCalculatedX(), 3);
    Serial.print("   ");
    Serial.print(mmaAccelero.getCalculatedX(), 3);

    Serial.print(" ||| ");

    multiplexerSelector(SENSOR_2);
//  accel.axes(axes);

    Serial.print(mmaAccelero.getCalculatedX(), 3);
    Serial.print("   ");
    Serial.print(mmaAccelero.getCalculatedX(), 3);
    Serial.print("   ");
    Serial.print(mmaAccelero.getCalculatedX(), 3);

    Serial.print(" ||| ");

    multiplexerSelector(SENSOR_3);
    getBMAData();

    Serial.print(xBMAData);
    Serial.print("   ");
    Serial.print(yBMAData);
    Serial.print("   ");
    Serial.print(zBMAData);

    Serial.print(" ||| ");

    multiplexerSelector(SENSOR_4);
    getBMAData();

    Serial.print(xBMAData);
    Serial.print("   ");
    Serial.print(yBMAData);
    Serial.print("   ");
    Serial.print(zBMAData);

    Serial.print(" ||| ");

    multiplexerSelector(SENSOR_5);
    getBMAData();

    Serial.print(xBMAData);
    Serial.print("   ");
    Serial.print(yBMAData);
    Serial.print("   ");
    Serial.print(zBMAData);

    Serial.print(" ||| ");

    multiplexerSelector(SENSOR_6);

    Serial.print(mmaAccelero.getCalculatedX(), 3);
    Serial.print("   ");
    Serial.print(mmaAccelero.getCalculatedX(), 3);
    Serial.print("   ");
    Serial.print(mmaAccelero.getCalculatedX(), 3);

    Serial.println();

    delay(100);
}

void initSensor() {
    int i = 0;
    for (char x = 1; x < 7; x++) {
        i++;
        multiplexerSelector(x);

        Serial.print("Initializing sensor ");
        Serial.println(i);

        if (x == SENSOR_3 || x == SENSOR_4 || x == SENSOR_5) {
            MMAData = readRegister(0x00);
            if (MMAData != 0xDD) {
                Serial.print("error while initiating sensor ");
                Serial.println(i);
                while (1);
            }
            Serial.print("Success init sensor ");
            Serial.println(i);
        } else {
            if (!mmaAccelero.begin()) {
                Serial.print("error while initiating sensor ");
                Serial.println(i);
                while (1);
            }

            Serial.print("Success init sensor ");
            Serial.println(i);
        }
        delay(1000);
    }
}

void multiplexerSelector(char x) {
    switch (x) {
        case SENSOR_1:
            digitalWrite(S0, HIGH);
            digitalWrite(S1, HIGH);
            digitalWrite(S2, HIGH);
            break;
        case SENSOR_2:
            digitalWrite(S0, HIGH);
            digitalWrite(S1, LOW);
            digitalWrite(S2, HIGH);
            break;

        case SENSOR_3:
            digitalWrite(S0, LOW);
            digitalWrite(S1, HIGH);
            digitalWrite(S2, HIGH);
            break;
        case SENSOR_4:
            digitalWrite(S0, LOW);
            digitalWrite(S1, LOW);
            digitalWrite(S2, HIGH);
            break;
        case SENSOR_5:
            digitalWrite(S0, LOW);
            digitalWrite(S1, HIGH);
            digitalWrite(S2, LOW);
            break;
        case SENSOR_6:
            digitalWrite(S0, HIGH);
            digitalWrite(S1, LOW);
            digitalWrite(S2, LOW);
            break;
    }
}

byte readRegister(uint8_t addr) {
    Wire.beginTransmission(0x0A);
    Wire.write(addr);
    Wire.endTransmission(false);
    Wire.requestFrom(0x0A, 1);

    if (!Wire.available()) {
        Serial.println("something error, please check connection in BMA sensor!");
        while (1);
    }

    return Wire.read();
}

void getBMAData() {
    Wire.beginTransmission(0x0A);
    Wire.write(0x04); //data x
    Wire.endTransmission();
    Wire.requestFrom(0x0A, 1);
    while (Wire.available()) // slave may send less than requested
    {
        bmaAccelero[0] = Wire.read(); // receive a byte as characte
    }
    xBMAData = (int8_t) bmaAccelero[0] >> 2;

    Wire.beginTransmission(0x0A); // address of the accelerometer
    // reset the accelerometer
    Wire.write(0x06); // Y data
    Wire.endTransmission();
    Wire.requestFrom(0x0A, 1); // request 6 bytes from slave device #2
    while (Wire.available())   // slave may send less than requested
    {
        bmaAccelero[1] = Wire.read(); // receive a byte as characte
    }
    yBMAData = (int8_t) bmaAccelero[1] >> 2;

    Wire.beginTransmission(0x0A); // address of the accelerometer
    // reset the accelerometer
    Wire.write(0x08); // Y data
    Wire.endTransmission();
    Wire.requestFrom(0x0A, 1); // request 6 bytes from slave device #2
    while (Wire.available())   // slave may send less than requested
    {
        bmaAccelero[2] = Wire.read(); // receive a byte as characte
    }
    zBMAData = (int8_t) bmaAccelero[2] >> 2;
}



