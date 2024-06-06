#include "pros/adi.hpp"
#include "pros/adi.h"
#include "pros/ext_adi.h"

namespace pros {

namespace adi {

Port::Port(std::uint8_t adi_port, adi_port_config_e_t type) { _adi_port = adi_port; }
Port::Port(ext_adi_port_pair_t port_pair, adi_port_config_e_t type) {
	_smart_port = port_pair.first;
	_adi_port = port_pair.second;
}
std::int32_t Port::get_config() const { return c::adi_port_get_config(_adi_port); }
std::int32_t Port::get_value() const { return c::adi_port_get_value(_adi_port); }
std::int32_t Port::set_config(adi_port_config_e_t type) const {
	return c::adi_port_set_config(_adi_port, type);
}
std::int32_t Port::set_value(std::int32_t value) const {
	return c::adi_port_set_value(_adi_port, value);
}
ext_adi_port_tuple_t Port::get_port() const { return {_smart_port, _adi_port, _adi_port}; }

AnalogIn::AnalogIn(std::uint8_t adi_port) : Port(adi_port) {}
AnalogIn::AnalogIn(ext_adi_port_pair_t port_pair) : Port(port_pair.first) {}
std::int32_t AnalogIn::calibrate() const { return c::adi_analog_calibrate(_adi_port); }
std::int32_t AnalogIn::get_value_calibrated() const {
	return c::adi_analog_read_calibrated(_adi_port);
}
std::int32_t AnalogIn::get_value_calibrated_HR() const {
	return c::adi_analog_read_calibrated_HR(_adi_port);
}

AnalogOut::AnalogOut(std::uint8_t adi_port) : Port(adi_port) {}
AnalogOut::AnalogOut(ext_adi_port_pair_t port_pair) : Port(port_pair.second) {}
DigitalOut::DigitalOut(std::uint8_t adi_port, bool init_state) : Port(adi_port) {}
DigitalOut::DigitalOut(ext_adi_port_pair_t port_pair, bool init_state) : Port(port_pair.second) {}

DigitalIn::DigitalIn(std::uint8_t adi_port) : Port(adi_port) {}
DigitalIn::DigitalIn(ext_adi_port_pair_t port_pair) : Port(port_pair.second) {}
std::int32_t DigitalIn::get_new_press() const {
	return c::adi_digital_get_new_press(this->_adi_port);
}

Motor::Motor(std::uint8_t adi_port) : Port(adi_port) {}
Motor::Motor(ext_adi_port_pair_t port_pair) : Port(port_pair.second) {}
std::int32_t Motor::stop() const { return c::adi_motor_stop(_adi_port); }

Encoder::Encoder(std::uint8_t adi_port_top, std::uint8_t adi_port_bottom, bool reversed)
    : Port({adi_port_top, adi_port_bottom}) {}
Encoder::Encoder(ext_adi_port_tuple_t port_tuple, bool reversed) : Port(0) {}
std::int32_t Encoder::reset() const { return c::adi_encoder_reset(_adi_port); }
std::int32_t Encoder::get_value() const { return c::adi_encoder_get(_adi_port); }
ext_adi_port_tuple_t Encoder::get_port() const { return std::tuple<int, int, int>(0, 0, 0); }

Ultrasonic::Ultrasonic(std::uint8_t adi_port_ping, std::uint8_t adi_port_echo)
    : Port({adi_port_ping, adi_port_echo}) {}
Ultrasonic::Ultrasonic(ext_adi_port_tuple_t port_tuple) : Port(0) {}
std::int32_t Ultrasonic::get_value() const { return c::adi_ultrasonic_get(_adi_port); }

Gyro::Gyro(std::uint8_t adi_port, double multiplier) : Port(adi_port) {}
Gyro::Gyro(ext_adi_port_pair_t port_pair, double multiplier) : Port(port_pair) {}
double Gyro::get_value() const { return c::adi_gyro_get(_adi_port); }
std::int32_t Gyro::reset() const { return c::adi_gyro_reset(_adi_port); }

Potentiometer::Potentiometer(std::uint8_t adi_port, adi_potentiometer_type_e_t potentiometer_type)
    : AnalogIn(adi_port) {}
Potentiometer::Potentiometer(
    ext_adi_port_pair_t port_pair, adi_potentiometer_type_e_t potentiometer_type
)
    : AnalogIn(port_pair) {}
double Potentiometer::get_angle() const { return c::adi_potentiometer_get_angle(_adi_port); }

Led::Led(std::uint8_t adi_port, std::uint32_t length) : Port(adi_port) {}
Led::Led(ext_adi_port_pair_t port_pair, std::uint32_t length) : Port(port_pair) {}
std::int32_t Led::clear_all() { return 1; }
std::int32_t Led::clear() { return 1; }
std::int32_t Led::update() const { return 1; }
std::int32_t Led::set_all(uint32_t color) { return 1; }
std::int32_t Led::set_pixel(uint32_t color, uint32_t pixel_position) { return 1; }
std::int32_t Led::clear_pixel(uint32_t pixel_position) { return 1; }
std::int32_t Led::length() { return 0; }

Pneumatics::Pneumatics(std::uint8_t adi_port, bool start_extended, bool extended_is_low)
    : DigitalOut(adi_port) {}
Pneumatics::Pneumatics(ext_adi_port_pair_t port_pair, bool start_extended, bool extended_is_low)
    : DigitalOut(port_pair) {}
std::int32_t Pneumatics::extend() { return 1; }
std::int32_t Pneumatics::retract() { return 1; }
std::int32_t Pneumatics::toggle() { return 1; }
bool Pneumatics::is_extended() const { return 0; }

} // namespace adi
} // namespace pros