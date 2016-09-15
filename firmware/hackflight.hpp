/*
   hackflight.hpp : general header

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

#pragma once

#include <stdint.h>
#include <stdarg.h>
#include <math.h>

#include "crossplatform.h"

#ifndef M_PI
#endif

#ifdef STM32F10X_MD 
#include <printf.h>
#endif

#ifndef PRINTF
#ifdef _SIM
void debug(const char * format, ...);
#else
#define debug printf
#endif
#endif

#include "board.hpp"
#include "imu.hpp"
#include "rc.hpp"
#include "stabilize.hpp"
#include "mixer.hpp"
#include "baro.hpp"
#include "sonars.hpp"
#include "msp.hpp"
#include "hover.hpp"
#include "filters.hpp"

#ifndef abs
#define abs(x)    ((x) > 0 ? (x) : -(x))
#define sgn(x)    ((x) > 0 ? +1 : -1)
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define constrain(val, lo, hi) (val) < (lo) ? lo : ((val) > hi ? hi : val) 
#endif

enum {
    DEMAND_ROLL = 0,
    DEMAND_PITCH,
    DEMAND_YAW,
    DEMAND_THROTTLE,
    DEMAND_AUX1,
    DEMAND_AUX2,
    DEMAND_AUX3,
    DEMAND_AUX4
};

enum {
    AXIS_ROLL = 0,
    AXIS_PITCH,
    AXIS_YAW
};

typedef enum {
    X = 0,
    Y,
    Z
} sensor_axis_e;

// Config =====================================================

#define CONFIG_MAGNETIC_DECLINATION                 0

#define CONFIG_CALIBRATING_ACC_MSEC                 1400

#define CONFIG_YAW_CONTROL_DIRECTION                1    // 1 or -1 
#define CONFIG_RC_LOOPTIME_MSEC                     20
#define CONFIG_CALIBRATE_ACCTIME_MSEC               500
#define CONFIG_SMALL_ANGLE                          250  // tenths of a degree
#define CONFIG_ALTITUDE_UPDATE_MSEC                 25   // based on accelerometer low-pass filter