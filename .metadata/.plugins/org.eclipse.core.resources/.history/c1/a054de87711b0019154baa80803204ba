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
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/*  
 * ======== main.c ========
 * Keyboard HID Demo:
 *
 * This example functions as a keyboard on the host. Once enumerated, pressing 
 * one of the target board?s buttons causes a string of six characters ? 
 * "msp430" -- to be "typed" at the PC?s cursor, wherever that cursor is.  
 * If the other button is held down while this happens, it acts as a shift key, 
 * causing the characters to become "MSP$#)".
 * Unlike the HID-Datapipe examples, this one does not communicate with the 
 * HID Demo Application.
  +----------------------------------------------------------------------------+
 * Please refer to the Examples Guide for more details.
 *----------------------------------------------------------------------------*/
#include <string.h>

#include "driverlib.h"

#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/usb.h"                  // USB-specific functions
#include "USB_API/USB_HID_API/UsbHid.h"

/*
 * NOTE: Modify hal.h to select a specific evaluation board and customize for
 * your own board.
 */
#include "hal.h"


#include <stdbool.h>
#include <msp430.h>
#include <stdint.h>


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





/*********** Application specific globals **********************/
volatile uint8_t button1Pressed = FALSE;
volatile uint8_t button2Pressed = FALSE;
volatile uint8_t keySendComplete = TRUE;
uint8_t button1Buf[128] = "msp430";
uint8_t button1StringLength;




void main (void){
     WDT_A_hold(WDT_A_BASE); // Stop watchdog timer

    // Minumum Vcore setting required for the USB API is PMM_CORE_LEVEL_2 .
    PMM_setVCore(PMM_CORE_LEVEL_2);
    USBHAL_initPorts();           // Config GPIOS for low-power (output low)
    USBHAL_initClocks(8000000);   // Config clocks. MCLK=SMCLK=FLL=8MHz; ACLK=REFO=32kHz
    USBHAL_initButtons();         // Init the two buttons
    USB_setup(TRUE, TRUE); // Init USB & events; if a host is present, connect

//    USBHID_sendReport( a, HID0_INTFNUM);



    USBHID_sendReport( a, HID0_INTFNUM);





    int outputs[7] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    P2DIR = 0b11111111;


    P2OUT = 0xFF;

    volatile int b;
    unsigned int i;
    unsigned int f;
    for (b = 10000; b>0; b--);

    P2OUT =   (outputs[6] & pin7) | (outputs[5] & pin6)
           | (outputs[4] & pin5) | (outputs[3] & pin4) | (outputs[2] & pin3)
           | (outputs[1] & pin2) | (outputs[0] & pin0);

    bool isQueued = true;


    int currBit = 0;








    __enable_interrupt();  // Enable global interrupts



    for(;USB_getConnectionState() == ST_ENUM_ACTIVE;){                //prints immediately
//    for(;USB_getConnectionState() == ST_ENUM_ACTIVE;){                //prints only when 7 chars printed



                //0s button
                 if (((P1IN & pin2) == pin2) && isQueued){
                     outputs[currBit] = 0x00;
                     currBit+= 1;



                     a[0] = 0x02;
                     a[1] = 0x00;
                     a[2] = 0x10;
                     a[3] = 0x04;
                     a[4] = 0x1B;
                     a[5] = 0x00;
                     a[6] = 0x00;
                     a[7] = 0x00;
                     //uint8_t b[8] = {0x9E, 0x0F, 0x01, 0x00, 0xDA, 0x05, 0x01, 0x00};
                     USBHID_sendReport( a, HID0_INTFNUM);

                     while(!keySendComplete);
                     keySendComplete = FALSE;

                     a[2] = 0x00;
                     a[3] = 0x00;
                     a[4] = 0x00;
                     a[5] = 0x00;
                     a[6] = 0x00;
                     a[7] = 0x00;
                     //uint8_t b[8] = {0x9E, 0x0F, 0x01, 0x00, 0xDA, 0x05, 0x01, 0x00};
                     USBHID_sendReport( a, HID0_INTFNUM);



                     isQueued = false;

                     P2OUT =   (outputs[6] & pin7) | (outputs[5] & pin6)
                             | (outputs[4] & pin5) | (outputs[3] & pin4) | (outputs[2] & pin3)
                             | (outputs[1] & pin2) | (outputs[0] & pin0);
                 }



                 else if(((P1IN & pin3) == pin3) && isQueued ){
                     outputs[currBit] = pinVal(currBit);
                     currBit+=1;
                     isQueued = false;
                     P2OUT =   (outputs[6] & pin7) | (outputs[5] & pin6)
                             | (outputs[4] & pin5) | (outputs[3] & pin4) | (outputs[2] & pin3)
                             | (outputs[1] & pin2) | (outputs[0] & pin0);
                 }



                 else if (((P1IN & pin4) == pin4) && isQueued){

                     for(i =0; i < 7; i++){
                         outputs[i] = 0x00;
                     }

                     currBit = 0;

                     isQueued = false;

                     P2OUT =   (outputs[6] & pin7) | (outputs[5] & pin6)
                             | (outputs[4] & pin5) | (outputs[3] & pin4) | (outputs[2] & pin3)
                             | (outputs[1] & pin2) | (outputs[0] & pin0);
                 }






                 if(      (((P1IN & pin2) != pin2) && ((P1IN & pin3) != pin3))      &&    (((P1IN & pin4) != pin4))){
                                    isQueued = true;
                 }





                 if(currBit == 7){
                     currBit = 0;

                     for(f = 0; f<7; f++){
                         outputs[f] = 0x00;
                     }

                     for (b = 1000000; b>0; b--);

                     P2OUT =   (outputs[6] & pin7) | (outputs[5] & pin6)
                             | (outputs[4] & pin5) | (outputs[3] & pin4) | (outputs[2] & pin3)
                             | (outputs[1] & pin2) | (outputs[0] & pin0);
                 }

    }


    while (1){


        switch(USB_getConnectionState())
        {
            // This case is executed while your device is enumerated on the
            // USB host
            case ST_ENUM_ACTIVE:
            
                // Enter LPM0 w/interrupt, until a keypress occurs
//                __bis_SR_register(LPM0_bits + GIE);


                a[0] = 0x02;
                a[1] = 0x00;
                a[2] = 0x10;
                a[3] = 0x04;
                a[4] = 0x1B;
                a[5] = 0x00;
                a[6] = 0x00;
                a[7] = 0x00;
                //uint8_t b[8] = {0x9E, 0x0F, 0x01, 0x00, 0xDA, 0x05, 0x01, 0x00};
                USBHID_sendReport( a, HID0_INTFNUM);

                while(!keySendComplete);
                keySendComplete = FALSE;

                a[2] = 0x00;
                a[3] = 0x00;
                a[4] = 0x00;
                a[5] = 0x00;
                a[6] = 0x00;
                a[7] = 0x00;
                //uint8_t b[8] = {0x9E, 0x0F, 0x01, 0x00, 0xDA, 0x05, 0x01, 0x00};
                USBHID_sendReport( a, HID0_INTFNUM);



                if (((P1IN & pin2) == pin2) && isQueued){
                            outputs[currBit] = 0x00;
                            currBit+= 1;


                            isQueued = false;

                            P2OUT =   (outputs[6] & pin7) | (outputs[5] & pin6)
                                    | (outputs[4] & pin5) | (outputs[3] & pin4) | (outputs[2] & pin3)
                                    | (outputs[1] & pin2) | (outputs[0] & pin0);
                        }

                        else if(((P1IN & pin3) == pin3) && isQueued ){
                            outputs[currBit] = pinVal(currBit);
                            currBit+=1;
                            isQueued = false;
                            P2OUT =   (outputs[6] & pin7) | (outputs[5] & pin6)
                                    | (outputs[4] & pin5) | (outputs[3] & pin4) | (outputs[2] & pin3)
                                    | (outputs[1] & pin2) | (outputs[0] & pin0);
                        }

                        else if (((P1IN & pin4) == pin4) && isQueued){



                            for(i =0; i < 7; i++){
                                outputs[i] = 0x00;
                            }

                            currBit = 0;

                            isQueued = false;

                            P2OUT =   (outputs[6] & pin7) | (outputs[5] & pin6)
                                    | (outputs[4] & pin5) | (outputs[3] & pin4) | (outputs[2] & pin3)
                                    | (outputs[1] & pin2) | (outputs[0] & pin0);
                        }




                        if(      (((P1IN & pin2) != pin2) && ((P1IN & pin3) != pin3))      &&    (((P1IN & pin4) != pin4))){
                                           isQueued = true;
                        }


                        if(currBit == 7){
                            currBit = 0;

                            for(f = 0; f<7; f++){
                                outputs[f] = 0x00;
                            }

                            for (b = 1000000; b>0; b--);

                            P2OUT =   (outputs[6] & pin7) | (outputs[5] & pin6)
                                    | (outputs[4] & pin5) | (outputs[3] & pin4) | (outputs[2] & pin3)
                                    | (outputs[1] & pin2) | (outputs[0] & pin0);
                        }




//                /************* HID keyboard portion ************************/
//                if ((P1IN & pin5) == pin5){
//
//
//                    a[0] = 0x02;
//                    a[1] = 0x00;
//                    a[2] = 0x10;
//                    a[3] = 0x04;
//                    a[4] = 0x1B;
//                    a[5] = 0x00;
//                    a[6] = 0x00;
//                    a[7] = 0x00;
//                    //uint8_t b[8] = {0x9E, 0x0F, 0x01, 0x00, 0xDA, 0x05, 0x01, 0x00};
//                    USBHID_sendReport( a, HID0_INTFNUM);
//
//                    while(!keySendComplete);
//                    keySendComplete = FALSE;
//
//                    a[2] = 0x00;
//                    a[3] = 0x00;
//                    a[4] = 0x00;
//                    a[5] = 0x00;
//                    a[6] = 0x00;
//                    a[7] = 0x00;
//                    //uint8_t b[8] = {0x9E, 0x0F, 0x01, 0x00, 0xDA, 0x05, 0x01, 0x00};
//                    USBHID_sendReport( a, HID0_INTFNUM);
//
//
//                }

                break;
            // These cases are executed while your device is disconnected from
            // the host (meaning, not enumerated); enumerated but suspended
            // by the host, or connected to a powered hub without a USB host
            // present.
            case ST_PHYS_DISCONNECTED:
            case ST_ENUM_SUSPENDED:
            case ST_PHYS_CONNECTED_NOENUM_SUSP:
                __bis_SR_register(LPM3_bits + GIE);
                _NOP();
                break;

            // The default is executed for the momentary state
            // ST_ENUM_IN_PROGRESS.  Usually, this state only last a few
            // seconds.  Be sure not to enter LPM3 in this state; USB
            // communication is taking place here, and therefore the mode must
            // be LPM0 or active-CPU.
            case ST_ENUM_IN_PROGRESS:
            default:;
        }
    }  //while(1)
} //main()


/*  
 * ======== UNMI_ISR ========
 */
#if defined(__TI_COMPILER_VERSION__) || (__IAR_SYSTEMS_ICC__)
#pragma vector = UNMI_VECTOR
__interrupt void UNMI_ISR (void)
#elif defined(__GNUC__) && (__MSP430__)
void __attribute__ ((interrupt(UNMI_VECTOR))) UNMI_ISR (void)
#else
#error Compiler not found!
#endif
{
    switch (__even_in_range(SYSUNIV, SYSUNIV_BUSIFG))
    {
        case SYSUNIV_NONE:
            __no_operation();
            break;
        case SYSUNIV_NMIIFG:
            __no_operation();
            break;
        case SYSUNIV_OFIFG:
             UCS_clearFaultFlag(UCS_XT2OFFG);
            UCS_clearFaultFlag(UCS_DCOFFG);
            SFR_clearInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);
            break;
        case SYSUNIV_ACCVIFG:
            __no_operation();
            break;
        case SYSUNIV_BUSIFG:
            // If the CPU accesses USB memory while the USB module is
            // suspended, a "bus error" can occur.  This generates an NMI.  If
            // USB is automatically disconnecting in your software, set a
            // breakpoint here and see if execution hits it.  See the
            // Programmer's Guide for more information.
            SYSBERRIV = 0; //clear bus error flag
            USB_disable(); //Disable
    }
}

//Released_Version_5_20_06_02
