#include <msp430.h> 
#include <stdbool.h>

//bit maskers
const int pin0 = 0b00000001;
const int pin2 = 0b00000100;
const int pin3 = 0b00001000;
const int pin4 = 0b00010000;
const int pin5 = 0b00100000;
const int pin6 = 0b01000000;


//func to return correct bit masker
int pinVal(int i){
    if(i == 0){
        return pin0;
    }else if(i == 1){
        return pin2;
    }else if(i == 2){
        return pin3;
    }else if(i == 3){
        return pin4;
    }

    return 0x00;
}

/**
 * main.c
 */
int main(void){
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	P2DIR = 0b00011101;            //P2.0 , P2.2, P2.3, P2.4 OUTPUTS
	                               // read P2.5, P2.6

	unsigned int i = 0;

	volatile unsigned int b;
	P2OUT = 0xFF;
	for (b = 10000; b>0; b--);


	int output[4] = {0x00, 0x00, 0x00, 0x00};

	P2OUT = (output[0] & pin0) | (output[1] & pin2) | (output[2] & pin3) | (output[3] & pin4);

	bool isQueued = true;

	for(;;){

	    //0's button
	    if((P2IN & pin5) == pin5 && isQueued){
	        output[i] = 0x00;
	        i += 1;
	        P2OUT = (output[0] & pin0) | (output[1] & pin2) | (output[2] & pin3) | (output[3] & pin4);
	        isQueued = false;

	    }

	    //1's button
	    if((P2IN & pin6) == pin6 && isQueued){
	        output[i] = pinVal(i);
	        i += 1;
	        P2OUT = (output[0] & pin0) | (output[1] & pin2) | (output[2] & pin3) | (output[3] & pin4);
	        isQueued = false;
	    }


	    if(i == 4){
	        i = 0;
	        unsigned int f;
	        for(f = 0; f<4; f++){
	            output[f] = 0x00;
	        }
	        volatile unsigned int a = 0;
	        for( a = 100000; a>0; a--);
	        P2OUT = 0x00;
	    }

	    if((P2IN & pin5) != pin5 && (P2IN & pin6) != pin6 ){
	        isQueued = true;
	    }




	    /*if((P1IN & pin1) == 0b00000100){
	        P1OUT = 0x01;
	        //for (i = 10000; i>0; i--);

	    }else{
	        P1OUT = 0x00;
	        //for (i = 10000; i>0; i--);
	    }*/




	}
	return 0;
}
