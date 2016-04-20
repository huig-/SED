/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "uart.h"
/*--- declaracion de funciones ---*/
int Main(void);
extern int update;
extern int switch_leds;

int led1 = 1;
int led2 = 1;
extern void Eint4567_init(void);
extern void D8Led_symbol(int value);
//extern void timer_init();
extern void leds_off();
extern void led1_on();
extern void leds_switch();
extern void increaseFreq();
extern void decreaseFreq();

/*--- variables globales ---*/
char str_send[10] = "\nSED-P4 >\0";
char str_error[50] = "\nSe ha producido un desbordamiento!\n\0";
char str[256];

/*--- codigo de la funcion ---*/
int Main(void){

	char *pt_str = str;

	sys_init(); // inicializacion de la placa, interrupciones, puertos

	Eint4567_init();

	Uart_Init(115200); // inicializacion de la Uart
	//*** Uart_Config(); // configuración de interrupciones y buffers
	Uart_Printf(str_send); // mostrar cabecera

	 // D8Led_symbol(8);//8
	leds_off();
	    Eint4567_init();
	   // keyboard_init();
	    while( 1 ){

	/*while(1){
		*pt_str = Uart_Getch(); // leer caracter

		
		 Uart_SendByte(*pt_str); // enviar caracter
		if (*pt_str == CR_char){ // retorno de carro?
			if (pt_str != str) { // si cadena no vacia, mostrar
				*(++pt_str) = '\0'; // terminar cadena antes
				Uart_Printf("\n");
				Uart_Printf(str);
			}
			Uart_Printf(str_send); // preparar siguiente
			pt_str = str;
		}
		else if (++pt_str == str + 255){ // desbordamiento?
			Uart_Printf(str_error); // avisar del desbordamiento
			pt_str = str;
		}
		*/
		while(1){
			*pt_str = Uart_Getch1(); // leer caracter


			 Uart_SendByte1(*pt_str); // enviar caracter
			if (*pt_str == CR_char){ // retorno de carro?
				if (pt_str != str) { // si cadena no vacia, mostrar
					*(++pt_str) = '\0'; // terminar cadena antes
					Uart_Printf1("\n");
					Uart_Printf1(str);
				}
				Uart_Printf1(str_send); // preparar siguiente
				pt_str = str;
			}
			else if (++pt_str == str + 255){ // desbordamiento?
				Uart_Printf1(str_error); // avisar del desbordamiento
				pt_str = str;
			}

		}

	    }
}
