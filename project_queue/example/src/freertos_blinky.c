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
#include "queue.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

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

xQueueHandle GLobal_Queue_Handle = 0;

/* LED1 toggle thread */
static void vsender_task(void *pvParameters) {

	volatile static int j=0;
	int i = (0,1,2);


	while(1) {
       {
	   (xQueueSend(GLobal_Queue_Handle, &i ,1000));
	   int c,n;
	   	for (c = 0; c <= 1; c++) {
	   	    n = rand() % 100 + 1;



	                            Board_LED_Set(i,false);
				             	 for(j=0;j<1e5;j++);
				             	 Board_LED_Set(i,true);

	}
  }
}
}


/* LED2 toggle thread */
void vreceiver_task(void *pvParameters) {

	volatile static int j=0;
	int i = (0,1,2);
	while(1){

		 xQueueReceive(GLobal_Queue_Handle, &i,1000);
		 int c,n;
		 	for (c = 0; c <= 1; c++) {
		 	    n = rand() % 100 + 1;

	                             Board_LED_Set(0,false);
		 		             	 for(j=0;j<1e5;j++);
				             	 Board_LED_Set(0,true);
				                 Board_LED_Set(1,false);
				             	 for(j=0;j<1e5;j++);
				             	 Board_LED_Set(1,true);
				             	 Board_LED_Set(2,false);
				             	 for(j=0;j<1e5;j++);
				             	 Board_LED_Set(2,true);
				             	 for(j=0;j<1e5;j++);



}
}
}


/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */
int main(void)
{
	GLobal_Queue_Handle = xQueueCreate(10, sizeof(int));
	prvSetupHardware();

	/* LED1 toggle thread */
	xTaskCreate(vsender_task, (signed char *) "vSendertask",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 2UL),
				(xTaskHandle *) NULL);

	/* LED2 toggle thread */
	xTaskCreate(vreceiver_task, (signed char *) "vReceivertask",
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
