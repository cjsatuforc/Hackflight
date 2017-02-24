/*
   board.cpp : implementation of board-specific routines

   This implemenation is for Teensy 3.1 / 3.2 with MPU9250 IMU. 

   MPU9250 code adapted from https://github.com/kriswiner/MPU-9250

   This file is part of Hackflight.

   Hackflight is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   Hackflight is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with Hackflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <math.h>
#include <stdint.h>
#include <stdarg.h>

#include <Arduino.h>

// https://github.com/simondlevy/SpektrumDSM
#include <SpektrumDSM.h>
static SpektrumDSM2048 rx;

// https://github.com/bolderflight/MPU9250
// https://www.tindie.com/products/onehorse/mpu9250-teensy-3x-add-on-shields/ (we're using micro shield)
#include <MPU9250.h>

#include "board.hpp"
#include "rc.hpp"

// an MPU9250 object with its I2C address 
// of 0x68 (ADDR to GRND) and on Teensy bus 0
// using pins 16 and 17 instead of 18 and 19
// and internal pullups instead of external.
MPU9250 imu(0x68, 1, I2C_PINS_29_30, I2C_PULLUP_INT);

void Board::dump(char * msg)
{
    for (char * c = msg; *c; c++)
        Serial.write(*c);
}

void Board::delayMilliseconds(uint32_t msec)
{
    delay(msec);
}

uint32_t Board::getMicros()
{
    return micros();
}

void Board::imuInit(uint16_t & acc1G, float & gyroScale)
{
    // wake up device
    imu.begin(ACCEL_RANGE_8G,GYRO_RANGE_2000DPS);
 
    // Accel scale 8g (4096 LSB/g)
    acc1G = 4096;

    // 16.4 dps/lsb scalefactor for all Invensense devices
    gyroScale = (1.0f / 16.4f) * (M_PI / 180.0f);
}

void Board::imuRead(int16_t accADC[3], int16_t gyroADC[3])
{
    imu.getMotion6Counts(&accADC[0], &accADC[1], &accADC[2], &gyroADC[0], &gyroADC[1], &gyroADC[2]);
}

void Board::init(uint32_t & looptimeMicroseconds, uint32_t & calibratingGyroMsec)
{
  
    // Set up LED
    pinMode(13, OUTPUT);

    // Set ADO low to guarantee 0x68 address
    digitalWrite(24, LOW);

    // Set up serial communication over USB
    Serial.begin(115200);

    // Use default hardware loop times
    looptimeMicroseconds = Board::DEFAULT_IMU_LOOPTIME_USEC; 
    calibratingGyroMsec  = Board::DEFAULT_GYRO_CALIBRATION_MSEC;
}


void Board::ledGreenOff(void)
{
    digitalWrite(13, LOW);
}

void Board::ledGreenOn(void)
{
    digitalWrite(13, HIGH);
}

void Board::ledRedOff(void)
{
    digitalWrite(13, LOW);
}

void Board::ledRedOn(void)
{
    digitalWrite(13, HIGH);
}


uint16_t Board::rcReadSerial(uint8_t chan)
{  
    static uint16_t values[5];

    values[0] = rx.readRawRC(1); // roll
    values[1] = rx.readRawRC(2); // pitch
    values[2] = rx.readRawRC(3); // throttle
    values[3] = rx.readRawRC(0); // yaw
    values[4] = rx.readRawRC(5); // auxfi

    return (int16_t)values[chan];
}

bool  Board::rcSerialReady(void)
{
    return rx.frameComplete();
}

bool Board::rcUseSerial(void)
{ 
    // Start receiver
    rx.begin();

    return true;
}

uint16_t Board::readPWM(uint8_t chan)
{
  (void)chan;
  return 0;
}


uint8_t Board::serialAvailableBytes(void)
{
    return Serial.available();
}

uint8_t Board::serialReadByte(void)
{
    return Serial.read();
}

void Board::serialWriteByte(uint8_t c)
{
    Serial.write(c);
}

void Board::writeMotor(uint8_t index, uint16_t value)
{ 
    (void)index;
    (void)value;
}

void Board::extrasCheckSwitch(void)
{
}

uint8_t  Board::extrasGetTaskCount(void){
    return 0;
}

bool Board::extrasHandleMSP(uint8_t command)
{
    return true;
}

void Board::extrasInit(class MSP * _msp)
{
    // Basic implementation doesn't need MSP
    (void)_msp;
}

void Board::extrasPerformTask(uint8_t taskIndex)
{
    (void)taskIndex;
}

void Board::showArmedStatus(bool armed)
{
    // XXX this would be a good place to sound a buzzer!

    (void)armed; 
}
 
void Board::showAuxStatus(uint8_t status)
{
    (void)status; 
}

void Board::checkReboot(bool)
{
}

void Board::reboot(void)
{
}