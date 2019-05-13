#ifndef __LCD1602_H__
#define __LCD1602_H__
/**********************************************************
工程名称：	1602显示程序
说    明：	只需先执行初始化液晶函数——LCD1602Init();
			调用DisplayListChar( X, Y, "字符串" );
				可以在( X, Y )位置显示字符串；
			调用DisplayOneChar( X, Y, ASCII码 );
				可以在( X, Y )位置显示这个ASCII码表示的字符；
**********************************************************/

#define LCDDATA  P2
#define BUSY    0x80 					//用于检测LCM状态字中的BUSY标识

/*
sbit  lcd1602rs	= P0^0;			//定义LCD引脚
sbit  lcd1602rw	= P0^1; 
sbit  lcd1602en	= P0^2;
*/

sbit  lcd1602rs	= P0^5;			//定义LCD引脚
sbit  lcd1602rw	= P0^6; 
sbit  lcd1602en	= P0^7;

void  LCD1602Init( void );
void  DisplayOneChar( uchar X, uchar Y, uchar DData );
void  DisplayListChar( uchar X, uchar Y, uchar code *DData );
void  Write1602Com( uchar WCLCM, BuysC );
void  Write1602Data( uchar );
uchar ReadStatusLCM( void );
void  Delay1ms( uint z );
	

void Delay1ms( uint z )					   
{
	uint x, y;
	for ( x = z; x > 0; x -- )
		for ( y = 110;y > 0; y -- );
}

/*	写数据	*/
void Write1602Data( uchar WDLCM ) 
{
	ReadStatusLCM(); 					//检测忙
	LCDDATA = WDLCM;
	lcd1602rs = 1;
	lcd1602rw = 0;
	lcd1602en = 0; 						//若晶振速度太高可以在这后加小的延时
	lcd1602en = 0; 						//延时
	lcd1602en = 1;
}


/*	写指令	*/
void Write1602Com( uchar WCLCM, BuysC ) //BuysC为0时忽略忙检测
{
	if ( BuysC ) ReadStatusLCM(); 		//根据需要检测忙
	LCDDATA = WCLCM;
	lcd1602rs = 0;
	lcd1602rw = 0;	
	lcd1602en = 0;
	lcd1602en = 0;
	lcd1602en = 1;	
}


/*	读状态	*/
uchar ReadStatusLCM( void )
{
	LCDDATA = 0xFF; 
	lcd1602rs = 0;
	lcd1602rw = 1;
	lcd1602en = 0;
	lcd1602en = 0;
	lcd1602en = 1;
	while ( LCDDATA & BUSY ); 		//检测忙信号
	return( LCDDATA );
}


/*	LCD初始化	*/
void LCD1602Init( void ) 
{
	LCDDATA = 0;
	Write1602Com( 0x38, 0 );		//三次显示模式设置，不检测忙信号
	Delay1ms( 5 ); 
	Write1602Com( 0x38, 0 );
	Delay1ms( 5 ); 
	Write1602Com( 0x38, 0 );
	Delay1ms( 5 ); 

	Write1602Com( 0x38, 1 ); 		//显示模式设置,开始要求每次检测忙信号
	Write1602Com( 0x08, 1 ); 		//关闭显示
	Write1602Com( 0x01, 1 ); 		//显示清屏
	Write1602Com( 0x06, 1 ); 		// 显示光标移动设置
	Write1602Com( 0x0C, 1 ); 		// 关闭光标显示设置
}


/*	按指定位置显示一个字符	*/
void DisplayOneChar( uchar X, uchar Y, uchar DData )
{
	Y &= 0x1;
	X &= 0xF; 						//限制X不能大于15，Y不能大于1
	if( Y ) X |= 0x40; 				//当要显示第二行时地址码+0x40;
	X |= 0x80; 						//算出指令码
	Write1602Com( X, 1 ); 			//发命令字
	Write1602Data( DData ); 		//发数据
}


/*	按指定位置显示一串字符	*/
void DisplayListChar( uchar X, uchar Y, uchar code *DData )
{
	uchar ListLength;
	ListLength = 0;
	Y &= 0x1;
	X &= 0xF; 								//限制X不能大于15，Y不能大于1
	while ( DData[ ListLength ] > 0x19 )	//若到达字串尾则退出
	{
		if ( X <= 0xF ) 					//X坐标应小于0xF
		{
			DisplayOneChar( X, Y, DData[ ListLength ] ); //显示单个字符
			ListLength ++;
			X ++;
		}
	}
}

#endif