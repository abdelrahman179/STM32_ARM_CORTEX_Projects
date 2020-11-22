/*
 * main.c
 *
 *  Created on: Sep 21, 2020
 *      Author: A.I.Zaki
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "SPI1_interface.h"
#include "STK_interface.h"

#include "TFT_interface.h"
#include "TFT_private.h"
#include "TFT_config.h"

#include "DELAY_interface.h"

#include "image.h"


void main(void)
{
	/* RCC Initialization */
	MRCC_voidInitSysClock();
	/* RCC GPIOA Enable */
	MRCC_voidEnableClock(APB2_BUS , 2);
	/* RCC SPI1 Enable */
	MRCC_voidEnableClock(APB2_BUS , 12);

	/* GPIO Pin Initialization */
	MGPIO_voidSetPinDirection(GPIOA, 1, 0b0010); /* A0 2MHz */
	MGPIO_voidSetPinDirection(GPIOA, 2, 0b0010); /* RST 2MHz */
	MGPIO_voidSetPinDirection(GPIOA, 5, 0b1001); /* CLK 10MHz */
	MGPIO_voidSetPinDirection(GPIOA, 7, 0b1001); /* MOSI 10MHz */

	/* Initialization STK */
	MSTK_voidInit();

	/* SPI1 Initialization */
	MSPI1_voidInit();

	/* TFT Initialization */
	HTFT_voidInit();

	/* Display Image */
	HTFT_voidFillImage(Img);

	while(1)
	{

	}
}
