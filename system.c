/**
* ###### PODI 2.0, a Footswitch MIDI controller for the Line6's P.O.D 2.0 ######
* This source file is subject to the GPL 3 license that is vailable
* through the world-wide-web at this URL:
* http://www.gnu.org/copyleft/gpl.html
*
* Copyright (c) 2011-2012, Fernando González López-Peñalver <aladaris@gmail.com>
*
**/

#include <htc.h>           /* HiTech General Includes */
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"

/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{
    OSCCON = 0x72; // Oscilador interno a 8MHz
}
