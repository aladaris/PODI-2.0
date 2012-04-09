/**
* ###### PODI 2.0, a Footswitch MIDI controller for the Line6's P.O.D 2.0 ######
* This source file is subject to the GPL 3 license that is vailable
* through the world-wide-web at this URL:
* http://www.gnu.org/copyleft/gpl.html
*
* Copyright (c) 2011-2012, Fernando González López-Peñalver <aladaris@gmail.com>
*
**/

#ifndef _MIDI_H_
#define _MIDI_H_

// Calculado para proporcionar 31250 Baudios funcionando a 8MHz
// para PIC16F690

// MIDI initialization
#define MIDI_Init()\
	SPBRGH = 0;     \
	SPBRG = 15;    	\
	BRGH = 1;     	\
	BRG16 = 0;     \
	SYNC = 0;     	\
	SPEN = 1;     	\
	TX9 = 0;     	\
	RX9 = 0;     	\
	TXEN = 1;     	\
	CREN = 1;     	\

void putch(unsigned char);
unsigned char getch(void);

#endif
