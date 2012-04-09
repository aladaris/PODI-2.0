/**
* ###### PODI 2.0, a Footswitch MIDI controller for the Line6's P.O.D 2.0 ######
* This source file is subject to the GPL 3 license that is vailable
* through the world-wide-web at this URL:
* http://www.gnu.org/copyleft/gpl.html
*
* Copyright (c) 2011-2012, Fernando González López-Peñalver <aladaris@gmail.com>
*
**/

#include <htc.h>
#include <stdio.h>
#include "midi.h"

void putch(unsigned char byte){
	// output one byte
	while(!TXIF)	// set when register is empty
		continue;
	TXREG = byte;
}

unsigned char getch(){
	// retrieve one byte
	while(!RCIF)	// set when register is NOT empty
		continue;
	return RCREG;	
}
