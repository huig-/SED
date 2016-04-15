/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "def.h"
#include "common_types.h"

/*--- variables globales ---*/
int button;
/*--- funciones externas ---*/
//extern void D8Led_Symbol(int value);
/*--- declaracion de funciones ---*/
void Eint4567_ISR(void) __attribute__ ((interrupt ("IRQ")));
void Eint4567_init(void);
extern void leds_switch ();
extern void D8Led_symbol(int value);
//extern void at24c04_bytewrite( uint16 addr, uint8 data );
//extern void at24c04_byteread( uint16 addr, uint8 *data );



/*--- codigo de funciones ---*/

int esta_pulsado(void)
{
	int aux = rPDATG & (0x3<<6);
	if (aux != 0xC0)
		return 1;
	else return 0;
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
	rPCONG = 0xf000;

	//Habilita las resistencias de pull-up
	rPUPG = 0x0;
	// Configura las lineas de int. como de flanco de bajada mediante EXTINT
	rEXTINT = 0x22222222;
	/* Por precaucion, se vuelven a borrar los bits de INTPND y EXTINTPND */
	rEXTINTPND = 0xf;
	rI_ISPC = 0x3ffffff;
}

void Eint4567_ISR(void)
{
	//Detectamos que boton se ha pulsado
	if ((rPDATG & (0x1<<6)) == 0) {
	    button = 0;
	}
	else {
	    button = 1;
	}
	while (esta_pulsado());

	//Delay para eliminar rebotes
	DelayMs(100);
	
	//Atendemos interrupciones
	//Borramos EXTINTPND ambas líneas EINT7 y EINT6
	rEXTINTPND = 0xC;
	//Borramos INTPND usando ISPC
	rI_ISPC = BIT_EINT4567;
}
