
#include <Python.h> // First include for avoiding "_POSIX_C_SOURCE" faults
#include <iostream> // std::cout


/* IDEA, CONSULTED:
https://stackoverflow.com/questions/3286448/calling-a-python-method-from-c-c-and-extracting-its-return-value
https://docs.python.org/3/c-api
*/

/* NOTE, MANUAL COMPILATION with gcc:
gcc -c c.cpp -I/usr/include/python3.6m -lpython3.6m -o c.cpp.o
gcc c.cpp.o -lstdc++ -I/usr/include/python3.6m -lpython3.6m -o test
*/

// Only calls Python function inside argv[1] (string) and prints out for argv[2]
// value converted using atof() function
int main( int argc, char *argv[]) {

	// Module name for p.py
	std::string libname = "p";
	std::string fcnname = argv[1];

	// Convert string to PyObject
	PyObject *py_arginst = PyFloat_FromDouble(atof(argv[2]));

	// Init Python interpreter (NOTE important)
	Py_Initialize();

	// Find module (current path) and use it
	PyObject *py_path = PyObject_GetAttrString(PyImport_ImportModule("sys"),"path");
	PyList_Append(py_path, PyUnicode_FromString("."));

	// Python module to import
	PyObject *py_modname = PyUnicode_FromString((char*)libname.c_str());
	PyObject *py_modinst = PyImport_Import(py_modname);

	// Python function to use
	PyObject *py_fcnname = PyUnicode_FromString((char*)fcnname.c_str());

	// Check if module contains the function
	if (!PyObject_HasAttr(py_modinst, py_fcnname))
		return -1;

	// Get the function because py_modinst has the function named py_fcnname
	PyObject *py_fcninst = PyObject_GetAttr(py_modinst,py_fcnname);

	// Create a Python tuple
	PyObject *py_argtupl = PyTuple_Pack(1, py_arginst);

	// Evaluate function with py_argtupl as arguments
	PyObject *py_ansinst = PyObject_CallObject(py_fcninst, py_argtupl);

	// Convert answer to double
	double ans = PyFloat_AsDouble(py_ansinst);

	std::cout << ans << std::endl;

	// Kills Python interpreter(sub) created from Py_Initialize (NOTE important)
	Py_Finalize();

	return 0;
}
