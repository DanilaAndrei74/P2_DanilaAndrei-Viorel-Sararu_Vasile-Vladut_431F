/*********************************************
Project : Test software
**********************************************
Chip type: ATmega164A
Clock frequency: 20 MHz
Compilers:  CVAVR 2.x
*********************************************/

#include <mega164a.h>
#include <delay.h>  
#include <string.h> 
#include <stdlib.h>
#include "defs.h"                 
#include <alcd.h>      // Alphanumeric LCD functions 

float temp_preset=25;   //temperatura setata default  
float err=1;    //eroarea permisa
int i=0;
int mod_set=1;      //1 =set temperatura, 0=set eroare temperatura
float temperatura=0;           //valoarea in grade Celsius
unsigned char buf1[6], buf2[6],  buf3[6];          // buffer folosit pt afisare pe LCD 


// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)    // citire adc, read_adc(0) - citeste PA0 si returneaza un nr intre 0-1023, adica 2^10
{
ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);         
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=0x40;
// Wait for the AD conversion to complete
while ((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCW;  //[0-1023]
}

void afisare(){
        ftoa(temperatura,1,buf1);                //converteste float in string cu precizie de 1 zecimala
        ftoa(temp_preset,1,buf2);                        //converteste int in char pt a nu avea zecimale
        ftoa(err,1,buf3);  
        
    lcd_clear();             //sterge tot LCD  
    lcd_gotoxy(0,0);                     // x=0,y=0
    lcd_puts("Temp:");                        
    lcd_gotoxy(6,0);              //x=6
    lcd_puts(buf1);                 //afisez temperatura masurata  
    lcd_puts("C");
     
    lcd_gotoxy(0,1);                  //randul y=1 
    lcd_puts("Set:");               //afisez temperatura setata
    lcd_gotoxy(4,1);
    lcd_puts(buf2); 
    lcd_puts("C");  
    
    lcd_gotoxy(11,1);                  //randul y=1 
    lcd_puts("E:");               //afisez  eroarea setata
    lcd_gotoxy(13,1);
    lcd_puts(buf3);  
    
    if(tranzistor==1){          //afisez starea ventilatorului
    lcd_gotoxy(12,0);   // x=0,y=0
    lcd_puts(" ON"); 
    }                
    else{
    lcd_gotoxy(12,0);   // x=0,y=0
    lcd_puts(" OFF");
    }
} 

/*
 * Timer 1 Output Compare A interrupt is used to blink LED
 */
interrupt [TIM1_COMPA] void timer1_compa_isr(void)     //intrerupere pe timer1 la 0.5 secunde
{
LED1 = ~LED1; // invert LED 

    for(i=0;i<20;i++){                              //face 20 citiri ale ADC pentru a elimina zgomotul
        temperatura=temperatura+read_adc(0);   //retuneaza val numerica 0-1023  
        delay_ms(2);                                  //2 ms intre citiri             
        }    
        temperatura=temperatura/20;                      //mediaza  cele 20 de citiri  
        temperatura=temperatura*2;      //divizor rezistiv 1/2
        temperatura=2.56*temperatura/1024;           //convertim in Volti, 2.565V - tens referinta
        temperatura=temperatura-2.73;                 //elimina offset de la senzor ( 2730mV offset si 10mV/°C panta) 
        temperatura=temperatura*100;                 //convertim in grade Celsius cunoscand 10mV/°C    
        
    if(temperatura>temp_preset+err){                 //daca a depasit temperatura setata
    tranzistor=1;                                    //porneste ventilator ;
    }
    else if(temperatura<temp_preset-err){         //daca este sub temperatura setata
     tranzistor=0;                                          //oprestre ventilator                                   
     }
    
    afisare();      //afisez periodic masuratorile 
}

                                 

/*
 * main function of program
 */
void main (void)
{          

	Init_initController();  // this must be the first "init" action/call!
	#asm("sei")             // enable interrupts pt timer1
	LED1 = 1;           	// initial state, will be changed by timer 1 
    lcd_init(16);   //apelam pt initializare LCD cu 16 caractere

	while(1)
	{       
         
		wdogtrig();	        // call often else processor will reset
                    
        if(buton_up == 0)        // pressed
        {
            delay_ms(30);   // debounce switch
            if(buton_up == 0)    
            {                // LED will blink slow or fast
                while(buton_up==0)    //astept eliberare buton
                 {   wdogtrig();   } // wait for release      
                 if(mod_set)   {
                    temp_preset=temp_preset+1;
                    if(temp_preset>40)temp_preset=40;   //limitez la 40 grade  
                    }
                    else {
                    err=err+0.5;
                    }
                 afisare();   //update afisare
            }                
        } 
        
        if(buton_down == 0)        // pressed
        {
            delay_ms(30);   // debounce switch
            if(buton_down == 0)    
            {                // LED will blink slow or fast
                while(buton_down==0)
                  {  wdogtrig();   } // wait for release 
                  
                  if(mod_set){ 
                    temp_preset=temp_preset-1;
                    if(temp_preset<18)temp_preset=18;
                    }
                    else {
                    if(err>=1)err=err-0.5;
                    }
                 afisare();   //update afisare
            }                
        }  
               
                if(buton_set == 0)        // pressed
        {
            delay_ms(30);   // debounce switch
            if(buton_set == 0)    
            {                // LED will blink slow or fast
                while(buton_set==0)    //astept eliberare buton
                 {   wdogtrig();   } // wait for release      
                 if(mod_set)  mod_set=0;
                    else mod_set=1;
               afisare();   //update afisare
            }                
        } 
      
    } 

            
}// end main loop 


