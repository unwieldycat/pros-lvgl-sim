#include "pros/adi.h"

adi_port_config_e_t adi_port_get_config(uint8_t port) { return E_ADI_TYPE_UNDEFINED; }
int32_t adi_port_get_value(uint8_t port) { return 0; }
int32_t adi_port_set_config(uint8_t port, adi_port_config_e_t type) { return 1; }
int32_t adi_port_set_value(uint8_t port, int32_t value) { return 1; }
int32_t adi_analog_calibrate(uint8_t port) { return 0; }
int32_t adi_analog_read(uint8_t port) { return 0; }
int32_t adi_analog_read_calibrated(uint8_t port) { return 0; }
int32_t adi_analog_read_calibrated_HR(uint8_t port) { return 0; }
int32_t adi_digital_read(uint8_t port) { return 0; }
int32_t adi_digital_get_new_press(uint8_t port) { return 0; }
int32_t adi_digital_write(uint8_t port, bool value) { return 1; }
int32_t adi_pin_mode(uint8_t port, uint8_t mode) { return 1; }
int32_t adi_motor_set(uint8_t port, int8_t speed) { return 1; }
int32_t adi_motor_get(uint8_t port) { return 0; }
int32_t adi_motor_stop(uint8_t port) { return 1; }
int32_t adi_encoder_get(adi_encoder_t enc) { return 0; }
adi_encoder_t adi_encoder_init(uint8_t port_top, uint8_t port_bottom, bool reverse) {
	return port_top;
}
int32_t adi_encoder_reset(adi_encoder_t enc) { return 1; }
int32_t adi_encoder_shutdown(adi_encoder_t enc) { return 1; }
int32_t adi_ultrasonic_get(adi_ultrasonic_t ult) { return 0; }
adi_ultrasonic_t adi_ultrasonic_init(uint8_t port_ping, uint8_t port_echo) { return port_echo; }
int32_t adi_ultrasonic_shutdown(adi_ultrasonic_t ult) { return 1; }
double adi_gyro_get(adi_gyro_t gyro) { return 0; }
adi_gyro_t adi_gyro_init(uint8_t port, double multiplier) { return port; }
int32_t adi_gyro_reset(adi_gyro_t gyro) { return 1; }
int32_t adi_gyro_shutdown(adi_gyro_t gyro) { return 1; }
adi_potentiometer_t adi_potentiometer_init(uint8_t port) { return port; }
adi_potentiometer_t
adi_potentiometer_type_init(uint8_t port, adi_potentiometer_type_e_t potentiometer_type) {
	return port;
}
double adi_potentiometer_get_angle(adi_potentiometer_t potentiometer) { return 0; }
adi_led_t adi_led_init(uint8_t port) { return port; }
int32_t adi_led_clear_all(adi_led_t led, uint32_t *buffer, uint32_t buffer_length) { return 1; }
int32_t adi_led_set(adi_led_t led, uint32_t *buffer, uint32_t buffer_length) { return 1; }
int32_t adi_led_set_all(adi_led_t led, uint32_t *buffer, uint32_t buffer_length, uint32_t color) {
	return 1;
}
int32_t adi_led_set_pixel(
    adi_led_t led, uint32_t *buffer, uint32_t buffer_length, uint32_t color, uint32_t pixel_position
) {
	return 1;
}
int32_t adi_led_clear_pixel(
    adi_led_t led, uint32_t *buffer, uint32_t buffer_length, uint32_t pixel_position
) {
	return 1;
}
