#include "mbed.h"

#include "mbed_events.h"


DigitalOut red(LED1);

DigitalOut blue(LED3);

InterruptIn btn(SW2);


EventQueue printfQueue;

EventQueue eventQueue;


void blink_led2() {

  // this runs in the normal priority thread

  red = !red;

}


void print_toggle_led() {

  // this runs in the lower priority thread

  printf("105061151 demo\r\n");

}


void btn_fall_irq() {

  blue = !blue;


  // defer the printf call to the low priority thread

  printfQueue.call(&print_toggle_led);

}


int main() {

 blue=1;

  // low priority thread for calling printf()

  Thread printfThread(osPriorityLow);

  printfThread.start(callback(&printfQueue, &EventQueue::dispatch_forever));


  // normal priority thread for other events

  Thread eventThread(osPriorityNormal);

  eventThread.start(callback(&eventQueue, &EventQueue::dispatch_forever));


  // call blink_led2 every second, automatically defering to the eventThread

  Ticker ledTicker;

  ledTicker.attach(eventQueue.event(&blink_led2), 5.0);


  // button fall still runs in the ISR

  btn.fall(&btn_fall_irq);


  while (1) {wait(1);}

}
