# C-Python-Fortran
Demonstrate the C API for Python 3, comunicating Python, C++ and Fortran 90 simplest as possible. The current examples are:

- example_001 : Calls Python function f(x) inside p.py from C++ printing out the result.
- example_002 : Python calls a method inside C++ named callCppFromPython(x), duplicates x and applies the function f(x) stored in pyfunc.py.
- example_003 : From Python calls a Fortran 90 subroutine as a function extended with C++.
- example_004 : From Python plot a figure and then the RGB values are sent to C++ where with Qt5 render the image in a label widget using Qpixmap object.
