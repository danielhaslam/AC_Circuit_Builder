#ifndef COMPONENT_H
#define COMPONENT_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include<complex>

class Component
{
protected:
    std::string component_type;
    std::string component_id;
    int start_node; int end_node; // start and end node indexes, to aid with circuit configuration 
    std::string configuration; // series ("S") or parallel ("P"), to aid with circuit configuration
    double frequency; // in Hertz [Hz] - so that ω = 2πf
    std::complex<double> impedance;

public:
    Component(std::string configuration_choice, double frequency_choice); // Defined constructor
    Component(const Component& other); // Copy constructor
    Component(Component&& other); // Move constructor

    virtual std::complex<double> find_impedance(double frequency) = 0; 

    void set_component_id(std::string component_id); // Setters
    void set_configuration(std::string configuration);
    void set_start_node(double start_node); 
    void set_end_node(double end_node); 
    void set_frequency(double frequency);
    void set_impedance(std::complex<double> impedance);

    virtual void set_parameter_value(double parameter_value) = 0; 

    std::string get_component_type() const; // Getters
    std::string get_component_id() const; 
    std::string get_configuration() const;
    double get_frequency() const;
    int get_start_node() const;
    int get_end_node() const;
    std::complex<double> get_impedance() const; 

    virtual double get_impedance_magnitude() const; // Pure virtual getters
    virtual double get_phase_difference() const;
    
    virtual double get_parameter_value() const = 0; 
    virtual std::unique_ptr<Component> clone() const = 0;

    virtual ~Component() = default; // Destructor
};


#endif