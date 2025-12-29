/*
 * File:  CAN_ECU3
 * Author: YESWANTH KUMAR
 *
 * Created on 25 September, 2025, 1:50 PM
 */
#include <xc.h>
#include <stdint.h>
#include "can.h"
#include "clcd.h"
#include "msg_id.h"
#include "message_handler.h"
#include "isr.h"
#include "timer0.h"

static void init_leds() 
{
    TRISB = 0x08; // Set RB2 as output, RB3 as input, remaining as output
    PORTB = 0x00; // Turn off all LEDs initially
    TRISB1 = 0;
    TRISB6 = 0;
    TRISB7 = 0;
}

static void init_config(void) 
{
    // Initialize CLCD and CANBUS
    init_clcd();
    init_can();
    init_leds();
    // Enable Interrupts
    PEIE = 1;
    GIE = 1;
    init_timer0();
}

void main(void) 
{
    static unsigned int blink_count = 0;
    static unsigned char blink_state = 0;
    
    // Initialize peripherals
    init_config();
    
    // Display static labels
    clcd_print("SP GR RPM  IND", LINE1(0));
    //clcd_print("00 ON 0000  - ", LINE2(0));
    
    // Ensure all LEDs are off at start
  //  PORTB = PORTB & 0x3C;
    
    /* ECU2 main loop */
    while (1) 
    {
        // Receive CAN messages from ECU1 and ECU2
        process_canbus_data();

        // Handle indicator LED blinking
        if (status == e_ind_left || status == e_ind_right) 
        {
            blink_count++;
            if (blink_count >= 10000) // Adjust for MCU speed
            {
                blink_count = 0;
                blink_state = !blink_state;

                if (status == e_ind_left) 
                {
                    if (blink_state)
                        LEFT_IND_ON();
                    else
                        LEFT_IND_OFF();
                        RIGHT_IND_OFF();
                } 
                else if (status == e_ind_right) 
                {
                    if (blink_state)
                        RIGHT_IND_ON();
                    else
                        RIGHT_IND_OFF();
                        LEFT_IND_OFF();
                }
            }
        } 
        else // Indicator OFF
        {
            LEFT_IND_OFF();
            RIGHT_IND_OFF();
            blink_state = 0;
            blink_count = 0;
        }
    }
    return;
}