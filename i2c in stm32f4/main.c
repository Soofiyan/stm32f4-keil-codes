//
//  main.c
//  i2c in stm32f4
//
//  Created by Soofiyan Atar on 07/11/18.
//
#include <stdio.h>
#include <stdbool.h>
#include <stm32f4xx.h>

bool write = 0, read = 1;

int main()
{
    I2C_init();
    while(1)
    {
        I2C_start();
        I2C_write_address(0x08);
        I2C_write_data(0x10);
        I2C_stop();
    }
}

void I2C_start()
{
    I2C1 -> CR1 |= (1<<10);
    I2C1 -> CR2 |= 0x0008;
//    I2C -> OAR1 |= (address<<1);            //for slave address like TWAR register in avr
    I2C1 -> CCR |= (1<<2);
    I2C1 -> CR1 |= (1<<0);                   //enable peripheral
    I2C1 -> CR1 |= (1<<8);                   //start condition
    while(!(I2C1 -> SR1 & (1<<0)));
}
void I2C_write_address(uint8_t address)     //address will be max 0x7F
{
    //while(!(I2C1 -> SR1 & (1<<7)));
    I2C1 -> DR |= (address<<1) + write;
    while(!(I2C1 -> SR1 & (1<<1)));
}
void I2C_write_data(uint8_t data)
{
    while(!(I2C1 -> SR1 & (1<<7)));
    I2C1 -> DR |= data;
}
void I2C_stop()
{
    I2C1 -> CR1 |= (1<<9);
    while(!(I2C1 -> SR1 & (1<<4)));
}
void I2C_init()
{
    RCC -> AHB1ENR |= (1<<1);
    RCC -> APB1ENR |= (1<<21);
    RCC -> APB2ENR |= (1<<14);
    GPIOB -> MODER |= (1<<13)|(1<<15);
    GPIOB -> OTYPER |= (1<<6)|(1<<7);
    GPIOB -> OSPEEDR |= (1<<12)|(1<<14);
    GPIOB -> AFR[0] |= (1<<26)|(1<<30);
}
