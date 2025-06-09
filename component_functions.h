#include<iostream>

#define COMPONENT_FUNCTIONS_H
#ifndef COMPONENT_FUNCTIONS_H

std::pair<int, int> find_nodes(Circuit& circuit, Component& new_component);
std::string find_component_id(Circuit& circuit, std::string& component_type);

#endif 