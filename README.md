# AC Circuit Builder 

## Background

This program allows the user to incrementally build an AC circuit, comprised of inductors, capacitors and resistors. These can be arranged in series, or parallel, with the circuit that already exists. Here, the implementation of nested sub-circuit functionality allows, in principle, the building of any possible circuit arrangement, using this incremental approach.

## Theory

When calculating the complex impedance of an AC circuit, consisting of Resistors (R), capacitors (C) and inductors (L), the following equations must be used: 

Resistor: $Z_R = R$ \
Capacitor: $Z_C = \frac{1}{j\omega C}$ \
Inductor: $Z_L = j\omega L$

where ω denotes the angular frequency of the AC source, $R$ the resistance, $C$ the capacitance, $L$ the inductance, and $j$ the imaginary number. 

Then, when adding the impedances of different components, adding in series goes as:

$Z_{tot} = Z_1 + Z_2 + Z_3 + \ldots $ 

while adding in parallel goes as: 

$\frac{1}{Z_{tot}} = \frac{1}{Z_1} + \frac{1}{Z_2} + \frac{1}{Z_3} + \ldots $

These equations serve as the basis by which circuit impedance is calculated. 


## How To Use

To begin, type "make" into the terminal, and the makefile will handle the compilation command. Then, typing "./a.o" will begin the program.

From here, the user can choose to begin a new file, by typing "N", or open an existing file, by typing "O". 
In the former case, the circuit menu will be accessed directly.
In the latter case, a filename will be required for input. If the file cannot be read, either due to non-existence or some format problem, the program will continue to the circuit menu with a new circuit. 

The circuit menu is comprised of the items required to build a circuit:
- __S/P__: Add a component of choice in series, or parallel, to the existing circuit (if adding the first component, choice of S or P does not make a difference, naturally).
- __F__: Set the desired frequency of the voltage source of the circuit
- __C__: Calculate the total impedance of the circuit, according to the governing circuit equations. This will output the complex value, the total magnitude of it, and the phase shift attributed to the impedance.
- __G__: Provide, in tabular format, all of the data which describes the circuit.
- __D__: Provide a quasi-graphical representation of the circuit, using symbols.
- __SAVE__: Save the circuit to a file - whose filename will be prompted if not already set. 
- __EXIT__: Quit the program.

Note that all inputs are NOT case sensitive.

Menu items are provided so that all choices above should be clear.

## Example of Functionality

Circuit file format:

| Component | Node 1 | Node 2 | Value | Type |
|-----------|--------|--------|-------|------|
| R1        | 000    | 001    | 4     | S    |
| R2        | 000    | 001    | 2     | P    |
| C1        | 000    | 001    | 5.2   | P    |
| R3        | 001    | 002    | 13    | S    |

- Row 1: provides a unique identifier for the component, with the letter representing the circuit component (R = resistor, L = inductor, C = capacitor), and the number
- Row 2: provides a beginning node for the component - this is of use in SPICE netlists.
- Row 3: provides a beginning node for the component - this is of use in SPICE netlists.
- Row 4: provides a parameter value for the component (units: resistor: Ohms, inductor: Henries, capacitor: Farads).
- Row 5: provides the configuration (S = series, P = parallel), relative to all entries above it.

Circuit impedance: $13.0007 - 0.0305906i$ ($13.0007$ magnitude) Ohms. \
Consequent phase shift: ~0 radians.

Example display from the above file example: \
*{{R1 --- R2} // C1} --- R3*






