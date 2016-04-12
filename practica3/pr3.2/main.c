#include "s3cev40.h"
#include "common_types.h"
#include "at24c04.h"

extern void DelayMs(int ms_time);
extern void sys_init();
extern void iic_init();
extern void D8Led_symbol(int value);
extern void at24c04_bytewrite( uint16 addr, uint8 data );
extern void at24c04_byteread( uint16 addr, uint8 *data );
extern void Eint4567_init(void);
extern void keyboard_init();

int val;

void Main( void )
{
    uint8 buffer[AT24C04_DEPTH];
    uint16 i;
    
    sys_init();
    iic_init();
    D8Led_symbol(8);//8
    Eint4567_init();
    keyboard_init();
    while( 1 );
}
