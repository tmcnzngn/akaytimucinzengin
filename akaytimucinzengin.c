#include "stm32f4xx_hal.h"
#include "usbd_cdc_if.h"

ADC_HandleTypeDef hadc1;

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_ADC1_Init(void);

int main(void)
{
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_ADC1_Init();

  while (1)
  {
    HAL_ADC_Start(&hadc1);

    if (HAL_ADC_PollForConversion(&hadc1, 10000) == HAL_OK)
    {
      uint32_t adcValue = HAL_ADC_GetValue(&hadc1);
      char output[50];
      sprintf(output, "ADC Value: %lu\r\n", adcValue);
      CDC_Transmit_FS((uint8_t*)output, strlen(output));
    }

    HAL_ADC_Stop(&hadc1);
  }
}
