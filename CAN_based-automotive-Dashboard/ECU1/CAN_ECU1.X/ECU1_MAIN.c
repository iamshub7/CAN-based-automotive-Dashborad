/*
 * File:  CAN_ECU1
 * Author: Yeswanth kumar
 *
 * Created on 19 September, 2025, 1:50 PM
 */

#include <xc.h>
#include "clcd.h"
#include "matrix_keypad.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "ecu1_sensor.h"
#define _XTAL_FREQ 2000000000

static void init_config(void)
{
    init_adc();
    init_clcd();
    init_matrix_keypad();
    init_can();
}

void main(void)
{
    init_config();

    while (1)
    {
        get_speed();
        get_gear_pos();
    }
}