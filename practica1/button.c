/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "def.h"
/*--- variables globales ---*/
int symbol = 0;
/*--- funciones externas ---*/
//extern void D8Led_Symbol(int value);
/*--- declaracion de funciones ---*/
void Eint4567_ISR(void) __attribute__ ((interrupt ("IRQ")));
void Eint4567_init(void);
extern void leds_switch ();
extern void D8Led_symbol(int value);

/*--- codigo de funciones ---*/

void button_init(void)
{
	rPCONG = rPCONG & ~(0x1<<12);
	rPCONG = rPCONG & ~(0x1<<13);
	rPCONG = rPCONG & ~(0x1<<14);
	rPCONG = rPCONG & ~(0x1<<15);
	//rPCONG = 0x0;
	rPUPG = 0x0;
}
void Eint4567_init(void)
{
/* Configuracion del controlador de interrupciones */
	// Borra EXTINTPND escribiendo 1s en el propio registro
	rEXTINTPND = 0xf;
	// Borra INTPND escribiendo 1s en I_ISPC
	rI_ISPC = 0x3ffffff;
	// Configura las lineas como de tipo IRQ mediante INTMOD
	rINTMOD = 0x0; 
	// Habilita int. vectorizadas y la linea IRQ (FIQ no) mediante INTCON
	rINTCON = 0x1;
	// Enmascara todas las lineas excepto Eint4567 y el bit global (INTMSK)
	rINTMSK = ~(BIT_EINT4567 | BIT_GLOBAL);
	// Establecer la rutina de servicio para Eint4567
	pISR_EINT4567 = (unsigned)Eint4567_ISR;
/* Configuracion del puerto G */
	// Establece la funcion de los pines (EINT7-EINT0)
	rPCONG = 0xff3f; //rPCONG como arriba!
	//Habilita las resistencias de pull-up
	rPUPG = 0x0;
	// Configura las lineas de int. como de flanco de bajada mediante EXTINT
	rEXTINT = 0x22222222;
/* Por precaucion, se vuelven a borrar los bits de INTPND y EXTINTPND */
	rEXTINTPND = 0xf;
	rI_ISPC = 0x3ffffff;
}

/*COMENTAR PARA LA PARTE DEL 8-SEGMENTOS
DESCOMENTAR PARA LA PRIMERA PARTE CON INTERRUPCIONES
*/
void Eint4567_ISR(void)
{
	while (is_button_pressed());
	//Conmutamos LEDs
	leds_switch();
	//Delay para eliminar rebotes
	DelayMs(100);
	
	/*Atendemos interrupciones*/
	//Borramos EXTINTPND ambas líneas EINT7 y EINT6
	rEXTINTPND = 0xC;
	//Borramos INTPND usando ISPC
	rI_ISPC = BIT_EINT4567;
}

/*DESCOMENTAR PARA LA PARTE DEL 8-SEGMENTOS
COMENTAR PARA LA PRIMERA PARTE CON INTERRUPCIONES
int which_int;
void Eint4567_ISR(void)
{
	//Identificar la interrupcion
	//which_int = rEXTINTPND;
	//Actualizar simbolo
	//switch (which_int) {
	//    case 0x4: //pulsador 1
    	//	led1_on(); led2_off(); //configuramos los leds
	//	symbol++;
	//	break;
	//    case 0x8: //pulsador 2
	//	led1_off(); led2_off();
	//	symbol--;
	//	break;
	//}
	// muestra el simbolo en el display
	//D8Led_symbol(symbol%16);
	// espera 100ms para evitar rebotes
	//DelayMs(100);
	
	// borra los bits en EXTINTPND  
	//rEXTINTPND = rEXTINTPND | 0xC;
	// borra el bit pendiente en INTPND
	//rI_ISPC = BIT_EINT4567;
//}
