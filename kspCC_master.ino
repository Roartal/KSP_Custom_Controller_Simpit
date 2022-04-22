#include <KerbalSimpit.h>
#include <PayloadStructs.h>
#include <OneButton.h>

// TIMEWARP PIN NUMBERS
const int TW_STOP_PIN = 3;
const int TW_ADD_PIN = 4;
const int TW_SUB_PIN = 2;

bool twstop_pressed = false;
bool twadd_pressed = false;
bool twsub_pressed = false;

//messages
struct timewarpMessage tw_msg;

//buttons
OneButton TW_STOP_btn(TW_STOP_PIN, false, true);
OneButton TW_ADD_btn(TW_ADD_PIN, true, true);
OneButton TW_SUB_btn(TW_SUB_PIN, true, true);

KerbalSimpit mySimpit(Serial);

void twStopClicked() {
  tw_msg.command = Timewarp::TIMEWARP_X1;
  mySimpit.send(TIMEWARP_MESSAGE, tw_msg);
}

void twAddClicked() {
  tw_msg.command = Timewarp::TIMEWARP_UP;
  mySimpit.send(TIMEWARP_MESSAGE, tw_msg);
}

void twSubClicked() {
  tw_msg.command = Timewarp::TIMEWARP_DOWN;
  mySimpit.send(TIMEWARP_MESSAGE, tw_msg);
}

void setup() {
  Serial.begin(115200);

 // pinMode(TW_STOP_PIN, INPUT);
//digitalWrite(TW_STOP_PIN, LOW);

  pinMode(LED_BUILTIN, OUTPUT);
  
  // Turn on the built-in to indicate the start of the handshake process
  digitalWrite(LED_BUILTIN, HIGH); 

  // This loop continually attempts to handshake with the plugin.
  // It will keep retrying until it gets a successful handshake.
  while (!mySimpit.init()) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
  }
  // Turn off the built-in LED to indicate handshaking is complete.
  digitalWrite(LED_BUILTIN, LOW);
  // Display a message in KSP to indicate handshaking is complete.
  mySimpit.printToKSP("Connected", PRINT_TO_SCREEN);
  TW_STOP_btn.setPressTicks(55);
  TW_STOP_btn.attachLongPressStart(twStopClicked);

  TW_ADD_btn.setPressTicks(55);
  TW_ADD_btn.attachLongPressStart(twAddClicked);

  TW_SUB_btn.setPressTicks(55);
  TW_SUB_btn.attachLongPressStart(twSubClicked);
}

void loop() {
  mySimpit.update();

  // TW STOP BEHAVIOR
  /*bool button_state = digitalRead(TW_STOP_PIN);
  if(!twstop_pressed && !button_state){
      digitalWrite(LED_BUILTIN, HIGH);
      tw_msg.command = Timewarp::TIMEWARP_X1;
    mySimpit.send(TIMEWARP_MESSAGE, tw_msg); 
    twstop_pressed = true;
  }
  if(twstop_pressed && button_state){
      digitalWrite(LED_BUILTIN, LOW); 
    twstop_pressed = false;
  }*/

  TW_STOP_btn.tick();
  TW_ADD_btn.tick();
  TW_SUB_btn.tick();
}
