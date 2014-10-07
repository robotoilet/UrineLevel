/************************************************************************************************************
 * UrineLevel.cpp - Arduino library for retrieving distance (in cm) from the analog Sharp GP2Y0A41Y         *
 * Distance sensor                                                                                   *
 * Copyright 2014 Joel Cormack (joel.greta@gmail.com)                                       *
 ************************************************************************************************************

 ************************************************************************************************************
 * This library is free software; you can redistribute it and/or                                            *
 * modify it under the terms of the GNU Lesser General Public                                               *
 * License as published by the Free Software Foundation; either                                             *
 * version 2.1 of the License, or (at your option) any later version.                                       *
 *                                                                                                          *
 * This library is distributed in the hope that it will be useful,                                          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                                           *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                                        *
 * Lesser General Public License for more details.                                                          *
 *                                                                                                          *
 * You should have received a copy of the GNU Lesser General Public                                         *
 * License along with this library; if not, write to the Free Software                                      *
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA                               *
 ***********************************************************************************************************/

#include "Arduino.h"
#include "UrineLevel.h"

/*this library is an adaptation of Dr. Marcal Casas-Cartagena (marcal.casas@gmail.com) library with the formulae exchanged.
it basically takes multiple readings and calculates the mean. rejecting some readings that are outside of the threshold limits
the inputs are:
pin = analogue pin number
range = number of readings from sensor before calculating the mean
threshold = the number to be added to the previousValue to create upper and lower threshold
*/

UrineLevel::UrineLevel(int pin, int range, int threshold) {
  
    _pin=pin;
    _range=range;
    _threshold=threshold;
    
    analogReference(DEFAULT);
}

//the following function uses the formulae from http://www.dfrobot.com/wiki/index.php/SHARP_GP2Y0A41SK0F_IR_ranger_sensor_%284-30cm%29_SKU:SEN0143
//converts the signal from the analog pin to cm
double UrineLevel::distance() {
	_mean = getMean();
	if (_mean < 16){					//if an object is too close to the sensor set the distance at its lowest 
		_mean = 16; 
	} return 2076.0 / (_mean - 11.0);
}


//this function takes multiple readings from the sensor and outputs the mean value. while ignoring values above and below a given threshold value
		
int UrineLevel::getMean(){
  _p = 0;
  _sum = 0;
  _previousValue = analogRead (_pin);          //read the input from sensor store it in previousValue 
                                                      //this is for first iteration of previousValue only so its not 0
  
  for (int i=0;i<_range;i++){                          //do the following as many time as range specifies
    _value = analogRead (_pin);                //read the input from sensor store it in value
    _lower = (_previousValue - _threshold );         //lower threshold
    _upper = (_previousValue + _threshold);          //upper threshold         
  
    if (! ((_value < _lower)  ||  (_value > _upper)) ){   //if the current sensor value is not below or above threshold
    _previousValue=_value;                              //set it to previousValue
    _sum=_sum+_value;                                    //add it to the total
    _p++;                                              //increment p
    }
    _previousValue=_value;                              //always set previous value to the previous value even if it wasnt added to sum                                                  
  }

  _meanValue = _sum/_p;                              //get mean by dividing total by entries
  Serial.print("meanValue");
  Serial.println(_meanValue);
  delay(1000);
  return _meanValue; 

}