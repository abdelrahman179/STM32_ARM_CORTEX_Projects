/*
 * main.c
 *
 *  Created on: Sep 14, 2020
 *      Author: A.I.Zaki
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "NVIC_interface.h"
#include "EXTI_interface.h"
#include "STK_interface.h"

#include "IR_interface.h"
#include "delay.h"

u8 LED_ARR[16] = {GPIOA , 9  , GPIOA , 10 , GPIOA , 11 , GPIOA , 12 , GPIOB , 12 ,GPIOB , 13 ,GPIOB , 14 ,GPIOB , 15 };

void LEDS_voidInit(void)
{
	/* initialize port */
	MGPIO_voidSetPinDirection(GPIOA , 9 , 0b0001);
	MGPIO_voidSetPinDirection(GPIOA , 10, 0b0001);
	MGPIO_voidSetPinDirection(GPIOA , 11, 0b0001);
	MGPIO_voidSetPinDirection(GPIOA , 12, 0b0001);
	MGPIO_voidSetPinDirection(GPIOB , 12, 0b0001);
	MGPIO_voidSetPinDirection(GPIOB , 13, 0b0001);
	MGPIO_voidSetPinDirection(GPIOB , 14, 0b0001);
	MGPIO_voidSetPinDirection(GPIOB , 15, 0b0001);
}

void LEDS_PingPong(void)
{
	for(u8 i = 0 ; i < 16 ; i+=2)
	{
		MGPIO_voidSetPinValue(LED_ARR[i] , LED_ARR[i+1] , HIGH);
		delay_ms(200);
		MGPIO_voidSetPinValue(LED_ARR[i] , LED_ARR[i+1] , LOW);
	}
	for(u8 i = 12 ; i > 0 ; i-=2)
	{
		MGPIO_voidSetPinValue(LED_ARR[i] , LED_ARR[i+1] , HIGH);
		delay_ms(200);
		MGPIO_voidSetPinValue(LED_ARR[i] , LED_ARR[i+1] , LOW);
	}

}

void LEDS_IN_OUT(void)
{
	u8 MID_1 = 6 ;
	u8 MID_2 = 8 ;
	for(u8 i = 0 ; i < 4 ; i++)
	{
		MGPIO_voidSetPinValue(LED_ARR[MID_1] , LED_ARR[MID_1 + 1] , HIGH);
		MGPIO_voidSetPinValue(LED_ARR[MID_2] , LED_ARR[MID_2 + 1] , HIGH);
		MID_1 -= 2 ;
		MID_2 += 2 ;
		delay_ms(200);
	}

	MID_1 = 0 ;
	MID_2 = 14 ;

	for(u8 i = 0 ; i < 4 ; i++)
	{
		MGPIO_voidSetPinValue(LED_ARR[MID_1] , LED_ARR[MID_1 + 1] , LOW);
		MGPIO_voidSetPinValue(LED_ARR[MID_2] , LED_ARR[MID_2 + 1] , LOW);
		MID_1 += 2 ;
		MID_2 -= 2 ;
		delay_ms(200);
	}
}

void LEDS_FLASHING(void)
{
	for(u8 i = 0 ; i < 16 ; i+=2)
	{
		MGPIO_voidSetPinValue(LED_ARR[i] , LED_ARR[i + 1] , HIGH);
	}
	delay_ms(300);

	for(u8 i = 0 ; i < 16 ; i+=2)
	{
		MGPIO_voidSetPinValue(LED_ARR[i] , LED_ARR[i + 1] , LOW);
	}
	delay_ms(300);
}

void LEDS_STOP(void)
{
	for(u8 i = 0 ; i < 16 ; i+=2)
	{
		MGPIO_voidSetPinValue(LED_ARR[i] , LED_ARR[i + 1] , LOW);
	}
}

int main()
{

	/* Lw mandetsh 3ala el RCC Init el default haysht3'al 3ala el
		 * HSI w el PLL on = 72MHz*/
	MRCC_voidInitSysClock();
	MRCC_voidEnableClock(APB2_BUS , GPIOA_RCC);
	MRCC_voidEnableClock(APB2_BUS , GPIOB_RCC);

	/* Initialize LEDS */
	LEDS_voidInit();
	/* IR Initialization */
	HIR_voidInit();


	while(1)
	{
		u8 Button = HIR_u8GetKey();
		switch(Button)
		{
			 case 69: LEDS_STOP();     break;
			 case 12: LEDS_FLASHING(); break;
			 case 24: LEDS_IN_OUT();   break;
			 case 94: LEDS_PingPong(); break;
			 default:                  break;
		}
	}

	return 0;
}
