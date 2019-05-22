# Build parser
make clean && make

# Build shared library - unix
g++ -shared bin/*.o -o libPDDLParser.so

# Copy shared library into Libs folder in Planner

# Run make
make clean && make

# Add link to libPDDLParser library
sudo ln -s -f $(pwd)/lib/libPDDLParser.so {LD_LIBRARY_PATH}/libPDDLParser.so

# Reload libraries
sudo ldconfig

# Run Planner
./Planner
