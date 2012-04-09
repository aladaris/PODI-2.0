////////////////
// CONSTANTES //
////////////////
   // Generales
const uint8_t nProgs = 0x24;             //!< Valor MIDI del �ltimo programa (9D) que tiene el POD.
const unsigned char Prog_Pos_Dir = 0x00; //!< Direcci�n de memoria EEPROM donde almacenar Prog_Pos.

   // Constantes relacionadas con los pulsadores
const uint16_t MaxHoldTime = 25000;     //!< "Tiempo" que transcurre hasta que se considera la acci�n "HOLD".
#define ReleaseDelay 2500000               //!< Tiempo de espera entre una acci�n y otra (PJ: Salir del modo Tuner).

   // MIDI Constants
const unsigned char MIDI_Manual = 0x00;   //!< Valor MIDI para el programa Manual.
const unsigned char MIDI_Tuner = 0x25;    //!< Valor MIDI para el programa Tuner.
const unsigned char MIDI_PChange = 0xC0;  //!< Comando MIDI "Program Change" para el canal 1.

    // Mapeo de PINes
#define B_UP    RC0       //!< Bot�n UP mapeado al pin C0.
#define B_DOWN  RC1       //!< Bot�n DOWN mapeado al pin C1.
#define LED_BUTTON RC2    //!< Led que indica que un bot�n es presionado.
#define LED_MIDI_IN RC3   //!< Led que indica actividad MIDI IN.
#define LED_MIDI_OUT RC4  //!< Led que indica actividad MIDI OUT.

////////////////////////
// VARIABLES GLOBALES //
////////////////////////
    // Relacionadas con los pulsadores
bool B_UP_pressed = false;           //!< Indica si Bot�n UP est� pulsado.
bool B_DOWN_pressed = false;         //!< Indica si Bot�n DOWN est� pulsado.
uint16_t UP_HoldTime = 0;            //!< Contador de "Hold Time" del Bot�n UP.
uint16_t DOWN_HoldTime = 0;          //!< Contador de "Hold Time" del Bot�n DOWN.
    // Estado del POD
bool TunerMode = false;              //!< Indica si el POD se encuentra en modo afinador.
bool ManualMode = false;             //!< Indica si el POD se encuentra en modo manual.
unsigned char Prog_Pos;                    //!< Valor MIDI del programa seleccionado actualmente.
bool MIDI_ProgChangeCmdRead = false; //!< Indica si se ha recibido un comando "Program Change".

////////////////////////
//      FUNCIONES     //
////////////////////////
void POD_Init(void);    //! Inicializa todo lo relacionado con el POD.
void MIDI_SendProgramChange (unsigned char); //! Env�a los bytes "Program Change" y el programa deseado, y actualiza el valor en la EEPROM.
void POD_Idle();        //!  Comprueba el estado de los Botones y de la recepci�n MIDI.
