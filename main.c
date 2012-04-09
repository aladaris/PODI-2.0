/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <htc.h>           /* Global Header File */
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "POD.h"          /* User funct/params, such as InitApp */
#include "MIDI/midi.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/


/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

uint8_t main(void){
    ConfigureOscillator();
    MIDI_Init(); // set up the MIDI COMS
    POD_Init();
    while(1){
        POD_Idle();
    }

}

