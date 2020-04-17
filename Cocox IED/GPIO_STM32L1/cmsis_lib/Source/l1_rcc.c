
#include "l1_rcc.h"

void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_RCC_AHB_PERIPH(RCC_AHBPeriph));
  assert_param(IS_FUNCTIONAL_STATE(NewState));

  if (NewState != DISABLE)
  {
    RCC->AHBENR |= RCC_AHBPeriph;
  }
  else
  {
    RCC->AHBENR &= ~RCC_AHBPeriph;
  }
}
