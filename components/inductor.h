#ifndef INDUCTOR_H
#define INDUCTOR_H

#include "component.h"

class Inductor : public Component
{
private:
    double inductance; // in Henries [H] 

public:
    Inductor() = default; 
    Inductor(double inductance, std::string configuration, double frequency);
    Inductor(const Inductor& other); 
    Inductor(Inductor&& other);

    std::complex<double> find_impedance(double frequency) override;

    void set_parameter_value(double parameter_value) override {this->inductance = parameter_value;} // Setter function for inductance

    double get_parameter_value() const override; // Return the inductance value
    std::unique_ptr<Component> clone() const override; 

    ~Inductor(); // Destructor
};

#endif