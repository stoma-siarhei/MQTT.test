#ifndef _DEFAULT_PARAM_HPP_
#define _DEFAULT_PARAM_HPP_


#include <stdint.h>


constexpr const char c_address[] = "tcp://213.33.180.130:1885";

constexpr const char c_client_id[] = "MQTT.test";

constexpr const uint8_t c_qos{ 1 };

constexpr const uint32_t c_timeout{ 10000 };

constexpr const uint8_t c_interval{ 20 };

constexpr const uint8_t c_clean_session{ 1 };

constexpr const char c_channel_p[] = "/hsu/client";

constexpr const char c_channel_s[] = "/hsu/server";


#endif // _DEFAULT_PARAM_HPP_
