#include<LPC17xx.h>

unsigned long LED[10] = {0x3F0, 0x060, 0x5B0, 0x4F0, 0x660, 0x6D0, 0x7D0, 0x070, 0x7F0, 0x6F0};
int BCD[4][4] = {{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 14, 15}};
int row=0, col=0, j;
int op1 = 0, op2 = 0, op = 0, flag_op1=0, flag_op2=0, flag_op=0, flag_eq=0, res = 0, dc_pin = 0;
long in=0x0000;

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
					if(flag_op1==0 && BCD[row][col]<=9)
					{
						op1 = BCD[row][col];
						flag_op1 = 1;
					}
					else if(flag_op==0 && (BCD[row][col]>9 && BCD[row][col]<=13))
					{
						op = BCD[row][col];
						flag_op=1;
					}
					else if(flag_op2==0 && BCD[row][col]<=9 && flag_op==1)
					{
						op2 = BCD[row][col];
						flag_op2=1;
					}
					if(flag_eq==0 && (BCD[row][col]==14 || BCD[row][col]==15))
						flag_eq=1;
					
					break;
				}
			}
			if(flag_eq==1)
				break;
		}
		
		if(op==10)
			res = op1 + op2;
		else if(op==11)
			res = op1 - op2;
		else if(op==12)
			res = op1 * op2;
		else if(op==13 && op2!=0)
			res = op1 / op2;
		
		dc_pin = 0;
		flag_op1=0;
		flag_op=0;
		flag_op2=0;
		flag_eq=0;
		while(res>0)
		{
			if(dc_pin==0){
				LPC_GPIO1->FIOPINH = 0x0000;
				dc_pin=1;
			}
			else if(dc_pin==1)
				LPC_GPIO1->FIOPINH = 0x0080;
			LPC_GPIO0->FIOPINL = LED[res%10];
			for(j=0;j<100;j++);
			LPC_GPIO1->FIOPINH = 0xFFFF;
			res/=10;
		}	
	}
}
