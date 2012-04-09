#ifndef _MIDI_H_
#define _MIDI_H_

// Calculado para proporcionar 31250 Baudios funcionando a 8MHz
// para PIC16F690

/* MIDI initialization */
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
