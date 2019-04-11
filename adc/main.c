#include <stm32f4xx.h>

//void configureadc();
void configureadc();
void configureledpins();

uint32_t a = 0,b = 0,c = 0;
int i = 0;
int main()
{
    configureadc();
    configureledpins();
    while(1)
    {
        
        ADC1->CR2 |= (1<<0)|(1<<30);
        while((ADC1 ->SR &(1<<4))==0)
        {}
        a = ADC1 -> DR;
        if(a >= 500 && a<=2000)
        {
            GPIOD ->ODR |= (1<<12)|(1<<13)|(1<<14)|(1<<15);
        }
        else{
            GPIOD ->ODR = 0x00;
        }
        //ADC1 ->CR2 &= ~(1<<0);
        while((ADC1 ->SR &(1<<1))==1)
        {}
        //    ADC1 ->SR = 0x0000000;
        
        
    }
}
void configureadc()
{
    RCC ->AHB1ENR |= (1<<0);
    RCC ->APB2ENR |= (1<<8);
    GPIOA ->MODER|=(1<<0)|(1<<1);
    GPIOA ->PUPDR = 0x00000000;
    RCC ->CR |= (1<<0);
    ADC1->CR2 |= (1<<0)|(1<<10);
    //ADC1->CR1 |=(1<<25);
    ADC1 ->SMPR2 |= (1<<0)|(1<<1);
    ADC1 ->SQR1 = 0x00000000;
    ADC1 ->SQR3 = 0x00000000;
    ADC ->CCR |= (1<<17)|(1<<16)|(1<<8)|(1<<9)|(1<<10)|(1<<11);
}
//void configureadc1()
//{
//    RCC ->AHB1ENR |= (1<<0);
//    RCC ->APB2ENR |= (1<<8);
//    GPIOA ->MODER|=(1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5);
//    GPIOA ->PUPDR = 0x00000000;
//    ADC1 -> CR2 |= (1<<10);
//    ADC1 -> CR1 |= (1<<13)|(1<<14);
//    ADC1 -> SMPR2 |= (1<<0)|(1<<1);
//    ADC1 -> SMPR2 |= (1<<5);
//    ADC1 -> SMPR2 |= (1<<8)|(1<<6);
//    ADC1 -> SQR1 |= (1<<21)|(1<<20);
//    ADC1 -> SQR3 |= (1<<5);
//    ADC1 -> SQR3 |= (1<<11);
//    ADC -> CCR |= (1<<17)|(1<<16)|(1<<8)|(1<<9)|(1<<10)|(1<<11);
//}
void configureledpins()
{
    RCC -> AHB1ENR |= (1<<3);
    GPIOD ->MODER |= (1<<24)|(1<<26)|(1<<28)|(1<<30);
    GPIOD ->PUPDR |= (1<<25)|(1<<27)|(1<<29)|(1<<31);
}
