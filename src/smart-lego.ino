#include <avr/sleep.h>

#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // disable ADC (ADC uses ~320uA)

const int LED_PIN = 0;
const unsigned long SLEEP_AFTER_MILIS = 60000; // sleep after 1 min

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  adc_disable();
}

void enterSleep()
{
  cli(); // disable all interrupts
  WDTCR = 0; // turn off the Watchdog timer
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  adc_disable();
  sleep_enable();
  sleep_cpu();
}


void loop()
{
  digitalWrite(LED_PIN, HIGH);
  do
  {
    delay(1000);
  } while (millis() < SLEEP_AFTER_MILIS);
  
  digitalWrite(LED_PIN, LOW);
  delay(1000);
  enterSleep();
  
  // ...continue after reset
}
