#include "stm32l4xx_hal.h"
#include "display.h"
#include "eeng1030_lib.h"

void SystemClock_Config(void);
static void GPIO_Init(void);
static int Button_Pressed(void);
static void Show_Green(void);
static void Show_Red(void);
static void Show_Yellow(void);
static void Show_Pedestrian(void);

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    GPIO_Init();

    init_display();
    clear();

    while (1)
    {
        // GREEN
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6 | GPIO_PIN_5, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
        Show_Green();

        int pedestrian_request = 0;

        for (int t = 0; t < 4000; t += 50)
        {
            if (Button_Pressed())
            {
                pedestrian_request = 1;
                break;
            }
            delay_ms(50);
        }

        if (pedestrian_request)
        {
            // YELLOW for 2 seconds
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7 | GPIO_PIN_6, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
            Show_Yellow();
            delay_ms(2000);

            // RED / pedestrian wait for 5 seconds
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7 | GPIO_PIN_5, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
            Show_Pedestrian();
            delay_ms(5000);

            continue;
        }

        // RED
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7 | GPIO_PIN_5, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
        Show_Red();
        delay_ms(4000);

        // YELLOW
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7 | GPIO_PIN_6, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
        Show_Yellow();
        delay_ms(1500);
    }
}

static void GPIO_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // LED pins: PA5, PA6, PA7
    GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Button pin: PA1
    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_PIN_RESET);
}

static int Button_Pressed(void)
{
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
    {
        delay_ms(20);
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
        {
            while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_RESET)
            {
            }
            return 1;
        }
    }
    return 0;
}

static void Show_Green(void)
{
    uint16_t bg = RGBToWord(0, 100, 0);
    clear();
    fillRectangle(0, 0, 160, 80, bg);
    printTextX2("GREEN", 28, 28, RGBToWord(255,255,255), bg);
}

static void Show_Red(void)
{
    uint16_t bg = RGBToWord(120, 0, 0);
    clear();
    fillRectangle(0, 0, 160, 80, bg);
    printTextX2("RED", 44, 28, RGBToWord(255,255,255), bg);
}

static void Show_Yellow(void)
{
    uint16_t bg = RGBToWord(160, 120, 0);
    clear();
    fillRectangle(0, 0, 160, 80, bg);
    printTextX2("YELLOW", 18, 28, RGBToWord(0,0,0), bg);
}

static void Show_Pedestrian(void)
{
    uint16_t bg = RGBToWord(0, 0, 120);
    clear();
    fillRectangle(0, 0, 160, 80, bg);
    printText("PEDESTRIAN CROSSING", 20, 20, RGBToWord(255,255,255), bg);
    printTextX2("WAIT", 42, 42, RGBToWord(255,255,0), bg);
}
static void Show_Green(void)
{
    clear();
    fillRectangle(0, 0, 160, 80, RGBToWord(0, 0, 0));   // black background
    printTextX2("GREEN", 28, 28, RGBToWord(255,255,255), RGBToWord(0,0,0));
}

static void Show_Red(void)
{
    clear();
    fillRectangle(0, 0, 160, 80, RGBToWord(0, 0, 0));   // black background
    printTextX2("RED", 44, 28, RGBToWord(255,255,255), RGBToWord(0,0,0));
}

static void Show_Yellow(void)
{
    clear();
    fillRectangle(0, 0, 160, 80, RGBToWord(0, 0, 0));   // black background
    printTextX2("YELLOW", 18, 28, RGBToWord(255,255,255), RGBToWord(0,0,0));
}

static void Show_Pedestrian(void)
{
    clear();
    fillRectangle(0, 0, 160, 80, RGBToWord(0, 0, 0));   // black background
    printText("PEDESTRIAN CROSSING", 20, 20, RGBToWord(255,255,255), RGBToWord(0,0,0));
    printTextX2("WAIT", 42, 42, RGBToWord(255,255,255), RGBToWord(0,0,0));
}


void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
    RCC_OscInitStruct.MSIState = RCC_MSI_ON;
    RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
    RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK |
                                  RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 |
                                  RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);
}
