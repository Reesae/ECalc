#include "Device.h"

namespace model {

double Device::m_energy_cost_per_kwh = 0.6;

Device::Device(std::string name, double power, double time, bool producer)
  : m_name(name), m_power(power), m_usage_time(time), m_producer(producer) {
  calculate();
}

Device::Device(std::string name, double power, std::string time, bool producer)
  : m_name(name), m_power(power), m_producer(producer) {
  setUsageTime(time);
}

void Device::calculate() {
  m_energy = m_power * m_usage_time * DAY_PER_YEAR;
  m_energy_cost = (m_energy/JOULES_TO_KWH) * m_energy_cost_per_kwh;
}

void Device::setUsageTime(std::string time) {
  if (std::isdigit(time[0]) && std::isdigit(time[1]) &&
      std::isdigit(time[3]) && std::isdigit(time[4]) && time[2] == ':') {
    double sec = 36000 * static_cast<int>(time[0] - '0') + 3600 * static_cast<int>(time[1] - '0') + 600 * static_cast<int>(time[3] - '0') + 60 * static_cast<int>(time[4] - '0');
    if (m_usage_time == sec) {
      return;
    } else {
      m_usage_time = sec;
      calculate();
    }
  }
}

std::string Device::getUsageTimeAsString() {
  std::string time;
  time += std::to_string(static_cast<int>(m_usage_time / 36000));
  time += std::to_string(static_cast<int>((m_usage_time / 3600)) % 10);
  time += ':';
  time += std::to_string(static_cast<int>(m_usage_time / 600) % 6);
  time += std::to_string(static_cast<int>(m_usage_time / 60) % 10);
  return time;

}

void Device::setPrice(double price) {
  m_energy_cost_per_kwh = price;
}


} /* namespace model */
