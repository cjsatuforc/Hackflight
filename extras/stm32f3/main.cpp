/*
main.cpp : Entry point for STM32F3 boards

Copyright (C) 2018 Simon D. Levy 

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

extern "C" {

#include "platform.h"
#include "system.h"
#include "dma.h"
#include "gpio.h"
#include "timer.h"
#include "serial.h"
#include "serial_uart.h"
#include "exti.h"

#
// Shared with F3Board
serialPort_t * serial0;

static void checkReboot(void)
{
    static uint32_t dbg_start_msec;
    // support reboot from host computer
    if (millis()-dbg_start_msec > 100) {
        dbg_start_msec = millis();
        while (serialRxBytesWaiting(serial0)) {
            uint8_t c = serialRead(serial0);
            if (c == 'R') 
                systemResetToBootloader();
        }
    }
}

static void ledInit(void)
{
    GPIO_TypeDef * gpio = LED0_GPIO;

    gpio_config_t cfg;

    cfg.pin = LED0_PIN;
    cfg.mode = Mode_Out_PP;
    cfg.speed = Speed_2MHz;

    gpioInit(gpio, &cfg);
}

int main(void) {

    // Defined in each sketch
    void setup();
    void loop();

    void SetSysClock(void);

    // Board-specific
    serialPort_t * serial0_open(void);

    // start fpu
    SCB->CPACR = (0x3 << (10*2)) | (0x3 << (11*2));

    SetSysClock();

    systemInit();

    timerInit();  // timer must be initialized before any channel is allocated

    serial0 = serial0_open();

    dmaInit();

    ledInit();

    setup();

    while (true) {

        checkReboot();

        loop();
    }
} // main

} // extern "C"