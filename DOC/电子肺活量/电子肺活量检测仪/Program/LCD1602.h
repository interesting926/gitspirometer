#ifndef __LCD1602_H__
#define __LCD1602_H__
/**********************************************************
�������ƣ�	1602��ʾ����
˵    ����	ֻ����ִ�г�ʼ��Һ����������LCD1602Init();
			����DisplayListChar( X, Y, "�ַ���" );
				������( X, Y )λ����ʾ�ַ�����
			����DisplayOneChar( X, Y, ASCII�� );
				������( X, Y )λ����ʾ���ASCII���ʾ���ַ���
**********************************************************/

#define LCDDATA  P2
#define BUSY    0x80 					//���ڼ��LCM״̬���е�BUSY��ʶ

/*
sbit  lcd1602rs	= P0^0;			//����LCD����
sbit  lcd1602rw	= P0^1; 
sbit  lcd1602en	= P0^2;
*/

sbit  lcd1602rs	= P0^5;			//����LCD����
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

/*	д����	*/
void Write1602Data( uchar WDLCM ) 
{
	ReadStatusLCM(); 					//���æ
	LCDDATA = WDLCM;
	lcd1602rs = 1;
	lcd1602rw = 0;
	lcd1602en = 0; 						//�������ٶ�̫�߿���������С����ʱ
	lcd1602en = 0; 						//��ʱ
	lcd1602en = 1;
}


/*	дָ��	*/
void Write1602Com( uchar WCLCM, BuysC ) //BuysCΪ0ʱ����æ���
{
	if ( BuysC ) ReadStatusLCM(); 		//������Ҫ���æ
	LCDDATA = WCLCM;
	lcd1602rs = 0;
	lcd1602rw = 0;	
	lcd1602en = 0;
	lcd1602en = 0;
	lcd1602en = 1;	
}


/*	��״̬	*/
uchar ReadStatusLCM( void )
{
	LCDDATA = 0xFF; 
	lcd1602rs = 0;
	lcd1602rw = 1;
	lcd1602en = 0;
	lcd1602en = 0;
	lcd1602en = 1;
	while ( LCDDATA & BUSY ); 		//���æ�ź�
	return( LCDDATA );
}


/*	LCD��ʼ��	*/
void LCD1602Init( void ) 
{
	LCDDATA = 0;
	Write1602Com( 0x38, 0 );		//������ʾģʽ���ã������æ�ź�
	Delay1ms( 5 ); 
	Write1602Com( 0x38, 0 );
	Delay1ms( 5 ); 
	Write1602Com( 0x38, 0 );
	Delay1ms( 5 ); 

	Write1602Com( 0x38, 1 ); 		//��ʾģʽ����,��ʼҪ��ÿ�μ��æ�ź�
	Write1602Com( 0x08, 1 ); 		//�ر���ʾ
	Write1602Com( 0x01, 1 ); 		//��ʾ����
	Write1602Com( 0x06, 1 ); 		// ��ʾ����ƶ�����
	Write1602Com( 0x0C, 1 ); 		// �رչ����ʾ����
}


/*	��ָ��λ����ʾһ���ַ�	*/
void DisplayOneChar( uchar X, uchar Y, uchar DData )
{
	Y &= 0x1;
	X &= 0xF; 						//����X���ܴ���15��Y���ܴ���1
	if( Y ) X |= 0x40; 				//��Ҫ��ʾ�ڶ���ʱ��ַ��+0x40;
	X |= 0x80; 						//���ָ����
	Write1602Com( X, 1 ); 			//��������
	Write1602Data( DData ); 		//������
}


/*	��ָ��λ����ʾһ���ַ�	*/
void DisplayListChar( uchar X, uchar Y, uchar code *DData )
{
	uchar ListLength;
	ListLength = 0;
	Y &= 0x1;
	X &= 0xF; 								//����X���ܴ���15��Y���ܴ���1
	while ( DData[ ListLength ] > 0x19 )	//�������ִ�β���˳�
	{
		if ( X <= 0xF ) 					//X����ӦС��0xF
		{
			DisplayOneChar( X, Y, DData[ ListLength ] ); //��ʾ�����ַ�
			ListLength ++;
			X ++;
		}
	}
}

#endif