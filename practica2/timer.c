/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "44blib.h"
#include <stdlib.h>

/* Variables globales */
int cont;
int numbers[4];
/*--- funciones externas ---*/
extern void D8Led_symbol(int value);
extern void D8Led_symbol_correct(int value);
extern int row;
extern int key;
extern void leds_switch(void);
/*--- declaracion de funciones ---*/
void timers_init(void);
void timer0_ISR(void) __attribute__ ((interrupt ("IRQ")));
void timer2_ISR(void) __attribute__ ((interrupt ("IRQ")));
void timer4_ISR(void) __attribute__ ((interrupt ("IRQ")));
void shuffle(int *array, int n);
void random_number_generator(void);
/*--- codigo de las funciones ---*/

void shuffle(int *array, int n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

void random_number_generator(void)
{
	int i;
	if (fila) {
		int num_row = rand() % 4;
		for (i = 0; i < 4; i++)
			numbers[i] = i + 4 * num_row;
	}
	else {
		int num_col = rand() % 4;
		for (i = 0; i < 4; i++)
			numbers[i] = 4 * i + num_col;
	}
	shuffle(numbers, 4);
}

void timers_init(void)
{
	random_number_generator();
	cont = 3;
	rINTMOD = 0x0; //enable IRQ
	rINTCON = 0x1; //enable IRQ pin and vect.
	pISR_TIMER0=(unsigned)timer0_ISR;
	pISR_TIMER2=(unsigned)timer2_ISR;
	pISR_TIMER4=(unsigned)timer4_ISR;
	rTCFG0 = rTCFG0 | 0xFFFFFF; //prescaler value 255
	rTCFG1 = rTCFG1 & 0xFF3F0F4; //divisor value, 1/16 timer4, 1/2 timer2, 1/32 timer0
	//Timer count buffer registers
	rTCNTB0 = 65535; //timer0
	rTCNTB2 = 65535; //timer2
	rTCNTB4 = 65535; //timer4
	//Timer compare buffer registers
	rTCMPB0 = 12800; //timer0
	rTCMPB2 = 12800; //timer2
	rTCMPB4 = 12800; //timer4
	//Enable timer0, timer2 interrupts
	rINTMSK = rINTMSK & ~(BIT_TIMER0 | BIT_TIMER2 | BIT_GLOBAL);
	/*Timer0 conf*/
	rTCON = rTCON | (0x01<<1);    // timer0 manual_update
	rTCON = rTCON & ~(0x01<<1);   // timer0 disable manual_update
	rTCON = rTCON | (0x01<<3);    // timer0 auto-reload
	rTCON = rTCON | (0x01<<0);    // timer0 start
	/*Timer2 conf*/
	rTCON = rTCON | (0x01<<13);   // timer2 manual_update
	rTCON = rTCON & ~(0x01<<13);  // timer2 disable manual_update
	rTCON = rTCON | (0x01<<15);   // timer2 auto-reload
	rTCON = rTCON | (0x01<<12);   // timer2 start 
	/*Timer4 conf*/
	rTCON = rTCON | (0x01<<21);   // timer4 manual_update
	rTCON = rTCON & ~(0x01<<21);  // timer4 disable manual_update
	rTCON = rTCON | (0x0<<23);    // timer4 one-shot
	rTCON = rTCON | (0x00<<20);   // timer4 stop
	
	/*All together
	rTCON = rTCON | (0x01<<1);    // timer0 manual_update
	rTCON = rTCON & ~(0x01<<1);   // timer0 disable manual_update
	rTCON = rTCON | (0x01<<13);   // timer2 manual_update
	rTCON = rTCON & ~(0x01<<13);  // timer2 disable manual_update
	rTCON = rTCON | (0x01<<21);   // timer4 manual_update
	rTCON = rTCON & ~(0x01<<21);  // timer4 disable manual_update
	rTCON = rTCON | 0x808008;     //timer0 timer2 timer4 autoreload
	rTCON = rTCON | 0x1001;     //timer0 timer2 start
	*/

}

void timer0_ISR(void)
{
	cont--;
	D8Led_symbol(numbers[cont]);
	if (cont == 0) {
		rINTMSK = rINTMSK | BIT_TIMER0; //disable timer0 
		rINTMSK = rINTMSK & ~(BIT_TIMER4); //enable timer4
		rTCON = rTCON | (0x01<<20);   // timer4 start
	}
	rI_ISPC = BIT_TIMER0;
}

void timer2_ISR(void)
{
	if (row) {
	    led1_on();
	    led1_off();
	}
	else {
	    led2_on();
	    led2_off();
	}
	rI_ISPC = BIT_TIMER2;
}

void timer4_ISR(void)
{
	DelayMs(100);
	/*Check if keyboard was pressed*/
	if (key == -1 || key != numbers[3]) //mistake
	    D8Led_symbol(numbers[3]);
	else
	    D8Led_symbol_correct(numbers[3]);
	DelayMs(100);
	random_number_generator();
	cont = 3;
	rINTMSK = rINTMSK & (~BIT_TIMER0); //enable timer0
	rINTMSK = rINTMSK | BIT_TIMER4; //disable timer4
	rI_ISPC = BIT_TIMER4;
}

