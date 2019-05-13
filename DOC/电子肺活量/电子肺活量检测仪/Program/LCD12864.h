
/**********************************************************
工程名称：	12864显示程序
创建时间：	2011-6-2
作    者：	秦英哲
说    明：	只需先执行初始化液晶函数——LCDInit();
			调用DisplayListChar( x, y, " 字符串 " );
				可以在(x,y)位置显示字符串；
			调用DisplayOneChar( x, y, 一个字符编码高4位, 一个字符编码高低4位, );
				可以在(x,y)位置显示这个字符；
			调用DisplayPicture( picture );
				可以整屏显示这张图片,图片分辨率必须为128*64；
			PORT口一定不能加上拉电阻，否则可能无法正常显示；
最后修改：	2011-6-7
**********************************************************/

#include<intrins.h>

#define PORT P2				//定义数据口

sbit lcd12864rs = P0^0;
sbit lcd12864rw = P0^1;
sbit lcd12864en = P0^2;
sbit lcd12864psb = P0^3;


void LCDInit();
void Delay5us( uint z );
void Write12864Com( uchar com );
void Write12864Date( uchar dat );
void DisplayOneChar( uchar x, uchar y, uchar a, uchar b );
void DisplayListChar( uchar x, uchar y, uchar *s );
void DisplayPicture( uchar *picture );
bit Busy();


/*
uchar code picture[]={
0x00,0x00,0x00,0x17,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x05,0xFF,0xFE,0x40,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x60,0x00,
0x00,0x00,0x1F,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0xF0,0x00,
0x00,0x00,0x7F,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x07,0x1F,0x00,0x00,0x71,0xF2,0x00,
0x00,0x07,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x07,0xBF,0x00,0x00,0x79,0xFF,0x00,
0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x03,0xFE,0x00,0x00,0xFF,0xFF,0x80,
0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x01,0xFC,0x00,0x00,0x7F,0xFF,0x80,
0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x01,0xFE,0x00,0x00,0x7F,0xEF,0xC0,
0x01,0xBF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x07,0xFC,0x00,0x00,0xFF,0xEF,0xC0,
0x00,0xBF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x07,0xF8,0x00,0x01,0xFF,0xFF,0x80,
0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x07,0xF0,0x00,0x07,0xFF,0xFF,0x00,
0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x03,0xFF,0x00,0x07,0xF7,0xFF,0x80,
0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x03,0xFF,0x80,0x03,0xF0,0xC7,0x80,
0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x05,0xF9,0xC0,0x00,0xE0,0xCF,0x80,
0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x0B,0xF3,0xC0,0x01,0xE0,0xDF,0x80,
0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x19,0xF7,0x80,0x01,0xF0,0xFF,0x00,
0x07,0xFF,0xFF,0xD5,0x6F,0xFF,0xFF,0x00,0x00,0x38,0xFF,0x80,0x03,0xF0,0xFE,0x00,
0x03,0xFF,0xFD,0x00,0x11,0xFF,0xFF,0x80,0x00,0x1D,0xFF,0xE0,0x07,0xBE,0xFF,0x80,
0x03,0xFF,0xFC,0x00,0x00,0xAF,0xFF,0x00,0x00,0x1D,0xFF,0xE0,0x07,0x7F,0xCF,0x80,
0x01,0xFF,0xE0,0x00,0x00,0x07,0xFF,0x00,0x00,0x1F,0xFF,0xE0,0x0E,0xEF,0xDF,0x80,
0x03,0xFF,0x00,0x00,0x00,0x03,0xFF,0x00,0x00,0xFF,0xFF,0x00,0x1E,0xCF,0xDF,0x00,
0x03,0xFD,0x00,0x00,0x00,0x00,0xFF,0x00,0x03,0xFF,0xF0,0x00,0x1D,0xFF,0xDE,0x00,
0x01,0xFC,0x00,0x00,0x00,0x01,0x3F,0x00,0x03,0xFF,0x8E,0x00,0x31,0xF3,0xCC,0x00,
0x01,0xF0,0x00,0x00,0x00,0x00,0xFE,0x00,0x01,0xFF,0x8F,0x80,0x01,0xC0,0xDF,0xE0,
0x03,0xF8,0x00,0x00,0x00,0x00,0x3E,0x00,0x00,0x0F,0x1F,0xC0,0x00,0x00,0xFF,0xF0,
0x01,0xE0,0x40,0x00,0x00,0x00,0x3E,0x00,0x00,0x1E,0x0F,0xE0,0x00,0x00,0xFF,0xE0,
0x01,0xD0,0x2A,0x80,0x03,0xF8,0x1E,0x00,0x00,0x3C,0x07,0xE0,0x00,0x00,0xCE,0x00,
0x01,0xE0,0x7F,0xC0,0x3F,0xFC,0x1E,0x00,0x00,0x78,0x03,0xF0,0x00,0x00,0xC0,0x00,
0x01,0xB0,0xFF,0xC0,0x3F,0xFC,0x2F,0x00,0x00,0x00,0x03,0xE0,0x00,0x00,0xC0,0x00,
0x03,0xC0,0xFF,0xC0,0xFF,0xFE,0x3E,0x00,0x00,0x00,0x01,0xE0,0x00,0x00,0x40,0x00,
0x01,0xA0,0x12,0xF0,0x38,0x10,0x2E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x03,0xC1,0x48,0x70,0x8B,0x40,0x1E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x07,0xC1,0x7F,0xDF,0xBD,0xFC,0x6F,0x00,0x00,0x00,0x70,0x00,0x00,0x03,0x00,0x00,
0x0F,0xC3,0xFF,0xFF,0xFF,0xFF,0x1F,0xC0,0x00,0x00,0x78,0x00,0x00,0x07,0xC0,0x00,
0x1F,0x87,0xFF,0xFD,0xFF,0xFF,0x9F,0xE0,0x00,0x00,0x78,0x00,0x00,0x0F,0xE0,0x00,
0x7D,0x07,0xFF,0xF4,0xFF,0xFF,0x17,0xE0,0x00,0x00,0x78,0x00,0x00,0x1F,0xE0,0x00,
0x3D,0x0F,0xFF,0xF2,0xFF,0xFF,0x11,0xF0,0x00,0x00,0x7E,0x00,0x00,0x3F,0xE8,0x00,
0x7A,0x87,0xFF,0xE0,0x7F,0xFF,0x08,0xE0,0x00,0x00,0x7F,0x00,0x00,0x7F,0xFE,0x00,
0x3A,0x43,0xFF,0xF1,0x7F,0xFE,0xB7,0xF0,0x00,0x00,0xFF,0x80,0x00,0xFF,0xFE,0x00,
0x3B,0x43,0xFF,0xD0,0x3F,0xFF,0x08,0xE0,0x00,0x03,0xFF,0x00,0x00,0x7F,0x7C,0x00,
0x3F,0xC1,0xFF,0xD0,0x1D,0xD0,0x3E,0xE0,0x00,0x0F,0xFE,0x00,0x00,0x38,0x7C,0x00,
0x3F,0xF0,0x5F,0x32,0x03,0x40,0x7E,0xC0,0x00,0x1F,0xFC,0x00,0x00,0x01,0xFC,0x00,
0x1F,0x70,0x00,0xB8,0x04,0x00,0x3F,0xE0,0x00,0x1F,0xF0,0x00,0x00,0x07,0xFE,0x00,
0x1F,0x70,0x00,0x61,0x18,0x00,0x7D,0xC0,0x00,0x0F,0xF8,0x00,0x00,0x1F,0xDE,0x00,
0x0F,0x38,0x00,0x54,0x50,0x00,0x7F,0x80,0x00,0x07,0xF8,0x00,0x00,0x3F,0x9E,0x00,
0x0E,0xB8,0x00,0xE9,0x30,0x00,0x79,0x80,0x00,0x07,0xFC,0x00,0x00,0x3F,0xBC,0x00,
0x07,0x78,0x00,0xFF,0xE0,0x00,0x37,0x80,0x00,0x0F,0xFF,0x00,0x00,0x0F,0xB8,0x00,
0x07,0xB8,0x00,0x55,0xC0,0x00,0x7B,0x80,0x00,0x0F,0xFF,0x80,0x00,0x07,0xF8,0x00,
0x03,0xF8,0x00,0x04,0x00,0x00,0x7F,0x00,0x00,0x1E,0xF7,0xE0,0x00,0x27,0xF0,0x00,
0x01,0xF8,0x00,0x00,0x08,0x00,0xFE,0x00,0x00,0x3E,0xFF,0xF8,0x00,0x67,0xF0,0x00,
0x00,0x78,0x00,0x40,0x0E,0x00,0x70,0x00,0x00,0x7C,0xFF,0xFC,0x00,0x6F,0xE0,0x00,
0x00,0x38,0x00,0x7A,0x3C,0x00,0xE0,0x00,0x00,0xFB,0xFF,0xFE,0x00,0x7F,0xC0,0x40,
0x00,0x1C,0x00,0x7A,0xF8,0x00,0xC0,0x00,0x01,0xEF,0xFC,0xFE,0x00,0x7F,0x00,0x20,
0x00,0x38,0x00,0x3F,0xF8,0x01,0xC0,0x00,0x00,0x87,0xF0,0x7E,0x00,0x7C,0x00,0x70,
0x00,0x0C,0x00,0x1F,0xE0,0x03,0xC0,0x00,0x00,0x07,0xF0,0x3C,0x00,0x70,0x00,0xF0,
0x00,0x0E,0x00,0x0F,0xA0,0x01,0xC0,0x00,0x00,0x00,0xF0,0x00,0x00,0xE0,0x01,0xF0,
0x00,0x0F,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,0xF0,0x0F,0xF0,
0x00,0x07,0xC0,0x00,0x00,0x0B,0x80,0x00,0x00,0x00,0xF0,0x00,0x00,0xFF,0xFF,0xF8,
0x00,0x03,0xB0,0x00,0x00,0x2F,0x00,0x00,0x00,0x01,0xF0,0x00,0x00,0x7F,0xFF,0xF0,
0x00,0x01,0xE8,0x00,0x00,0x3C,0x00,0x00,0x00,0x01,0xF0,0x00,0x00,0x3F,0xFF,0xC0,
0x00,0x00,0x7C,0x00,0x01,0xF8,0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x1F,0xFE,0x00,
0x00,0x00,0x3F,0x80,0x02,0xE0,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x0F,0x60,0x07,0xA0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x03,0xBE,0xBF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,   
};
*/


void LCDInit()							//12864初始化
{
	Write12864Com( 0x30 );				//切换到标准指令
	Delay5us( 40 );
	Write12864Com( 0x0c );				//打开显示,不显示光标
	Delay5us( 40 );
	Write12864Com( 0x01 );				//清除显示
	Delay5us( 2000 );
	Write12864Com( 0x06 );				//光标自动加1
}


/*
void DisplayPicture( uchar *picture )	
{
	uchar i,j;
	Write12864Com( 0x34 );				//切换到扩充指令
	Write12864Com( 0x36 );
	for(i=0;i<32;i++)
	{ 
		Write12864Com( 0x80 | i );		//垂直坐标		
		Write12864Com( 0x80 );			//水平坐标					  	 
		for( j = 0; j < 16; j ++ )				//一行可显示16个字符
		{
			Write12864Date( *picture ++ );
		}
 	}
	for( i = 0; i < 32; i ++ )
	{	  
		Write12864Com( 0x80 + i );
		Write12864Com( 0x88 );						  
		for( j = 0; j < 16; j ++ )
		{
			Write12864Date( *picture ++ );
		}
	}
	Write12864Com( 0x30 );
}
*/

/*	在( x, y )处显示一串文字	*/
void DisplayListChar( uchar x, uchar y, uchar *s )	
{
	uchar pos;
	if( y == 1 )						//第一行
	{
		y = 0x80;
	}
	else if( y == 2 )					//第二行
	{
		y = 0x90;
	}
	else if( y == 3 )					//第三行
	{
		y = 0x88;
	}
	else if( y == 4 )					//第四行
	{
		y = 0x98;
	}
	pos = x + y - 1;					//首地址为0X80	
	Write12864Com( pos );
	while ( *s != '\0' )             
	{                          
		Write12864Date( *s );
		s ++;
	}
}


/*	在( x, y )处显示一个文字 	*/
void DisplayOneChar( uchar x, uchar y, uchar a, uchar b )	 
{
	uchar pos;
	if( y == 1 )						//第一行
	{
		y = 0x80;
	}
	else if( y == 2 )					//第二行
	{
		y = 0x90;
	}
	else if( y == 3 )					//第三行
	{
		y = 0x88;
	}
	else if( y == 4 )					//第四行
	{
		y = 0x98;
	}
	pos = x + y - 1;					//首地址为0X80	
	Write12864Com( pos );                          
	Write12864Date( a );
	Write12864Date( b );
}


void Delay5us( uint z )							//延时5毫秒
{
	uint i = z;
	while( i )
	{
		_nop_();
		_nop_();
		_nop_();
		i --;
	}
}


void Write12864Com( uchar com )			//写指令
{
	while( Busy() );
	lcd12864rw = 0;
	lcd12864rs = 0;
	lcd12864en = 0;
	Delay5us( 1 );
	PORT = com;
	Delay5us( 1 );
	lcd12864en = 1;
	Delay5us( 1 );
	lcd12864en = 0;
}


void Write12864Date( uchar dat )		//写数据
{
	while( Busy() );
	lcd12864rw = 0;
	lcd12864rs = 1;
	lcd12864en = 0;
	Delay5us( 1 );
	PORT = dat;
	Delay5us( 1 );
	lcd12864en = 1;
	Delay5us( 1 );
	lcd12864en = 0;
}


bit Busy()								//检测忙碌状态
{
	bit result;
	PORT = 0xff;
	lcd12864rs = 0;  
	lcd12864rw = 1;
	lcd12864en = 1;
	Delay5us( 1 );
	result = ( bit ) ( PORT & 0x80 );	//DB7位1忙碌
	Delay5us( 1 );
	lcd12864en = 0;
	return result;
}