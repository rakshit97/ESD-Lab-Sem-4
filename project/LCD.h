#ifndef LCD_H
#define LCD_H

#define RS_CTRL 0x08000000;	//0.27
#define EN_CTRL 0x10000000;	//0.28
#define DT_CTRL 0x07800000;	//0.23-0.26

void init(void);
void clearPorts(void);
void writeCmd(void);
void writeData(void);
void disp(char *);
void disp_with_delay(char *);
void move(int l, int c);
void clear_display(void);
extern int flag, cmd, data;
#endif
