#include "mbed.h"


Ticker time_up;

//DigitalOut redLED(LED1);
DigitalOut blueLED(LED3);

void blink(){

    //redLED = !redLED;
    blueLED = !blueLED;
}


int main(){

    time_up.attach( &blink, 0.2 );

    while(1);

}
