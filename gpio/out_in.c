#include <stm32f4xx.h>

void configureledpins();
void delay_ms(int count);
void configurebuttons();
	

int main()
{
	configureledpins();
	configurebuttons();
	while(1)
	{
		if((GPIOA->IDR & (1<<0)) == 1)
		{
			GPIOD ->ODR |= (1<<12)|(1<<13)|(1<<14)|(1<<15);
		}
		else
		{//delay_ms(1000);
		GPIOD ->ODR &= ~((1<<12)|(1<<13)|(1<<14)|(1<<15));
		//delay_ms(1000);
	  }
  }
}
void configureledpins()
{
	RCC -> AHB1ENR |= (1<<3);
	GPIOD ->MODER |= (1<<24)|(1<<26)|(1<<28)|(1<<30);
	GPIOD ->PUPDR |= (1<<25)|(1<<27)|(1<<29)|(1<<31);
}
void configurebuttons()
{
	RCC ->AHB1ENR |= (1<<0);
	GPIOA ->PUPDR |= (1<<1);
}
void delay_ms(int count)
{
	int i = 0;
	for(i = 0;i<count*4000;i++)
	{
	}
}