//sdu_ags_library.cpp

/*
*
* Version 0.5
* Created: 28/08/2019 
* Author : Jacob Caspers
*
*/


#include "OneWire.h"
#include "DallasTemperature.h"
#include "sdu_ags_library.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

//Definitions
#define ONE_WIRE_BUS 	6         			//Define sensor output
#define RELAY1 			4              		//PD4
#define RELAY2 			5					//PD5
#define USB1			3					//PD3
#define USB2			2					//PD2

// Internal Functions
void excel_setup(void);					//setup to send to excel
void timer0_interrupt_setup(void);		//1kHz Timer setup

//Internal Variables
volatile long int sampletime = 1000; 	//sample time in [mili seconds] 
volatile int sample_counter = 0;		//counter to count to the sample time
volatile char flag_print = 0;			//active when data should be printed to excel
volatile char flag_getData = 0;			//getting Data only when neccessary
volatile char print_enable = 0;

int timeStamp = 0;

// Initialise the OneWire and Dallas Objects (Sensor D6)
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//=====================================================//
///////////////////////INIT//////////////////////////////
void init_sdu_ags_library(void){
	
	Serial.begin(9600); 	
	
	sensors.begin();					//function from other libary
		
	///////////////////////Outputs to relays//////////////////////////////
	pinMode(RELAY1, OUTPUT);            //Set "RELAY1" as an output.
	digitalWrite(RELAY1, HIGH);         //Set initial High which means off. 
	
	pinMode(RELAY2, OUTPUT);             //Set "RELAY1" as an output.
	digitalWrite(RELAY2, HIGH);         //Set initial High which means off. 
	
	pinMode(USB1, OUTPUT);				//Set "USB1" as an output.
	digitalWrite(USB1, LOW);			//Set initial low which means off.
	
	pinMode(USB2, OUTPUT);				//Set "USB2" as an output.
	digitalWrite(USB2, LOW);			//Set initial low which means off.	
	
	excel_setup();						//Excel coms init.
	
	timer0_interrupt_setup();			//setup for Timer0
	
}

void excel_setup(void){
	//printing setup for excel
	Serial.println("CLEARSHEET");
	Serial.println("CLEARDATA");
	Serial.println("DATA, #, Celcius[C]");
}

void timer0_interrupt_setup(void){
	
	/// THIS TIMER INTERRUPTS EVERY 1ms //
	
	// Set the Timer Mode to CTC
	TCCR0A |= (1 << WGM01);
	
	// Set the value that you want to count to
	OCR0A = 0xF9;
	
	//Set the ISR COMPA vect
	TIMSK0 |= (1 << OCIE0A);
	
	// set prescaler to 64 and start the timer
	TCCR0B |= (1 << CS01) | (1 << CS00);	 	
	
	//Enable interrupts
	sei();				
}


void set_sampletime(long int new_Ts){
	
	//check boundary
	if((new_Ts <= 99)||(new_Ts >= 100001)){
		sampletime = 1000;
	}
	
	//set timing value 
	sampletime = new_Ts;
}


float getTemp(void)
{
	while(!flag_getData); 							//wait until should be sampled 
	
	if(flag_getData >= 1){
		flag_getData = 0;
		float Celsius = 0;
		sensors.requestTemperatures();              //Request temperature.
		Celsius = sensors.getTempCByIndex(0);       //Wait for value and store.
		
		if(flag_print == 1){
			flag_print = 0;							//resetting the flag to 0
			Serial.print("DATA, ");
			//Serial.print("AUTOSCROLL_20, ");
			Serial.print(timeStamp);
			Serial.print(",");
			Serial.println(Celsius);
		}
		return Celsius;
	}
	else	
		flag_getData = 0;
}


void printToExcel(void)	//setting it to print to excel
{
	print_enable = 1;
}


ISR (TIMER0_COMPA_vect) // timer0 overflow interrupt 1kHz
{	//event to be executed every 1ms here

	if(sample_counter >= sampletime){
		sample_counter = 0;
		timeStamp++;
		
		if(print_enable == 1){
			flag_print = 1;
		}
		
		flag_getData = 1;	//enables new data
	}
	else	
		sample_counter++;
}


void relay1_on(void){
	digitalWrite(RELAY1, LOW);
}	
void relay1_off(void){
	digitalWrite(RELAY1, HIGH);
}
void relay2_on(void){
	digitalWrite(RELAY2, LOW);
}
void relay2_off(void){
	digitalWrite(RELAY2, HIGH);
}
void USB1_on(void)
{
	digitalWrite(USB1, HIGH);
}
void USB1_off(void)
{
	digitalWrite(USB1, LOW);
}
void USB2_on(void)
{
	digitalWrite(USB2, HIGH);
}
void USB2_off(void)
{
	digitalWrite(USB2, LOW);
}
