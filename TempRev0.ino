#include <LedControl.h>

/*
  Author:   Sylvan Morris
  Created:  24 Feb 2017
  Contact:  sylvan.j.morris@gmail.com
*/

LedControl lc=LedControl(10,11,12,1);
float temp1;
float temp2;
float volt; //positive input voltage

void setup() {
  //wake up the MAX72XX from power-saving mode 
   lc.shutdown(0,false);
   //set a medium brightness for the Leds
   lc.setIntensity(0,15);
   //Clearing display just to sanitise it
   lc.clearDisplay(0);
   Serial.begin(9600);
}

void loop() {
    //voltage reading
  volt = analogRead(A0)*5*5.10/1023.0; // times 5 to get the voltage at A0 and times 5.03 to convert to actual positive rail voltage
  printVolt(int(volt*10));
  
  //reading in signal from  left MCP9700, 10mV/C and converting the value to volts
  temp1 = analogRead(A1)*5/1023.0;
  //removing the offset (0 C = 500mV)
  temp1 = temp1 -0.5;
  //preparing the value to display temp*100 would give the actual temp.
  temp1 = temp1*100;
  printTempLeft(int(temp1));
  
  //now looking at right temp
  temp2 = analogRead(A2)*5/1023.0;
  //removing the offset (0 C = 500mV)
  temp2 = temp2 -0.5;
  //preparing the value to display temp*100 would give the actual temp.
  temp2 = temp2*100;
  printTempRight(int(temp2));
  delay(500);
}

void printTempLeft(int v) {
    int ones;
    int tens;


    if(v < 0 || v > 99) 
       return;
    ones=v%10;
    v=v/10;
    tens=v%10;     
 
    //Now print the number digit by digit
    lc.setDigit(0,3,tens,false);
    lc.setDigit(0,2,ones,false); 
}

void printTempRight(int v) {
    int ones;
    int tens;
 
 
    if(v < 0 || v > 99) 
       return;
    ones=v%10;
    v=v/10;
    tens=v%10;     
 
    //Now print the number digit by digit
    lc.setDigit(0,1,tens,false);
    lc.setDigit(0,0,ones,false); 
}

void printVolt(int v) {
    int ones;
    int tens;
    int hundreds;
 

    if(v < 0 || v > 999) 
       return;
    ones=v%10;
    v=v/10;
    tens=v%10;
    v=v/10;
    hundreds=v%10;     
 
    //Now print the number digit by digit
    lc.setDigit(0,6,hundreds,false);
    lc.setDigit(0,5,tens,true);
    lc.setDigit(0,4,ones,false); 
}

