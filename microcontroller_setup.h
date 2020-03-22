#ifndef MICROCONTROLLER_SETUP_H
#define MICROCONTROLLER_SETUP_H

void enable_ports_b_c(void);

void set_port_c14_as_output(void);

void set_port_b9_as_input(void);

void configure_registers(void);

void c14_on(void);

void c14_off(void);

int get_b9(void);

#endif
