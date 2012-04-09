/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <htc.h>           /* HiTech General Includes */
#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#include "system.h"

/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{
    OSCCON = 0x72; // Oscilador interno a 8MHz
}
