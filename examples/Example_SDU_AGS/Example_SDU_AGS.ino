#include"sdu_ags_library.h"

float Celsius = 0;            		//Holds the current Temperature


//////////////////////////////////////////////////////////////////////////////////
//====================================SETUP=====================================//
//      			  	This part of the code only runs once in the beginning	     	  //
//////////////////////////////////////////////////////////////////////////////////

void setup(void){
  init_sdu_ags_library();			//Setup up of AGS sensor board library .
  set_sampletime(1000);				//Set sample time in ms (1000ms = 1sec).
  printToExcel();					    //enable print to excel.
}


//////////////////////////////////////////////////////////////////////////////////
//====================================Loop======================================//
//					        	This part of the code runs in loop.			            			//
//////////////////////////////////////////////////////////////////////////////////

void loop(void)
{
  Celsius = getTemp();			//Reads the temperature sensor and stores it in Celcius
  
  if(Celsius >= 25.1)			//If temp is bigger og equal to 25.1 then do commands in {}
  {		
  	relay1_off();
  	relay2_off();
  	USB1_off();
  	USB2_off();
  }
  
  if(Celsius <= 22.9)			//If temp is bigger og equal to 25.1 then do commands in {}
  {				
  	relay1_on();
  	relay2_on();
  	USB1_on();
  	USB2_on();
  }
	  
}






// Guide how to programm:
/*
 * Default sample time (Ts):		1000 ms = 1 s
 * 
 * printToExcel();					        //Makes the programm print to excel (enables)
 *      
 * getTemp();						            //Returns the temperature every Ts (sample time)
 * 
 * set_sampletime([float] new_Ts);	//Change the sample time!
 *                                	Note: Can be changed to values between 100 ms and 100000 ms
 *									                If value out of this range is set: 1sec is overwriting.
 *
 *
 * relay1_on();						          //turns on the Relay1
 * relay1_off();					          //turns off the Relay1
 *
 * relay2_on();						          //turns on the Relay2
 * relay2_off();					          //turns off the Relay2
 *
 * USB1_on();						            //turns on the USB1
 * USB1_off();						          //turns off the USB1
 *
 * USB2_on();						            //turns on the USB2
 * USB2_off();					          	//turns off the USB2
 
//Definition of the Outputs on the shield
#define Analog_1 A1
#define Analog_2 A3
#define Analog_3 A0
#define Analog_4 A4

#define Digital_1 9
#define Digital_2 10
#define Digital_3 7
#define Digital_4 6
 

 */
