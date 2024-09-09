/**
 * NOTE      - lmt85.c
 * Author    - Chae Lee-Jin
 *
 * Created   - 2024.09.08
 * Github    - https://github.com/aruyu
 * Contact   - vine9151@gmail.com
 */



#include "lmt85.h"


/*----------------------------------------//
                Insert Bit
//----------------------------------------*/

bool calc_adc(uint16_t voltage, uint16_t* result)
{
  double adc_calc = (200.0f / 1654.0f) * (voltage - 301);
  int16_t value = 150 - adc_calc;

  if (value >= 0)
  {
    *result = (uint16_t)value;
    return false;
  }
  else
  {
    value *= -1;
    *result = (uint16_t)value;
    return true;
  }
}