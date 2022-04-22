/*
 * VU_METER_WITHOUT_USING_MICROPHONE.c
 *
 * Created: 1/24/2018 5:38:53 PM
 *  Author: BestEngineeringProject
 */ 

/*
OCDEN = [ ]
JTAGEN = [ ]
SPIEN = [X]
CKOPT = [ ]
EESAVE = [ ]
BOOTSZ = 2048W_3800
BOOTRST = [ ]
BODLEVEL = 2V7
BODEN = [ ]
SUT_CKSEL = EXTHIFXTALRES_16KCK_64MS
HIGH = 0xD9 (valid)
LOW = 0xFF (valid)
*/


#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED_VU_L DDRC |= 0xFF
#define audio_LED_L PORTC

#define S 32
void adc_init();
uint16_t adc_read();

int32_t A[S];
int i=0;

int x_1[] =
{
	0x00,0x00,0x01,0x03,
	0x07,0x0F,0x1F,0x3F,
	0x7F,0xFF
};

int main(void)
{
	DDRD |= 1<<PIND6 | 1<<PIND7; 
	PORTD |= 1<<PIND7 | 1<<PIND6; 
	LED_VU_L;
	adc_init();
	
    while(1)
    {
      for(int x=0;x<S/2;x++)
      {
		  A[x] = ((uint16_t)adc_read());
		  A[x] = A[x]/10;
		  audio_LED_L = x_1[A[x]]; 
		  _delay_ms(20); 
		  
      }
	  
    }
}

void adc_init()
{
	ADMUX = 0xC0;
	ADCSRA = 0x82; 
}

uint16_t adc_read()
{
	volatile uint16_t retl,reth;
	ADMUX = 0xC0;
	ADCSRA |= 1<<ADSC;
	while(!ADIF);
	ADCSRA |= 1<<ADIF;
	retl = ADCL;
	reth = ADCH;
	reth<<=8;
	reth|=retl;
	return reth;
}