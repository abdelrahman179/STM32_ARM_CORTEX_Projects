/*
 * main.c
 *
 *  Created on: Nov 29, 2020
 *      Author: A.I.Zaki
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "USART_interface.h"
#include "ESP_interface.h"


void main(void)
{
	MRCC_voidInitSysClock();
	MRCC_voidEnableClock(APB2_BUS, GPIOA_RCC);		/* Enable GPIOA clock*/
	MRCC_voidEnableClock(APB2_BUS, USART1_RCC);		/* Enable USART1 Clock */

	/* Setting A9:TX pin as Output alternate function push pull w max speed 50 MHz */
	MGPIO_voidSetPinDirection(GPIOA, PIN9, OUTPUT_SPEED_50MHZ_AFPP);
	/* Setting A10:RX pin as input floating */
	MGPIO_voidSetPinDirection(GPIOA, PIN10, INPUT_FLOATING);

	MGPIO_voidSetPinDirection(GPIOA, PIN0, OUTPUT_SPEED_10MHZ_PP);

	MUSART_voidInit();

	HESP_voidInit();
	/* Connect to Router, sending name and password as strings*/
	HESP_voidConnectToRouter("Zaki", "Egypt-7890011");

	u8  Led_Status = 0;

	while(1)
	{
		/*Connecting to server, sending data transmit mode UDP or TCP and IP of server and port number as strings*/
		/* We connect each time as my server is free one and disconnects automatically, if you got a server yourself you don't
		 * have to do so
		 */
		HESP_voidConnectToServer("TCP", "162.253.155.226", "80");
		/* Send the reqest as string*/
		Led_Status = HESP_u8ExecuteRequest("GET http://ismart.freevar.com/status.txt");
		MGPIO_voidSetPinValue(GPIOA, PIN0, Led_Status);
	}
}
