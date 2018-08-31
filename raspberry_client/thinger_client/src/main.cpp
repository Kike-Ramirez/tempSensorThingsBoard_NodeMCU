// The MIT License (MIT)
//
// Copyright (c) 2015 THINGER LTD
// Author: alvarolb@gmail.com (Alvaro Luis Bustamante)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "thinger/thinger.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define USER_ID             "KikeRamirez"
#define DEVICE_ID           "P003"
#define DEVICE_CREDENTIAL   "46y2@ok2vI#n"

#define WATER_VALVE_PIN     3   // GPIO22

// #define CAPACITIVE_TX_PIN   0  // GPIO17
// #define CAPACITIVE_TX_PIN   2  // GPIO27


int main(void)
{

    thinger_device thing(USER_ID, DEVICE_ID, DEVICE_CREDENTIAL);

    wiringPiSetup();

    pinMode (WATER_VALVE_PIN, OUTPUT) ;


    // define thing resources here. i.e, this is a sum example
    thing["sum"] = [](pson& in, pson& out){
         out["result"] = (int) in["value1"] + (int) in["value2"];
    };

	thing["valve"] << [](pson & in){
        if(in.is_empty()){
			digitalWrite(WATER_VALVE_PIN, in ? LOW : HIGH);
        }
		else{
        	if(in){
				digitalWrite (WATER_VALVE_PIN, LOW);
        	}else{
        		digitalWrite (WATER_VALVE_PIN, HIGH);
        	}
        }
	};

    thing.start();
    return 0;
}
