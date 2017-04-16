#include<LPC17xx.h>
#include "LCD.h"

int j1;
char line1[10] = {"Rakshit"};
char line2[] = {"Thakkar"};

int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	
	init();
	line1[8] = '\0';
	
	disp(&line1[0]);		//display line 1
	
	flag=0;
	data = 0xC0;		//move to second line, first column
	writeData();
	for(j1=0;j1<30000;j1++);
	
	disp(&line2[0]);		//display line 2
}
