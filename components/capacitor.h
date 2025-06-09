#ifndef CAPACITOR_H
#define CAPACITOR_H     

#include "component.h"

class Capacitor : public Component
{
private:
    double capacitance; // in Farads [F]

public:
    Capacitor() = default; 
    Capacitor(double capacitance, std::string configuration, double frequency);
    Capacitor(const Capacitor& other); 
    Capacitor(Capacitor&& other);

    std::complex<double> find_impedance(double frequency) override;

    void set_parameter_value(double parameter_value) override {this->capacitance = parameter_value;} // Setter function for capacitance

    double get_parameter_value() const override;
    std::unique_ptr<Component> clone() const override; 

    ~Capacitor(); // Destructor
};

#endif
