/* definitions / defines file */
#define DEFS_H

#define SW_VERSION		20   /* i.e. major.minor software version nbr. */

#ifndef NULL
#define NULL  0
#endif
        

#define wdogtrig()			#asm("wdr") // call often if Watchdog timer enabled
 

#define LED1 PORTD.6        // LED placa
#define buton_set PIND.5      //select intre temp si err
#define buton_up PIND.3          
#define buton_down PIND.4   
#define tranzistor PORTD.7       //ventilator
    
#include "funct.h"
//#define ADC_VREF_TYPE 0x40   //referinta interna de 5V
#define ADC_VREF_TYPE 0xC0   //referinta interna de 2.56V

