

sbit s1 = P3^7;					// ��ʼ
sbit s2 = P3^0;					// ��ȡ����
sbit s3 = P3^1;					// �Ϸ�
sbit s4 = P3^2;					// �·�

/*
sbit s1 = P0^4;					// ��ʼ
sbit s2 = P0^5;					// ��ȡ����
sbit s3 = P0^6;					// �Ϸ�
sbit s4 = P0^7;					// �·�
*/

uint xdata Save[102];
char save_sel; 					// ��ǰѡ���ҳ�� ÿҳ6������ ��17��
uchar save_all;					// �ܹ���¼�����ݸ���  
bit   flag_read;				// 1 ������ʾ��ʷ���� 0 ������ʾ��ʷ����

void Dispaly_ADC_Temp(disp)
{
	uchar temp_a, temp_b, temp_c, temp_d;
	temp_a = (uchar)(disp % 10000 / 1000);
	temp_b = (uchar)(disp % 1000 / 100);
	temp_c = (uchar)(disp % 100 / 10);
	temp_d = (uchar)(disp % 10);

	DisplayOneChar(10, 0, temp_a + 0x30);	
	DisplayOneChar(11, 0, temp_b + 0x30);
	DisplayOneChar(12, 0, temp_c + 0x30);	
	DisplayOneChar(13, 0, temp_d + 0x30);
}


void Voice_Reader_Number(unsigned int temp)
{
	uchar temp_a, temp_b, temp_c, temp_d;
	
	temp_a = temp % 10000 / 1000; 
	temp_b = temp % 1000 / 100; 
	temp_c = temp % 100 / 10; 
	temp_d = temp % 10;
	
	WTV020_SPI(0, 0x21); 			// ���ķλ���Ϊ	
	delay2s();

	// ��ǧλ
	if (temp_a > 0)
	{
		WTV020_SPI(0, temp_a);
		delay450ms();
		WTV020_SPI(0, 0x10);
		delay650ms();
	}
	else 
	{
	}

	// ����λ
	if (temp_b > 0)
	{
		WTV020_SPI(0, temp_b);
		delay450ms();
		WTV020_SPI(0, 0x11);
		delay650ms();
	}
	else if (temp_a > 0) 
	{
		WTV020_SPI(0, temp_b);
		delay650ms();
	}
	else
	{
	}

	// ��ʮλ
	if (temp_c > 0)
	{
		WTV020_SPI(0, temp_c);
		delay450ms();
		WTV020_SPI(0, 0x12);
		delay850ms();
	}
	else 
	{
	}

	// ����λ
	if (temp_d > 0)
	{
		WTV020_SPI(0, temp_d);
		delay850ms();		
	}
	else 
	{
	}

	// ����
	WTV020_SPI(0, 0x13);
	delay2s();

	if (temp < 2500)
		WTV020_SPI(0, 0x22);
	else if (temp < 5000)
		WTV020_SPI(0, 0x23);
	else
		WTV020_SPI(0, 0x24);
}


// ��ʼ����
void Begin()
{
//	uchar temp_a, temp_b, temp_c, temp_d;
	unsigned char i;
	unsigned long int adc_add;		// ����ֵ���
	bit flag;
	flag = 1;
	DisplayListChar(0, 0, " Please Wait... ");		
	DisplayListChar(0, 1, "                ");
	for (i = 0; i < 100; i ++)
	{
		Transform();
		adc_add += adc_cita;			// �洢��ʼֵ
	}
	zero = adc_add / 100;
	adc_add = 0;
	WTV020_SPI(0, 0x25);
	delay2s();
	DisplayListChar(0, 0, "  Please Start  "); 
	DisplayListChar(0, 1, "   measuring    "); 
	led = 0;
	// --  ��ʼ��������ɣ��ȴ������������  -- // 
	
	while (flag)
	{
		Transform();
 		
		if (adc_cita > (zero + MEASURE))
			flag = 0;
			
		if (s1 == 0)						// ����ȡ������
		{
			Delay_1ms(50);
			if (s1 == 0)
			{
				flag = 0;	
			}
		}			
	}
	flag = 1;
	DisplayListChar(0, 0, " Come On        ");
	DisplayListChar(0, 1, " VC Is:      ml ");

	// --  �����������  -- //		
	while (flag)
	{
		Transform();

		if (adc_cita <= (zero + 2))
			flag = 0;

		if (s1 == 0)						// ����ȡ������
		{
			Delay_1ms(50);
			if (s1 == 0)
			{
				flag = 0;	
			}
		}
		
		adc_add += (adc_cita - zero);
		
		DisplayOneChar(8, 1, adc_add / 20 % 10000 / 1000 + 0x30);
		DisplayOneChar(9, 1, adc_add / 20 % 1000 / 100 + 0x30);
		DisplayOneChar(10, 1, adc_add / 20 % 100 / 10 + 0x30);
		DisplayOneChar(11, 1, adc_add / 20 % 10 + 0x30);
		 
		Dispaly_ADC_Temp(adc_cita);	
	}
	led = 1;
	adc_add = adc_add / 20;
	DisplayListChar(0, 0, " Vital Capacity ");
	DisplayListChar(0, 1, "  Is:       ml  ");
	DisplayOneChar(7, 1, adc_add % 10000 / 1000 + 0x30);
	DisplayOneChar(8, 1, adc_add % 1000 / 100 + 0x30);
	DisplayOneChar(9, 1, adc_add % 100 / 10 + 0x30);
	DisplayOneChar(10, 1, adc_add % 10 + 0x30);
	// --  ������ɼ�¼����  -- //

	Save[save_all] = adc_add;
	save_all ++;
	if (save_all >= 102)
		save_all = 0;

	Voice_Reader_Number(adc_add);
	
}


void Display_Data()
{
	// ��ʾ���
	DisplayOneChar(0, 0, save_sel + 0x41);

	// ��ʾһ���еĵ�1������
	DisplayOneChar(2, 0, Save[save_sel*6] % 10000 / 1000 + 0x30);
	DisplayOneChar(3, 0, Save[save_sel*6] % 1000 / 100 + 0x30);
	DisplayOneChar(4, 0, Save[save_sel*6] % 100 / 10 + 0x30);
	DisplayOneChar(5, 0, Save[save_sel*6] % 10 + 0x30);
	
	// ��ʾһ���еĵ�2������
	DisplayOneChar(7, 0, Save[save_sel*6 + 1] % 10000 / 1000 + 0x30);
	DisplayOneChar(8, 0, Save[save_sel*6 + 1] % 1000 / 100 + 0x30);
	DisplayOneChar(9, 0, Save[save_sel*6 + 1] % 100 / 10 + 0x30);
	DisplayOneChar(10, 0, Save[save_sel*6 + 1] % 10 + 0x30);
	
	// ��ʾһ���еĵ�3������
	DisplayOneChar(12, 0, Save[save_sel*6 + 2] % 10000 / 1000 + 0x30);
	DisplayOneChar(13, 0, Save[save_sel*6 + 2] % 1000 / 100 + 0x30);
	DisplayOneChar(14, 0, Save[save_sel*6 + 2] % 100 / 10 + 0x30);
	DisplayOneChar(15, 0, Save[save_sel*6 + 2] % 10 + 0x30);
	
	// ��ʾһ���еĵ�4������
	DisplayOneChar(2, 1, Save[save_sel*6 + 3] % 10000 / 1000 + 0x30);
	DisplayOneChar(3, 1, Save[save_sel*6 + 3] % 1000 / 100 + 0x30);
	DisplayOneChar(4, 1, Save[save_sel*6 + 3] % 100 / 10 + 0x30);
	DisplayOneChar(5, 1, Save[save_sel*6 + 3] % 10 + 0x30);
	
	// ��ʾһ���еĵ�5������
	DisplayOneChar(7, 1, Save[save_sel*6 + 4] % 10000 / 1000 + 0x30);
	DisplayOneChar(8, 1, Save[save_sel*6 + 4] % 1000 / 100 + 0x30);
	DisplayOneChar(9, 1, Save[save_sel*6 + 4] % 100 / 10 + 0x30);
	DisplayOneChar(10, 1, Save[save_sel*6 + 4] % 10 + 0x30);
	
	// ��ʾһ���еĵ�6������
	DisplayOneChar(12, 1, Save[save_sel*6 + 5] % 10000 / 1000 + 0x30);
	DisplayOneChar(13, 1, Save[save_sel*6 + 5] % 1000 / 100 + 0x30);
	DisplayOneChar(14, 1, Save[save_sel*6 + 5] % 100 / 10 + 0x30);
	DisplayOneChar(15, 1, Save[save_sel*6 + 5] % 10 + 0x30);	
}


void Key_Scan()
{
	if (s1 == 0)				// ��ʼ
	{
		Delay_1ms(50);
		if (s1 == 0)
		{						
			while (! s1);
			Delay_1ms(50);
			flag_read = 0;
			Begin();
		}
	}

	if (s2 == 0)			// ��ȡ����
	{
		Delay_1ms(50);
		if (s2 == 0)
		{
			if (flag_read == 0)
			{
				flag_read = 1;
				DisplayListChar(0, 0, "                ");
				DisplayListChar(0, 1, "                ");
				Display_Data();							
			}
			else 
			{
				flag_read = 0;
				DisplayListChar(0, 0, " Welcome to Use ");
				DisplayListChar(0, 1, "   VC  Tester   ");
			}
			while (! s2);
		}
	}

	if (s3 == 0)			// �Ϸ�
	{
		Delay_1ms(50);
		if (s3 == 0)
		{
			if (flag_read)
			{
				save_sel ++;
				if (save_sel > 16)
					save_sel = 0;
	
				Display_Data();
			}
			else
			{
			}
			while (! s3);
		}
	}

	if (s4 == 0)			// �·�
	{
		Delay_1ms(50);
		if (s4 == 0)
		{
			if (flag_read)
			{
				save_sel --;
				if (save_sel < 0)
					save_sel = 16;
	
				Display_Data();
			}
			else
			{
			}
			while (! s4);
		}
	}
}