#include<iostream>

#include "circuit.h"

#ifndef MENU_INTERFACE_H
#define MENU_INTERFACE_H

// Display the menu options
void create_introduction_menu();
void create_circuit_menu(int& circuit_level); // Circuit menu display depends on whether in main circuit or sub-circuit
void choose_component_menu();

// Generalise capitalisation of input
std::string find_uppercase(const std::string& user_input);

// Query user for inputs
std::string get_introduction_choice();
std::string get_circuit_choice(int& circuit_level);
std::string get_component_choice();

std::string get_filename(std::string& getting_filename_status);
std::pair<std::string, std::string> get_component_units(const std::string& component_type);
double get_parameter_value(const std::string& component_type);
double get_user_frequency(double frequency_value);

Circuit validate_file(std::string filename); 

// Give circuit information
void display_circuit(Circuit& circuit);
void display_circuit_info(Circuit& circuit);

#endif
