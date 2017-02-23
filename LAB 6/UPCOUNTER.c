#include<LPC17xx.h>
unsigned int i, j;
unsigned long LED = 0x00000001;

int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0 &= 0xFF0000FF;
	LPC_GPIO0->FIODIR |= 0x00000FF0;
	
	while(1)
	{
		LED = 0x00000001;
		for(i=1;i<256;i++)
		{
			LPC_GPIO0->FIOPIN = LED;
			for(j=0;j<100000;j++);
			LED+=1;
		}
	}
}
