/*
===============================================================================
 Name        : helloproj.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    Board_LED_Set(0, false);
    Board_LED_Set(1, false);
    Board_LED_Set(2, false);
    Board_LED_Set(3, false);
#endif
#endif

    // TODO: insert code here

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    volatile static int j = 0 ;
    int a = {0,1,3,2};
    // Enter an infinite loop, just incrementing a counter
    while(1) {
           // uint8_t LEDNumber;

            {
                Board_LED_Toggle(0);
                for(j=0;j<1e6;j++);
                Board_LED_Toggle(1);
                for(j=0;j<1e6;j++);
                Board_LED_Toggle(2);
                for(j=0;j<1e6;j++);
                Board_LED_Toggle(3);
            }


            i++ ;
        }
        return 0 ;
    }



