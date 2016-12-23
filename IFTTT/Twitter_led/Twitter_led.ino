//The pin you want to control, in this case I'm blinking the on-board blue LED on digital pin 7
int led = D7;
//This function is called after the Photon has started 
void setup(){
    //We set the pin mode to output
    pinMode(led, OUTPUT);
    //We "Subscribe" to our IFTTT event called Button so that we get events for it 
    Particle.subscribe("Button", myHandler);
}
//The program loop, not sure if this has to be here for the program to run or not
void loop() {
}
//The function that handles the event from IFTTT
void myHandler(const char *event, const char *data){
    // We'll turn the LED on
    digitalWrite(led, HIGH);
    
    // We'll leave it on for 5 second...
    delay(5000);
    
    //Then we'll turn it off...
    digitalWrite(led, LOW);
}