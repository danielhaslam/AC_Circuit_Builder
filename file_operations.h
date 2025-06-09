#include<iostream>

#include "circuit.h"

#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

// Determine line entry components
std::string pad_node_number(int node_number);


// Manipulate files
std::pair<bool, Circuit> file_processed(const std::string& filename); 
void save_circuit_to_file(std::string& filename, Circuit& circuit);

#endif