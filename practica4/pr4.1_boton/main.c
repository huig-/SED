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
extern void leds_switch();
extern void Eint4567_init();
extern void D8Led_symbol(int value);
/*--- variables globales ---*/
char str_send[10] = "\nSED-P4 >\0";
char str_error[50] = "\nSe ha producido un desbordamiento!\n\0";
char str[256];
int led1 = 1;
int led2 = 1;
/*--- codigo de la funcion ---*/
int Main(void){

	char *pt_str = str;
	D8Led_symbol(4);
	leds_off();

	int count = 0;
	sys_init(); // inicializacion de la placa, interrupciones, puertos
	Eint4567_init();
	Uart_Init(115200); // inicializacion de la Uart
	Uart_Config(); // configuración de interrupciones y buffers
	Uart_Printf1(str_send); // mostrar cabecera

	while(1){
		*pt_str = Uart_Getch1(); // leer caracter
		//Uart_SendByte(*pt_str); // enviar caracter no
		if(pt_str[0] == 'L'){
			led1_on();
			D8Led_symbol(6);
			led2_off();
		} else if (pt_str[0] == 'R'){
			led2_on();
			D8Led_symbol(7);
			led1_off();
		}

		if (*pt_str == CR_char){ // retorno de carro?
			if (pt_str != str) { // si cadena no vacia, mostrar
				*(++pt_str) = '\0'; // terminar cadena antes
				Uart_Printf1("\n");
				Uart_Printf1(str);


			}
			else{
				Uart_Printf1(str_send); // preparar siguiente
				pt_str = str;

				///
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
