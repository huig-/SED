/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "uart.h"

/*--- declaracion de funciones ---*/
int Main(void);
extern void leds_off();
extern void led1_on();
extern void led1_off();
extern void led2_on();
extern void led2_off();
extern void Eint4567_init();
extern void D8Led_symbol(int value);
extern void keyboard_init();
/*--- variables globales ---*/
char str[256];

/*--- codigo de la funcion ---*/
int Main(void){

	char *pt_str = str;
	leds_off();
	sys_init(); // inicializacion de la placa, interrupciones, puertos
	Eint4567_init();
	keyboard_init();
	Uart_Init(115200); // inicializacion de la Uart
	Uart_Config(); // configuración de interrupciones y buffers

	while(1){
		*pt_str = Uart_Getch1(); // leer caracter
		if(pt_str[0] == 'L'){
			led1_on();
			led2_off();
		} else if (pt_str[0] == 'R'){
			led2_on();
			led1_off();
		}

		else  {
			D8Led_symbol(pt_str[0]-'0');
		}
	}
}
