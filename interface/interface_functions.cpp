#include<iostream> 
#include <fstream>
#include <iomanip>

#include "interface_functions.h"
#include "../file_operations.h"

// Display the menu options

void create_introduction_menu()
{
    std::cout<<"--------------------------------------------------"<<std::endl;
    std::cout<<"--------------------------------------------------"<<std::endl;
    std::cout<<"Welcome to the circuit simulator!"<<std::endl;
    std::cout<<"This program simulates a circuit with resistors, inductors, and capacitors."<<std::endl;
    std::cout<<"You may add components, or sub-circuits of components, in series or parallel, set the frequency of the circuit, and calculate the total impedance of it."<<std::endl;
    std::cout<<"--------------------------------------------------"<<std::endl;
    std::cout<<"--------------------------------------------------"<<std::endl;
    std::cout<<"N: Create new circuit"<<std::endl;
    std::cout<<"O: Open circuit file"<<std::endl;
    std::cout<<"EXIT: Exit"<<std::endl;
    std::cout<<"Please choose an option: ";
}


void create_circuit_menu(int& circuit_level)
{
    if(circuit_level > 0) std::cout<<"Level "<<circuit_level<<" sub-circuit."<<std::endl; // Display the current circuit level for user to keep track

    std::cout<<"--------------------------------------------------"<<std::endl;
    std::cout<<"S: Add component(s) in series"<<std::endl;
    std::cout<<"P: Add component(s) in parallel"<<std::endl;
    if(circuit_level == 0) // If in main menu
    {
        std::cout<<"F: Set frequency of circuit"<<std::endl;
        std::cout<<"C: Calculate total impedance of circuit"<<std::endl;
        std::cout<<"G: Give circuit component information"<<std::endl;
        std::cout<<"D: Display the circuit"<<std::endl;
    }
    else if(circuit_level > 0) // If in sub-circuit menu
    {
        std::cout<<"X: Finish sub-circuit"<<std::endl;
    }
    std::cout<<"SAVE: Save circuit to file"<<std::endl;
    std::cout<<"EXIT: Exit"<<std::endl;
    std::cout<<"--------------------------------------------------"<<std::endl;
    std::cout<<"Please choose an option: ";
}


void choose_component_menu()
{
    std::cout<<"--------------------------------------------------"<<std::endl;
    std::cout<<"R: Resistor"<<std::endl;
    std::cout<<"L: Inductor"<<std::endl;
    std::cout<<"C: Capacitor"<<std::endl;
    std::cout<<"SUB: Sub-circuit"<<std::endl;
    std::cout<<"X: Back to main menu"<<std::endl;
    std::cout<<"--------------------------------------------------"<<std::endl;
    std::cout<<"Please choose a component to add to the circuit: ";
}

// Generalise capitalisation of input

std::string find_uppercase(const std::string& user_input)
{
    std::string uppercase_input{user_input};
    for(char& character : uppercase_input) character = toupper(character); // Convert each letter to uppercase
    return uppercase_input; 
}

// Query user for inputs

std::string get_introduction_choice()
{
    std::string option_choice; 
    std::cin>>option_choice; // Get the user's choice

    if(find_uppercase(option_choice) == "N") return "N"; // Create new circuit
    else if(find_uppercase(option_choice) == "O") return "O"; // Open circuit file
    else if(find_uppercase(option_choice) == "EXIT") return "EXIT"; // Exit
    else
    {
        std::cout<<"Invalid option. Please try again."<<std::endl;
        return get_introduction_choice(); // Recursively call the function until a valid option is chosen
    }
}


std::string get_circuit_choice(int& circuit_level)
{
    std::string option_choice; 
    std::cin>>option_choice; // Get the user's choice

    if(find_uppercase(option_choice) == "S") return "S"; // Add component(s) in series
    else if(find_uppercase(option_choice) == "P") return "P"; // Add component(s) in parallel
    else if(find_uppercase(option_choice) == "SAVE") return "SAVE"; // Save circuit to file
    else if(find_uppercase(option_choice) == "EXIT") return "EXIT"; // Exit

    if(circuit_level == 0) // If in main menu
    {
        if(find_uppercase(option_choice) == "F") return "F"; // Set frequency
        else if(find_uppercase(option_choice) == "C") return "C"; // Calculate total impedance
        else if(find_uppercase(option_choice) == "G") return "G"; // Give component information
        else if(find_uppercase(option_choice) == "D") return "D"; // Display circuit
    }

    else if(circuit_level > 0) // If in sub-circuit menu
    {
        if(find_uppercase(option_choice) == "X") return "X"; // Finish sub-circuit
    }
    
    else
    {
        std::cout<<"Invalid option. Please try again."<<std::endl;
        return get_circuit_choice(circuit_level); // Recursively call the function until valid option is chosen
    }

    return " ";
}


std::string get_component_choice()
{
    std::string option_choice; 
    std::cin>>option_choice; // Get the user's choice

    if(find_uppercase(option_choice) == "R") return "R"; // Resistor
    else if(find_uppercase(option_choice) == "L") return "L"; // Inductor
    else if(find_uppercase(option_choice) == "C") return "C"; // Capacitor
    else if(find_uppercase(option_choice) == "SUB") return "SUB"; // Add sub-circuit
    else if(find_uppercase(option_choice) == "X") return "X"; // Back to main menu
    else
    {
        std::cout<<"Invalid option. Please try again."<<std::endl;
        return get_component_choice(); // Recursively call the function until valid option is chosen
    }
}


std::string get_filename(std::string& getting_filename_status)
{
    std::string filename; 
    if(getting_filename_status == "SAVE") std::cout<<"Please enter the filename to save the circuit (must end with .txt): "<<std::endl; // If called to save to file
    else if(getting_filename_status == "O") std::cout<<"Please enter the filename to open the circuit (must end with .txt): "<<std::endl; // If called to open file
    
    while(true)
    {
        std::cin>>filename; // Get the filename from the user

        if(filename.length() < 4 || filename.substr(filename.length() - 4) != ".txt") // Check if the filename ends with .txt
        {
            std::cout<<"Invalid filename. Please enter a valid filename (must end with .txt): "<<std::endl;
        }

        else if(filename.find_first_of("/\\:*?\"<>|") != std::string::npos) // Check for invalid characters in the filename
        {
            std::cout<<"Invalid filename. Please enter a valid filename (no special characters): "<<std::endl;
        }

        else if(filename.find(" ") != std::string::npos) // Check for spaces in the filename
        { 
            std::cout<<"Invalid filename. Please enter a valid filename (no spaces): "<<std::endl;
        }

        else break; // Valid filename
    }

    if(getting_filename_status == "O")
    {
        std::ifstream file_check(filename);
        if(!file_check.good()) // Check if the file can be opened
        {
            std::cout<<"File cannot be opened. A new circuit will be created. "<<std::endl;
            return " ";
        }
    }
    
    return filename; // Check if the file already exists
}

Circuit validate_file(std::string filename)
{
    std::ifstream file_check(filename);
    if(file_check.good()) // Checks if file exists and is readable
    {
        std::pair<bool, Circuit> result{file_processed(filename)}; // Process the file
        if(result.first)
        {
            std::cout<<"File successfully read to the program."<<std::endl;
            return result.second; // Process the file and return the circuit
        }
        else
        {
            std::cout<<"Error occurred processing the file. Empty circuit created."<<std::endl;
            return result.second;
        }
    }
    else
    {
        std::cout<<"File does not exist. Creating a new file."<<std::endl;
    }

    return Circuit{"S", 0}; // Return a pair with a default Circuit and a false flag
}


std::pair<std::string, std::string> get_component_units(const std::string& component_type)
{
    if(component_type == "Inductor")
        return {"inductance", "Henries (H)"};
    else if(component_type == "Resistor")
        return {"resistance", "Ohms (Ω)"};
    else if(component_type == "Capacitor")
        return {"capacitance", "Farads (F)"};
    else
        return {"", ""}; // Return empty strings if the component type is not recognised
}


double get_parameter_value(const std::string& component_type)
{
    double parameter_value{0.0};
    auto [parameter_name, units] = get_component_units(component_type);
    std::cout<<"Please enter the "<<parameter_name<<" of the "<<component_type<<" (in "<<units<<"): "<<std::endl;
    while(true)
    {
        std::cin>>parameter_value;

        if(std::cin.fail() || parameter_value < 0) // If invalid input type, or parameter value is negative
        {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(1000, '\n'); // Discard invalid input
            std::cout<<"Invalid value. Please try again: "<<std::endl;
        }
        else break; // Valid input
    }
    
    return parameter_value;
}


double get_user_frequency(double frequency_value)
{
    std::cout<<"Please enter the frequency of the circuit, in Hz: "<<std::endl;

    while(true)
    {
        std::cin>>frequency_value;

        if (std::cin.fail()) // Check if input is invalid
        {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(1000, '\n'); // Discard invalid input
            std::cout<<"Invalid input. Please enter a numeric value for the frequency: "<<std::endl;
        }
        else if (frequency_value <= 0) std::cout<<"Invalid value: frequency must be greater than zero. Please try again: "<<std::endl;

        else break; // Valid input
    }

    return frequency_value;
}


// Display the circuit

void display_circuit(Circuit& circuit)
{
    std::string circuit_representation;

    int component_index{0}; // To handle first two components differently
    std::string previous_configuration{" "}; // To track the configuration of the previous component

    std::string component_id;
    std::string component_configuration;

    for(auto& component : circuit.get_components())
    {
        component_id = component->get_component_id();
        component_configuration = component->get_configuration();

        if(component_index == 0) circuit_representation = component_id;
        else if(component_index == 1) circuit_representation += (" --- " + component_id);

        else
        {
            if(previous_configuration == "S" && component_configuration == "S") // If both components are in series
            {
                circuit_representation += (" --- " + component_id);
            }
            else if(previous_configuration == "P" && component_configuration == "S") 
            {
                circuit_representation = "{" + circuit_representation + "}" + " --- " + component_id; // Enclose previous series components in brackets
            }
            else if(component_configuration == "P") // If previous is parallel and current is series
            {
                circuit_representation = "{" + circuit_representation + "}" + " // " + component_id;
            }
        }

        component_index++;
        previous_configuration = component->get_configuration();
    }

    std::cout<<"Circuit: "<<std::endl;
    std::cout<<"--------------------------------------------------"<<std::endl;
    std::cout<<circuit_representation<<std::endl;
    std::cout<<"--------------------------------------------------"<<std::endl;

    return;
}


void display_circuit_info(Circuit& circuit) 
{
    std::ostringstream oss;

    // Header line
    oss<<std::left<<std::setw(15)<<"Type"<<std::setw(15)<<"Parameter"<<std::setw(12)<<"Start Node"<<std::setw(10)<<"End Node"<<std::setw(15)<<"Config"<<"\n";

    oss<<std::string(67, '-')<<"\n"; // Divider line

    // Rows
    for (auto& component : circuit.get_components())
    {           
        std::string param{(component->get_component_type() != "Circuit") ? std::to_string(std::round(component->get_parameter_value() * 1000.0) / 1000.0) : "-"};
        
        std::string config;
        switch (component->get_configuration()[0]) // Check the first character of the configuration
        {
            case 'S':
            {
                config = "Series";
                break;  
            } 
            case 'P':
            {
                config = "Parallel";
                break;
            }
            default:
                config = "Unknown";
                break;
        }

        oss<<std::left<<std::setw(15)<<component->get_component_type()<<std::setw(15)<<param<<std::setw(12)<<component->get_start_node()<<std::setw(10)<<component->get_end_node()<<std::setw(15)<<config<<"\n";
    }

    std::cout<<oss.str();
}
