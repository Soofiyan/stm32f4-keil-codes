
/*
Since some SPI1 and SPI3/I2S3 pins may be mapped onto
some pins used by the JTAG interface (SPI1_NSS onto JTDI,
SPI3_NSS/I2S3_WS onto JTDI and SPI3_SCK/I2S3_CK onto
JTDO), you may either:
– map SPI/I2S onto other pins
– disable the JTAG and use the SWD interface prior to
configuring the pins listed as SPI I/Os (when debugging the
application) or
– disable both JTAG/SWD interfaces (for standalone
applications).
For more information on the configuration of the JTAG/SWD
interface pins, please refer to Section 8.3.2: I/O pin
multiplexer and mapping.

#include <stm32f4xx.h>
uint8_t i = 26;

void afio_config(void);
void spi_init(void);
void receive(void);
void transmit(void);

int main(void)
{
	spi_init();
	afio_config();	
	while(1)
	{
		transmit();
	}
}
void afio_config()
{*/
/*
	When configured in master mode with
NSS configured as an input (MSTR=1 and SSOE=0) and if NSS is pulled low, the SPI
enters the master mode fault state: the MSTR bit is automatically cleared and the
device is configured in slave mode
	*/
/*	RCC -> AHB1ENR |= (1<<1)|(1<<2);
	RCC -> APB1ENR |= (1<<14);
	GPIOB -> MODER |= (1<<21)|(1<<24);
	GPIOC -> MODER |= (1<<7)|(1<<5);
	GPIOC -> OSPEEDR |= (1<<5)|(1<<7);
	GPIOB -> OSPEEDR |= (1<<25)|(1<<21);
	//GPIOB -> OTYPER |= (1<<10);
	GPIOB -> PUPDR |= (1<<20)|(1<<25);
	GPIOC -> PUPDR |= (1<<4)|(1<<6);
	GPIOC -> AFR[0] |= (1<<14)|(1<<12)|(1<<10)|(1<<8);
	GPIOB -> AFR[1] |= (1<<10)|(1<<8);
	GPIOB -> ODR |= (1<<12);
}

void spi_init()
{
	SPI2 ->CR1 |= (1<<6)|(1<<2)|(1<<15)|(1<<14)|(1<<4)|(1<<5);
	SPI2 ->CR2 |= (1<<2);
	//SPI2 ->CR1 |= (1<<9);
}
void transmit()
{
	GPIOB -> ODR &= ~(1<<12);
	SPI2 -> DR = 0x55;
	while(((SPI2 -> SR) & (1<<1)) == 0)
	{}
	while(((SPI2 -> SR) & (1<<0)) == 1)
	{}	
	while(((SPI2 -> SR) & (1<<7)) == 1)
	{}
	GPIOB -> ODR |= (1<<12);
	//SPI2 -> CR1 |= (1<<12);
	//int y = (SPI2 -> DR);
}*/
/*#include <stm32f4xx_hal.h>
 void SysTick_Handler(void);
#ifdef __cplusplus
extern "C"
#endif
void SysTick_Handler(void)
{
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}
 
int main(void)
{
    HAL_Init();
 
    __GPIOA_CLK_ENABLE();
    __SPI1_CLK_ENABLE();
    
    static SPI_HandleTypeDef spi = { .Instance = SPI1 };
    spi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
    spi.Init.Direction = SPI_DIRECTION_2LINES;
    spi.Init.CLKPhase = SPI_PHASE_2EDGE;
    spi.Init.CLKPolarity = SPI_POLARITY_LOW;
    spi.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLED;
    spi.Init.DataSize = SPI_DATASIZE_8BIT;
    spi.Init.FirstBit = SPI_FIRSTBIT_LSB;
    spi.Init.NSS = SPI_NSS_HARD_OUTPUT;
    spi.Init.TIMode = SPI_TIMODE_DISABLED;
    spi.Init.Mode = SPI_MODE_MASTER; 
    
    GPIO_InitTypeDef  GPIO_InitStruct;
  
    GPIO_InitStruct.Pin       = GPIO_PIN_5 | GPIO_PIN_7;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
 
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
 
    GPIO_InitStruct.Pin  = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); 
    
    GPIO_InitStruct.Pin  = GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); 
    
    for (int i = 0;; i++)
    {
        int result = 0;
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
        HAL_SPI_TransmitReceive(&spi, (uint8_t *)&i, (uint8_t*)&result, sizeof(i), HAL_MAX_DELAY);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
        HAL_Delay(10);
    }
}
*/
#include <stm32f4xx.h>
uint8_t i = 100;
int j = 0;
int rec_data = 0;
uint8_t data = 82;
void afio_config(void);
void spi_init(void);
int transmit(uint8_t data);
void disable_spi(void);
void enable_spi(void);

int main(void)
{
	afio_config();
	spi_init();
	NVIC_EnableIRQ(SPI2_IRQn);
	while(1)
	{
		//transmit(data);
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
	GPIOB ->ODR &= ~(1<<12);
}

void spi_init()
{
	//disable_spi();
	SPI2 ->CR1 |= (1<<4)|(1<<5);
	SPI2 ->CR1 |= (1<<15)|(1<<14);
	SPI2 ->CR1 |= (1<<9)|(1<<8);
	SPI2 ->CR2 |= (1<<7);
	SPI2 ->CR1 |= (1<<2);
	SPI2 ->CR1 |= (1<<6);
	//enable_spi();
}
int transmit(uint8_t data)
{
	//spi_init();
	//if(((SPI2 -> SR) & (0x0080)) == 0x0080)
	//{
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
	//	disable_spi();
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
void SPI2_IRQHandler()
{
	while((((SPI2 -> SR) & (0x0002)) == 0x0000))
	{}
	SPI2 ->DR = data;
}
