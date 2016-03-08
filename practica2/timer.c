/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "44blib.h"
#include <stdlib.h>

int cont;
int numeros[4];
/*--- funciones externas ---*/
extern void D8Led_symbol(int value);
extern int fila;
/*--- declaracion de funciones ---*/
void timer0_ISR(void) __attribute__ ((interrupt ("IRQ")));
void timer0_init(void);
/*--- codigo de las funciones ---*/

void shuffle(int *array, size_t n)
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

void generar_numeros_aleatorios()
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

void timer0_init(void)
{
	/* Configuracion del controlador de interrupciones */	
	rINTMOD=0x0;// Configurar las lineas como de tipo IRQ	
	rINTCON=0x1;// Habilitar int. vectorizadas y la linea IRQ (FIQ no)	
	rINTMSK = rINTMSK & ~(BIT_TIMER0 | BIT_GLOBAL);// Enmascarar todas las lineas excepto Timer0 y el bit global
	/* Establece la rutina de servicio para TIMER0 */
	pISR_TIMER0=(unsigned)timer0_ISR;
	/* Configurar el Timer0 (el resto de los timers se dejan a la
	configuración por defecto) */
	rTCFG0=0xFF;// pre-escalado = 255
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
	if (cont == 0)
		rINTMSK = rINTMSK | BIT_TIMER0; //desactivamos la interrupcion
	rI_ISPC = BIT_TIMER0;
}
