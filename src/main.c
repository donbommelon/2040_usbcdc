#include <stdio.h>
#include <unistd.h>
#include "pico/stdlib.h"
//#include "stdio_usb.h"
// #include "hardware/vreg.h"
// #include "hardware/clocks.h"
#include "tusb_config.h"

#define samples  10000

void main() {
	uint8_t __attribute__((aligned(4))) data[samples];
	uint64_t start_time;
	uint64_t end_time;
	
	// vreg_set_voltage(VREG_VOLTAGE_0_90);
	// set_sys_clock_khz(48 * KHZ, true);
    for (int i =0; i<samples; i++)
        data[i] = (uint8_t) i;
	stdio_init_all();
	stdio_set_translate_crlf(&stdio_usb, false);
	sleep_ms(4500);

	while (true) {
		// start_time = get_absolute_time();
		write(1, &data, samples);
		// end_time = get_absolute_time();
		
		// printf("%.3f ms\n", absolute_time_diff_us(start_time, end_time) / 1000.0);
		// sleep_ms(1000);
	}
}
