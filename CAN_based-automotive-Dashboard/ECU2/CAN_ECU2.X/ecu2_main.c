/*
 * File:  CAN_ECU2
 * Author: YESWANTH KUMAR
 *
 * Created on 22 September, 2025, 1:50 PM
 */

#include <xc.h>
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "ssd_display.h"
#include "digital_keypad.h"
#include "timer0.h"
#define _XTAL_FREQ 4000000

// ------------------- Global Variables -------------------
unsigned int rpm;
unsigned char key;
unsigned long delay = 0;    // Use long to avoid overflow
unsigned int flag1 = 0;
static unsigned char ssd[MAX_SSD_CNT];
unsigned int blink_counter = 0;

// 7-seg digit lookup table
static const unsigned char digit[] = 
{
    ZERO, ONE, TWO, THREE, FOUR, FIVE,
    SIX, SEVEN, EIGHT, NINE
};
unsigned int msg_id = 0;
unsigned char data[8] = {0};        // FIXED: proper char array, larger size
unsigned int length = 0;
unsigned char flag[3];

// Define macros for PORTB patterns
#define LED_MASK1   0xC0    // RB7 & RB6 ON
#define LED_MASK2   0x03    // RB1 & RB0 ON

// ------------------- Initialization -------------------
void init_config(void)
{
    PEIE=1;
    TRISB = 0x08;   // PORTB as output
    PORTB = 0x00;   // Clear PORTB
    
    init_adc();
    init_digital_keypad();
//    init_ssd_control();
    init_can();
    init_timer0();
    GIE=1;
    
}
void get_ssd(unsigned int rpm)
{
    ssd[3] = (rpm % 10);          // Ones
    ssd[2] = ((rpm / 10) % 10) ;   // Tens
    ssd[1] = ((rpm / 100) % 10);  // Hundreds
    ssd[0] = (rpm / 1000); 
//    ssd[4] = '\0';
    can_transmit( RPM_MSG_ID, ssd,4);
//    can_receive(&msg_id, data, &length);
//    if ( RPM_MSG_ID==msg_id)
//    {
//        display(data);
//    }
 
}

void main(void) 
{
    unsigned int adc_value;
    init_config();
    while (1)
    {
        // -------- Read RPM from ADC (integer math) --------
        
        adc_value = read_adc(CHANNEL4);         // 0?1023
        rpm = adc_value/10.23;         // Scale to 0?100
        rpm *= 60; 
        get_ssd(rpm);// Convert to 0?6000
        key = read_digital_keypad(STATE_CHANGE);

        if (key == SWITCH1)
        {
            flag[0] = '1';  // Indicator ON
            blink_counter = 0;
        }
        else if (key == SWITCH2)
        {
            flag[0] = '0';  // Indicator OFF
             PORTB = 0x00;
             
             
        }
        else if (key == SWITCH3)
        {
            flag[0] = '2';   // Blink mode
            blink_counter = 0;
        }
        can_transmit( INDICATOR_MSG_ID, flag,1);
        
//        can_receive(&msg_id, data, &length);
//        if(INDICATOR_MSG_ID==msg_id)
//        {
//            if(data[0]=='1')
//            {
//                flag1=1;
//            }
//            else if(data[0]=='0')
//            {
//                flag1=0;
//            }
//            else
//            {
//                flag1=2;
//            }
//        }
//       __delay_ms(100);
    }
}