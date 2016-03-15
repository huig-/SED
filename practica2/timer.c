/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "44blib.h"
#include <stdlib.h>

/* Variables globales */
int cont;
int numeros[4];
/*--- funciones externas ---*/
extern void D8Led_symbol(int value);
extern int fila;
extern void leds_switch(void);
/*--- declaracion de funciones ---*/
void timer0_ISR(void) __attribute__ ((interrupt ("IRQ")));
void timer0_init(void);
void timer2_ISR(void) __attribute__ ((interrupt ("IRQ")));
void timer2_init(void);
void timer4_ISR(void) __attribute__ ((interrupt ("IRQ")));
void timer4_init(void);
void shuffle(int *array, int n);
void generar_numeros_aleatorios(void);
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

void generar_numeros_aleatorios(void)
{
	int i;
	if (fila) {
		int num_fila = rand() % 4;
		for (i = 0; i < 4; i++)
			numeros[i] = i + 4 * num_fila;
	}
	else {
		int num_columna = rand() % 4;
		for (i = 0; i < 4; i++)
					numeros[i] = 4 * i + num_columna;
	}
	shuffle(numeros, 4);
}

void timer0_init(void) //se encarga del timer entre cada uno de los numeros que se muestran en el display
{
	/* Configuracion del controlador de interrupciones */	
	rINTMOD=0x0;// Configurar las lineas como de tipo IRQ	
	rINTCON=0x1;// Habilitar int. vectorizadas y la linea IRQ (FIQ no)	
	rINTMSK = rINTMSK & ~(BIT_TIMER0 | BIT_GLOBAL);// Enmascarar todas las lineas excepto Timer0 y el bit global
	/* Establece la rutina de servicio para TIMER0 */
	pISR_TIMER0=(unsigned)timer0_ISR;
	/* Configurar el Timer0 (el resto de los timers se dejan a la
	configuración por defecto) */
	//rTCFG0=0xFF;// pre-escalado = 255
	rTCFG0 = rTCFG0 | 0xF;
	rTCFG1 &= 0xFFFFF4;// divisor = 1/32
	rTCNTB0=65535;
	rTCMPB0=12800;
	
	/* Generar numeros aleatorios */
	generar_numeros_aleatorios();

	rTCON=rTCON| (0x01<<1);// establecer manual_update
	rTCON=rTCON & ~(0x01<<1);// DESACTIVA manual_update
	rTCON=rTCON|(0x01<<3);//activar modo auto-reload
	rTCON=rTCON|(0x01<<0);// iniciar timer
	cont = 3;
}

void timer0_ISR(void){
	cont--;
	D8Led_symbol(numeros[cont]);
	//if (cont == 1)
	//	rTCON=rTCON|(0x00<<3);//activar modo one-shot
	if (cont == 0) {
		rINTMSK = rINTMSK | BIT_TIMER0; //desactivamos la interrupcion
		timer4_init();
	}
	rI_ISPC = BIT_TIMER0;
}

void timer2_init(void) //se encarga del timer del led
{
	/* Configuracion del controlador de interrupciones */	
	rINTMOD=0x0;// Configurar las lineas como de tipo IRQ	
	rINTCON=0x1;// Habilitar int. vectorizadas y la linea IRQ (FIQ no)	
	rINTMSK = rINTMSK & ~(BIT_TIMER2 | BIT_GLOBAL);// Enmascarar todas las lineas excepto Timer0 y el bit global
	/* Establece la rutina de servicio para TIMER0 */
	pISR_TIMER0=(unsigned)timer2_ISR;
	/* Configurar el Timer0 (el resto de los timers se dejan a la
	configuración por defecto) */
	rTCFG0 = rTCFG0 | 0xF0;// pre-escalado = 255
	rTCFG1 &= 0xFFF0FF;// divisor = 1/2
	rTCNTB2=65535;
	rTCMPB2=12800;
	
	rTCON =rTCON | (0x01<<13);// establecer manual_update
	rTCON =rTCON & ~(0x01<<13);// DESACTIVA manual_update
	rTCON =rTCON | (0x01<<15);//activar modo auto-reload
	rTCON =rTCON | (0x01<<12);// iniciar timer
}

void timer2_ISR(void){
	if (fila == 1) {
	    led1_on();
	    led1_off();
	}
	else {
	    led2_on();
	    led2_off();
	}
	rI_ISPC = BIT_TIMER2;
}

void timer4_init(void) //se encarga del tiempo que tiene el usuario para pulsar la tecla
{
	/* Configuracion del controlador de interrupciones */	
	rINTMOD=0x0;// Configurar las lineas como de tipo IRQ	
	rINTCON=0x1;// Habilitar int. vectorizadas y la linea IRQ (FIQ no)	
	rINTMSK = rINTMSK & ~(BIT_TIMER4 | BIT_GLOBAL);// Enmascarar todas las lineas excepto Timer0 y el bit global
	/* Establece la rutina de servicio para TIMER0 */
	pISR_TIMER0=(unsigned)timer4_ISR;
	/* Configurar el Timer0 (el resto de los timers se dejan a la
	configuración por defecto) */
	rTCFG0 = rTCFG0 | 0xF00;// pre-escalado = 255
	rTCFG1 &= 0xF3FFFF;// divisor = 1/16
	rTCNTB4=65535;
	rTCMPB4=12800;
	
	rTCON =rTCON | (0x01<<21);// establecer manual_update
	rTCON =rTCON & ~(0x01<<21);// DESACTIVA manual_update
	rTCON =rTCON | (0x0<<23);//activar modo one-shot
	rTCON =rTCON | (0x01<<20);// iniciar timer
}

void timer4_ISR(void){
	DelayMs(100);
	rTCON =rTCON | (0x00<<12);// parar timer
	rTCON =rTCON | (0x01<<13);// establecer manual_update
	rTCON =rTCON & ~(0x01<<13);// DESACTIVA manual_update
	rTCON =rTCON | (0x01<<15);//activar modo auto-reload
	rTCON =rTCON | (0x01<<12);// iniciar timer
	rINTMSK = rINTMSK & (~BIT_TIMER0); 
	rI_ISPC = BIT_TIMER4;
}

