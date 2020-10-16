/*****************************************************************************
 * notmain.c: Blinks the built-in LED attached to PA7 of the STM32 Blackboard
 * at the rhythm of a heartbeat.
 *****************************************************************************
 * Copyright (C) 2020-2021
 *  
 * Author: DigitallyAmar (@digitallyamar)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/


void PUT32 ( unsigned int, unsigned int );
unsigned int GET32 ( unsigned int );
unsigned int DELAY ( unsigned int );

int notmain(void) {
    unsigned int rval;
    //Set the heart beat delays
    unsigned int delay_small = 599999;
    unsigned int delay_big = 2999999;

    // RCC Register Bank start address - 0x40023800
    // Enable GPIOA clock using reg: RCC_AHB1ENR (addr: 0x40023830)
    rval = GET32(0x40023830) | 0x1;
    PUT32(0x40023830,rval);

    // Set the GPIO to operate in output mode
    // Use the GPIOA_MODER register to do that.
    rval = GET32(0x40020000) | 0x00104000;
    PUT32(0x40020000, rval);

    while (1) {
        // Turn ON the LED. Since the LED is connected to +3.3V on one end, we 
        // only need to pull the other end of the pin LOW.So we use bit masking
        // to do that and do a bitwise AND operation over the current value.
        // Use the GPIOA_ODR register to lower the bit corresponding to pin PA7

         rval = GET32(0x40020014) & 0xFFFFFB7F;
         PUT32(0x40020014, rval);

        DELAY(delay_small);
 
        // Turn OFF the LED. We do this by pulling the other end of the LED pin 
        // HIGH. So we use bit masking to do that and do an OR operation over 
        // the current value.
        // Use the GPIOA_ODR register to up the bit corresponding to pin PA7
        rval = GET32(0x40020014) | 0x00000480;
        PUT32(0x40020014, rval);

        DELAY(delay_small);
 
 
        // Turn ON the LED again
         rval = GET32(0x40020014) & 0xFFFFFB7F;
         PUT32(0x40020014, rval);

        DELAY(delay_small);
 
        //Turn OFF the LED again
        rval = GET32(0x40020014) | 0x00000480;
        PUT32(0x40020014, rval);

        DELAY(delay_big);
 
    }
    
    return(0);
}