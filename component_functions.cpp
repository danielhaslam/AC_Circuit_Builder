#include<iostream> 
#include<fstream>
#include<sstream>

#include "component_functions.h"
#include "component.h"
#include "circuit.h"

std::pair<int, int> find_nodes(Circuit& circuit, Component& new_component)
{
    std::pair<int, int> nodes;
    
    if(circuit.get_number_of_components() == 0) return {0, 1}; // Default starting nodes when building a new circuit

    int last_component_end_node{circuit.get_components().back()->get_end_node()}; // Access the last component pointer and retrieve its end node
    
    if(new_component.get_configuration() == "S")
    {
        nodes.first = last_component_end_node; //  "Series components join from the end of the circuit"
        nodes.second = last_component_end_node + 1; 
    }
    else if(new_component.get_configuration() == "P")
    {
        nodes.first = 0; // "Parallel components join from the beginning of the circuit"
        nodes.second = last_component_end_node; // "Parallel components join to the end of the circuit"
    }
    else std::invalid_argument("Invalid configuration. The component was not added to the circuit.");
  
    return nodes; 
}


std::string find_component_id(Circuit& circuit, const std::string& component_type)
{
    std::string component_code;
    if(component_type == "Inductor") component_code = "L";
    else if(component_type == "Resistor") component_code = "R";
    else if(component_type == "Capacitor") component_code = "C";
    else if(component_type == "Circuit") component_code = "SUB"; 
    else return ""; // Return an empty string if the component type is not recognized

    // Find the maximum number in the file associated with the component code, to find our new unique identifier for the component
    int max_number{0};
    if(component_code == "L") max_number = circuit.get_number_of_inductors();
    else if(component_code == "R") max_number = circuit.get_number_of_resistors();
    else if(component_code == "C") max_number = circuit.get_number_of_capacitors();
    else if(component_code == "SUB") max_number = circuit.get_number_of_subcircuits();

    return component_code + std::to_string(max_number + 1); // This is the final component code for the new line
}

