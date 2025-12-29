#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"

uint16_t get_rpm()
{
    // Read and convert ADC value to RPM
    unsigned int adc_value = read_adc(CHANNEL4);
    uint16_t rpm = adc_value / 10.23;  // Scale 0?100
    rpm *= 60;                         // Convert to 0?6000
    return rpm;
}

uint16_t get_engine_temp()
{
    // Placeholder for engine temperature sensor
    // For future expansion (use another ADC channel)
    return read_adc(CHANNEL5);
}

IndicatorStatus process_indicator()
{
    // Only transmit indicators, no receive logic here
    return e_ind_off;
}
