//global interrupt
//APB1ENR is 16MHz

/*The maximum allowed frequency of the high-speed APB2 domain is 84 MHz. The
maximum allowed frequency of the low-speed APB1 domain is 42 MHz*/
/*but as default HSI is on thus 84MHz is 16MHz*/



/*#include <stm32f407xx.h>

void configuregpio();
void configureledpins();
void delay_ms(int count);
int i = 0;

int main()
{
  configuregpio();
	configureledpins();
	while(1)
	{
		
	}
}
void configuregpio()
{
	RCC ->APB1ENR = (1<<0);
	NVIC_EnableIRQ(TIM2_IRQn);
	TIM2 ->PSC = 2;
	TIM2 -> ARR = 80000;
	TIM2 -> DIER |= (1<<0);
	TIM2 -> CR1 |= (1<<0);
}
void TIM2_IRQHandler()
{
	TIM2 -> SR &=~(1<<0);
	i++;
	if(i == 1000)
	{
		GPIOD ->ODR |= (1<<12)|(1<<13)|(1<<14)|(1<<15);
		delay_ms(100);
	}
	else if(i>=2000)
	{
		GPIOD ->ODR &= ~((1<<12)|(1<<13)|(1<<14)|(1<<15));
		delay_ms(100);
		i = 0;
	}
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
}*/
//update interrupt
//APB2ENR is 8 MHz
#include <stm32f407xx.h>

void configuregpio();
void configureledpins();
void delay_ms(int count);
int i = 0;

int main()
{
  configuregpio();
	configureledpins();
	while(1)
	{
		
	}
}
void configuregpio()
{
	RCC ->APB2ENR = (1<<0);
	NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
	TIM1 ->PSC = 0;
	TIM1 -> ARR = 80000;
	TIM1 -> DIER |= (1<<0)|(1<<8);
	TIM1 -> CR1 |= (1<<0);
}
void TIM1_UP_TIM10_IRQHandler()
{
	TIM1 -> SR &= ~(1<<0);
	i++;
	if(i == 1000)
	{
		GPIOD ->ODR |= (1<<12)|(1<<13)|(1<<14)|(1<<15);
	}
	else if(i>=2000)
	{
		GPIOD ->ODR &= ~((1<<12)|(1<<13)|(1<<14)|(1<<15));
		i = 0;
	}
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