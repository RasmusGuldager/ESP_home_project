#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "dht.h" // Header from the esp-idf-lib/dht component

// Define the GPIO pin and sensor type
#define SENSOR_TYPE DHT_TYPE_DHT11
#define SENSOR_GPIO 4 // Make sure this is the GPIO pin you are using

// Tag for logging
static const char *TAG = "DHT11_SENSOR";

void dht_task(void *pvParameters)
{
    float temperature, humidity;

    while(1)
    {
        // This library uses a simple function to read float data
        if (dht_read_float_data(SENSOR_TYPE, SENSOR_GPIO, &humidity, &temperature) == ESP_OK)
        {
            ESP_LOGI(TAG, "Humidity: %.1f%%, Temperature: %.1f°C", humidity, temperature);
        }
        else
        {
            ESP_LOGE(TAG, "Failed to read data from sensor");
        }

        // Wait 3 seconds before the next reading
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

void app_main(void)
{
    // Create the sensor reading task
    xTaskCreate(dht_task, "dht_task", 2048, NULL, 5, NULL);
}