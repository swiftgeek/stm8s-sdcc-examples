#include "stm8s_conf.h"
#define MAX_DUTY 350
int main() {
  // Setup!
  uint8_t PD3;
  uint8_t direction;
  uint16_t duty, __ARR;
  int d;
  duty = MAX_DUTY;
  direction = 0;
  __ARR = 999;
  PD3 = 1 << 3;
  // Configure pins
  GPIOD->CR1 = GPIO_PIN_3;  // Enable push-pull
  //TimeBaseInit
  TIM2->ARRH = BYTE_1(__ARR);
  TIM2->ARRL = BYTE_0(__ARR);
  //OC2Init
  TIM2->CCER1 = TIM2_CCER1_CC2P | TIM2_CCER1_CC2E ; // Set output polarity to active low and enable output
  TIM2->CCMR2 = TIM2_OCMODE_PWM2 | TIM2_CCMR_OCxPE  ; //Set pwm1 mode and enable preload for CCR2H/L
  // Initial state, not needed?
  TIM2->CCR2H =  BYTE_1(duty);
  TIM2->CCR2L =  BYTE_0(duty);

  //Enable TIM2
  TIM2->CR1 = TIM2_CR1_CEN | TIM2_CR1_ARPE ;

  // Loop
  do {
    TIM2->CCR2H =  BYTE_1(duty);
    TIM2->CCR2L =  BYTE_0(duty);
    if ( direction == 0 ) {
      if (duty >= 10) {
        duty = duty - 10;
      } else {
        direction = 1;
      }
    }  else {
      if (duty <= (MAX_DUTY - 10) ) {
        duty = duty + 10;
      } else {
        direction = 0;
      }
    }
    //Sleep
    for(d = 0; d < 2900; d++) { }

  } while(1);
}
