/**
* ###### PODI 2.0, a Footswitch MIDI controller for the Line6's P.O.D 2.0 ######
* This source file is subject to the GPL 3 license that is vailable
* through the world-wide-web at this URL:
* http://www.gnu.org/copyleft/gpl.html
*
* Copyright (c) 2011-2012, Fernando González López-Peñalver <aladaris@gmail.com>
*
**/

// Microcontroller MIPs (FCY)
#define SYS_FREQ        8000000L
#define FCY             SYS_FREQ/4

// System Function Prototypes
void ConfigureOscillator(void); /* Handles clock switching/osc initialization */
