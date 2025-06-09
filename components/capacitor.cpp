#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<complex>

#include "capacitor.h"

const double pi{3.1415926536}; // Define pi as a constant for calculations

Capacitor::Capacitor(double capacitance, std::string configuration, double frequency) : Component(configuration, frequency), capacitance(capacitance)
{
    if (capacitance < 0) throw std::invalid_argument("capacitance value cannot be negative. The Capacitor was not created.");

    component_type = "Capacitor"; 

    // std::cout<<"Constructor called for Capacitor."<<std::endl;
    std::cout<<this->component_type<<" added to the circuit in ";
    if(configuration == "P") std::cout<<"parallel."<<std::endl;
    else if(configuration == "S") std::cout << "series."<<std::endl;
}


Capacitor::Capacitor(const Capacitor& other) : Component(other), capacitance(other.capacitance) 
{
    // std::cout<<"Copy constructor called for Capacitor."<<std::endl;
}


Capacitor::Capacitor(Capacitor&& other) : Component(std::move(other)), capacitance(other.capacitance)
{
    // std::cout<<"Move constructor called for Capacitor."<<std::endl;
}


std::complex<double> Capacitor::find_impedance(double frequency)
{
    std::complex<double> impedance_value{0.0, -1.0 / (2 * pi * frequency * capacitance)};
    set_impedance(impedance_value);
    return impedance_value; // Impedance of a capacitor is imaginary: Z_C = -i / (ω * C).
}


double Capacitor::get_parameter_value() const {return this->capacitance;} 

std::unique_ptr<Component> Capacitor::clone() const {return std::make_unique<Capacitor>(*this);} 

Capacitor::~Capacitor() // Destructor
{
   // std::cout<<"Destructor called for Capacitor."<<std::endl;
} 