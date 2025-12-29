#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"

volatile unsigned char led_state = LED_OFF, status = e_ind_off;
    
// Storage for display data
static unsigned char speed_str[3] = "00";
static unsigned char gear_str[3] = "ON";
static unsigned char rpm_str[5] = "0000";

void handle_speed_data(uint8_t *data, uint8_t len)
{
   // if (len >= 2) 
    {
        // Data is sent as ASCII digits from ECU1
        speed_str[0] = data[0];
        speed_str[1] = data[1];
      //  speed_str[2] = '\0';
        
        // Display on CLCD Line 2, position 0-1
        clcd_print(speed_str, LINE2(0));
    }
}

void handle_gear_data(uint8_t *data, uint8_t len) 
{
   // if (len >= 2) 
    //{
        // Gear data sent as string (ON, GN, G1, G2, etc.)
        gear_str[0] = data[0];
        gear_str[1] = data[1];
        gear_str[2] = '\0';
        
        // Display on CLCD Line 2, position 3-4
        clcd_print(gear_str, LINE2(3));
    //}
}

void handle_rpm_data(uint8_t *data, uint8_t len) 
{
    if (len >= 4) 
    {
        // RPM sent as 4 digit values (0-9), convert to ASCII
        for (int i = 0; i < 4; i++) 
        {
            rpm_str[i] = data[i] + '0';  // Convert digit to ASCII
        }
        rpm_str[4] = '\0';
        
        // Display on CLCD Line 2, position 6-9
        clcd_print(rpm_str, LINE2(6));
    }
}

void handle_engine_temp_data(uint8_t *data, uint8_t len) 
{
    // Temperature function - not implemented yet
}

void handle_indicator_data(uint8_t *data, uint8_t len) 
{
    if (len >= 1) 
    {
        // Indicator data: '0' = off, '1' = left, '2' = right
        if (data[0] == '1') 
        {
            status = e_ind_left;
            clcd_print("<-", LINE2(11));  // Left arrow (2 chars)
        }
        else if (data[0] == '2') 
        {
            status = e_ind_right;
            clcd_print("->", LINE2(11));  // Right arrow (2 chars)
        }
        else  // '0' = OFF
        {
            status = e_ind_off;
            clcd_print("--", LINE2(11));  // Off shows dashes (2 chars)
            LEFT_IND_OFF();
            RIGHT_IND_OFF();
            led_state = LED_OFF;
        }
    }
}

void process_canbus_data() 
{   
    uint16_t msg_id = 0;
    uint8_t data[8] = {0};
    uint8_t len = 0;
    
    // Try to receive CAN message
    can_receive(&msg_id, data, &len);
    
    // If data received, process based on message ID
    if (len > 0) 
    {
        switch (msg_id) 
        {
            case SPEED_MSG_ID:
                handle_speed_data(data, len);
                break;
                
            case GEAR_MSG_ID:
                handle_gear_data(data, len);
                break;
                
            case RPM_MSG_ID:
                handle_rpm_data(data, len);
                break;
                
            case ENG_TEMP_MSG_ID:
                handle_engine_temp_data(data, len);
                break;
                
            case INDICATOR_MSG_ID:
                handle_indicator_data(data, len);
                break;
                
            default:
                // Unknown message ID, ignore
                break;
        }
    }
}