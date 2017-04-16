#include<LPC17xx.h>
#include<stdio.h>
#include "LCD.h"

unsigned int i1, j1;
	float dist;
char str[16];
int main (void)
{
	char msg1[16]={"WELCOME TO"};
	char msg3[16] = {"DISTANCE"};
	char msg4[16] = {"CALCULATOR"};
	char msg[16] = {"DIST: "};
	
	SystemInit();
	SystemCoreClockUpdate();
	init();
	
	//welcome display
	move(1, 3);
	disp_with_delay(&msg1[0]);
	clear_display();
	for(j1=0;j1<100000;j1++);
	move(1, 4);
	disp_with_delay(&msg3[0]);
	move(2, 3);
	disp_with_delay(&msg4[0]);
	for(j1=0;j1<10000;j1++);
	clear_display();
	move(1, 0);
	disp(&msg[0]);


	LPC_PINCON->PINSEL4 = (1<<20)|(0<<22); // setting P2.10 as echo pin ( function 1 ) and P2.11 as trigger Output ( function 0 )

	LPC_GPIO2->FIODIR = (0x1<<11); // setting P2.11 as Trigger Output
	
	LPC_SC->EXTINT=0x01;
	LPC_SC->EXTMODE = 0x01;
	LPC_SC->EXTPOLAR = 0x01;
	
	LPC_TIM0->TCR=0x02;
	LPC_TIM0->PR=0x02;
	LPC_TIM0->CTCR=0x00;
	LPC_TIM0->MR0 = 9;
	LPC_TIM0->MCR = 0x03;
	
	LPC_TIM1->TCR = 0x02;
	LPC_TIM1->PR = 0x2;
	
	LPC_TIM2->TCR=0x02;
	LPC_TIM2->PR=0x02;
	LPC_TIM2->CTCR=0x00;
	LPC_TIM2->MR1 = 59999;
	LPC_TIM2->MCR = (0x03<<3);
	
	NVIC_EnableIRQ(TIMER0_IRQn);
	NVIC_EnableIRQ(EINT0_IRQn);
	
	
	LPC_TIM0->TCR = 0x01;
	LPC_GPIO2->FIOSET = 1<<11;
	while(1);
}
void TIMER0_IRQHandler()
{
	LPC_TIM0->IR = 0x01;
	LPC_TIM2->TCR=0x01;
	LPC_GPIO2->FIOCLR = 1<<11;
	LPC_TIM0->TCR=0x00;
	
}
void TIMER2_IRQHandler()
{
	LPC_TIM2->IR = 0x01;
	LPC_GPIO2->FIOSET = 1<<11;
	
	LPC_TIM2->TCR=0x00;
	
}
void EINT0_IRQHandler()
{
	LPC_SC->EXTINT = 0x01;
	if(LPC_SC->EXTPOLAR&0x01)
	{
		LPC_SC->EXTPOLAR = 0x00;
		LPC_TIM1->TCR=0x02;
		LPC_TIM1->TCR = 0x01;
	}
	else
	{	
		i1 = LPC_TIM1->TC;
		move(1, 6);
		LPC_SC->EXTPOLAR = 0x01;
		LPC_TIM1->TCR = 0x00;
		dist = i1/58.0;//dividing tc value by 58 to get the result in cm 
	
		sprintf(str , "%3.2fcm   " , dist);
		disp(&str[0]);
		for(j1=0;j1<10000;j1++);
		LPC_TIM0->TCR=0x02;
		LPC_TIM0->TCR=0x01;
		LPC_GPIO2->FIOSET = 1<<11;
	}
}
