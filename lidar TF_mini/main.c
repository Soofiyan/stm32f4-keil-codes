#include <stm32f407xx.h>

int i=0,j=0;
uint8_t data;
uint8_t TFbuff[9] = {0};
long checksum  = 0 ;
int distance = 0,strength = 0;

void gpioinit(void);
void usartinit(void);
void configureledpins(void);
void delay_ms(int count);
int receive(void);
void get_values(void);
void clock_config(void);

int main()
{
	clock_config();
	configureledpins();
	gpioinit();
	usartinit();
	while(1)
	{
		/*get_values();*/
		if(distance >= 50)
		{
			GPIOD ->BSRR = (1<<12)|(1<<13)|(1<<14)|(1<<15);
		}
		else
		{
			GPIOD ->BSRR = (1<<28)|(1<<29)|(1<<30)|(1<<31);
		}
		/*GPIOD ->BSRR = (1<<12)|(1<<13)|(1<<14)|(1<<15);
		for(int y = 0;y<=100000;y++)
		{
		}
		GPIOD ->BSRR = (1<<28)|(1<<29)|(1<<30)|(1<<31);
		for(int y = 0;y<=100000;y++)
		{
		}*/
	}
}
void gpioinit()
{
	RCC -> APB2ENR |= (1<<4);
	RCC -> AHB1ENR |= (1<<0);
	GPIOA -> MODER |= (1<<21);
	GPIOA -> OSPEEDR |= (1<<20);
	GPIOA -> PUPDR |= (1<<21);
	GPIOA -> AFR[1] |= (1<<8)|(1<<9)|(1<<10);
}
void clock_config(void)
{
	RCC -> CR |= (1<<16);
	RCC -> PLLCFGR &= ~((1<<16)&(1<<17));
	RCC -> PLLCFGR &= ~((1<<0)&(1<<1)&(1<<2)&(1<<3)&(1<<4)&(1<<5));
	RCC -> PLLCFGR |= (1<<3);
	RCC -> PLLCFGR &= ~((1<<6)&(1<<7)&(1<<8)&(1<<9)&(1<<10)&(1<<11)&(1<<12)&(1<<13)&(1<<14));
	RCC -> PLLCFGR |= (1<<13);
	RCC -> PLLCFGR |= (1<<22);
	RCC -> PLLCFGR &= ~((1<<24)&(1<<25)&(1<<26)&(1<<27));
	RCC -> PLLCFGR |= (1<<26);
	RCC -> CFGR &= ~((1<<0)&(1<<1));
	RCC -> CFGR &= ~((1<<4)&(1<<5)&(1<<6)&(1<<7));
	RCC -> CFGR |= (1<<7);
	RCC -> CFGR &= ~((1<<10)&(1<<11)&(1<<12));
	RCC -> CFGR &= ~((1<<15)&(1<<14)&(1<<13));
	RCC -> CFGR |= (1<<15);
	RCC -> CFGR |= (1<<12);
	RCC -> CR |= (1<<24);
	while(!(RCC -> CR & (1<<25)));
	RCC -> CFGR |= (1<<1);
	while(!(RCC -> CFGR & 0x00000008));
	RCC -> APB2ENR |= (1<<14);
}
void usartinit()
{
	USART1 -> CR1 |= (1<<13);
	USART1 -> BRR |= 0x045;                     //17.361 fraction 3 mantissa 104
	USART1 -> CR1 |= (1<<2)|(1<<5);
	NVIC_EnableIRQ(USART1_IRQn);
}
void configureledpins()
{
	RCC -> AHB1ENR |= (1<<3);
	GPIOD ->MODER |= (1<<24)|(1<<26)|(1<<28)|(1<<30);
	GPIOD ->PUPDR |= (1<<25)|(1<<27)|(1<<29)|(1<<31);
}
void delay_ms(int count)
{
	int i = 0;
	for(i = 0;i<count*4000;i++)
	{
	}
}

int receive()
{
	while((USART1 -> SR & (1<<5)) == 0);
	data = USART1 -> DR;
	return data;
}

void get_values()
{
	TFbuff[0] = receive();
	checksum += TFbuff[0];
	if(	TFbuff[0] == 'Y')
 	{
		TFbuff[1] = receive();
    checksum += TFbuff[1];
    if(TFbuff[1] == 'Y')
		{
			for(i = 2;i < 8;i++)
			{
				TFbuff[i] = receive();
        checksum += TFbuff[i];
      }
      TFbuff[8] = receive();
      if(checksum == TFbuff[8])
			{
				distance = TFbuff[2]+TFbuff[3]*256;
        strength = TFbuff[4]+TFbuff[5]*256;
			}
			else
			{
        checksum  = 0;
      }
    }
		else
		{
      checksum  = 0;
		}
	}
	else
	{
		checksum  = 0;
	}
}

void USART1_IRQHandler()
{
	//TFbuff[0] = receive();
	
	//GPIOD ->ODR = (1<<12)|(1<<13)|(1<<14)|(1<<15);
	switch(i)
	{
		case 0:
			TFbuff[0] = receive();
			checksum += TFbuff[0];
			i++;
			break;
		case 1:
			if(TFbuff[0] == 'Y')
			{
				i++;
				TFbuff[1] = receive();
				checksum += TFbuff[1];
			}
			else 
			{
				checksum = 0;
				i = 0;
			}
			break;
		case 2:
			if(TFbuff[1] == 'Y')
			{	
				TFbuff[i] = receive();
				checksum += TFbuff[i];
				i++;
			}
			else
			{
				checksum = 0;
				i = 0;
			}
			break;
		case 3:
			TFbuff[i] = receive();
      checksum += TFbuff[i];
			i++;
			break;
		case 4:
			TFbuff[i] = receive();
      checksum += TFbuff[i];
			i++;
			break;
		case 5:
			TFbuff[i] = receive();
      checksum += TFbuff[i];
			i++;
			break;
		case 6:
			TFbuff[i] = receive();
      checksum += TFbuff[i];
			i++;
			break;
		case 7:
			TFbuff[i] = receive();
      checksum += TFbuff[i];
			i++;
			break;
		case 8:
			TFbuff[8] = receive();
      checksum &= 0xFF;
		if(checksum == TFbuff[8])
			{
				distance = TFbuff[2]+TFbuff[3]*256;
				strength = TFbuff[4]+TFbuff[5]*256;
			}
			else
			{
				checksum = 0;
			}
			i = 0;
			break;
		default:
			break;
	}
}


