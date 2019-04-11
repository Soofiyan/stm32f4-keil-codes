#include <stm32f407xx.h>

void configuretimer();
void configurepwm();
void delay_ms(int count);

int i = 0;
int main(void)
{
	configuretimer();
	configurepwm();
	while(1)
	{
		for(i =0 ;i<=50000;i+=100)
		{
			TIM4 -> CCR1 = i;
			delay_ms(20);
		}
	}
}

void configurepwm()
{
	TIM4 -> CR1 = (1<<0)|(1<<7);
	TIM4 -> EGR = (1<<0);
	TIM4 -> PSC = 0;
	TIM4 -> ARR = 50000;
	TIM4 -> CCMR1 = (1<<5)|(1<<6);
	TIM4 -> CCER = (1<<0);
}
void configuretimer()
{
	RCC ->AHB1ENR = (1<<3);
	RCC ->APB1ENR = (1<<2);
	GPIOD -> MODER = (1<<25);
	GPIOD -> PUPDR |= (1<<25);
	GPIOD ->AFR[1] = 0x00020000;
}
void delay_ms(int count)
{
	int i = 0;
	for(i = 0;i<count*400;i++)
	{
	}
}