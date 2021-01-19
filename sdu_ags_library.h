//sdu_ags_library.h

/*
*
* Version 0.5
* Created: 28/08/2019 
* Author : Jacob Caspers
*
*/

#ifndef SDU_AGS_LIBRARY_INCLUDED
#define SDU_AGS_LIBRARY_INCLUDED


//function declaration
void init_sdu_ags_library(void);


void printToExcel(void);

float getTemp(void);		

void set_sampletime(long int new_Ts);

void relay1_on(void);		//turn on RELAY1
void relay1_off(void);		//turn off RELAY1
     
void relay2_on(void);		//turn on RELAY2
void relay2_off(void);      //turn off RELAY2

void USB1_on(void);
void USB1_off(void);

void USB2_on(void);
void USB2_off(void);


#endif



