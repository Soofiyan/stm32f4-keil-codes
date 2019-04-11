/*#include <stm32f407xx.h>
int i=0,j=0;

void gpioinit();
void usartinit();


int main()
{
	
	
		gpioinit();
		usartinit();
		
	while(1)
	{
		for(i =0;i<=100;i++)
		{
			while((USART1 -> SR & (1<<7)) == 0)
		{}
	  USART1 -> DR = i;
			for(j = 0;j<=10000;j++);
	  while((USART1 -> SR & (1<<6))== 0)
	  {}
	  USART1 -> SR = 0x00C0;
	}
}
}
void gpioinit()
{
	RCC -> APB2ENR |= (1<<4);
	RCC -> AHB1ENR |= (1<<1);
	GPIOB -> MODER |= (1<<13);
	GPIOB -> OSPEEDR |= (1<<12);
	GPIOB -> PUPDR |= (1<<13);
	GPIOB -> AFR[0] |= (1<<24)|(1<<25)|(1<<26);
}
void usartinit()
{
	USART1 -> CR1 |= (1<<13);
	USART1 -> BRR |= (1<<0)|(1<<1)|(1<<7)|(1<<9)|(1<<10);                     //104.1875 fraction 3 mantissa 104
	USART1 -> CR1 |= (1<<3);
}*/
/*
1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
2. Program the M bit in USART_CR1 to define the word length.
3. Program the number of stop bits in USART_CR2.
4. Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take
place. Configure the DMA register as explained in multibuffer communication.
5. Select the desired baud rate using the USART_BRR register.
6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
7. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
for each data to be transmitted in case of single buffer.
8. After writing the last data into the USART_DR register, wait until TC=1. This indicates
that the transmission of the last frame is complete. This is required for instance when
the USART is disabled or enters the Halt mode to avoid corrupting the last
transmission.*/

#include <stm32f407xx.h>

uint8_t i=0,j=0;

void gpioinit();
void usartinit();
void configureledpins();
void delay_ms(int count);

int main()
{
		configureledpins();
	gpioinit();
		usartinit();
	while(1)
	{
		USART1 -> CR1 |= (1<<2);
		while((USART1 -> SR & (1<<9)) == 0)
		{}
		while((USART1 -> SR & (1<<5)) == 0)
		{}
	  i = (USART1 -> DR);
			if(USART1->DR == 0x0031)
			{
				GPIOD ->ODR |= (1<<12)|(1<<13)|(1<<14)|(1<<15);
			}
			else
			{
				GPIOD ->ODR &= ~((1<<12)&(1<<13)&(1<<14)&(1<<15));
			}
			USART1 -> SR = 0x00C0;
	}
}
void gpioinit()
{
	RCC -> APB2ENR |= (1<<4);
	RCC -> AHB1ENR |= (1<<1);
	GPIOB -> MODER |= (1<<15);
	GPIOB -> OSPEEDR |= (1<<14);
	GPIOB -> PUPDR |= (1<<15);
	GPIOB -> AFR[0] |= (1<<28)|(1<<29)|(1<<30);
}
void usartinit()
{
	USART1 -> CR1 |= (1<<13);
	USART1 -> BRR |= (1<<0)|(1<<1)|(1<<7)|(1<<9)|(1<<10);                     //104.1875 fraction 3 mantissa 104
	USART1 -> CR1 |= (1<<2);
	USART1 -> CR3 |= (1<<8)|(1<<9)|(1<<0);
	USART1 -> CR1 &= ~(1<<14);
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