#include<LPC17xx.h>

unsigned long LED[] = {0x3F0, 0x060, 0x5B0, 0x4F0, 0x660, 0x6D0, 0x7D0, 0x070, 0x7F0, 0x6F0};
unsigned int j, s=0, min=0, hour = 0,flag=0;

int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0 &= 0xFF0000FF;
	LPC_PINCON->PINSEL3 &= 0XFFC03FFF;
	LPC_GPIO0->FIODIRL |= 0x0FF0;
	LPC_GPIO1->FIODIRH |= 0x0780;
	LPC_GPIO0->FIOMASKL |= 0xF00F;
	LPC_GPIO1->FIOMASKH |= 0xF87F;
	
	LPC_TIM0->PR = 2999;
	LPC_TIM0->MR0 = 5999;
	LPC_TIM0->TCR = 0x02;
	LPC_TIM0->MCR = 0x03;
	LPC_TIM0->TCR = 0x01;
	NVIC_EnableIRQ(TIMER0_IRQn);
	
	while(1)
	{
		LPC_GPIO1->FIOPINH = 0x0000;
		LPC_GPIO0->FIOPINL = LED[min%10];
		for(j=0;j<100;j++);
		LPC_GPIO1->FIOPINH = 0xFFFF;
		
		LPC_GPIO1->FIOPINH = 0x0080;
		LPC_GPIO0->FIOPINL = LED[min/10];
		for(j=0;j<100;j++);
		LPC_GPIO1->FIOPINH = 0xFFFF;
		
		LPC_GPIO1->FIOPINH = 0x0100;
		LPC_GPIO0->FIOPINL = LED[hour%10];
		for(j=0;j<100;j++);
		LPC_GPIO1->FIOPINH = 0xFFFF;
		
		LPC_GPIO1->FIOPINH = 0x0180;
		LPC_GPIO0->FIOPINL = LED[hour/10];
		for(j=0;j<100;j++);
		LPC_GPIO1->FIOPINH = 0xFFFF;
	}
}

void TIMER0_IRQHandler(void)
{
	LPC_TIM0->IR=1;
	min++;
	//if(flag==1){
		//min--;
		//flag=0;}
	//else if (flag==0){
		//flag=1;
	//}
	if(min>59){
		min=0;
		hour++;
	}
	if (hour>23){
		hour=0;
	}
}
