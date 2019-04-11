#include <stm32f407xx.h>


void clock_config(void);
void encoder_init(void);

uint8_t currstatea1=0,currstateb1=0,currstatea2=0,currstateb2=0;
int countercw1 =0,countercw2 = 0;


int main(void)
{
  clock_config();
	encoder_init();
	while(1)
	{
		countercw1 = TIM2->CNT;
		for(int i =0;i<=10000;i++);
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

void encoder_init()
{
	RCC -> APB1ENR |= (1<<0);
	RCC -> AHB1ENR |= (1<<0);
	GPIOA -> MODER |= (1<<1)|(1<<3);
	GPIOA -> OTYPER &= ~((1<<0)&(1<<1));
	GPIOA -> OSPEEDR |= (1<<0)|(1<<1)|(1<<2)|(1<<3);
  GPIOA -> PUPDR |= (1<<2)|(1<<0);
	
	GPIOA -> AFR[0] |= (1<<0)|(1<<4);
	TIM2 -> ARR = 0xFFFFFFFF;
	TIM2 -> SMCR |= (1<<0)|(1<<1);
	TIM2 -> CCMR1 |= (1<<0);
	TIM2 -> CCMR1 |= (1<<8);
	TIM2 -> CCER &= ~((1<<1)&(1<<3));
	TIM2 -> CR1 |= (1<<0);
}
