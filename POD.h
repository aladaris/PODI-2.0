/**
* ###### PODI 2.0, a Footswitch MIDI controller for the Line6's P.O.D 2.0 ######
* This source file is subject to the GPL 3 license that is vailable
* through the world-wide-web at this URL:
* http://www.gnu.org/copyleft/gpl.html
*
* Copyright (c) 2011-2012, Fernando González López-Peñalver <aladaris@gmail.com>
*
**/

////////////////
// CONSTANTES //
////////////////
   // Generales
const uint8_t nProgs = 0x24;             //!< Valor MIDI del último programa (9D) que tiene el POD.
const unsigned char Prog_Pos_Dir = 0x00; //!< Dirección de memoria EEPROM donde almacenar Prog_Pos.

   // Constantes relacionadas con los pulsadores
const uint16_t MaxHoldTime = 25000;     //!< "Tiempo" que transcurre hasta que se considera la acción "HOLD".
#define ReleaseDelay 2500000               //!< Tiempo de espera entre una acción y otra (PJ: Salir del modo Tuner).

   // MIDI Constants
const unsigned char MIDI_Manual = 0x00;   //!< Valor MIDI para el programa Manual.
const unsigned char MIDI_Tuner = 0x25;    //!< Valor MIDI para el programa Tuner.
const unsigned char MIDI_PChange = 0xC0;  //!< Comando MIDI "Program Change" para el canal 1.

    // Mapeo Pin de cada color (TODO: Comprobar asignación)
#define LED_RED RC4
#define LED_GREEN RC3
#define LED_BLUE RC2

    // Mapeo de PINes
#define B_UP    RC0       //!< Botón UP mapeado al pin C0.
#define B_DOWN  RC1       //!< Botón DOWN mapeado al pin C1.
#define LED_BUTTON LED_BLUE    //!< Led que indica que un botón es presionado.
#define LED_MIDI_IN LED_GREEN   //!< Led que indica actividad MIDI IN.
#define LED_MIDI_OUT LED_RED  //!< Led que indica actividad MIDI OUT.

////////////////////////
// VARIABLES GLOBALES //
////////////////////////
    // Relacionadas con los pulsadores
bool B_UP_pressed = false;           //!< Indica si Botón UP está pulsado.
bool B_DOWN_pressed = false;         //!< Indica si Botón DOWN está pulsado.
uint16_t UP_HoldTime = 0;            //!< Contador de "Hold Time" del Botón UP.
uint16_t DOWN_HoldTime = 0;          //!< Contador de "Hold Time" del Botón DOWN.
    // Estado del POD
bool TunerMode = false;              //!< Indica si el POD se encuentra en modo afinador.
bool ManualMode = false;             //!< Indica si el POD se encuentra en modo manual.
unsigned char Prog_Pos;                    //!< Valor MIDI del programa seleccionado actualmente.
bool MIDI_ProgChangeCmdRead = false; //!< Indica si se ha recibido un comando "Program Change".

////////////////////////
//      FUNCIONES     //
////////////////////////
void POD_Init(void);    //! Inicializa todo lo relacionado con el POD.
void MIDI_SendProgramChange (unsigned char); //! Envía los bytes "Program Change" y el programa deseado, y actualiza el valor en la EEPROM.
void POD_Idle();        //!  Comprueba el estado de los Botones y de la recepción MIDI.
