/*
   f3usb_vcp.cpp Board class implementation for F3Boards that use USB Virtual COM Port

   Copyright (c) 2018 Simon D. Levy

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

#include "f3board.h"

// This code has to talk to the C code supporing USB Virtual COM Port ------------------------------------------

extern "C" {

#include "platform.h"
#include "dma.h"
#include "gpio.h"
#include "serial.h"
#include "system.h"
#include "serial_uart.h"
#include "serial_usb_vcp.h"

    static serialPort_t * serial0;

    void F3Board::usbInit(void)
    {
        serial0 = usbVcpOpen();
    }

    uint8_t F3Board::serialAvailableBytes(void)
    {
        return usbVcpAvailable(serial0);
    }

    uint8_t F3Board::serialReadByte(void)
    {
        return usbVcpRead(serial0);
    }

    void F3Board::serialWriteByte(uint8_t c)
    {
        usbVcpWrite(serial0, c);
        while (!isSerialTransmitBufferEmpty(serial0));
    }

    void F3Board::outchar(char c)
    {
        usbVcpWrite(serial0, c);
    }

    USART_TypeDef * getDsmUart()
    {
        return USART2;
    }

} // extern "C"
