#ifndef CIRCUIT_H
#define CIRCUIT_H

#include<iostream>
#include<vector>
#include<memory>
#include<complex>

#include "component.h"

class Circuit: public Component // to be instantiated at the beginning of the program, and then used to add components to the circuit.
{
private:
    std::vector<std::unique_ptr<Component>> components; 
    int number_of_components; 
    int number_of_resistors; int number_of_inductors; int number_of_capacitors; // Necessary for notational purposes in the data file
    int number_of_subcircuits; 
    std::string filename;

public:
    Circuit() = default; // Default constructor
    Circuit(std::string configuration, double frequency); // Constructor with parameters
    Circuit(const Circuit& other); // Copy constructor
    Circuit(Circuit&& other); // Move constructor

    Circuit& operator=(const Circuit& other); // Copy assignment operator
    Circuit& operator=(Circuit&& other) noexcept; // Move assignment operator

    void set_frequency(double frequency); // Setter function for frequency

    std::string get_filename() const; // Getter functions
    std::vector<std::unique_ptr<Component>>& get_components();
    double get_frequency() const; 
    int get_number_of_components() const; 
    int get_number_of_resistors() const; 
    int get_number_of_inductors() const; 
    int get_number_of_capacitors() const;
    int get_number_of_subcircuits() const;
    
    void set_filename(std::string filename);

    void add_component(std::unique_ptr<Component> component);
    std::complex<double> find_impedance(double frequency) override; // Find the impedance of the circuit
    void display_circuit_info() const; // Display the circuit information

    void set_parameter_value(double parameter_value) override {} // Not of use to Circuit
    
    double get_parameter_value() const override; // Not of use to Circuit
    std::unique_ptr<Component> clone() const override; 
    
    ~Circuit(); // Destructor
};

#endif