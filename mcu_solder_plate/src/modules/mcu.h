/**
 * NOTE      - mcu.h
 * Author    - Chae Lee-Jin
 * 
 * Created   - 2024.09.01
 * Github    - https://github.com/aruyu
 * Contact   - vine9151@gmail.com
 */



#pragma once
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "../lib/ssd1306.h"

typedef uint8_t bool;
#define false 0
#define true 1

#define OFF 0
#define ON 1
#define LOW 0
#define HIGH 1
#define IN 0
#define OUT 1

#define OVF 0
#define COMP 1
#define CORRECT 0
#define FAST 1
#define MAINTAIN 0
#define DOWN 1
#define UP 2

#define AREF 0
#define AVCC 1
#define INTERNAL 2

#define _OCR0A 0xFF   // Compare with 255   Timer0
#define _OCR2A 0xF9   // Compare with 249   Timer2 (1ms in 64 Prescaler)
#define _OCR1AH 0x00
#define _OCR1AL 0xFF  // Compare with 15624 Timer1 (1s in 1024 Prescaler)

enum PinNumber
{
  B, C, D, OC0A, OC0B, OC1A, OC1B, OC2A, OC2B
};




uint8_t insert_bit(uint8_t bitValue, bool isHigh);
uint8_t to_hex(int8_t decimal);
uint8_t to_ascii(int8_t decimal);
char* to_str(uint32_t intager);

void begin_pin(int8_t port, int8_t pinNumber);
void begin_port(int8_t port, bool isOutput);
void begin_interrupt(int8_t INTIndex, int8_t INTMode);
void begin_pc_interrupt(int8_t PCINTIndex);
void begin_timer(int8_t timerIndex, bool timerMode);
void begin_pwm(int8_t PWMIndex, bool PWMMode);
void begin_spi(void);
void begin_adc(uint8_t adc_channel, int8_t adc_mode);
uint16_t read_adc();