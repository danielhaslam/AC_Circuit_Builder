#ifndef RESISTOR_H
#define RESISTOR_H

#include "component.h"

class Resistor : public Component
{
private:
    double resistance; // in Ohms [Ω] 

public:
    Resistor() = default; 
    Resistor(double resistance, std::string configuration, double frequency);
    Resistor(const Resistor& other); 
    Resistor(Resistor&& other);

    std::complex<double> find_impedance(double frequency) override;

    void set_parameter_value(double parameter_value) override {this->resistance = parameter_value;} // Setter function for resistance

    double get_parameter_value() const override;
    std::unique_ptr<Component> clone() const override; 

    ~Resistor(); // Destructor
};

#endif