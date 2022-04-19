#include "esp_log.h"
#include "rc522.h"

static const char* TAG = "app";

void first_contact(uint8_t* sn) { 
    // This handler runs only once when a card is first brought up to the scanner
    ESP_LOGI(TAG, "Tag: %#x %#x %#x %#x %#x",
        sn[0], sn[1], sn[2], sn[3], sn[4] );
}

void continued_contact(int sn) {
    // This handler runs on repeat (default 125ms delay) when a card is against the scanner
    ESP_LOGI(TAG, "Tag: %d", sn );
}

void removal(int sn) {
    // This handler runs when card is removed from scanner
    ESP_LOGI(TAG, "Tag: %d", sn );
}

void app_main(void) {
    const rc522_start_args_t start_args = {
        // Pinout ESP32-S2 dev kit
		.miso_io = 33,
		.mosi_io = 34,
		.sck_io = 35,
		.sda_io = 15,
        .callback = &first_contact,
        .callback2 = &continued_contact,
        .callback3 = &removal,

        // Uncomment next line for attaching RC522 to SPI2 bus. Default is VSPI_HOST (SPI3)
        .spi_host_id = HSPI_HOST
    };

    rc522_start(start_args);
}