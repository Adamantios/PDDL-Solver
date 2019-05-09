# Run make
make clean && make

# Add link to libPDDLParser library
sudo ln -s -f $(pwd)/Lib/libPDDLParser.so {LD_LIBRARY_PATH}/libPDDLParser.so

# Reload libraries
sudo ldconfig

# Run Planner
./Planner
