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
#include "stdio.h"
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

volatile static int j=0;


xQueueHandle GLobal_Queue_Handle = 0;

void sender_task(void *p)
{
	int i=0;
	 while(1) {


		                 Board_LED_Set(0,false);
		             	 for(j=0;j<1e6;j++);
		             	 Board_LED_Set(0,true);
		             	 for(j=0;j<1e6;j++);
		             	 Board_LED_Set(1,false);
		             	 for(j=0;j<1e6;j++);
		             	 Board_LED_Set(1,true);
		             	 for(j=0;j<1e6;j++);
		             	 Board_LED_Set(3,false);
		             	 for(j=0;j<1e6;j++);
		             	 Board_LED_Set(3,true);
		             	 for(j=0;j<1e6;j++);


	            	 xQueueSend(GLobal_Queue_Handle, &i ,100);
	           }
	 }

void receiver_task(void *p)
{
    int rx_t = 0;
	 while(1) {

		                 Board_LED_Set(0,false);
		             	 for(j=0;j<1e6;j++);
		             	 Board_LED_Set(0,true);
		             	 for(j=0;j<1e6;j++);
		             	 Board_LED_Set(1,false);
		             	 for(j=0;j<1e6;j++);
		             	 Board_LED_Set(1,true);
		             	 for(j=0;j<1e6;j++);
		             	 Board_LED_Set(3,false);
		             	 for(j=0;j<1e6;j++);
		             	 Board_LED_Set(3,true);


	            	 xQueueReceive(GLobal_Queue_Handle, &rx_t,100);
	           }
	 }



int main (void)

{
	GLobal_Queue_Handle = xQueueCreate(3, sizeof(int));

	/* Create tasks */
	xTaskCreate(sender_task, (signed char*) "vSenderTask",
			configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 2Ul),
			(xTaskHandle *) NULL);

	xTaskCreate(receiver_task, (signed char*) "vReceiverTask",
			configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1Ul),
			(xTaskHandle *) NULL);


	/* Start the scheduler */
		vTaskStartScheduler();

		return 0;
}



