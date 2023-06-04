# CS57 MINI-C Compiler
## Kevin Lin 

### Running Tests (6/4/2023)
Unfortunately the top level make file for this compiler is not yet working. The modules can be run seperately. Both the "assembly_gen" and "optimizer" modules can be run from their respective directory with "make run". Modify the "test_file" variable in the makefile as necessary for testing. 

A debug macro is used to organize stdout prints. In either module, the debug macro "DEB == ..." check and "DEB" value can be modified as necessary to print different levels of DEBUG(1,2,3). The "verbose" variable is used to turn all messages on or off. 