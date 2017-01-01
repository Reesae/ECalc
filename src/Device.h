#ifndef DEVICE_H_
#define DEVICE_H_
#include <string>

namespace model {
// Constants
constexpr int DAY_PER_YEAR = 365;
constexpr int JOULES_TO_KWH = 3600000;

class Device {
  public:
    Device(std::string name, double power = 0.0, double time = 0.0, bool producer = false);
    Device(std::string name, double power = 0.0, std::string time = "00:00", bool producer = false);

    void calculate();

    inline std::string getName() {return m_name;}
    inline double getPower() {return m_power;}
    inline double getUsageTime() {return m_usage_time;}
    inline double getEnergy() {return m_energy;}
    inline double getEnergyInKwh() {return m_energy / JOULES_TO_KWH;}
    inline double getEnergyCost() {return m_energy_cost;}
    inline void setPower(double power) {m_power = power; calculate();}
    inline void setName(std::string name) {m_name = name;}
    void setUsageTime(std::string time);
    std::string getUsageTimeAsString();
    static void setPrice(double price);

  private:
    std::string m_name;
    double m_power;
    double m_usage_time;
    double m_energy;
    double m_energy_cost;
    bool m_producer;
    static double m_energy_cost_per_kwh;

};

} /* namespace model */

#endif /* DEVICE_H_ */
