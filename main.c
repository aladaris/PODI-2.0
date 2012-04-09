/**
* ###### PODI 2.0, a Footswitch MIDI controller for the Line6's P.O.D 2.0 ######
* This source file is subject to the GPL 3 license that is vailable
* through the world-wide-web at this URL:
* http://www.gnu.org/copyleft/gpl.html
*
* Copyright (c) 2011-2012, Fernando González López-Peñalver <aladaris@gmail.com>
*
**/


#include <htc.h>           /* Global Header File */
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "POD.h"          /* User funct/params, such as InitApp */
#include "MIDI/midi.h"


uint8_t main(void){
    ConfigureOscillator();
    MIDI_Init(); // set up the MIDI COMS
    POD_Init();
    while(1){
        POD_Idle();
    }

}

