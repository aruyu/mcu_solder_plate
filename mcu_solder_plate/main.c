/**
 * NOTE      - main.c
 * Author    - Chae Lee-Jin
 *
 * Created   - 2024.09.01
 * Github    - https://github.com/aruyu
 * Contact   - vine9151@gmail.com
 */



#include "src/modules/mcu.h"
#include "src/modules/lmt85.h"

ISR(INT0_vect);
ISR(INT1_vect);

uint8_t g_set_temperature = 100;


int main(void)
{
  SSD1306_Init(SSD1306_ADDR);                      // 0x3C

  SSD1306_ClearScreen();                           // clear screen
  SSD1306_DrawLine(0, MAX_X, 4, 4);                // draw line
  SSD1306_SetPosition(7, 1);                       // set position
  SSD1306_DrawString("* MCU SOLDER PLATE *");      // draw string
  SSD1306_DrawLine(0, MAX_X, 18, 18);              // draw line
  SSD1306_SetPosition(40, 3);                      // set position
  SSD1306_DrawString("LEE JIN");                   // draw string
  SSD1306_SetPosition(53, 5);                      // set position
  SSD1306_DrawString("2024");                      // draw string
  SSD1306_UpdateScreen(SSD1306_ADDR);              // update

  _delay_ms(1000);
  SSD1306_InverseScreen(SSD1306_ADDR);
  _delay_ms(1000);
  SSD1306_NormalScreen(SSD1306_ADDR);

  begin_pin(B, 1);
  begin_pwm(OC1A, FAST);
  sei();
  OCR1A = 10000;


  begin_adc(2, AVCC);
  begin_interrupt(0, MAINTAIN);
  begin_interrupt(1, MAINTAIN);


  /* Replace with your application code */
  while (1)
  {
    uint16_t tmp = (uint16_t)((5000.0f / 1023.0f) * read_adc());
    uint16_t result = 0;
    bool is_neg = calc_adc(tmp, &result);

    SSD1306_ClearScreen();

    SSD1306_SetPosition(10, 1);
    SSD1306_DrawString("Set :");
    SSD1306_SetPosition(80, 1);
    SSD1306_DrawString(to_str(g_set_temperature));
    SSD1306_SetPosition(100, 1);
    SSD1306_DrawString("`C");

    if (tmp < 2000)
    {
      SSD1306_SetPosition(10, 3);

      if (is_neg)
      {
        SSD1306_DrawString("Present : -");
      }
      else
      {
        SSD1306_DrawString("Present : +");
      }

      SSD1306_SetPosition(80, 3);
      SSD1306_DrawString(to_str(result));
      SSD1306_SetPosition(100, 3);
      SSD1306_DrawString("`C");
    }
    else
    {
      SSD1306_SetPosition(10, 3);
      SSD1306_DrawString("No Plate Detected");
    }

    SSD1306_UpdateScreen(SSD1306_ADDR);
    _delay_ms(1);
  }

  return 0;
}



ISR(INT0_vect)
{
  if (g_set_temperature > 0)
  {
    g_set_temperature--;
  }
  _delay_ms(50);
}

ISR(INT1_vect)
{
  if (g_set_temperature < 150)
  {
    g_set_temperature++;
  }
  _delay_ms(50);
}