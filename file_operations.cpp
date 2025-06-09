#include<iostream> 
#include<fstream>
#include<sstream>

#include "file_operations.h"
#include "component.h"
#include "circuit.h"
#include "resistor.h"
#include "inductor.h"
#include "capacitor.h"

std::string pad_node_number(int node_number)
{
    std::string padded_number{std::to_string(node_number)};

    while(padded_number.length() < 3) padded_number = "0" + padded_number; // Pad the number with leading zeros to make it 3 digits
    return padded_number;
}


std::pair<bool, Circuit> file_processed(const std::string& filename)
{
    std::ifstream file_check(filename); // Open the file to check if it exists
    if (!file_check.is_open()) return {false, Circuit{"S", 0.0}}; // If file doesn't exist / can't be opened, return false and an empty circuit if the file cannot be opened

    Circuit circuit_made{"S", 0.0};
    std::string line;
    std::fstream file(filename, std::ios::in); // Open file for reading

    while (std::getline(file, line)) // Read each line of the file
    {
        std::istringstream iss(line);
        std::string component_id;
        int start_node, end_node;
        double parameter_value;
        std::string configuration;

        iss>>component_id; // Read the component ID

        if(component_id[0] == 'S') // If the component is a sub-circuit
        {
            std::string filename; 
            iss>>filename>>configuration; // Read the filename of the sub-circuit
            parameter_value = 0.0;

            // Process the sub-circuit file
            auto [success, sub_circuit] = file_processed(filename); // Recursive calling of the function to process sub-circuits (and any sub-circuit files within them!)

            if(!success)
            {
                throw std::invalid_argument("Error: Unable to process sub-circuit file " + filename + ". Please verify the filepath.");
                return {false, Circuit{"S", 0.0}}; // Return false and an empty circuit if the sub-circuit file cannot be processed
            }
            else
            {
                circuit_made.add_component(std::make_unique<Circuit>(configuration, 0.0));

                for(auto& component : sub_circuit.get_components())
                {
                    circuit_made.add_component(std::move(component));
                }
                sub_circuit.get_components().clear();
            }
        }

        else
        {
            iss>>start_node>>end_node>>parameter_value>>configuration; // Read the start node, end node, parameter value, and configuration

            if(component_id[0] == 'R') circuit_made.add_component(std::make_unique<Resistor>(parameter_value, configuration, 0.0)); // Add the component to the circuit
            else if(component_id[0] == 'L') circuit_made.add_component(std::make_unique<Inductor>(parameter_value, configuration, 0.0)); // Add the component to the circuit
            else if(component_id[0] == 'C') circuit_made.add_component(std::make_unique<Capacitor>(parameter_value, configuration, 0.0)); // Add the component to the circuit
            else
            {
                std::cerr<< "Error: Unknown component type in file: "<<component_id<<std::endl; // Handle unknown component types
                return {false, Circuit{"S", 0.0}}; // Return false and an empty circuit if an unknown component type is found
            }
        }
        
        circuit_made.get_components().back()->set_component_id(component_id); // Set the component ID
        circuit_made.get_components().back()->set_start_node(start_node); // Set the start node
        circuit_made.get_components().back()->set_end_node(end_node); // Set the end node

        std::cout<<"Component added: "<<component_id<<". Start Node: "<<start_node<<". End Node: "<<end_node<<". Parameter Value: "<<parameter_value<<". Configuration: "<<configuration<<std::endl;
    }

    file.close();
    return {true, circuit_made}; // Return true and the constructed circuit
}


void save_circuit_to_file(std::string& filename, Circuit& circuit)
{
    if(circuit.get_number_of_components() == 0) // Check if there are no components in the circuit
    {
        std::cout<<"No components in the circuit, so nothing was saved."<<std::endl;
        return;
    }

    std::fstream file(filename, std::ios::out | std::ios::trunc); // Open file for writing and clear its contents

    if(!file.is_open()) // Check if file opened successfully
    {
        throw std::invalid_argument("Error: Unable to open file " + filename + ". Please verify the filepath.");
        return;
    }

    for(auto& component : circuit.get_components()) // Write each component to the file iteratively
    {   // Write the component code, node numbers, and configuration to the file

        if(component->get_component_type() == "Circuit") 
        {
            std::cout<<"Circuit"<<std::endl;
            auto circuit_component = dynamic_cast<Circuit*>(component.get()); // So that filename is accessible
            file<<circuit_component->get_component_id()<<circuit_component->get_filename()<<" "<<circuit_component->get_configuration()<<std::endl; 
        }
        else file<<component->get_component_id()<<" "<<pad_node_number(component->get_start_node())<<" "<<pad_node_number(component->get_end_node())<<" "<<component->get_parameter_value()<<" "<<component->get_configuration()<<std::endl; 
    }

    file.close(); 
    std::cout<<"Components saved to file successfully."<<std::endl;
}