#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#define L_LED 28
#define R_LED 4

void led_init(int GPIO) {
    gpio_init(GPIO);
    gpio_set_dir(GPIO, GPIO_OUT);
}

void wifi_init() {
    if (cyw43_arch_init()) {
        printf("Wifi Module Failed to Initialize\n");
    }
    cyw43_arch_enable_sta_mode();
    if (cyw43_arch_wifi_connect_timeout_ms("Traffic-light-Sequencer", "THisISAPassword", CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("Failed to connect to WiFi\n");
    } else {
        printf("Connected to WiFi\n");
        // Set Wifi Connected LED
        gpio_put(R_LED, 1);
    }
}

int main() {
    stdio_init_all();
    // Enable Both status leds
    led_init(L_LED);
    led_init(R_LED);
    // Set Power LED
    gpio_put(L_LED, 1);
    // Setup WiFi
    wifi_init();
    return 0;
}
