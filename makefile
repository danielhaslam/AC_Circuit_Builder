CXX = g++-11
CXXFLAGS = -std=gnu++17 -Iinterface -Icomponents 

SRC = main.cpp components/circuit.cpp components/component.cpp components/capacitor.cpp components/inductor.cpp components/resistor.cpp interface/interface_functions.cpp component_functions.cpp file_operations.cpp

OUT = a.o

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

.PHONY: clean
clean:
	rm -f $(OUT) *.o