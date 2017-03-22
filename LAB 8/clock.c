#include<LPC17xx.h>

unsigned long LED[] = {0x3F0, 0x060, 0x5B0, 0x4F0, 0x660, 0x6D0, 0x7D0, 0x070, 0x7F0, 0x6F0};
unsigned int j, s=0, sec=0, min=0;

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
	
	while(1)
	{
		LPC_GPIO1->FIOPINH = 0x0000;
		LPC_GPIO0->FIOPINL = LED[sec%10];
		for(j=0;j<100;j++);
		LPC_GPIO1->FIOPINH = 0xFFFF;
		
		LPC_GPIO1->FIOPINH = 0x0080;
		LPC_GPIO0->FIOPINL = LED[sec/10];
		for(j=0;j<100;j++);
		LPC_GPIO1->FIOPINH = 0xFFFF;
		
		LPC_GPIO1->FIOPINH = 0x0100;
		LPC_GPIO0->FIOPINL = LED[min%10];
		for(j=0;j<100;j++);
		LPC_GPIO1->FIOPINH = 0xFFFF;
		
		LPC_GPIO1->FIOPINH = 0x0180;
		LPC_GPIO0->FIOPINL = LED[min/10];
		for(j=0;j<100;j++);
		LPC_GPIO1->FIOPINH = 0xFFFF;
		
	  for(j=0;j<1000;j++);
		s++;
		if(s==100)
	  {
			sec++;
			if(sec>59)
			{
				min++;
				sec=0;
			}
			if(min>59)
				min=0;
			s=0;
		}		
	}
}
