

#include <stm32f4xx.h>

void clock_config(void);
void configureledpins(void);
void delay_ms(int count);

int main(void)
{
	//clock_config();
	configureledpins();
	while(1)
	{
		GPIOD ->ODR |= (1<<12)|(1<<13)|(1<<14)|(1<<15);
		delay_ms(500);
		GPIOD ->ODR &= ~((1<<12)|(1<<13)|(1<<14)|(1<<15));
		delay_ms(500);
	}
}

void clock_config(void) {
  RCC->CR |= (1 << 16);
  while (!(RCC->CR & (1 << 17)))
    ;
  RCC->CFGR |= (1 << 0);
  RCC->CR &= ~((1 << 24));
  RCC->PLLCFGR &= ~((1 << 16) & (1 << 17));
  RCC->PLLCFGR &= ~((1 << 0) & (1 << 1) & (1 << 2) & (1 << 3) & (1 << 4) & (1 << 5));
  RCC->PLLCFGR |= (1 << 3);
  RCC->PLLCFGR &= ~((1 << 6) & (1 << 7) & (1 << 8) & (1 << 9) & (1 << 10) & (1 << 11) & (1 << 12) & (1 << 13) & (1 << 14));
  RCC->PLLCFGR |= (1 << 13);
  RCC->PLLCFGR &= ~((1 << 24) & (1 << 25) & (1 << 26) & (1 << 27));
  RCC->PLLCFGR |= (1 << 26);
  RCC->CFGR |= (1 << 7);
  RCC->CR |= (1 << 24);
  while (!(RCC->CR & (1 << 25)))
    ;
  RCC->CFGR |= (1 << 1);
  RCC->CFGR &= ~(1 << 0);
  while (!(RCC->CFGR & (1 << 3)))
    ;
  RCC->PLLCFGR |= (1 << 22);
}

void configureledpins(void)
{
	RCC -> AHB1ENR |= (1<<3);
	GPIOD ->MODER |= (1<<24)|(1<<26)|(1<<28)|(1<<30);
	GPIOD ->PUPDR |= (1<<31)|(1<<25)|(1<<27)|(1<<29);
}

void delay_ms(int count)
{
	int i = 0;
	for(i = 0;i<=count;i++)
        {
        
        }
}