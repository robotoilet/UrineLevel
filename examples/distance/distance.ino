#include <UrineLevel.h>

//connect sharp sensor to A0
#define pin A0

//create instance of Urine Level with inputs
//urineLevel(pin = pin number, range = number of readings, threshold value)
UrineLevel urineLevel(pin,100,5);


void setup () {
        Serial.begin (9600);   //start serial monitor
        pinMode(pin, INPUT);  //set input pin
}

void loop () {
        delay(2000);                //delay to give you time toopen serial
       double urine = urineLevel.distance();    //call distance on th eobject urineLevel 
       Serial.print("Urine Level = ");
       Serial.println(urine);                   //print the output returned by the call to distance
}  

