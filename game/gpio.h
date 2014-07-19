//-----------------------------------------------------------------------------
/*

GPIO Control for the STM32F4 Discovery Board

Pin Assignments for STM32F429I Discovery Board

PA0 = push button
PA1 = system_reset
PA2 =
PA3 =
PA4 = codec
PA5 = accel
PA6 = accel
PA7 = accel
PA8
PA9 = usb
PA10 = usb
PA11 = usb (not on header)
PA12 = usb (not on header)
PA13 = swd
PA14 = swd
PA15 =

PB0
PB1
PB2
PB3 = swd
PB4
PB5
PB6 = codec
PB7 =
PB8
PB9 = codec
PB10 = mic
PB11
PB12
PB13
PB14
PB15

PC0 = usb
PC1
PC2
PC3 = mic
PC4 = codec
PC5
PC6
PC7 = codec
PC8
PC9
PC10 = codec
PC11
PC12 = codec
PC13
PC14 = osc_in
PC15 = osc_out

PD0 =
PD1 =
PD2 =
PD3 =
PD4 = codec
PD5 = usb
PD6 =
PD7 =
PD8 =
PD9 =
PD10 =
PD11 =
PD12 = led
PD13 = led
PD14 = led
PD15 = led

PE0 = accel
PE1 = accel
PE2
PE3 = accel
PE4 =
PE5 =
PE6 =
PE7 =
PE8 =
PE9 =
PE10 =
PE11 =
PE12 =
PE13 =
PE14 =
PE15 =

PH0 = ph0_osc_in
PH1 = ph1_osc_out

*/
//-----------------------------------------------------------------------------

#ifndef GPIO_H
#define GPIO_H

//-----------------------------------------------------------------------------

#include "stm32f4xx_hal.h"

//-----------------------------------------------------------------------------
// port numbers

#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4
#define PORTF 5
#define PORTG 6
#define PORTH 7
#define PORTI 8

//-----------------------------------------------------------------------------
// gpio macros

#define GPIO_NUM(port, pin) ((port << 4) | (pin))
#define GPIO_PORT(n) (n >> 4)
#define GPIO_PIN(n) (n & 0xf)
#define GPIO_BIT(n) (1 << GPIO_PIN(n))
#define GPIO_BASE(n) ((GPIO_TypeDef  *)(GPIOA_BASE + (GPIO_PORT(n) * 0x400)))

//-----------------------------------------------------------------------------
// gpio assignments

// standard board GPIO
#define LED_GREEN       GPIO_NUM(PORTG, 13)
#define LED_RED         GPIO_NUM(PORTG, 14)
#define PUSH_BUTTON     GPIO_NUM(PORTA, 0) // 0 = open, 1 = pressed

//-----------------------------------------------------------------------------
// generic api functions

static inline void gpio_clr(int n)
{
    GPIO_BASE(n)->BSRRH = GPIO_BIT(n);
}

static inline void gpio_set(int n)
{
    GPIO_BASE(n)->BSRRL = GPIO_BIT(n);
}

static inline void gpio_toggle(int n)
{
    GPIO_BASE(n)->ODR ^= GPIO_BIT(n);
}

static inline int gpio_rd(int n)
{
    return (GPIO_BASE(n)->IDR >> GPIO_PIN(n)) & 1;
}

static inline int gpio_rd_inv(int n)
{
    return (~(GPIO_BASE(n)->IDR) >> GPIO_PIN(n)) & 1;
}

void gpio_init(void);

//-----------------------------------------------------------------------------
// The input gpios are spread out across several ports. We read and pack them into a
// single uint32_t and debounce them together.

// debounced input switches
#define PUSH_BUTTON_BIT 0

static inline uint32_t debounce_input(void)
{
    // pack the gpio inputs to be debounced into the uint32_t debounce state
    return (gpio_rd(PUSH_BUTTON) << PUSH_BUTTON_BIT);
}

//-----------------------------------------------------------------------------

#endif // GPIO_H

//-----------------------------------------------------------------------------
