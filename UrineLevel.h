/************************************************************************************************************
 * UrineLevel.h - Arduino library for retrieving distance (in cm) from the analog Sharp GP2Y0A41Y         *
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

 /*this library is an adaptation of Dr. Marcal Casas-Cartagena (marcal.casas@gmail.com) library with the formulae exchanged.
it basically takes multiple readings and calculates the mean. rejecting some readings that are outside of the threshold limits
the inputs are:
pin = analogue pin number
range = number of readings from sensor before calculating the mean
threshold = the number to be added to the previousValue to create upper and lower threshold
*/
 
 
#ifndef UrineLevel_h
#define UrineLevel_h

#include "Arduino.h"

class UrineLevel
{
  public:
    UrineLevel (int pin, int range, int threshold);
    double distance();
    
    
  private:
    
    int getMean();
    
    int _pin;
    int _range;
    int _threshold;
    int _p;
    int _sum;
    int _previousValue;
    int _value;
	int _lower;
	int _upper;
	int _meanValue;
	int _mean;
    
};

#endif
