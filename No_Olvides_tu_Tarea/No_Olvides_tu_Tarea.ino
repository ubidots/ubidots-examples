//The pin you want to control, in this case the servo on digital pin 0
int servoPin = D0;
Servo myservo;
int servoPos = 0;
int count = 0;

//This function is called after the Photon has started 
void setup(){
    //We set attach the servo to the pin
    myservo.attach(D0);
    //We "Subscribe" to our IFTTT event called Button so that we get events for it 
    Particle.subscribe("Yes", myHandler);
}
//The program loop, not sure if this has to be here for the program to run or not
void loop() {
}
//The function that handles the event from IFTTT
void myHandler(const char *event, const char *data){

        // We'll change the servo position to "yes"
        myservo.write(45);
        // wait for 1 minute
        delay(60000);
        //Then we'll change the servo position to "no" 
        myservo.write(0);
}

