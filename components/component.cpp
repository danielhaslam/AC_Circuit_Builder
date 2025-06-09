#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<complex>

#include "component.h"

Component::Component(std::string configuration_choice, double frequency_choice): // Defined constructor
    frequency(frequency_choice), impedance(0., 0.), configuration(configuration_choice) {}


Component::Component(const Component& other): // Copy constructor
    component_type(other.component_type), frequency(other.frequency), impedance(other.impedance),
    configuration(other.configuration), start_node(other.start_node), end_node(other.end_node), component_id(other.component_id) {}


Component::Component(Component&& other): // Move constructor
    component_type(other.component_type), frequency(other.frequency), impedance(other.impedance),
    configuration(other.configuration), start_node(other.start_node), end_node(other.end_node), component_id(other.component_id) {}


void Component::set_component_id(std::string component_id) {this->component_id = component_id;} // Setter functions
void Component::set_configuration(std::string configuration) {this->configuration = configuration;}
void Component::set_start_node(double start_node) {this->start_node = start_node;}
void Component::set_end_node(double end_node) {this->end_node = end_node;}
void Component::set_frequency(double frequency)
{
    if(frequency < 0) throw std::invalid_argument("Frequency cannot be negative. The frequency was not set.");
    this->frequency = frequency;
}


void Component::set_impedance(std::complex<double> impedance) {this->impedance = impedance;} 


std::string Component::get_component_type() const {return this->component_type;}
std::string Component::get_component_id() const {return this->component_id;} 
std::string Component::get_configuration() const {return this->configuration;}
double Component::get_frequency() const {return this->frequency;} 
int Component::get_start_node() const {return this->start_node;} 
int Component::get_end_node() const {return this->end_node;} 
std::complex<double> Component::get_impedance() const {return this->impedance;} 


double Component::get_impedance_magnitude() const {return std::abs(this->impedance);} // Magnitude of impedance is the absolute value of the complex number.
double Component::get_phase_difference() const 
{
    if (impedance.real() == 0. && impedance.imag() == 0.) return 0.0; // If both real and imaginary parts are (for some reason) zero, the argument would be undefined.
    else return std::arg(impedance); // Phase difference = argument of the complex number
}

