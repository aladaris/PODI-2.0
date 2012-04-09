/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <htc.h>            /* HiTech General Includes */
#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "POD.h"
#include "MIDI/midi.h"

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void POD_Init(void){
    // IMPORTANTES ESTOS REGISTROS:
    // Configuran si los pines con I/O y A/D actuan como I/O o A/D...
    ANSEL = 0x00;
    ANSELH = 0x00;


    // Configuramos como ENTRADA los pines C0 y C1 (B_UP y B_DOWN)
    TRISC = 0b00000011;
    
    
    // Nos aseguramos de que los LEDs se inicializan apagados
    PORTC = 0x00;

    // Leemos Prog_Pos desde la EEPROM
    Prog_Pos = eeprom_read(Prog_Pos_Dir);
    // Nos aseguramos de que el valor leído esté en el rango [1 - nProgs]
    if (Prog_Pos > nProgs + 1)
        Prog_Pos = nProgs;
    
    MIDI_SendProgramChange (Prog_Pos);  // Ponemos el POD en el programa almacenado
}



void SetTunerMode(bool status){
    if (status){ // TUNER MODE: ON
        LED_BUTTON = 0;
        TunerMode = true;
        UP_HoldTime = 0;
        // Mostramos color Naranja
        LED_MIDI_IN = 1;
        LED_MIDI_OUT = 1;
    }else{       // TUNER MODE: OFF
        TunerMode = false;
        _delay(ReleaseDelay/4);
        /* TODO: Estudiar poner delays al entrar y salir de los programas
         *       especiales, ya que el POD tiene un pequeño retraso al cambiar
         *       de, y a, estos programas.
         */
        // Dejamos de mostrar el color Naranja
        LED_MIDI_IN = 0;
        LED_MIDI_OUT = 0;
    }
}

void SetManualMode(bool status){
    if (status){ // MANUAL MODE: ON
        ManualMode = true;
        DOWN_HoldTime = 0;
        // Mostramos color Violeta
        LED_MIDI_OUT = 1;
        LED_BUTTON = 1;
    }else{       // MANUAL MODE: OFF
        ManualMode = false;
        _delay(ReleaseDelay/4);
        // Dejamos de mostrar el color Violeta
        LED_MIDI_OUT = 0;
        LED_BUTTON = 0;
    }
}



//! Envía los bytes "Program Change" y el programa deseado, y actualiza el valor en la EEPROM.
/*!
    \param prg Valor del programa a enviar. Ese mismo valor se escribe en la EEPROM.
*/
void MIDI_SendProgramChange (unsigned char prg){

    LED_MIDI_OUT = 1;
    putch(MIDI_PChange);  // Comando: Program Change On Chanel 1
    if (prg <= nProgs + 1)
        putch(prg);           // Numero del programa ~ [0 - 25]
    else{ // Si el valor está fuera de los límites, lo ponemos a '1'
        Prog_Pos = 0x01;
        putch(Prog_Pos);
    }


   // No almacenamos los programas especiales en EEPROM.
    if ((prg != MIDI_Tuner) && (prg != MIDI_Manual))
        EEPROM_WRITE (Prog_Pos_Dir, Prog_Pos); // Almacenamos el cambio en la EEPROM

    _delay(ReleaseDelay/32);
    if ((!TunerMode)&&(!ManualMode))
        LED_MIDI_OUT = 0;
}

void MIDI_receiveProgramChange(){
    if (RCIF){
        unsigned char inChar = getch();
        if (inChar == MIDI_PChange){
            inChar = getch();
            if (inChar <= nProgs + 1){ // nProgs + 1 porque queremos incluir el programa MIDI_Tuner
                LED_MIDI_IN = 1;
                // No almacenamos los programas especiales en EEPROM.
                if ((inChar != MIDI_Tuner) && (inChar != MIDI_Manual)){
                    Prog_Pos = inChar;
                    EEPROM_WRITE (Prog_Pos_Dir, Prog_Pos); // Almacenamos el cambio en la EEPROM
                    if (TunerMode) // Al recibir un cambio de programa salimos de los modos especiales
                        SetTunerMode(false);
                    if (ManualMode)
                        SetManualMode(false);
                }
                // Manejo de programas especiales (Por alguna razon el compilador no me deja usar un SWITCH)
                else if (inChar == MIDI_Tuner)
                    SetTunerMode(true);
                else if (inChar == MIDI_Manual)
                    SetManualMode(true);

                _delay(ReleaseDelay/32);
                if (!TunerMode)
                    LED_MIDI_IN = 0;
            }
        }
    }
}

//!    Controla el comportamiento de Botón UP:
//!        * Al pulsarlo se enciende el LED_BUTTON.
//!        * Al soltarlo se incrementa el programa actual en uno. (Si se llega a nProgs, se vuelve al programa 1 [1A en el POD]).
//!        * Si se mantiene pulsado durante 'MaxHoldTime' o más, se entra en modo TUNER (afinación).
//!        * Para salir del modo TUNER hay que presionar Botón UP, y se regresa al programa en el que se encontraba.
void POD_UpButton(){
    if ((TunerMode)&&(B_UP)&&(!B_UP_pressed)){ // TUNER MODE OFF
        MIDI_SendProgramChange (Prog_Pos); // Volvemos al Preset que estabamos
        SetTunerMode(false);
    }else if ((B_UP)&&(!B_UP_pressed)&&(!ManualMode)){ // PUSH
        LED_BUTTON = 1;
        B_UP_pressed = true;
    }else  if ((!B_UP)&&(B_UP_pressed)&&(!ManualMode)){ // RELEASE
        LED_BUTTON = 0;
        B_UP_pressed = false;
        if (!TunerMode){
            UP_HoldTime = 0; // Reset contador de Hold, para evitar contabilizar cada pulsacion
            Prog_Pos++;
            if (Prog_Pos > nProgs) // Si llegamos al ultimo programa ...
                Prog_Pos = 1;      // Volvemos al primero
            MIDI_SendProgramChange (Prog_Pos);
        }
    }else if ((B_UP)&&(B_UP_pressed)&&(!TunerMode)){ // HOLD
        UP_HoldTime++;
        if (UP_HoldTime >= MaxHoldTime){  // TUNER MODE ON
            MIDI_SendProgramChange(MIDI_Tuner);
            SetTunerMode(true);
        }
    }
}

//!    Controla el comportamiento de Botón DOWN
//!        * Al pulsarlo se enciende el LED_BUTTON.
//!        * Al soltarlo se decrementa el programa actual en uno. (Si se llega a 0, se vuelve al programa nProgs [9D en el POD]).
//!        * Si se mantiene pulsado durante 'MaxHoldTime' o más, se entra en modo MANUAL.
//!        * Para salir del modo MANUAL hay que presionar Botón DOWN, y se regresa al programa en el que se encontraba.
void POD_DownButton(){

    if ((ManualMode)&&(B_DOWN)&&(!B_DOWN_pressed)){ // MANUAL MODE OFF
        MIDI_SendProgramChange (Prog_Pos); // Volvemos al Preset que estabamos
        SetManualMode(false);
    }else if ((B_DOWN)&&(!B_DOWN_pressed)&&(!TunerMode)){ // PUSH
        LED_BUTTON = 1;
        B_DOWN_pressed = true;
    }else  if ((!B_DOWN)&&(B_DOWN_pressed)&&(!TunerMode)){ // RELEASE
        if (!ManualMode)
            LED_BUTTON = 0;
        B_DOWN_pressed = false;
        if (!ManualMode){
            DOWN_HoldTime = 0; // Reset contador de Hold, para evitar contabilizar cada pulsacion
            Prog_Pos--;
            if (Prog_Pos <= 0)       // Si llegamos a 0 (cero)...
                Prog_Pos = nProgs;   // Vamos al otro extremo (nProgrs)
            MIDI_SendProgramChange (Prog_Pos);
        }
    }else if ((B_DOWN)&&(B_DOWN_pressed)&&(!ManualMode)){ // HOLD
        DOWN_HoldTime++;
        if (DOWN_HoldTime >= MaxHoldTime){ // MANUAL MODE ON
            MIDI_SendProgramChange(MIDI_Manual);
            SetManualMode(true);
        }
    }
}

//!  Funcion llamada en cada iteración del bucle, controla la actividad del POD.
//!  Comprueba el estado de los Botones y de la recepción MIDI.
void POD_Idle(){
   MIDI_receiveProgramChange();
   POD_UpButton();
   POD_DownButton();
   /*
   if (MIDI_ProgChangeCmdRead){
      LED_MIDI_IN = 1;
   }else
      LED_MIDI_IN = 0;
   */
}
