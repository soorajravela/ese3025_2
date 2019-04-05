/*
 * @brief FreeRTOS Blinky example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();

	Board_LED_Set(0, false);
	Board_LED_Set(1, false);
	Board_LED_Set(2, false);
	Board_LED_Set(0, true);
	Board_LED_Set(1, true);
	Board_LED_Set(2, true);

}

 xSemaphoreHandle binsem=0;

/*  led1 task */
static void vLED_1(void *pvParameters) {

	while (1) {
	xSemaphoreTake(binsem, 5000); // we set delay as 5000, we can use (binsem, portMAX_DELAY) //
	Board_LED_Set(0, false);
	vTaskDelay(1000);
	Board_LED_Set(0, true);
	xSemaphoreGive(binsem);

	}
}

/* led2 task */

static void vLED_2(void *pvParameters) {

	while (1){
	xSemaphoreTake(binsem, 5000);  // we set delay as 5000, we can use (binsem, portMAX_DELAY) //
	Board_LED_Set(1, false);
	vTaskDelay(1000);
	Board_LED_Set(1, true);
	xSemaphoreGive(binsem);

	}
}

/* led3 task */

static void vLED_3(void *pvParameters) {

	while (1){

	xSemaphoreTake(binsem, 5000);  // we set delay as 5000, we can use (binsem, portMAX_DELAY) //
	Board_LED_Set(2, false);
	vTaskDelay(1000);
	Board_LED_Set(2, true);
	xSemaphoreGive(binsem);

	}
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * define binarysemaphore and tasks
 * @return	Nothing, function should not exit
 */
int main(void)
{
	vSemaphoreCreateBinary(binsem);
	prvSetupHardware();

	/* LED1 */
	xTaskCreate(vLED_1, (signed char *) "vLED1",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);

	/* LED2 */
	xTaskCreate(vLED_2, (signed char *) "vLED2",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);

	/* LED3 */
	xTaskCreate(vLED_3, (signed char *) "vLED3",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);

	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}

/**
 * @}
 */
