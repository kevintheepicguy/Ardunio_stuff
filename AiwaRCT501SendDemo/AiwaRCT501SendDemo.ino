/*
 * IRremote: IRsendRawDemo - demonstrates sending IR codes with sendRaw
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 *
 * IRsendRawDemo - added by AnalysIR (via www.AnalysIR.com), 24 August 2015
 *
 * This example shows how to send a RAW signal using the IRremote library.
 * The example signal is actually a 32 bit NEC signal.
 * Remote Control button: LGTV Power On/Off.
 * Hex Value: 0x20DF10EF, 32 bits
 *
 * It is more efficient to use the sendNEC function to send NEC signals.
 * Use of sendRaw here, serves only as an example of using the function.
 *
 */

#include <IRremote.h>

IRsend irsend;
int g = 8415;
 int RECV_PIN =9; 

IRrecv irrecv(RECV_PIN); 

decode_results results; 

// On the Zero and others we switch explicitly to SerialUSB
#if defined(ARDUINO_ARCH_SAMD)
#define Serial SerialUSB
#endif

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    irrecv.enableIRIn(); 

    
    Serial.begin(9600);
#if defined(__AVR_ATmega32U4__)
    while (!Serial); //delay for Leonardo, but this loops forever for Maple Serial
#endif
#if defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)
    delay(2000); // To be able to connect Serial monitor after reset and before first printout
#endif
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__));
    Serial.print(F("Ready to send IR signals at pin "));
    Serial.println(IR_SEND_PIN);
}

void loop() {
    int khz = 38; // 38kHz carrier frequency for the NEC protocol
    /*
     * Send data from RAM
     */
    unsigned int irSignal[] = { g }; // AnalysIR Batch Export (IRremote) - RAW
    irsend.sendRaw(irSignal, sizeof(irSignal) / sizeof(irSignal[0]), khz); // Note the approach used to automatically calculate the size of the array.
    Serial.println();
     if (irrecv.decode(&results)){ 

      int value = results.value; 

      Serial.println(value);  
 

      irrecv.resume();  

    } 

}
