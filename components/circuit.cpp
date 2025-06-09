#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<complex>

#include "circuit.h"
#include "../component_functions.h"
#include "component.h"


std::string find_component_id(Circuit& circuit, const std::string& component_type); 
std::pair<int, int> find_nodes(Circuit& circuit, Component& new_component);


Circuit::Circuit(std::string configuration, double frequency):
Component(configuration, frequency), number_of_components(0), number_of_resistors(0), number_of_inductors(0), number_of_capacitors(0), number_of_subcircuits(0)
{
    component_type = "Circuit"; 
    // std::cout<<"Constructor called for Circuit."<<std::endl;
}


Circuit::Circuit(const Circuit& other): // Copy constructor
Component(other.configuration, other.frequency), number_of_components(other.number_of_components), number_of_resistors(other.number_of_resistors), number_of_inductors(other.number_of_inductors), 
number_of_capacitors(other.number_of_capacitors), number_of_subcircuits(other.number_of_subcircuits)
{
    // std::cout<<"Copy constructor called for Circuit."<<std::endl;
    for(const auto& component : other.components) components.push_back(component->clone()); // Create new unique pointers for each component
} 


Circuit::Circuit(Circuit&& other):  // Move constructor
Component(other.configuration, other.frequency), number_of_components(other.number_of_components), number_of_resistors(other.number_of_resistors), number_of_inductors(other.number_of_inductors), 
number_of_capacitors(other.number_of_capacitors), number_of_subcircuits(other.number_of_subcircuits), components(std::move(other.components))
{
    // std::cout<<"Move constructor called for Circuit."<<std::endl;

    other.number_of_components = 0;
    other.number_of_resistors = 0;
    other.number_of_inductors = 0;
    other.number_of_capacitors = 0;
    other.number_of_subcircuits = 0;
    other.frequency = 0.0;
    other.components.clear(); // Empty other circuit
} 

Circuit& Circuit::operator=(const Circuit& other) // Copy assignment operator
{
    if (this == &other) return *this; // self-assignment

    this->configuration = other.configuration; // Manually copy base class members
    this->frequency = other.frequency;

    number_of_components = other.number_of_components;
    number_of_resistors = other.number_of_resistors;
    number_of_inductors = other.number_of_inductors;
    number_of_capacitors = other.number_of_capacitors;
    number_of_subcircuits = other.number_of_subcircuits;

    components.clear(); // Clear existing components
    for (const auto& component : other.components)
    {
        components.push_back(component->clone()); // Deep copy each component
    }

    return *this;
}

Circuit& Circuit::operator=(Circuit&& other) noexcept // Move assignment operator
{
    if (this == &other) return *this; // self-assignment

    this->configuration = std::move(other.configuration); // Move base class members
    this->frequency = other.frequency;

    number_of_components = other.number_of_components;
    number_of_resistors = other.number_of_resistors;
    number_of_inductors = other.number_of_inductors;
    number_of_capacitors = other.number_of_capacitors;
    number_of_subcircuits = other.number_of_subcircuits;

    components = std::move(other.components); // Move components

    other.number_of_components = 0;
    other.number_of_resistors = 0;
    other.number_of_inductors = 0;
    other.number_of_capacitors = 0;
    other.number_of_subcircuits = 0;
    other.frequency = 0.0;
    other.components.clear(); // Clear the moved-from object's components

    return *this;
}

void Circuit::set_frequency(double frequency)
{
    if(frequency < 0) throw std::invalid_argument("Frequency cannot be negative. The frequency was not set.");

    if(components.size() != 0)
    {
        this->frequency = frequency; // Set the frequency of the circuit
        for (auto& component : components) 
        {
            component->set_frequency(frequency); 
            component->set_impedance(component->find_impedance(frequency));
        } // Set the frequency of each component in the circuit
    }
    else std::cout<<"No components in the circuit. Frequency not set."<<std::endl; // If there are no components, frequency cannot be set
}


std::string Circuit::get_filename() const {return filename;} // Getter functions
std::vector<std::unique_ptr<Component>>& Circuit::get_components() {return components;}
double Circuit::get_frequency() const {return frequency;} 
double Circuit::get_parameter_value() const {return 0.0;}
int Circuit::get_number_of_components() const {return number_of_components;} 
int Circuit::get_number_of_resistors() const {return number_of_resistors;} 
int Circuit::get_number_of_inductors() const {return number_of_inductors;} 
int Circuit::get_number_of_capacitors() const {return number_of_capacitors;}
int Circuit::get_number_of_subcircuits() const {return number_of_subcircuits;} 


void Circuit::set_filename(std::string filename) {this->filename = filename;} // Set the filename for the circuit

void Circuit::add_component(std::unique_ptr<Component> component)
{
    component->set_component_id(find_component_id(*this, component->get_component_type())); // Set the component ID
    std::pair<int, int> nodes{find_nodes(*this, *component)}; // Find the start and end nodes for the component
    component->set_start_node(nodes.first); 
    component->set_end_node(nodes.second);

    components.push_back(std::move(component)); // Add the component to the vector of components
    number_of_components++; // Increment the number of components in the circuit

    if (components.back()->get_component_type() == "Resistor") number_of_resistors++;
    else if (components.back()->get_component_type() == "Inductor") number_of_inductors++;
    else if (components.back()->get_component_type() == "Capacitor") number_of_capacitors++;
    else if (components.back()->get_component_type() == "Circuit") number_of_subcircuits++; // Increment the number of sub-circuits
    else throw std::invalid_argument("Component type is invalid. The component was not added to the circuit."); // Handle invalid component types

    for(auto& component : components) // Set the frequency and impedance for each component
    {
        std::cout<<"Component type: "<<component->get_component_type()<<std::endl;
    }
} 


std::complex<double> Circuit::find_impedance(double frequency) 
{
    while(frequency <= 0) 
    {
        std::cout<<"Frequency must be a positive value. Please set the frequency of the circuit before calculating the impedance."<<std::endl;
        return{0.0, 0.0}; // Return zero impedance if frequency isn't valid
    }

    if(components.size() == 0)
    {
        std::cout<<"There are components in the circuit."<<std::endl;
        return{0.0, 0.0}; // Return zero impedance if there are no components
    }

    std::complex<double> impedance{0.0};

    for(auto& component : components)
    {
        if(component->get_configuration() == "S") // Series
        {
            impedance += component->find_impedance(component->get_frequency()); // Add the impedance of the component to the total impedance
        }
        else if(component->get_configuration() == "P") // Parallel
        {
            if(std::abs(impedance) == 0.0) impedance = component->find_impedance(component->get_frequency()); // If total impedance is zero, set it to the impedance of the first component
            else impedance = 1.0 / (1.0 / impedance + 1.0 / component->find_impedance(component->get_frequency())); // Calculate the total impedance in parallel
        }
        else throw std::invalid_argument("Component configuration is invalid. The total impedance was not calculated.");
    }
    if (impedance.imag() < 0)
        std::cout<<"Total impedance of the circuit is: "<<impedance.real()<<" - "<<std::abs(impedance.imag())<<"i ("<<std::abs(impedance)<<" magnitude) Ohms."<<std::endl;
    else
        std::cout<<"Total impedance of the circuit is: "<<impedance.real()<<" + "<<impedance.imag()<<"i ("<<std::abs(impedance)<<" magnitude) Ohms."<<std::endl;

    std::cout<<"Total phase difference of the circuit is: "<<components.back()->get_phase_difference()<<" radians."<<std::endl; // Display the total phase difference

    return impedance;
}


void Circuit::display_circuit_info() const
{
    std::cout<<"Displaying the circuit information..."<<std::endl;
    for(auto& component : components)
    {
        std::cout<<"Component type: "<<component->get_component_type()<<std::endl;
        if(component->get_component_type() != "Circuit") std::cout<<"Parameter value: "<<component->get_parameter_value()<<std::endl;
        std::cout<<"Start node: "<<component->get_start_node()<<std::endl;
        std::cout<<"End node: "<<component->get_end_node()<<std::endl;
        std::cout<<"Configuration: "<<component->get_configuration()<<std::endl;
        std::cout<<"--------------------------------------"<<std::endl;
    }
}


std::unique_ptr<Component> Circuit::clone() const 
{
    return std::make_unique<Circuit>(*this); // Create a new unique pointer to the cloned circuit
}


Circuit::~Circuit() // Destructor
{
   // std::cout<<"Destructor called for Circuit."<<std::endl;
} 