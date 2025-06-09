This program allows the user to incrementally build an AC circuits, comprised of inductors, capacitors and resistors. These can be arranged in series, or parallel, with the circuit that already exists.

###

HOW TO USE:

To begin, type "make" into the terminal, and the makefile will handle the compilation command. Then, typing "./a.o" will begin the program.

From here, the user can choose to begin a new file, by typing "N", or open an existing file, by typing "O". 
In the former case, the circuit menu will be accessed directly.
In the latter case, a filename will be required for input. If the file cannot be read, either due to non-existence or some format problem, the program will continue to the circuit menu with a new circuit. 

The circuit menu is comprised of the items required to build a circuit:
- S/P: Add a component of choice in series, or parallel, to the existing circuit (if adding the first component, choice of S or P does not make a difference, naturally).
- F: Set the desired frequency of the voltage source of the circuit
- C: Calculate the total impedance of the circuit, according to the governing circuit equations. This will output the complex value, the total magnitude of it, and the phase shift attributed to the impedance.
- G: Provide, in tabular format, all of the data which describes the circuit.
- D: Provide a quasi-graphical representation of the circuit, using symbols.
- SAVE: Save the circuit to a file - whose filename will be prompted if not already set. 
- EXIT: Quit the program.

Note that all inputs are NOT case sensitive.

Menu items are provided so that all choices above should be clear.

###

EXAMPLES:

Circuit file format:
R1 000 001 4 S
R2 000 001 2 P
C1 000 001 5.2 P
R3 001 002 13 S

- Row 1: provides a unique identifier for the component, the letter representing the circuit component (R = resistor, L = inductor, C = capacitor).
- Row 2: provides a beginning node for the component - this is of use in SPICE netlists.
- Row 3: provides a beginning node for the component - this is of use in SPICE netlists.
- Row 4: provides a parameter value for the component (units: resistor: Ohms, inductor: Henries, capacitor: Farads).
- Row 5: provides the configuration (S = series, P = parallel), relative to all entries above it.

Circuit impedance arising from it: 13.0007 - 0.0305906i (13.0007 magnitude) Ohms. Phase shift: ~0 radians.

Example display from the above file example:
{{R1 --- R2} // C1} --- R3



