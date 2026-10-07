/*
 * File:   main.c
 * Author: Welcome
 *
 * Created on September 28, 2026, 2:39 PM
 */


#include <xc.h>
#include "main.h"
#include "digital_keypad.h"
#include "ssd.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
//#include "clcd.h"
#define _XTAL_FREQ 20000000

static unsigned char ssd[MAX_SSD_CNT];
unsigned int key = 0;
unsigned int delay = 0;
unsigned int flag = 0;
unsigned int count = 0;
    
void init_config(void)
{
    init_adc();
    
    TRISB = 0x00;
    PORTB = 0x00;
    
    init_can();
    TRISC = TRISC | 0X0F;
    
    //clcd_print("RPM:  INDICATOR:  ", LINE1(0));
}

void main(void)
{
    unsigned short rpm;
    unsigned char digit[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
    char rpm_data[5];
    unsigned char indicator_data[2];

    init_config();

    while(1)
    {

        rpm = (read_adc(CHANNEL4) / 10.23) * 60;

        rpm_data[0] = ((rpm / 1000) % 10 + '0');
        rpm_data[1] = ((rpm / 100) % 10 + '0');
        rpm_data[2] = ((rpm / 10) % 10 + '0');
        rpm_data[3] = (rpm % 10 + '0');
        rpm_data[4] = '\0';
        
        can_transmit(RPM_MSG_ID, rpm_data, 4);
        __delay_ms(80);
        
        key = read_digital_keypad(STATE_CHANGE);
         
            if(key == SWITCH1)
            {
                flag = 1;
                count = 0;
                PORTB = 0x00;
            }
            else if(key == SWITCH2)
            {
                flag = 2;
                count = 0;
                PORTB = 0x00;
            }
            else if(key == SWITCH3)
            {
               flag = 3;
               count = 0;
               PORTB = 0x00;
            }
        if(delay++ == 50)
        {
        if(flag == 1)
        {
            if(count % 2 == 0)
            {
                PORTB = 0x03;
            }
            else
            {
                PORTB = 0x00;
            }
            count++;
        }
        else if(flag == 2)
        {
            if(count % 2 == 0)
            {
                PORTB = 0xC0;
            }
            else
            {
                PORTB = 0x00;
            }
            count++;
        }
        else
        {
            PORTB = 0X00;
        }
            delay = 0;
        }
        
        indicator_data[0] = (flag + '0');
        indicator_data[1] = '\0';
        
        can_transmit(INDICATOR_MSG_ID, indicator_data, 1);
        __delay_ms(80);
    }
}