/*
 * File:   main.c
 * Author: Welcome
 *
 * Created on September 28, 2026, 2:18 PM
 */


#include <xc.h>
#include "main.h"
#include "digital_keypad.h"
#include "clcd.h"
#include "adc.h"
#include "msg_id.h"
#include "can.h"

char gear[8][3] = {"GO","GN","G1","G2","G3","G4","G5","G6"};
unsigned char index = 0;



#ifndef DIGITAL_KEYPAD_H
#define DIGITAL_KEYPAD_H

#define LEVEL					     	0
#define STATE_CHANGE			       	1

#define KEY_PORT					PORTC

#define SWITCH1					0x0E
#define SWITCH2					0x0D
#define SWITCH3					0x0B
#define SWITCH4					0x07
#define ALL_RELEASED					0x0F

#define INPUT_PINS					0x0F

void init_digital_keypad(void);
unsigned char read_digital_keypad(unsigned char detection_type);

#endif
  


void init_digital_keypad(void)
{
	TRISC = TRISC | INPUT_PINS;
}

unsigned char read_digital_keypad(unsigned char detection_type)
{
	static unsigned char once = 1;

	if (detection_type == STATE_CHANGE)
	{
		if (((KEY_PORT & INPUT_PINS) != ALL_RELEASED) && once)
		{
			once = 0;

			return (KEY_PORT & INPUT_PINS);
		}
		else if ((KEY_PORT & INPUT_PINS) == ALL_RELEASED)
		{
			once = 1;
		}
	}
	else if (detection_type == LEVEL)
	{
		return (KEY_PORT & INPUT_PINS);
	}

	return 0xFF;
}

void init_config(void)
{
    init_digital_keypad();
   
    init_adc();
    init_can();

    clcd_print(" Speed: Gear: ", LINE1(0));
}

void main(void)
{
     unsigned char key;
    unsigned short adc_reg_val;
    unsigned int speed_value,index=0;
    char speed[3];

    init_config();

    while(1)
    {
       
        adc_reg_val = read_adc(CHANNEL4);

        speed_value = adc_reg_val / 10.23;

        speed[0] = (speed_value / 10) + '0';
        speed[1] = (speed_value % 10) + '0';
        speed[2] = '\0';

        
       // check_matrix_keypad();
        can_transmit(SPEED_MSG_ID, speed, 2);
     __delay_ms(80);
        
        
         

    key = read_digital_keypad(STATE_CHANGE);

    if(key == SWITCH1)
    {
        if(index < 7)
        {
            index++;
        }
    }
    else if(key == SWITCH2)
    {
        if(index > 0)
        {
            index--;
        }
    }

       
        can_transmit(GEAR_MSG_ID, gear[index], 2);
        __delay_ms(80);
    }
}