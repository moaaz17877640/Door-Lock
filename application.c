/*
 * File:   application.c
 * Author: MOAAZ
 *
 * Created on December 1, 2023, 10:21 PM
 */
#define HWREG8(_X)  (*((volatile unsigned char *)(_X)))
#define MOAZ_LATC (HWREG8(0xF8B))
#define MOAZ_TRISC (HWREG8(0xF94))
#include "application.h"


void app_initialize(void);
void key_pad_get(void);
keypad_t keypad_1 ={
 .pad_row[0].direction = OUTPUT ,
.pad_row[0].pin = PIN6 ,
.pad_row[0].port =PORTC_INDEX  ,
.pad_row[0].logic = LOGIC_LOW ,
.pad_row[1].direction = OUTPUT ,
.pad_row[1].pin = PIN7 ,
.pad_row[1].port =PORTC_INDEX  ,
.pad_row[1].logic = LOGIC_LOW ,
.pad_row[2].direction = OUTPUT ,
.pad_row[2].pin = PIN0 ,
.pad_row[2].port =PORTD_INDEX  ,
.pad_row[2].logic = LOGIC_LOW ,
.pad_row[3].direction = OUTPUT ,
.pad_row[3].pin = PIN1 ,
.pad_row[3].port =PORTD_INDEX  ,
.pad_row[3].logic = LOGIC_LOW ,
.pad_column[0].direction = INPUT ,
.pad_column[0].pin = PIN2 ,
.pad_column[0].port =PORTD_INDEX  ,
.pad_column[0].logic = LOGIC_LOW ,
.pad_column[1].direction = INPUT ,
.pad_column[1].pin = PIN3 ,
.pad_column[1].port =PORTD_INDEX  ,
.pad_column[1].logic = LOGIC_LOW ,
.pad_column[2].direction = INPUT ,
.pad_column[2].pin = PIN4 ,
.pad_column[2].port =PORTD_INDEX  ,
.pad_column[2].logic = LOGIC_LOW ,
    .pad_column[3].direction = INPUT ,
    .pad_column[3].pin = PIN5 ,
    .pad_column[3].port =PORTD_INDEX  ,
    .pad_column[3].logic = LOGIC_LOW 
};

chr_lcd_4bit_t lcd_2 = {
  .pin_Rs.port = PORTC_INDEX,
   .pin_Rs.pin = PIN0,
   .pin_Rs.direction = OUTPUT,
   .pin_Rs.logic =LOGIC_LOW,
   .pin_en.port = PORTC_INDEX,
   .pin_en.pin = PIN1,
   .pin_en.direction = OUTPUT,
   .pin_en.logic = LOGIC_HIGH,
    
  .lcd_pins[0].port = PORTC_INDEX,
  .lcd_pins[0].logic = LOGIC_LOW,
  .lcd_pins[0].direction = OUTPUT,
  .lcd_pins[0].pin = PIN2,
   
  .lcd_pins[1].port = PORTC_INDEX,
  .lcd_pins[1].pin = PIN3,
  .lcd_pins[1].direction = OUTPUT,
   .lcd_pins[1].logic = LOGIC_LOW,
   
   .lcd_pins[2].port = PORTC_INDEX,
    .lcd_pins[2].pin = PIN4,
  .lcd_pins[2].direction = OUTPUT,
  .lcd_pins[2].logic = LOGIC_LOW,
   
   .lcd_pins[3].port = PORTC_INDEX,
   .lcd_pins[3].pin = PIN5 ,
   .lcd_pins[3].direction = OUTPUT,
   .lcd_pins[3].logic = LOGIC_LOW,

          
};
motor_t motor_1 ={ 
 .motors[0].pin= PIN0 ,
 .motors[0].port = PORTB_INDEX ,
 .motors[0].logic = MOTOR_OFF_STATUS ,
 .motors[0].direction = OUTPUT , 
 .motors[1].pin = PIN1 ,
 .motors[1].port = PORTB_INDEX ,
 .motors[1].logic = MOTOR_OFF_STATUS ,
 .motors[1].direction = OUTPUT ,
};
motor_t motor_2 ={ 
 .motors[0].pin= PIN2 ,
 .motors[0].port = PORTB_INDEX ,
 .motors[0].logic = MOTOR_OFF_STATUS ,
 .motors[0].direction = OUTPUT , 
 .motors[1].pin = PIN3 ,
 .motors[1].port = PORTB_INDEX ,
 .motors[1].logic = MOTOR_OFF_STATUS ,
 .motors[1].direction = OUTPUT ,
}; 
 led_t red ={
    .pin = PIN0 ,
    .port = PORTA_INDEX ,
    .statu = LED_OFF
};
led_t green ={
    .pin = PIN1 ,
    .port = PORTA_INDEX ,
    .statu = LED_OFF
};


Std_ReturnType ret = E_NOT_OK;
uint8 value =0;
uint8 str[5]  ;
uint8 Stored_password[5] = {'1' , '2', '3' , '4'};
uint8 enter_password[5]= {0x0 ,0x0 ,0x0 ,0x0} ;
static uint8 num_of_incor= 0 ;
int main() {
    
    EEPROM_Read_Data(0x14 , &num_of_incor);
    app_initialize();
    while(1){
    
//      ret = lcd_4bit_send_data_string_posit(&lcd_2 , 1 ,1 ,"HELLO");
//     __delay_ms(1000);
//     ret = lcd_4bit_send_command(&lcd_2 , LCD_CLEAR_DISPLAY);
//     __delay_ms(1000);
     ret = lcd_4bit_send_data_string_posit(&lcd_2 , 1 ,3 ,"enter password");
     __delay_ms(500);
     ret = lcd_4bit_send_command(&lcd_2 , LCD_CLEAR_DISPLAY);
     __delay_ms(500);
     key_pad_get();
     for(int k = 0 ; k<4 ; k++){
         if(Stored_password[k]==enter_password[k]){
             value++;
         }else{
             break ;
         }
     }
     if(value == 4){
         value =0 ;
     ret = lcd_4bit_send_data_string_posit(&lcd_2 , 1 ,1 ,"correct password");
      EEPROM_Write_Data( 0x14, 0);
        ret = led_on(&green);
        //open the door
        motor_move_right(&motor_1);
        motor_move_right(&motor_2);
       __delay_ms(1000);
       ret = lcd_4bit_send_command(&lcd_2 , LCD_CLEAR_DISPLAY);
     __delay_ms(1000);
     //lock door again
     ret = lcd_4bit_send_data_string_posit(&lcd_2 , 1 ,1 ,"look door again");
        motor_move_left(&motor_1);
        motor_move_left(&motor_2);
      __delay_ms(1000);
      ret = lcd_4bit_send_command(&lcd_2 , LCD_CLEAR_DISPLAY);
     }else { 
         
      ret = lcd_4bit_send_data_string_posit(&lcd_2 , 1 ,1 ,"incorrect");
     ret = led_on(&red);
       __delay_ms(1000);
     
      ret = lcd_4bit_send_command(&lcd_2 , LCD_CLEAR_DISPLAY);
     __delay_ms(1000);
     EEPROM_Write_Data( 0x14, ++num_of_incor);
     if( 3 == num_of_incor){
         EEPROM_Write_Data( 0x14, 0);
          ret = lcd_4bit_send_data_string(&lcd_2  ,"please wait:");
          for(int i = 30 ; i>=0 ; i--){
              convert_uint8_to_string(i , &str);
           ret = lcd_4bit_send_data_string_posit(&lcd_2 , 1 ,13 ,str);
           ret = lcd_4bit_send_data_char(&lcd_2 ,' ');
           __delay_ms(1000);
           
          }
         ret = lcd_4bit_send_command(&lcd_2 , LCD_CLEAR_DISPLAY);
          __delay_ms(1000);
     }
     }
     
      return (EXIT_SUCCESS);
    }
   
    
}

void  app_initialize(void) {

    Std_ReturnType ret = E_NOT_OK;
    ret =keypad_initialize(&keypad_1);
    ret= lcd_4bit_initialize(&lcd_2);
    ret = motor_initialize(&motor_1); 
     ret = motor_initialize(&motor_2);
     ret= led_intalize(&red);
     ret= led_intalize(&green);
}   
void key_pad_get(void){
    while(1){
        for(int i= 0 ; i< 4 ; ){
            if(enter_password[i] == 0x0){
        ret = keypad_get_value(&keypad_1 , &enter_password[i]); 
        
            }else{
                
                i++;
                __delay_ms(250);
            }
            ret= lcd_4bit_send_data_char_posit(&lcd_2 , 2, i+1 ,enter_password[i]);
           __delay_us(1000);
            if(enter_password[i]){
            ret= lcd_4bit_send_data_char_posit(&lcd_2 , 2, i+1 ,'*');
            
            }
        }
        if(enter_password[3] != 0x0){
            break ;
        }
    }

}