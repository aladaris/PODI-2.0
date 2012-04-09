#include <htc.h>
#include <stdio.h>
#include "midi.h"

void putch(unsigned char byte){
	/* output one byte */
	while(!TXIF)	/* set when register is empty */
		continue;
	TXREG = byte;
}

unsigned char getch(){
	/* retrieve one byte */
	while(!RCIF)	/* set when register is NOT empty */
		continue;
	return RCREG;	
}
