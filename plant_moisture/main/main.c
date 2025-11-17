#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"

#define TAG "MAIN"


void app_main(void) {
    adc_oneshot_unit_handle_t adc_handle;

    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
        .clk_src = 0,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };

    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc_handle));

    adc_oneshot_chan_cfg_t chan_config = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };

    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, ADC_CHANNEL_4, &chan_config));
    
    int air_value = 3700;
    int water_value = 1200;

    int raw;
    int moisture_percentage;

    while (1) {
        ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, ADC_CHANNEL_4, &raw));
        moisture_percentage = (air_value - raw) * 100 / (air_value - water_value);
        ESP_LOGI(TAG, "Moisture percentage: %d%%", moisture_percentage);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
    
    return;
}
