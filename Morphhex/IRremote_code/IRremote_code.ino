#include <boarddefs.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <IRremote.h>
#include <IRremoteInt.h>


 
const int CODE_0          = 0xFF6897;
const int CODE_1          = 0xFF30CF;
const int CODE_2          = 0xFF18E7;
const int CODE_3          = 0xFF7A85;
const int CODE_4          = 0xFF10EF;
const int CODE_5          = 0xFF38C7;
const int CODE_6          = 0xFF5AA5;
const int CODE_7          = 0xFF42BD;
const int CODE_8          = 0xFF4AB5;
const int CODE_9          = 0xFF52AD;
const int CODE_EQ         = 0xFF906F;
const int CODE_VOL_UP     = 0xFFA857;
const int CODE_VOL_DOWN   = 0xFFE01F;
const int CODE_PLAY_PAUSE = 0xFFC23D;
const int CODE_NEXT       = 0xFF02FD;
const int CODE_PREV       = 0xFF22DD;
const int CODE_CH         = 0xFF629D;
const int CODE_CH_PLUS    = 0xFFE21D;
const int CODE_CH_MINUS   = 0xFFA25D;

int RECV_PIN = 50;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  irrecv.blink13(true);

}

void loop() {
   if (irrecv.decode(&results))
   {
     Serial.println(results.value, HEX);
     irrecv.resume(); // Receive the next value
   }
}
