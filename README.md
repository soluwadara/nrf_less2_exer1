# nrf_less2_exer1

1. What are the hardware registers that cause the LED to turn on and off? (From the processor manual, don’t worry about initialization.)
   The LED on board is on the GPIO port 1 peripheral. In Zephyr, the dts is where the hardware configuration of the board is managed.
The base address of Gpio1 is 0x418c0800. The GPIO OUT register is a register in the GPIO1 register. It allows you to drive the pin 
either high or low. It has at a 0x004 offset. And you write either 1 or 0 to the register. In this example to turn on the LED, 
a 1 would be written to the register and to turn off the LED a 0 would be written. The GPIO DIR register is another register
in the GPIO1 register. It defines the direction of the GPIO pin. It is either an in put or output, which in this case was 1. 
to set it as an output. I'm not sure how the zephyr functions (in gpio.h) utimately call the nrf functions (nrf_gpio.h). 

2. What are the registers that you read in order to find out the state of the button?
Can you read the register directly and see the button change in a debugger or by printing out thes value of the memory at the register’s address?
