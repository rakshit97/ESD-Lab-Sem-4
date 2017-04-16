#include<LPC17xx.h>
#include "LCD.h"
#include<stdio.h>

char to_disp[10];
float x;
int j1;

int main(void)
{
	LPC_SC->PCONP &= (0x1<<12)|(0x1<<15);
	LPC_PINCON->PINSEL3 = 0xC0000000;	//P1.31 for channel 5
	init();
	
	while(1)
	{
		flag=0;
		data = 0x80;		//move to first line, first column
		writeData();
		for(j1=0;j1<30000;j1++);
		LPC_ADC->ADCR = 0x01200020;
		for(j1=0;j1<2000;j1++);
		if(LPC_ADC->ADGDR & 0x1<<31)
		{
			x = (LPC_ADC->ADGDR & 0xFFF0)>>4;
			x = x*0.0008;
			sprintf(to_disp, "%fV", x);
			disp(&to_disp[0]);
		}
	}
}
