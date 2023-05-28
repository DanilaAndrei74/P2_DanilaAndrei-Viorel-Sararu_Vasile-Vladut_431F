/* initialization file */

#include <mega164a.h>
#include "defs.h"
                                          

/*
 * most intialization values are generated using Code Wizard and depend on clock value
 */
void Init_initController(void)
{
// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=0x80;
CLKPR=0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTA=0x00;       //registru de stare logica 1=5V, 0=0
DDRA=0x00;      //registru directie 0=IN, 1=OUT

// Port B initialization
PORTB=0x00;
DDRB=0x00;                      

// Port C initialization
PORTC=0x00;
DDRC=0x00;

// Port D initialization
PORTD=0x38;       //pull-up activat pe PD3,4,5 
DDRD=0xC0;  // PD6 este iesire pt LED, PD7 iesire pentru tranzistor

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: Timer 0 Stopped
// Mode: Normal top=FFh
// OC0 output: Disconnected
TCCR0A=0x00;
TCCR0B=0x00;
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 19.531 kHz = CLOCK/256
// Mode: CTC top=OCR1A
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer 1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: On
// Compare B Match Interrupt: Off

TCCR1A=0x00;
TCCR1B=0x0D;         //configurare timer1
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;

OCR1AH=0x26;  //0x2620 = 9760/19531  =a dica 0.5 secunde
OCR1AL=0x20;

OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer2 Stopped
// Mode: Normal top=0xFF
// OC2A output: Disconnected
// OC2B output: Disconnected
ASSR=0x00;
TCCR2A=0x00;
TCCR2B=0x00;
TCNT2=0x00;
OCR2A=0x00;
OCR2B=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
// Interrupt on any change on pins PCINT0-7: Off
// Interrupt on any change on pins PCINT8-15: Off
// Interrupt on any change on pins PCINT16-23: Off
// Interrupt on any change on pins PCINT24-31: Off
EICRA=0x00;
EIMSK=0x00;
PCICR=0x00;

// Timer/Counter 0,1,2 Interrupt(s) initialization
TIMSK0=0x00;
TIMSK1=0x02;   //activat timer1
TIMSK2=0x00;

// USART0 initialization
UCSR0A=0x00;
UCSR0B=0x00;
UCSR0C=0x00;
UBRR0H=0x00;
UBRR0L=0x00;

// USART1 initialization
// USART1 disabled
UCSR1B=0x00;


// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
ADCSRB=0x00;
DIDR1=0x00;

// ADC initialization
// ADC Clock frequency: 625.000 kHz
// ADC Voltage Reference:                2.56V, cap. on AREF
// ADC Auto Trigger Source: ADC Stopped
// Digital input buffers on ADC0: On, ADC1: On, ADC2: On, ADC3: On
// ADC4: On, ADC5: On, ADC6: On, ADC7: On
DIDR0=0x00;
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x85;

// Watchdog Timer initialization
// Watchdog Timer Prescaler: OSC/2048  
#pragma optsize-
#asm("wdr")
// Write 2 consecutive values to enable watchdog
// this is NOT a mistake !
WDTCSR=0x18;
WDTCSR=0x08;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

}



