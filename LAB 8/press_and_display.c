#include<LPC17xx.h>

unsigned long LED[4][4] = {{0x3F0, 0x060, 0x5B0, 0x4F0}, {0x660, 0x6D0, 0x7D0, 0x070}, {0x7F0, 0x6F0, 0x770, 0x7C0}, {0x390, 0x5E0, 0x790, 0x710}};
int row=0, col=0, j, flag=1;
long in=0x0000, val;

//0.4-0.11 - LED
//0.15-0.18 - rows
//0.19-0.22 - cols
//1.23-1.26 - LED controller

int main(void)
{
	SystemInit();
	SystemCoreClockUpdate();
	
	LPC_PINCON->PINSEL0 &= 0x3F0000FF;
	LPC_PINCON->PINSEL1 &= 0xFFFFC000;
	LPC_PINCON->PINSEL3 &= 0XFFC03FFF;
	LPC_GPIO0->FIODIRL |= 0x0FF0;
	LPC_GPIO0->FIODIRH |= 0x0078;
	LPC_GPIO1->FIODIRH |= 0x0780;
	//LPC_GPIO0->FIOMASKL |= 0x700F;
	//LPC_GPIO0->FIOMASKH |= 0xFFF8;
	//LPC_GPIO1->FIOMASKH |= 0xF87F;
	LPC_GPIO0->FIOCLR = 0xFFFFFFFF;
	val=LED[0][0];
	
	while(1)
	{
		while(1)
		{
			for(row=0;row<4;row++)
			{
				LPC_GPIO0->FIOCLR = 0x00780000;
				if(row==0)
				  LPC_GPIO0->FIOPINH = 0x0008;
				else if(row==1)
					LPC_GPIO0->FIOPINH = 0x0010;
				else if(row==2)
					LPC_GPIO0->FIOPINH = 0x0020;
				else
					LPC_GPIO0->FIOPINH = 0x0040;
				
				in = LPC_GPIO0->FIOPIN & 0x00078000;
				if(in==0x00008000)
					col = 0;
				else if(in==0x00010000)
					col = 1;
				else if(in==0x00020000)
					col = 2;
				else if(in==0x00040000)
					col=3;
				
				if(in!=0x00000000)
				{
					flag=1;
					val=LED[row][col];
					break;
				}
			}
			break;
		}
		
		LPC_GPIO1->FIOPINH = 0x0000;
		LPC_GPIO0->FIOPINL = val;
		for(j=0;j<100;j++);
		LPC_GPIO1->FIOPINH = 0xFFFF;
			
	}
}
