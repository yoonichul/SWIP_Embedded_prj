/*
 * main_controller.c
 *
 *  Created on: 2022. 6. 14.
 *      Author: user
 */

#include <main_controller.h>


enum {IDLE = 0, BCA_SCENE = 1, SCC_SCENE = 2, TUNNEL_SCENE = 3};

unsigned char scenario_button = IDLE;
extern unsigned int left_us_range;
extern unsigned int right_us_range;

void controller_init(void)
{
    initERU01();
    initERU02();
    initERU03();
    initCCU60();
    initCCU61();
    initButton();
    initRGBLED();
    init_left_UltraSonic();
    init_right_UltraSonic();
    initGTM();
    init_VADC_light_sensor();
    initLED_PWM();
    PWM_trigger();
}
void doWork(void)
{
    switch(scenario_button)
    {
    case IDLE:
    {
        idle_func();
    }
        break;
    case BCA_SCENE:
    {
        BCA_SCENE_func();
    }
        break;
    case SCC_SCENE:
    {
        SCC_SCENE_func();
    }
        break;
    case TUNNEL_SCENE:
    {
        TUNNEL_SCENE_func();
    }
        break;
    default:
        scenario_button = IDLE;
        break;
    }
}


void idle_func(void)
{
    P02_OUT.U &= ~(0x1 << P7_BIT_LSB_IDX);    // LED RED D9 (RGB)
    P10_OUT.U &= ~(0x1 << P5_BIT_LSB_IDX); // LED GREEN D10 (RGB)
    P10_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX); // LED BLUE D11 (RGB)
    BLUE_change_duty_ratio(1);
    RED_change_duty_ratio(1);
}
void BCA_SCENE_func(void)
{
    P02_OUT.U |= (0x1 << P7_BIT_LSB_IDX);    // LED RED D9 (RGB)
    for(unsigned int i = 0; i < 10000000; i++ );
      right_UltraSonic_trigger();
      while(get_right_range_valid_flag() == 0);
      if(right_us_range >= 0 && right_us_range <= 10 )
      {
          BLUE_change_duty_ratio(12500);
//        BUZZER_FUNCTION
      }
      else if(right_us_range > 10 && right_us_range <= 30 )
      {
          BLUE_change_duty_ratio(6500);
//        BUZZER_FUNCTION
      }
      else if(right_us_range > 30 && right_us_range <= 60 )
      {
          BLUE_change_duty_ratio(3000);
      }
      else
      {
          BLUE_change_duty_ratio(1);
      }
      left_UltraSonic_trigger();
      while(get_left_range_valid_flag() == 0);
      if(left_us_range >= 0 && left_us_range <= 10 )
      {
          RED_change_duty_ratio(12500);
          //        BUZZER_FUNCTION
      }
      else if(left_us_range > 10 && left_us_range <= 30 )
      {
          RED_change_duty_ratio(6500);
          //        BUZZER_FUNCTION
      }
      else if(left_us_range > 30 && left_us_range <= 60 )
      {
          RED_change_duty_ratio(3000);
      }
      else
      {
          RED_change_duty_ratio(1);
      }
}
void SCC_SCENE_func(void)
{
     P02_OUT.U &= ~(0x1 << P7_BIT_LSB_IDX);    // LED RED D9 (RGB)
     P10_OUT.U |= (0x1 << P5_BIT_LSB_IDX); // LED GREEN D10 (RGB)
     P10_OUT.U &= ~(0x1 << P3_BIT_LSB_IDX); // LED BLUE D11 (RGB)

     for(unsigned int i = 0; i < 10000000; i++ );
     left_UltraSonic_trigger();
     while(get_right_range_valid_flag() == 0);
     if(left_us_range >= 0 && left_us_range <= 40 )
     {
         RED_change_duty_ratio(12500);
         BLUE_change_duty_ratio(1);
         if(left_us_range <= 20)
         {
         //        BUZZER_FUNCTION
         }
     }
     else
     {
         BLUE_change_duty_ratio(12500);
         RED_change_duty_ratio(1);
     }
}
void TUNNEL_SCENE_func(void)
{
    unsigned int adcResult = 0;
    P02_OUT.U &= ~(0x1 << P7_BIT_LSB_IDX);    // LED RED D9 (RGB)
    P10_OUT.U &= ~(0x1 << P5_BIT_LSB_IDX); // LED GREEN D10 (RGB)
    P10_OUT.U |= (0x1 << P3_BIT_LSB_IDX); // LED BLUE D11 (RGB)
    VADC_light_sensor_startConversion();
    adcResult = VADC_light_sensor_readResult();
    if(adcResult < 700)
    {
        RED_change_duty_ratio(12500);
        BLUE_change_duty_ratio(12500);
    }
    else
    {
        RED_change_duty_ratio(1);
        BLUE_change_duty_ratio(1);
    }
}
