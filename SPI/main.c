#include <stm32f4xx.h>
uint8_t i = 100;
int j = 0;
int rec_data = 0;
uint8_t data = 203;
void afio_config(void);
void spi_init(void);
int transmit(uint8_t data);
void disable_spi(void);
void enable_spi(void);

int main(void)
{
	afio_config();
	spi_init();
//	NVIC_EnableIRQ(SPI2_IRQn);
	while(1)
	{
		transmit(data);
	//	for(j=0;j<=15000;j++)
		//{}
		//transmit(0x54);
	//	for(j=0;j<=15000;j++)
		//{}
		//rec_data = transmit(0);
		//disable_spi();
	}
}
void afio_config()
{/*
	When configured in master mode with
NSS configured as an input (MSTR=1 and SSOE=0) and if NSS is pulled low, the SPI
enters the master mode fault state: the MSTR bit is automatically cleared and the
device is configured in slave mode
	*/
	RCC -> AHB1ENR |= (1<<1)|(1<<2);
	RCC -> APB1ENR |= (1<<14);
	GPIOB -> MODER |= (1<<21)|(1<<24);
	GPIOC -> MODER |= (1<<7)|(1<<5);
	GPIOB ->OTYPER &= ~((1<<10));
	GPIOB -> OSPEEDR |= (1<<24)|(1<<20);
	GPIOC -> OSPEEDR |= (1<<4)|(1<<6);
	GPIOB -> PUPDR |= (1<<25)|(1<<21);
	GPIOC -> PUPDR |= (1<<4)|(1<<6);
	GPIOC -> AFR[0] |= (1<<14)|(1<<12)|(1<<10)|(1<<8);
	GPIOB -> AFR[1] |= (1<<10)|(1<<8);
        GPIOC -> ODR &= ~(1<<3);
        GPIOB -> ODR &= ~(1<<10);
	GPIOB ->ODR |= (1<<12);
}

void spi_init()
{
//	disable_spi();
	SPI2 ->CR1 |= (1<<3);
	SPI2 ->CR1 |= (1<<15)|(1<<14);
//	SPI2 ->CR1 |= (1<<9)|(1<<8);
//	SPI2 ->CR2 |= (1<<7);
        SPI2 ->CR2 |= (1<<2);
	SPI2 ->CR1 |= (1<<2);
	SPI2 ->CR1 |= (1<<6);
//        SPI2->CR1 |= (1<<7);
//	enable_spi();
}
int transmit(uint8_t data)
{
	//spi_init();
	//if(((SPI2 -> SR) & (0x0080)) == 0x0080)
	//{
        enable_spi();
	while((((SPI2 -> SR) & (0x0002)) == 0x0000))
	{
	}
	SPI2 ->DR = data;
	//if(((SPI2 -> SR) & (0x0001)) != 0x0001)
	//{
	//	int y = SPI2 ->DR;
	//}
      while((((SPI2 -> SR) & (0x0080)) == 0x0080))
	{}
	disable_spi();
	//}
	return 1;
}
void disable_spi()
{
	GPIOB ->ODR |= (1<<12);
}
void enable_spi()
{
	GPIOB ->ODR &= ~(1<<12);
}
//void SPI2_IRQHandler()
//{
//    while((((SPI2 -> SR) & (0x0002)) == 0x0000))
//    {}
//    SPI2 ->DR = data;
//}