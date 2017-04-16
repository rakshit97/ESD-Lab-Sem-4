#include <LPC17xx.h>
void init(void);

unsigned long int i;
unsigned char flag,flag1;
unsigned int val,row,col,var1,dig1;
void init(void){
		LPC_SC->PCONP|=1<<6;
		LPC_PINCON->PINSEL3&= ~(0x0000C000);
		LPC_PINCON->PINSEL3 |= 0x00008000;
		LPC_PWM1->PCR=0x1000;
		LPC_PWM1->MCR=0x3;
		LPC_PWM1->MR0=30000;
		LPC_PWM1->MR4=40000;
		LPC_PWM1->LER=0xFF;
		LPC_PWM1->TCR=0x02;
		LPC_PWM1->TCR=0x09;
		NVIC_EnableIRQ(PWM1_IRQn);
		return;
}


int scan(){
	unsigned long temp3;
	while(1){
		flag=0;
		for (row=0;row<4;row++){
					if (row==0){
						var1=0x0080000;
					}
					else if (row==1){
						var1=0x0100000;
					}
					else if(row==2){
						var1=0x02000000;
					}
					else if(row==3){
						var1=0x04000000;
					}
					LPC_GPIO0->FIOCLR=0x07800000;
					LPC_GPIO0->FIOSET=var1;
					temp3 = LPC_GPIO0->FIOPIN;
					temp3 &= 0x00078000;
					if (temp3!=0x00000000){
						if(temp3==0x00008000){
							col=0;
							flag=1;
							break;
						}
						if (temp3==0x00010000){
							col=1;
							flag=1;
							break;
						}
						if (temp3==0x00020000){
							col=2;
							flag=1;
							break;
						}
						if (temp3==0x00040000){
							col=3;
							flag=1;
							break;
						}
					}
				}
				if (flag==1){
					break;
				}
		}
	return col;
}


void PWM1_IRQHandler(void){
	LPC_PWM1->IR = 0xFF;
	dig1=scan();
	if (dig1==0){
			LPC_PWM1->MR4=3000;
	}
	else if (dig1==1){
			LPC_PWM1->MR4=7500;
	}
	else if (dig1==2){
			LPC_PWM1->MR4=15000;
	}
	else if (dig1==3){
			LPC_PWM1->MR4=22500;
	}
	LPC_PWM1->LER=0xFF;
}

int main(void){
		SystemInit();
		SystemCoreClockUpdate();
		LPC_PINCON->PINSEL0=0x3F0000FF;
		LPC_PINCON->PINSEL1=0xFFFFC000;
		LPC_GPIO0->FIODIR=0x007800000;
		init();
		while(1){
				for (i=0;i<100;i++);
		}
}
