#include <reg51.h>

unsigned char KeyValue;		//键值
unsigned char sec_50, sec, min, hour;
unsigned char number[8];
unsigned char table[13] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x73};//显示0~9的值
sbit BS_A = P3^0;
sbit BS_B = P3^1;
sbit BS_C = P3^2;

//i=1时，延时10us
void delay(unsigned int i)	{while(i--);}

/*交换AP的显示*/
void exchangeAP(void)
{
	if( number[0] == 0x77 )  number[0] = 0x73;
	else  number[0] = 0x77;		
}

//定时器0初始化
void timer0Init(void)
{
	TMOD = 0x01;
	TH0 = 0x3c;  TL0 = 0xb0;		//50ms初值
	EA=1;  ET0 = 1;  TR0 = 1;	//开中断，开定时器
	sec_50 = sec = min = hour = 0;	//初始化清零
	number[0] = 0x77;  number[1] = 0x40;	//'A'//'-'
}

//中断，自动计时
void timer0() interrupt 1
{
	TH0 = 0x3c;	TL0 = 0xb0;			//50ms初值
	sec_50++;
	if( sec_50 == 20 )
	{
		sec_50 = 0;  sec++;			//50ms计数清零，秒数加一
		if( sec >= 60 )
		{
			sec = 0;  min++;		//秒数清零，分钟数加一
			if( min >= 60 )
			{
				min = 0; hour++;	//分钟数清零，小时数加一
				if( hour >=12 )
				{
					hour = hour - 12;
					exchangeAP();	
				}
			}
		}
	}
}

//有键按下时求键值
void findKey(void)
{
	int counter;
	bit flag = 0;				//低四位列值作为输入
	P1 = 0x0f;
	if( P1 != 0x0f )
	{
		delay(10000);		//延时消抖
		if( P1 != 0x0f )
		{
			flag = 1;		//有按键按下			
			//找列标
			P1 = 0x0f;
			switch(P1)
			{
				case(0x07):	KeyValue = 1; break;
				case(0x0b):	KeyValue = 2; break;
				case(0x0d): KeyValue = 3; break;
				case(0x0e):	KeyValue = 4; break;
			}
			//找行标
			P1 = 0xf0;
			switch(P1)
			{
				case(0x70):	KeyValue = KeyValue; break;
				case(0xb0):	KeyValue = KeyValue+4; break;
				case(0xd0): KeyValue = KeyValue+8; break;
				case(0xe0):	KeyValue = KeyValue+12; break;
			}
		}
	}
	while( (counter<50) && (P1!=0xf0) )	 //松手检测
	{
		delay(10000);
		counter++;
	}
	if(flag)		//若有按键按下	
	{
		flag = 0;
		if(KeyValue == 1)
		{
			number[1] = 0x40;
			exchangeAP();
		}
		else if(KeyValue == 5)  {number[0]=0x00; number[1]=0x00;}
		else if(KeyValue == 2)  hour++;
		else if(KeyValue == 6)
		{
			if( hour == 0 )
			{
				hour = 11;
				if( number[0] == 0x77 )  number[0] = 0x73;
				else  number[0] = 0x77;
			}
			else  hour--;
		}  
		else if(KeyValue == 3)  min++;
		else if(KeyValue == 7)
		{
			if( min == 0 )
			{
				min = 59;
				if( hour == 0 )
				{
					hour = 11;
					exchangeAP();
				}
				else hour--;
			}
			else  min--;
		}  
		else if(KeyValue == 4)  sec++;
		else if(KeyValue == 8)
		{
			if( sec == 0 )
			{
				sec = 59;
				if( min == 0 )
				{
					min = 59;
					if( hour == 0 )
					{
						hour = 11;
						exchangeAP();
					}
					else  hour--;
				}
				else  min--;
			}				
			else  sec--;
		}  
		if( sec == 60 )  {sec = 0; min++;}
		if( min == 60 )  {min = 0; hour++;}
		if( hour ==12 )  {hour = hour - 12;	exchangeAP();}

	}
}

//求数码管每位的输出值
void output(void)
{
	number[2] = table[hour/10];
	number[3] = table[hour%10];
	number[4] = table[min/10];
	number[5] = table[min%10];
	number[6] = table[sec/10];
	number[7] = table[sec%10];
}

//显示在数码管上
void show()
{
	int i;
	for( i = 0; i < 8; i++ )
	{
		switch(i)	 //选择点亮的数码管
		{
			case(0): BS_A=0; BS_B=0; BS_C=0; break;//显示第0位
			case(1): BS_A=1; BS_B=0; BS_C=0; break;//显示第1位
			case(2): BS_A=0; BS_B=1; BS_C=0; break;//显示第2位
			case(3): BS_A=1; BS_B=1; BS_C=0; break;//显示第3位
			case(4): BS_A=0; BS_B=0; BS_C=1; break;//显示第4位
			case(5): BS_A=1; BS_B=0; BS_C=1; break;//显示第5位
			case(6): BS_A=0; BS_B=1; BS_C=1; break;//显示第6位
			case(7): BS_A=1; BS_B=1; BS_C=1; break;//显示第7位	
	    }
		P2 = number[i];
		delay(100);
		P2 = 0x00;
	}
}
	
//主函数
void main(void)
{
	timer0Init();
	while(1)
	{
		findKey();
		output();
		show();
	}
}