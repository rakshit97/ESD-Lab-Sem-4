#include<LPC17xx.h>
#include "LCD.h"
int cmd=0x0, data=0x00, flag=0, j,i;
void init()
{
	LPC_PINCON->PINSEL1 = 0xFC003FFF;
	LPC_GPIO0->FIODIRH = 0x1F80;
	clearPorts();
	flag=0;
	for(j=0;j<3200;j++);
	
	for(i=0;i<3;i++)		//wake up
	{
		cmd = 0x3<<23;
		writeCmd();
		for(j=0;j<30000;j++);
	}
	cmd = 0x2<<23;		//return home
	writeCmd();
	for(j=0;j<30000;j++);
	
	data = 0x28;		//inform that there are 2 lines, default font
	writeData();
	for(j=0;j<30000;j++);
	
	data = 0x01;		//clear display
	writeData();
	for(j=0;j<10000;j++);
	
	data = 0x06;		//increment cursor after writing, don't shift data
	writeData();
	for(j=0;j<800;j++);
	
	data = 0x80;		//move to first line, first column
	writeData();
	for(j=0;j<800;j++);
	
	data = 0x0C;		//switch on LCD, show cursor and blink
	writeData();
	for(j=0;j<800;j++);
}

void clearPorts()
{
	LPC_GPIO0->FIOCLRH = 0x1F80;
}

void writeCmd()
{
	clearPorts();
	LPC_GPIO0->FIOPIN = cmd;
	if(flag==0)
	{
		LPC_GPIO0->FIOCLR = RS_CTRL;
	}
	else if(flag==1)
	{
		LPC_GPIO0->FIOSET = RS_CTRL;
	}
	LPC_GPIO0->FIOSET = EN_CTRL;
	for(j=0;j<50;j++);
	LPC_GPIO0->FIOCLR = EN_CTRL;
}

void writeData()
{
	cmd = (data & 0xF0)<<19;
	writeCmd();
	cmd = (data & 0x0F)<<23;
	writeCmd();
	for(j=0;j<1000;j++);
}

void disp(char *to_disp)
{
	i = 0;
	while(to_disp[i]!='\0')
	{
		data = to_disp[i];
		flag=1;
		writeData();
		i++;
	}
}

void disp_with_delay(char *to_disp)
{
	i = 0;
	while(to_disp[i]!='\0')
	{
		data = to_disp[i];
		flag=1;
		writeData();
		i++;
		for(j=0;j<50000;j++);
	}
}

void move(int l, int c)
{
	flag=0;
	if(l==1)
		data = 0x80;
	else
		data = 0xC0;
	data = data+c;
	writeData();
	for(j=0;j<800;j++);
}

void clear_display()
{
	flag = 0;
	data = 0x01;
	writeData();
	for(j=0;j<10000;j++);
}
