#include "ecu1_sensor.h"
#include "adc.h"
#include "can.h"
#include "matrix_keypad.h"
#include "msg_id.h"
#define _XTAL_FREQ 2000000000


unsigned char key;
static int index = 0, flag = 0;
char event[9][3] = {"ON", "GN", "G1", "G2", "G3", "G4", "G5", "GR", "C_"};

uint16_t get_speed(void)
{
    uint16_t velocity;
    char speed_str[3];

    velocity = read_adc(CHANNEL4) / 10.23;
    speed_str[1] = (velocity % 10) + '0';
    speed_str[0] = (velocity / 10) + '0';
    speed_str[2] = '\0';

    can_transmit(SPEED_MSG_ID, speed_str, 2);
     __delay_ms(10);

    return velocity;
}

unsigned char get_gear_pos(void)
{
    key = read_switches(STATE_CHANGE);

    if (key != ALL_RELEASED)
    {
        if (key == MK_SW1)
        {
            index++;
            if (flag == 1 && index >= 8)
            {
                index = 1;
                flag = 0;
            }
            if (index > 7)
                index = 7;
        }
        else if (key == MK_SW2)
        {
            index--;
            if (flag == 1 && index >= 7)
            {
                index = 1;
                flag = 0;
            }
            if (index <= 0)
                index = 0;
        }
        else if (key == MK_SW3)
        {
            index = 8;
            flag = 1;
        }
    }

    can_transmit(GEAR_MSG_ID, event[index], 2);
     __delay_ms(10);

    return index;
}