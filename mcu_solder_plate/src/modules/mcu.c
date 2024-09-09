/**
 * NOTE      - mcu.c
 * Author    - Chae Lee-Jin
 *
 * Created   - 2024.09.01
 * Github    - https://github.com/aruyu
 * Contact   - vine9151@gmail.com
 */



#include "mcu.h"


/*----------------------------------------//
                Insert Bit
//----------------------------------------*/

uint8_t insert_bit(uint8_t bitValue, bool isHigh)
{
  uint8_t returnValue = 0x00;

  if (isHigh == true)
  {
    return returnValue |= (1 << bitValue);
  }
  else
  {
    return returnValue &= ~(1 << bitValue);
  }
}


/*----------------------------------------//
            Convert 10 to 16
//----------------------------------------*/

uint8_t to_hex(int8_t decimal)
{
  uint8_t hexadecimal = 0x00;

  if (decimal >= 0 && decimal <= 9)
  {
    hexadecimal = decimal;
  }

  else if (decimal >= 10 && decimal <= 19)
  {
    hexadecimal = decimal + 6;
  }

  else if (decimal >= 20 && decimal <= 29)
  {
    hexadecimal = decimal + 12;
  }

  else if (decimal >= 30 && decimal <= 39)
  {
    hexadecimal = decimal + 18;
  }

  else if (decimal >= 40 && decimal <= 49)
  {
    hexadecimal = decimal + 24;
  }

  else if (decimal >= 50 && decimal <= 59)
  {
    hexadecimal = decimal + 30;
  }

  else if (decimal >= 60 && decimal <= 69)
  {
    hexadecimal = decimal + 36;
  }

  else if (decimal >= 70 && decimal <= 79)
  {
    hexadecimal = decimal + 42;
  }

  else if (decimal >= 80 && decimal <= 89)
  {
    hexadecimal = decimal + 48;
  }

  else if (decimal >= 90 && decimal <= 99)
  {
    hexadecimal = decimal + 54;
  }

  return hexadecimal;
}

/*----------------------------------------//
            Convert 10 to ASCII
//----------------------------------------*/

uint8_t to_ascii(int8_t decimal)
{
  uint8_t ASCIIValue = 0x00;

  if (decimal >= 0 && decimal <= 9)
  {
    ASCIIValue = decimal + 0x30;
  }

  return ASCIIValue;
}

/*----------------------------------------//
            Convert 10 to ASCII
//----------------------------------------*/

char* to_str(uint32_t intager)
{
  long placeValue = 1;
  char digit = 1;
  char* retval;

  while ((intager / placeValue) > 9)
  {
    digit++;
    placeValue *= 10;
  }

  char tmp[digit + 1];

  for (int i=0; i<digit; i++)
  {
    tmp[i] = (char)((intager / placeValue) + 0x30);
    intager %= placeValue;
    placeValue /= 10;
  }

  tmp[digit] = '\0';
  retval = tmp;
  return retval;
}

/*----------------------------------------//
                Begin Pin
//----------------------------------------*/

void begin_pin(int8_t port, int8_t pinNumber)
{
  switch (port)
  {
    // PORTB
    case B:
      DDRB |= insert_bit(pinNumber, HIGH);
      PORTB |= insert_bit(pinNumber, LOW);
      break;

    // PORTC
    case C:
      DDRC |= insert_bit(pinNumber, HIGH);
      PORTC |= insert_bit(pinNumber, LOW);
      break;

    // PORTD
    case D:
      DDRD |= insert_bit(pinNumber, HIGH);
      PORTD |= insert_bit(pinNumber, LOW);
      break;

    default:
      break;
  }
}

/*----------------------------------------//
                Begin Port
//----------------------------------------*/

void begin_port(int8_t port, bool isOutput)
{
  uint8_t ddrValue;
  uint8_t portValue;

  // INPUT or OUTPUT
  if (isOutput == true)
  {
    ddrValue = 0xFF;
    portValue = 0x00;
  }
  else
  {
    ddrValue = 0x00;
  }

  switch (port)
  {
    // PORTB
    case B:
      DDRB = ddrValue;
      PORTB = portValue;
      break;

    // PORTC
    case C:
      DDRC = ddrValue;
      PORTC = portValue;
      break;

    // PORTD
    case D:
      DDRD = ddrValue;
      PORTD = portValue;
      break;

    default:
      break;
  }
}

/*----------------------------------------//
        Begin Extended Interrupt
//----------------------------------------*/

void begin_interrupt(int8_t INTIndex, int8_t INTMode)
{
  EIMSK |= insert_bit(INTIndex, HIGH);

  switch (INTMode)
  {
    case MAINTAIN:
      EICRA = 0x00;
      break;

    case DOWN:
      EICRA = 0x0A;
      break;

    case UP:
      EICRA = 0x0F;
      break;

    default:
      break;
  }
}

/*----------------------------------------//
        Begin Pin Change Interrupt
//----------------------------------------*/

void begin_pc_interrupt(int8_t PCINTIndex)
{
  if (PCINTIndex <= 7)
  {
    PCMSK0 |= insert_bit(PCINTIndex, HIGH);
    PCICR |= 0x01;
    return;
  }

  else if (PCINTIndex <= 14)
  {
    PCINTIndex -= 8;
    PCMSK1 |= insert_bit(PCINTIndex, HIGH);
    PCICR |= 0x02;
    return;
  }

  else if (PCINTIndex <= 23)
  {
    PCINTIndex -= 16;
    PCMSK1 |= insert_bit(PCINTIndex, HIGH);
    PCICR |= 0x04;
    return;
  }
}

/*----------------------------------------//
            Begin Timer Interrupt
//----------------------------------------*/

void begin_timer(int8_t timerIndex, bool timerMode)
{
  switch (timerIndex)
  {
    // TIMER INTERRUPT 0, 2 (8 BIT)
    case 0:
      if (timerMode == OVF)
      {
        TIMSK0 = 0x01;

        TCCR0A = 0x00;    // 1024 Prescaler, Normal Mode
        TCCR0B = 0x05;
        TCNT0 = 0x00;     // Start Counting 0x00
      }

      else
      {
        TIMSK0 = 0x02;

        TCCR0A = 0x02;    // 1024 Prescaler, CTC Mode
        TCCR0B = 0x05;
        TCNT0 = 0x00;     // Start Counting 0x00

        OCR0A = _OCR0A;
      }

      break;

    case 2:
      if (timerMode == OVF)
      {
        TIMSK2 = 0x01;

        TCCR2A = 0x00;    // 1024 Prescaler, Normal Mode
        TCCR2B = 0x04;
        TCNT2 = 0x00;     // Start Counting 0x00
      }

      else
      {
        TIMSK2 = 0x02;

        TCCR2A = 0x02;    // 1024 Prescaler, CTC Mode
        TCCR2B = 0x04;
        TCNT2 = 0x00;     // Start Counting 0x00

        OCR2A = _OCR2A;
      }

      break;

    // TIMER INTERRUPT 1 (16 BIT)
    case 1:
      if (timerMode == OVF)
      {
        TIMSK1 = 0x01;

        TCCR1A = 0x00;    // 1024 Prescaler, Normal Mode
        TCCR1B = 0x05;
        TCNT1H = 0x00;    // Start Counting 0x0000
        TCNT1L = 0x00;
      }

      else
      {
        TIMSK1 = 0x02;

        TCCR1A = 0x00;    // 1024 Prescaler, CTC Mode
        TCCR1B = 0x0D;
        TCNT1H = 0x00;    // Start Counting 0x0000
        TCNT1L = 0x00;

        OCR1AH = _OCR1AH;
        OCR1AL = _OCR1AL;
      }

      break;

    default:
      break;
  }
}

/*----------------------------------------//
            Begin Timer PWM
//----------------------------------------*/

void begin_pwm(int8_t PWMIndex, bool PWMMode)
{
  switch (PWMIndex)
  {
    // TIMER PWM 0, 2 (8 BIT)
    case OC0A:
      if (PWMMode == CORRECT)
      {
        TCCR0A |= 0x01 | (1 << COM0A0);   // 256 Prescaler, Phase Correct PWM
        TCCR0B = 0x0C;                    // Phase Correct PWM to OCR0A
        TCNT0 = 0x00;                     // Start Counting 0x00
      }

      else
      {
        TCCR0A |= 0x03 | (1 << COM0A0);   // 256 Prescaler, Fast PWM Mode
        TCCR0B = 0x0C;                    // Fast PWM to OCR0A
        TCNT0 = 0x00;                     // Start Counting 0x00
      }

      break;

    case OC0B:
      if (PWMMode == CORRECT)
      {
        TCCR0A |= 0x01 | (1 << COM0B0);   // 256 Prescaler, Phase Correct PWM
        TCCR0B = 0x0C;                    // Phase Correct PWM to OCR0A
        TCNT0 = 0x00;                     // Start Counting 0x00
      }

      else
      {
        TCCR0A |= 0x03 | (1 << COM0B0);   // 256 Prescaler, Fast PWM Mode
        TCCR0B = 0x0C;                    // Fast PWM to OCR0A
        TCNT0 = 0x00;                     // Start Counting 0x00
      }

      break;

    case OC2A:
      if (PWMMode == CORRECT)
      {
        TCCR2A |= 0x01 | (1 << COM2A1);   // 256 Prescaler
        TCCR2B = 0x06;                    // Phase Correct PWM to 255
        TCNT2 = 0x00;                     // Start Counting 0x00
      }

      else
      {
        TCCR2A |= 0x03 | (1 << COM2A1);   // 256 Prescaler
        TCCR2B = 0x06;                    // Fast PWM to 255
        TCNT2 = 0x00;                     // Start Counting 0x00
      }

      break;

    case OC2B:
      if (PWMMode == CORRECT)
      {
        TCCR2A |= 0x01 | (1 << COM2B1);   // 256 Prescaler
        TCCR2B = 0x06;                    // Phase Correct PWM to 255
        TCNT2 = 0x00;                     // Start Counting 0x00
      }

      else
      {
        TCCR2A |= 0x03 | (1 << COM2B1);   // 256 Prescaler
        TCCR2B = 0x06;                    // Fast PWM to 255
        TCNT2 = 0x00;                     // Start Counting 0x00
      }

      break;

    // TIMER PWM 1 (10 BIT)
    case OC1A:
      if (PWMMode == CORRECT)
      {
        TCCR1A |= 0x03 | (1 << COM1A1);   // 256 Prescaler
        TCCR1B = 0x04;                    // Phase Correct PWM to 1023
        TCNT1H = 0x00;                    // Start Counting 0x0000
        TCNT1L = 0x00;
      }

      else
      {
        TCCR1A |= 0x03 | (1 << COM1A1);   // 256 Prescaler
        TCCR1B = 0x0C;                    // Fast PWM to 1023
        TCNT1H = 0x00;                    // Start Counting 0x0000
        TCNT1L = 0x00;
      }

      break;

    case OC1B:
      if (PWMMode == CORRECT)
      {
        TCCR1A |= 0x03 | (1 << COM1B1);   // 256 Prescaler
        TCCR1B = 0x04;                    // Phase Correct PWM to 1023
        TCNT1H = 0x00;                    // Start Counting 0x0000
        TCNT1L = 0x00;
      }

      else
      {
        TCCR1A |= 0x03 | (1 << COM1B1);   // 256 Prescaler
        TCCR1B = 0x0C;                    // Fast PWM to 1023
        TCNT1H = 0x00;                    // Start Counting 0x0000
        TCNT1L = 0x00;
      }

      break;

    default:
      break;
  }
}

/*----------------------------------------//
            Begin SPI Protocol
//----------------------------------------*/

void begin_spi(void)
{
  SPCR = (1 << SPE) | (1 << MSTR);
  SPSR = (1 << SPI2X);
}

/*----------------------------------------//
                Begin ADC
//----------------------------------------*/

void begin_adc(uint8_t adc_channel, int8_t adc_mode)
{
  switch (adc_mode)
  {
    case AREF:
      ADMUX |= insert_bit(REFS1, false) | insert_bit(REFS0, false) | (adc_channel <= 8) ? adc_channel : 0b1111;
      break;

    case AVCC:
      ADMUX |= insert_bit(REFS1, false) | insert_bit(REFS0, true) | (adc_channel <= 8) ? adc_channel : 0b1111;
      break;

    case INTERNAL:
      ADMUX |= insert_bit(REFS1, true) | insert_bit(REFS0, true) | (adc_channel <= 8) ? adc_channel : 0b1111;
      break;

    default:
      break;
  }

  /* Prescaler 128 */
  ADCSRA |= insert_bit(ADPS2, true) | insert_bit(ADPS1, true) | insert_bit(ADPS0, true);
  /* Auto Trigger Mode (Free Running) */
  ADCSRA |= insert_bit(ADATE, true);
  /* Enable ADC */
  ADCSRA |= insert_bit(ADEN, true);
  /* Start ADC */
  ADCSRA |= insert_bit(ADSC, true);
}

/*----------------------------------------//
                Read ADC
//----------------------------------------*/

uint16_t read_adc()
{
  while(!(ADCSRA & insert_bit(ADIF, true)));
  return ((ADCH << 8) | ADCL);
}
