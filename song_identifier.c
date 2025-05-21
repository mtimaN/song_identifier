#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"

int main()
{
    stdio_init_all();

    // Initialise the Wi-Fi chip
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        return -1;
    }

    // Turn on the onboard LED
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

    // --- Initialize ADC ---
    adc_init();                     // Start the ADC peripheral
    adc_gpio_init(26);              // Enable GPIO26 (ADC0)
    adc_select_input(0);            // Select ADC input 0 (GPIO26)

    while (true) {
        uint16_t result = adc_read();  // Read from ADC (12-bit: 0–4095)
        float voltage = result * 3.3f / 4095.0f;

        printf("Mic ADC: %d\tVoltage: %.2f V\n", result, voltage);

        sleep_ms(100); // 10 readings per second
    }
}
