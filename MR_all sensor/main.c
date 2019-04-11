#include <stm32f407xx.h>

int i=0,j=0;
uint8_t data;
uint8_t TFbuff[9] = {0};
long checksum  = 0 ;
int distance = 0;//,strength = 0;
int yaw_angle = 0;

void gpioinit(void);
void usartinit1(void);
void usartinit2(void);
void usartinit3(void);
void configureledpins(void);
void delay_ms(int count);
int receive(void);
void get_values(void);
void clock_config(void);
void usart2_send(int pwm);
void encoder_init1(void);
void encoder_init2(void);

int main()
{
	clock_config();
	configureledpins();
	gpioinit();
	usartinit1();
	usartinit2();
	usartinit3();
	encoder_init1();
	encoder_init2();
	
	while(1)
	{
		
	}
}

void gpioinit()
{
	//usart1 for lidar(rx) PA9 PA10 TX RX
	RCC -> APB2ENR |= (1<<4);			//usart1
	RCC -> AHB1ENR |= (1<<0);			//gpioaen
	GPIOA -> MODER |= (1<<21);		//afio
	GPIOA -> OSPEEDR |= (1<<20);	//medium speed
	GPIOA -> PUPDR |= (1<<21);		//pull down
	GPIOA -> AFR[1] |= (1<<8)|(1<<9)|(1<<10);		//usart1 afio
	//usart2 for imu(rx) PA2 PA3 TX RX
	RCC -> APB1ENR |= (1<<17);		//usart2
	GPIOA -> MODER |= (1<<7);			//afio
	GPIOA -> OSPEEDR |= (1<<6);		//medium speed
	GPIOA -> PUPDR |= (1<<7);			//pull down
	GPIOA -> AFR[0] |= (1<<12)|(1<<13)|(1<<14);		//USART2 afio
	//usart3 for avr(tx) PA5 PB3 TX RX
	RCC ->AHB1ENR |= (1<<1);			//gpioben
	RCC -> APB1ENR |= (1<<8);			//usart3
	GPIOB -> MODER |= (1<<21);			//afio
	GPIOB -> OSPEEDR |= (1<<20);		//medium speed
	GPIOB -> PUPDR |= (1<<21);			//pull down
	GPIOB -> AFR[1] |= (1<<8)|(1<<9)|(1<<10);		//USART2 afio
	//drive encoder1 PA5 PB3 CH1 CH2
	RCC -> APB1ENR |= (1<<0);				//timer2 
	GPIOA -> MODER |= (1<<1);      //afio
	GPIOB -> MODER |= (1<<7);			 //afio
	GPIOA -> OTYPER &= ~((1<<5));	//push pull
	GPIOB -> OTYPER &= ~((1<<3));	//push pull
	GPIOA -> OSPEEDR |= (1<<10)|(1<<11);		//very high speed
	GPIOB -> OSPEEDR |= (1<<6)|(1<<7);  		//very high speed
  GPIOA -> PUPDR |= (1<<10);			//pull up
  GPIOB -> PUPDR |= (1<<6);			//pull up
	GPIOA -> AFR[0] |= (1<<20);			//tim2
	GPIOB -> AFR[0] |= (1<<12);			//tim2
	//drive encoder2 PA0 PA1 CH1 CH2
	RCC -> APB1ENR |= (1<<3);				//timer5 
	GPIOA -> MODER |= (1<<1)|(1<<3);		//afio
	GPIOA -> OTYPER &= ~((1<<0)&(1<<1));		//afio
	GPIOA -> OSPEEDR |= (1<<0)|(1<<1)|(1<<2)|(1<<3);			//high speed
  GPIOA -> PUPDR |= (1<<2)|(1<<0);				//pull up
	GPIOA -> AFR[0] |= (1<<0)|(1<<4);				//tim5
}

void encoder_init1(void)								//timer2  PA5 PB3 CH1 CH2
{
	TIM2 -> ARR = 0xFFFFFFFF;
	TIM2 -> SMCR |= (1<<0)|(1<<1);
	TIM2 -> CCMR1 |= (1<<0);
	TIM2 -> CCMR1 |= (1<<8);
	TIM2 -> CCER &= ~((1<<1)&(1<<3));
	TIM2 -> CR1 |= (1<<0);
}

void encoder_init2(void)								//timer5  A0 A1 CH1 CH2
{
	TIM5 -> ARR = 0xFFFFFFFF;       
	TIM5 -> SMCR |= (1<<0)|(1<<1);
	TIM5 -> CCMR1 |= (1<<0);
	TIM5 -> CCMR1 |= (1<<8);
	TIM5 -> CCER &= ~((1<<1)&(1<<3));
	TIM5 -> CR1 |= (1<<0);
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

void usartinit1()
{
	USART1 -> CR1 |= (1<<13);										//A9 A10 TX RX
	USART1 -> BRR |= 0x045;                     //17.361 fraction 3 mantissa 104
	USART1 -> CR1 |= (1<<2)|(1<<5);
	NVIC_EnableIRQ(USART1_IRQn);
}

void usartinit2()
{
	USART2 -> CR1 |= (1<<13);										//A2 A3 TX RX
	USART2 -> BRR |= 0x045;                     //17.361 fraction 3 mantissa 104
	USART2 -> CR1 |= (1<<2)|(1<<5);
	NVIC_EnableIRQ(USART2_IRQn);
}

void usartinit3()
{																							
	USART3 -> CR1 |= (1<<13);										//B10 B11 TX RX
	USART3 -> BRR |= 0x045;                     //17.361 fraction 3 mantissa 104
	USART3 -> CR1 |= (1<<3);
}

void usart2_send(int pwm)
{
	while((USART2 -> SR & (1<<7)) == 0)
	{}
	USART2 -> DR = pwm;
	while((USART2 -> SR & (1<<6))== 0)
	{}
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
//	while((USART1 -> SR & (1<<5)) == 0);
	data = USART1 -> DR;
	return data;
}

void USART2_IRQHandler()			//imu
{
	yaw_angle = receive();
}

void USART1_IRQHandler()//lidar
{
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
			//	strength = TFbuff[4]+TFbuff[5]*256;
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


