/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME_MS   10UL * 60UL * 1000UL
/* Get the node identifier for button 1 through its alias sw0 */
#define SW0_NODE DT_ALIAS(sw0) // sw3 on the board
/* LED0_NODE is the devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0) // red led

/* Get the device pointer. pin number, and pin's configuration flags through gpio_dt_spec */
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(SW0_NODE, gpios);
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void button_pressed_isr(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	gpio_pin_toggle_dt(&led);
}
static struct gpio_callback button_cb_data;

void main(void)
{
	int ret;
	/* Verify that the device is ready for use */
	if (!device_is_ready(led.port)) {
		return;
	}
	if (!device_is_ready(button.port)) {
		return;
	}
	/* Configure the pin connected to the button to be an input pin and set its hardware specifications */
	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return;
	}
	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
	if (ret < 0) {
		return;
	}
	ret = gpio_pin_interrupt_configure_dt(&button,GPIO_INT_EDGE_TO_ACTIVE);
	if (ret < 0) {
		return;
	}
	gpio_init_callback(&button_cb_data,button_pressed_isr,BIT(button.pin));
	gpio_add_callback(button.port, &button_cb_data);
	
	while (1) {
		
		k_msleep(SLEEP_TIME_MS); // Put the main thread to sleep for 100ms for power optimization
	}
}
