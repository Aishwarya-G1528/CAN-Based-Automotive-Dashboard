/*
 * File:   main.c
 * Author: Welcome
 *
 * Created on October 6, 2026, 11:40 AM
 */


#include <xc.h>
#include "main.h"
#include "can.h"
#include "clcd.h"
#include "msg_id.h"

unsigned char delay = 0;
unsigned int count = 0;
unsigned char flag = 0;

void init_config(void)
{
    init_clcd();
    

    TRISB = 0x00;
    PORTB = 0x00;
    init_can();

    clcd_print("S:  G:  R:  I:  ", LINE1(0));
}

void main(void)
{
    unsigned int rx_msg_id;
    unsigned char rx_data[5];
    unsigned int rx_len;

    init_config();

    while(1)
    {
        can_receive(&rx_msg_id, rx_data, &rx_len);

        if(rx_msg_id == SPEED_MSG_ID)
        {
            rx_data[2] = '\0';
            clcd_print((char *)rx_data, LINE2(0));
        }

        else if(rx_msg_id == GEAR_MSG_ID)
        {
            rx_data[2] = '\0';
            clcd_print((char *)rx_data, LINE2(3));
        }

        else if(rx_msg_id == RPM_MSG_ID)
        {
            rx_data[4] = '\0';

            clcd_print((char *)rx_data, LINE2(6));
        }

        else if(rx_msg_id == INDICATOR_MSG_ID)
        {
            flag = (rx_data[0] - '0');
            rx_data[1] = '\0';
          
            if(flag == 1)
            {
                clcd_print("<-", LINE2(11));
            }
            else if(flag == 2)
            {
                clcd_print("->", LINE2(11));
            }
            else if(flag == 3)
            {
                clcd_print("  ", LINE2(11));
            }
       }

        if(delay++ == 100)
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
                PORTB = 0x00;
            }

            delay = 0;
        }
    }
}