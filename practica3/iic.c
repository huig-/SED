#include "44b.h"
#include "iic.h"

extern uint32 mclk;			   // Frecuencia actual del reloj (Hz)

extern void DelayMs(int ms_time);

void iic_init( void )
{
    // Enable IIC & GPIO & BDMA blocks (si no se activa BDMA, el controlador IIC no es accesible)
    rCLKCON = rCLKCON | 0x2480;
    // PF[1] = IICSDA, PF[0] = IICSCL
    rPCONF = 0xA;
    // Pull-up enable
    rPUPF = 0x0;
	
    //Configurar la dirección del slave
    rIICADD = S3C44B0X_SLAVE_ADDRESS;

    //Generación ACK habilitada, interrupciones habilitadas
    rIICCON = rIICCON | 0xA0;
    rIICCON = rIICCON | ((mclk / 4000000 - 1) & 0xf); 	//Valor de preescalado, PREESCALER = mclk/16/250000 -1
	
    // Activa Tx/Rx
    rIICSTAT = 0x10;
}

void iic_putByte_start( uint8 byte )
{
	// Escribe el dato
	rIICDS = byte;
	// Máster Tx, start condition, Tx/Rx habilitada
	rIICSTAT= 0xf0;
	// Comienza la transmisión (borrando pending bit del IICCON)
	rIICCON= rIICCON & 0xef;
	// Espera la recepción de ACK
	while ((rIICSTAT & 0x1) == 1);
}

void iic_putByte( uint8 byte )
{
    // Escribe el dato
	rIICDS = byte;
	// Comienza la transmisión del dato (borrando pending bit del IICCON)
	rIICCON= rIICCON & 0xef;
    // Espera la recepción de ACK  
	while ((rIICSTAT & 0x1) == 1);
};

void iic_putByte_stop( uint8 byte )
{
    // Escribe el dato
	rIICDS = byte;
	// Comienza la trasmisión del dato (borrando pending bit del IICCON)
	rIICCON= rIICCON & 0xef;
    // Espera la recepción de ACK  
	while ((rIICSTAT & 0x1) == 1);
    
    // Máster Tx, stop condition, Tx/Rx habilitada
	rIICSTAT= 0xd0;
    // Comienza la trasmisión de STOP (borrando pending bit del IICCON)
	rIICCON= rIICCON & 0xef;
    // Espera a que la stop condition tenga efecto (5 ms para la at24c04)
	DelayMs(5);

}

void iic_getByte_start( uint8 byte )
{
	// Escribe el dato
	rIICDS = byte;
    // Máster Rx, start condition, Tx/Rx habilitada
	rIICSTAT= 0xb0;
    // Comienza la transmisión (borrando pending bit del IICCON)
	rIICCON= rIICCON & 0xef;
    // Espera la rececpión de ACK
	while ((rIICSTAT & 0x1) == 1);
}

uint8 iic_getByte( void )
{
    // Reanuda la recepción (borrando pending bit del IICCON)
	rIICCON= rIICCON & 0xef;
	// Espera la recepción del dato
	while ((rIICCON & 0x10) == 0);
    return rIICDS;// Lee el dato
}

uint8 iic_getByte_stop( int8 ack )
{
	uint8 byte;

    rIICCON = (rIICCON & ~(1 << 7)) | (ack << 7); // Habilita/deshabilita la generación de ACK

    // Reanuda la recepción (borrando pending bit del IICCON)
    rIICCON= rIICCON & 0xef;
	// Espera la recepción del dato
    while ((rIICCON & 0x10) == 0);
    byte = rIICDS;	// Lee el dato

   	// Máster Rx, stop condition, Tx/Rx habilitada
    rIICSTAT= 0x90;
   	// Comienza la trasmisión de STOP (borrando pending bit del IICCON)
    rIICCON= rIICCON & 0xef;
   	// Espera a que la stop condition tenga efecto (5 ms para la at24c04)
    DelayMs(5);

	rIICCON |= (1<<7); // Habilita la generación de ACK
   	return byte;
}
