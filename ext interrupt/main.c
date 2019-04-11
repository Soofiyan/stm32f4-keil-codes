/*#include <stm32f407xx.h>

void exti_setup();
void configureledpins();
void delay_ms(int count);

int i = 0;

int main()
{
	//All ports have external interrupt capability. To use external interrupt lines, the port must be
    //configured in input mode
	exti_setup();
  configureledpins();
	while(1)
	{
	
	}
}

void exti_setup()
{
	RCC -> AHB1ENR |= (1<<0);
	RCC -> APB2ENR |= (1<<14);
	GPIOA -> MODER &= ~((1<<0)&(1<<1));
  GPIOA ->OSPEEDR |= (1<<0)|(1<<1);
	GPIOA -> PUPDR |= (1<<1);
	SYSCFG -> EXTICR[0] &= ~((1<<0)&(1<<1)&(1<<2)&(1<<3));
	EXTI -> IMR |= (1<<0);
	EXTI -> RTSR |= (1<<0);
	EXTI -> FTSR |= (1<<0);
	NVIC_EnableIRQ(EXTI0_IRQn);
}
void EXTI0_IRQHandler()
{   
		EXTI -> PR |= (1<<0);
	  i ++;
	if((((GPIOA -> IDR) & (1<<0)) == 1))
	{
		GPIOD ->ODR |= (1<<12)|(1<<13)|(1<<14)|(1<<15);
	}
	else
	{
		GPIOD ->ODR &= ~((1<<12)|(1<<13)|(1<<14)|(1<<15));
	}
		//delay_ms(100);
}
void delay_ms(int count)
{
	int i = 0;
	for(i = 0;i<count*4000;i++)
	{
	}
}
void configureledpins()
{
	RCC -> AHB1ENR |= (1<<3);
	GPIOD ->MODER |= (1<<24)|(1<<26)|(1<<28)|(1<<30);
	GPIOD ->PUPDR |= (1<<25)|(1<<27)|(1<<29)|(1<<31);
}*/
#include <stm32f407xx.h>


void clock_config(void);
void drive_enc_init(void);

uint8_t currstatea1=0,currstateb1=0,currstatea2=0,currstateb2=0;
int countercw1 =0,countercw2 = 0;


int main(void)
{
  clock_config();
	drive_enc_init();
	while(1)
	{
		
	}
}

void clock_config(void)
{
	RCC -> CR |= (1<<16);
	RCC -> PLLCFGR &= ~((1<<16)&(1<<17));
	RCC -> PLLCFGR &= ~((1<<0)&(1<<1)&(1<<2)&(1<<3)&(1<<4)&(1<<5));
	RCC -> PLLCFGR |= (1<<4);
	RCC -> PLLCFGR &= ~((1<<6)&(1<<7)&(1<<8)&(1<<9)&(1<<10)&(1<<11)&(1<<12)&(1<<13)&(1<<14));
	RCC -> PLLCFGR |= (1<<9)|(1<<12)|(1<<13);
	RCC -> PLLCFGR |= (1<<22);
	RCC -> PLLCFGR &= ~((1<<24)&(1<<25)&(1<<26)&(1<<27));
	RCC -> PLLCFGR |= (1<<26);
	RCC -> CFGR &= ~((1<<0)&(1<<1));
	RCC -> CFGR &= ~((1<<4)&(1<<5)&(1<<6)&(1<<7));
	RCC -> CFGR |= (1<<7);
	RCC -> CFGR &= ~((1<<10)&(1<<11)&(1<<12));
	RCC -> CFGR |= (1<<12);
	RCC -> CR |= (1<<24);
	while(!(RCC -> CR & (1<<25)));
	RCC -> CFGR |= (1<<1);
	while(!(RCC -> CFGR & 0x00000008));
}

void drive_enc_init(void)
{
	RCC -> AHB1ENR |= (1<<2);
	RCC -> APB2ENR |= (1<<14);
	GPIOC -> MODER &= ~((1<<0)&(1<<1)&(1<<2)&(1<<3)&(1<<4)&(1<<5)&(1<<6)&(1<<7));
	GPIOC -> OSPEEDR |= (1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7);
	GPIOC -> PUPDR |= (1<<0)|(1<<2)|(1<<4)|(1<<6);
	SYSCFG -> EXTICR[0] |= (1<<1)|(1<<5)|(1<<9)|(1<<13);
	EXTI -> IMR |= (1<<0)|(1<<2)|(1<<3)|(1<<1);
	EXTI -> RTSR |= (1<<0)|(1<<2)|(1<<3)|(1<<1);
	EXTI -> FTSR |= (1<<0)|(1<<1)|(1<<2)|(1<<3);
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
}

void EXTI0_IRQHandler()
{   
		EXTI -> PR |= (1<<0);
		if(((GPIOC->IDR)& (1<<0)) == 1)
		{
			currstateb1 = 1;
			if(currstatea1 == 0)
			{
				countercw1 ++;
			}
			else
			{
				countercw1 --;
			}
		}
		else
		{
			currstateb1 = 0;
			if(currstatea1 == 0)
			{
				countercw1 --;
			}
			else
			{
				countercw1 ++;
			}
		}
}
void EXTI2_IRQHandler()
{   
		EXTI -> PR |= (1<<2);
		if(((GPIOC->IDR)& (1<<2)) == 1)
		{
			currstateb2 = 1;
			if(currstatea2 == 0)
			{
				countercw2 ++;
			}
			else
			{
				countercw2 --;
			}
		}
		else
		{
			currstateb2 = 0;
			if(currstatea2 == 0)
			{
				countercw2 --;
			}
			else
			{
				countercw2 ++;
			}
		}
}
void EXTI1_IRQHandler()
{ 
    EXTI->PR |= (1<<1);    // keeping it to 1 so that it clears the trigger
		if(((GPIOC->IDR)& (1<<11)) == 1)
		{
			currstatea1 = 1;
			if(currstateb1 == 0)
			{
				countercw1 --;
			}
			else
			{
				countercw1 ++;
			}
		}
		else
		{
			currstatea1 = 0;
			if(currstateb1 == 0)
			{
				countercw1 ++;
			}
			else
			{
				countercw1 --;
			}
		}
}
void EXTI3_IRQHandler()
{
	  EXTI->PR |= (1<<3);    // keeping it to 1 so that it clears the trigger
		if(((GPIOC->IDR)& (1<<3)) == 1)
		{
			currstatea2 = 1;
			if(currstateb2 == 0)
			{
				countercw2 --;
			}
			else
			{
				countercw2 ++;
			}
		}
		else
		{
			currstatea2 = 0;
			if(currstateb2 == 0)
			{
				countercw2 ++;
			}
			else
			{
				countercw2 --;
			}
		}
}
