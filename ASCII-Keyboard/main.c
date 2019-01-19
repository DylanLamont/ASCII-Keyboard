/* --COPYRIGHT--,BSD
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * --/COPYRIGHT--*/




#include "driverlib.h"

#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/usb.h"                  // USB-specific functions
#include "USB_API/USB_HID_API/UsbHid.h"
#include "hal.h"
#include <stdbool.h>
#include <msp430.h>
#include <stdint.h>
#include "ASCIITranslator.h"
#include <math.h>


uint8_t a[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


//bit maskers
const int pin0 = 0b00000001;
const int pin1 = 0b00000010;
const int pin2 = 0b00000100;
const int pin3 = 0b00001000;
const int pin4 = 0b00010000;
const int pin5 = 0b00100000;
const int pin6 = 0b01000000;
const int pin7 = 0b10000000;





int pinVal(int i){
    if(i == 0){
        return pin0;
    }else if(i == 1){
        return pin2;
    }else if(i == 2){
        return pin3;
    }else if(i == 3){
        return pin4;
    }else if(i == 4){
        return pin5;
    }else if(i == 5){
        return pin6;
    }else if(i == 6){
        return pin7;
    }
    return 0x00;
 }


void main (void){


    WDTCTL = WDTPW | WDTHOLD;

    // Minumum Vcore setting required for the USB API is PMM_CORE_LEVEL_2 .
    PMM_setVCore(PMM_CORE_LEVEL_2);
    USBHAL_initPorts();           // Config GPIOS for low-power (output low)
    USBHAL_initClocks(8000000);   // Config clocks. MCLK=SMCLK=FLL=8MHz; ACLK=REFO=32kHz
    USBHAL_initButtons();         // Init the two buttons
    USB_setup(TRUE, TRUE); // Init USB & events; if a host is present, connect





    USBHID_sendReport( a, HID0_INTFNUM);


    P2DIR = 0b11111111;
    P2OUT = 0xFF;



    uint8_t outputs[7] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool isQueued = true;


    int currBit = 0;

    volatile int b;
    unsigned int i;
    unsigned int f;
    for (b = 10000; b>0; b--);

    P2OUT =   (outputs[6] & pin7) | (outputs[5] & pin6)
           | (outputs[4] & pin5) | (outputs[3] & pin4) | (outputs[2] & pin3)
           | (outputs[1] & pin2) | (outputs[0] & pin0);



    __enable_interrupt();  // Enable global interrupts



    for(;;){                //prints immediately


    //0s button
     if (((P1IN & pin2) == pin2) && isQueued){
         outputs[currBit] = 0x00;
         currBit+= 1;
         isQueued = false;

         //display LEDs
         P2OUT =   (outputs[6] & pin7) | (outputs[5] & pin6)
                 | (outputs[4] & pin5) | (outputs[3] & pin4) | (outputs[2] & pin3)
                 | (outputs[1] & pin2) | (outputs[0] & pin0);
     }

     //1's key
     else if(((P1IN & pin3) == pin3) && isQueued ){
         outputs[currBit] = pinVal(currBit);
         currBit+=1;
         isQueued = false;

         //display LEDs
         P2OUT =   (outputs[6] & pin7) | (outputs[5] & pin6)
                 | (outputs[4] & pin5) | (outputs[3] & pin4) | (outputs[2] & pin3)
                 | (outputs[1] & pin2) | (outputs[0] & pin0);
     }



     //Clear entered bits
     else if (((P1IN & pin4) == pin4) && isQueued){

         for(i =0; i < 7; i++){
             outputs[i] = 0x00;
         }
         currBit = 0;
         isQueued = false;

         //display LEDs
         P2OUT =   (outputs[6] & pin7) | (outputs[5] & pin6)
                 | (outputs[4] & pin5) | (outputs[3] & pin4) | (outputs[2] & pin3)
                 | (outputs[1] & pin2) | (outputs[0] & pin0);
     }


     //Reset queue to stop double counting
     if(      (((P1IN & pin2) != pin2) && ((P1IN & pin3) != pin3))      &&    (((P1IN & pin4) != pin4))){
                        isQueued = true;
     }




     //7 bit message finished
     if(currBit == 7){
         uint8_t key = 0;

         int o;
         for(o = 0; o < 7; o++){
             if(outputs[o] != 0x00){
                 key += pow(2, o);
             }
         }

         a[0] = getByteZero(key);
         a[1] = 0x00;
         a[2] = getByteTwo(key);
         a[3] = 0x00;
         a[4] = 0x00;
         a[5] = 0x00;
         a[6] = 0x00;
         a[7] = 0x00;
         USBHID_sendReport( a, HID0_INTFNUM);

         a[0] = 0x00;
         a[1] = 0x00;
         a[2] = 0x00;
         a[3] = 0x00;
         a[4] = 0x00;
         a[5] = 0x00;
         a[6] = 0x00;
         a[7] = 0x00;
         USBHID_sendReport( a, HID0_INTFNUM);



         currBit = 0;

         for(f = 0; f<7; f++){
             outputs[f] = 0x00;
         }

         for (b = 100000000; b>0; b--);

         P2OUT =   (outputs[6] & pin7) | (outputs[5] & pin6)
                 | (outputs[4] & pin5) | (outputs[3] & pin4) | (outputs[2] & pin3)
                 | (outputs[1] & pin2) | (outputs[0] & pin0);
     }

    }
}

