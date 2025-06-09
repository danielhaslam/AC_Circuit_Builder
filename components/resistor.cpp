#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<complex>

#include "resistor.h"

Resistor::Resistor(double resistance, std::string configuration, double frequency) : Component(configuration, frequency), resistance(resistance)
{
    if (resistance < 0) throw std::invalid_argument("Resistance cannot be negative. The resistor was not created.");

    component_type = "Resistor";

    // std::cout<<"Constructor called for Resistor. "<<std::endl;
    std::cout<<this->component_type<<" added to the circuit in ";
    if(configuration == "P") std::cout<<"parallel."<<std::endl;
    else if(configuration == "S") std::cout << "series."<<std::endl;
}


Resistor::Resistor(const Resistor& other) : Component(other), resistance(other.resistance) 
{
    // std::cout<<"Copy constructor called for Resistor."<<std::endl;
}


Resistor::Resistor(Resistor&& other) : Component(std::move(other)), resistance(other.resistance)
{
    // std::cout<<"Move constructor called for Resistor."<<std::endl;
}


std::complex<double> Resistor::find_impedance(double frequency)
{
    std::complex<double> impedance_value{resistance, 0.0};
    set_impedance(impedance_value);
    return impedance_value; // Impedance of a resistor is purely real: Z_R = R.
}


double Resistor::get_parameter_value() const {return this->resistance;}

std::unique_ptr<Component> Resistor::clone() const {return std::make_unique<Resistor>(*this);}

Resistor::~Resistor() // Destructor
{
   // std::cout<<"Destructor called for Resistor."<<std::endl;
} 