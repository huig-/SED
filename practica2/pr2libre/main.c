/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "stdio.h"
/*--- funciones externas ---*/
extern void leds_off();
extern void led1_on();

//Declarar funciones externas de inicializaci�n

/*--- declaracion de funciones ---*/
void Main(void);
/*--- codigo de funciones ---*/
void Main(void)
{
	/* Inicializar controladores */
	sys_init(); // Inicializacion de la placa, interrupciones y puertos
	// Inicializacion del temporizador
	D8Led_init();
	Eint4567_init();
	// Inicializaci�n del teclado matricial
	keyboard_init();

	timers_init();
	/* Establecer valor inicial de los LEDs */
	leds_off();
	led1_on();
	while(1); // espera
}