/**
 * NOTE      - main.c
 * Author    - Chae Lee-Jin
 * 
 * Created   - 2024.09.01
 * Github    - https://github.com/aruyu
 * Contact   - vine9151@gmail.com
 */



#include "src/modules/mcu.h"


ISR(INT0_vect);
ISR(INT1_vect);



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
  
  
  begin_pin(B, 1);
  begin_pwm(OC1A, FAST);
  sei();
  OCR1A = 10000;


  /* Replace with your application code */
  while (1)
  {
    _delay_ms(1000);
    SSD1306_InverseScreen(SSD1306_ADDR);

    _delay_ms (1000);
    SSD1306_NormalScreen(SSD1306_ADDR);
  }
  
  return 0;
}



ISR(INT0_vect)
{
}

ISR(INT1_vect)
{
}