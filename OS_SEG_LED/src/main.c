/*
 * main.c
 *
 *  Created on: Sep 07, 2020
 *      Author: A.I.Zaki
 */




#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"


#include "OS_interface.h"
#include "OS_private.h"
#include "OS_config.h"
#include "SSG_interface.h"

u8 Iterator = 0 ;
void SGM_voidDisplaySGM(void)
{
	MGPIO_voidSetPinValue(GPIOB, PIN8, LOW);
	SSG_voidDisplayNumber(Iterator);
	Iterator++;

	if(Iterator == 10)
	{
		OS_voidSuspendTask(0);
		OS_voidResumeTask (1);
	}
}
void LED_voidLED_ON(void)
{
	MGPIO_voidSetPinValue(GPIOB, PIN8, HIGH);
	OS_voidSuspendTask( 1 );
	Iterator = 0 ;
	OS_voidResumeTask ( 0 );
}



int main()
{
    // RCC Init, PORTA
	MRCC_voidInitSysClock();
	MRCC_voidEnableClock(APB2_BUS, GPIOA_RCC);
	MRCC_voidEnableClock(APB2_BUS, GPIOB_RCC);

	MGPIO_voidSetPinDirection(GPIOB, PIN8, OUTPUT_SPEED_2MHZ_PP);

	/* GPIO Directions */
	MGPIO_voidSetPortMode(GPIOA , OUTPUT_SPEED_2MHZ_PP);



	SSG_voidInit();

	OS_voidCreateTask(0 , 1000, SGM_voidDisplaySGM, 0);

	OS_voidCreateTask(1 , 1000, LED_voidLED_ON    , 0);

	OS_voidSuspendTask(1);


	OS_voidStart();

    while(1)
    {

    }
    return 0;
}

