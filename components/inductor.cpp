#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<complex>

#include "inductor.h"

const double pi{3.1415926536};

Inductor::Inductor(double inductance, std::string configuration, double frequency) : Component(configuration, frequency), inductance(inductance)
{
    if (inductance < 0) throw std::invalid_argument("Inductance value cannot be negative. The inductor was not created.");

    component_type = "Inductor"; 

    // std::cout<<"Constructor called for Inductor. "<<std::endl;
    std::cout<<this->component_type<<" added to the circuit in ";
    if(configuration == "P") std::cout<<"parallel."<<std::endl;
    else if(configuration == "S") std::cout << "series."<<std::endl;
}

Inductor::Inductor(const Inductor& other) : Component(other), inductance(other.inductance) 
{
    // std::cout<<"Copy constructor called for Inductor."<<std::endl;
}

Inductor::Inductor(Inductor&& other) : Component(std::move(other)), inductance(other.inductance)
{
    // std::cout<<"Move constructor called for Inductor."<<std::endl;
}

std::complex<double> Inductor::find_impedance(double frequency)
{
    std::complex<double> impedance_value{0.0, 2 * pi * frequency * inductance};  // Impedance of an inductor is imaginary: Z_I = i * ω * L.
    return impedance_value; 
}

double Inductor::get_parameter_value() const {return this->inductance;}

std::unique_ptr<Component> Inductor::clone() const {return std::make_unique<Inductor>(*this);} 

Inductor::~Inductor()
{
   // std::cout<<"Destructor called for Inductor."<<std::endl;
} // Destructor