/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "stdio.h"
/*--- funciones externas ---*/
extern void leds_off();
extern void led1_on();
extern void leds_switch();
extern void Eint4567_init(void);
extern void button_init(void);
//extern void sys_init();
/*--- declaracion de funciones ---*/
//void Main(void);
/*--- codigo de funciones ---*/
void Main(void)
{
	/* Inicializar controladores */
	sys_init(); // Inicializacion de la placa, interrupciones y puertos
	/* Establecer valor inicial de los LEDs */
	leds_off();
	led1_on();
	/*Inicializar los botones*/
	button_init();
	while (1){
		if (rPDATG & (0x3<<6) != 0xC0) { // se pulsa un boton
			while (rPDATG & (0x3<<6) != 0xC0); // espera a que se suelte el boton
			DelayMs(1000);
			leds_switch();
			DelayMs(1000);
		}
	}
}
