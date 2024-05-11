/* 
 * File:   application.h
 * Author: Moaaz elmahi
 *
 * Created on December 1, 2023, 10:34 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H
/* SECTION : includes*/
#include "ECU_Layer/LED/ecu_led.h"
#include "ECU_Layer/BUTTON/ecu_botton.h"
#include "ECU_Layer/RELAY/relay_ecu.h"
#include "ECU_Layer/DC_MOTOR/ecu_dc_motor.h"
#include "ECU_Layer/7_Segment/7_segment.h"
#include "ECU_Layer/KEYPAD/ecu_keypad.h"
#include "ECU_Layer/CHR_LCD/ecu_chr_lcd.h"
#include "MCAL_Layer/Interrupt/mcal_external_interrupt.h"
#include"MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
#include"MCAL_Layer/ADC/hal_adc.h"
#include "ecu_init.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"
#include "MCAL_Layer/ADC/hal_adc.h"
#include "MCAL_Layer/device_config.h"
#include "MCAL_Layer/TIMER0/hal_timer0.h"
#include "MCAL_Layer/TIMER1/hal_timer1.h"
#include "MCAL_Layer/TIMER2/hal_timer2.h"
#include "MCAL_Layer/TIMER3/hal_timer3.h"
#include "MCAL_Layer/MSSP_I2C/hal_i2c.h"
#include "MCAL_Layer/CPP1/hal_ccp.h"
#include "MCAL_Layer/MSSP_SPI/hal_spi.h"
/*  SECTION :macro declarations  */

/* SECTION : macro function declarations */

/* SECTION : datatype declarations */

/* SECTION : functions declaration*/

#endif	/* APPLICATION_H */

