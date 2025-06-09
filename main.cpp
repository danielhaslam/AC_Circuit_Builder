// Program to simulate the user-defined, incremental building of an AC circuit, comprised of resistors, capacitors, and inductors.
// The user can add components in series or parallel, set the frequency of the circuit, and calculate the total impedance of it.
// Author: Daniel Haslam. Student ID: 10833591. Date: 2025-05-11.

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<complex>

// Circuit components
#include "component.h"
#include "capacitor.h"
#include "inductor.h"
#include "resistor.h"
#include "circuit.h"

// Circuit functions
#include "component_functions.h"

// User functions
#include "interface_functions.h"
#include "file_operations.h"

// Integrate subcircuit functionality
// Integrate circuit display functionality

void run_circuit_menu(std::string& option_choice, std::string& configuration_choice, Circuit& main_circuit, int circuit_level, std::vector<std::unique_ptr<Circuit>>& sub_circuits)
{
    double frequency_set{0.0};
    std::string filename{" "};

    if(sub_circuits.empty()) sub_circuits.push_back(std::make_unique<Circuit>(main_circuit)); // So that the primary circuit will always be first in the sub_circuits hierarchy

    while(true)
    {
        create_circuit_menu(circuit_level); // Display the menu options
        option_choice = get_circuit_choice(circuit_level); // Get the user's choice

        if(option_choice == "S" || option_choice == "P") // Add component(s) in series or parallel
        {
            configuration_choice = option_choice; // Store the configuration choice

            choose_component_menu(); // Ask the user to choose a component to add to the circuit
            option_choice = get_component_choice();

            // Add the component to the circuit based on user choice
            if(option_choice == "R") main_circuit.add_component(std::make_unique<Resistor>(get_parameter_value("Resistor"), configuration_choice, frequency_set)); 
            else if(option_choice == "L") main_circuit.add_component(std::make_unique<Inductor>(get_parameter_value("Inductor"), configuration_choice, frequency_set)); 
            else if(option_choice == "C") main_circuit.add_component(std::make_unique<Capacitor>(get_parameter_value("Capacitor"), configuration_choice, frequency_set)); 
            else if(option_choice == "SUB") 
            {
                auto sub_circuit = std::make_unique<Circuit>(configuration_choice, frequency_set);
                sub_circuits.push_back(std::move(sub_circuit));
                main_circuit.add_component(std::make_unique<Circuit>(configuration_choice, frequency_set)); // Add a sub-circuit
                run_circuit_menu(option_choice, configuration_choice, *sub_circuit, circuit_level + 1, sub_circuits); // Run the menu for the sub-circuit created
            }
            else if(option_choice == "X") continue; // Exit back to main menu
        }

        else if(option_choice == "F") // Set frequency
        {
            if(circuit_level == 0)
            {
                frequency_set = get_user_frequency(frequency_set);
                main_circuit.set_frequency(frequency_set);
            }
            else std::cout<<"Frequency cannot be set for sub-circuits."<<std::endl; 
        }
            
        else if(option_choice == "C") // Calculate total impedance 
        {
            if(circuit_level == 0) main_circuit.set_impedance(main_circuit.find_impedance(main_circuit.get_frequency()));
            else std::cout<<"Impedance cannot be calculated for sub-circuits."<<std::endl;
        }
        
        else if(option_choice == "G") display_circuit_info(main_circuit); // Display circuit information

        else if(option_choice == "D") display_circuit(main_circuit);

        else if(option_choice == "SAVE") // Save circuit to file
        {
            if(filename == " ") filename = get_filename(option_choice); 
            save_circuit_to_file(filename, main_circuit);
        }

        else if(option_choice == "X") 
        {
            if(filename == " ") 
            {
                std::cout<<"Please save the circuit to a file before exiting."<<std::endl;
                std::cout<<"Enter a filename to save the circuit: "<<std::endl;
                filename = get_filename(option_choice);
                main_circuit.set_filename(filename);
                save_circuit_to_file(filename, main_circuit);
            }
            std::cout<<"Exiting back into parent circuit. "<<std::endl;
            sub_circuits.pop_back(); // Remove the last sub-circuit
            run_circuit_menu(option_choice, configuration_choice, *sub_circuits.back(), circuit_level - 1, sub_circuits); // Exit back to parent circuit
        }

        else if(option_choice == "EXIT") // Exit
        {
            std::cout<<"Exiting the program."<<std::endl;
            return;
        } 
    }
}

void run_introduction_menu(std::string& option_choice, std::string& configuration_choice, double& frequency_set)
{
    std::vector<std::unique_ptr<Circuit>> sub_circuits; // Initialize an empty vector for sub-circuits to track them when building the circuit

    create_introduction_menu(); // Display the introduction menu
    option_choice = get_introduction_choice(); // Get the user's choice

    if(option_choice == "N") // Create a new circuit
    {
        std::cout<<"Creating a new circuit."<<std::endl;
        Circuit new_circuit{"S", 0.0}; // Create new circuit
        run_circuit_menu(option_choice, configuration_choice,new_circuit, 0, sub_circuits);
    }
    else if(option_choice == "O") // Open an existing circuit file
    {
        std::string filename{get_filename(option_choice)}; // Get the filename from the user

        Circuit main_circuit{"S", 0.0}; // Declare main_circuit before the conditional blocks

        if(filename != " ") 
        {
            auto [success, circuit] {file_processed(filename)}; // Process the file and create the circuit
            if(success) main_circuit = std::move(circuit);
        } 

        run_circuit_menu(option_choice, configuration_choice, main_circuit, 0, sub_circuits);
    }
    else if(option_choice == "EXIT") // Exit
    {
        std::cout<<"Exiting the program."<<std::endl;
        return;
    }
}

int main()
{
    std::string option_choice; std::string configuration_choice; // Define in main so it remains accessible throughout the program
    double frequency_set{0.0}; 

    run_introduction_menu(option_choice, configuration_choice, frequency_set); // Run the introduction menu
    
    return 0;
}