
#include <Python.h> // First include for avoiding "_POSIX_C_SOURCE" faults
#include <iostream> // std::cout


/* IDEA, CONSULTED:
https://stackoverflow.com/questions/3286448/calling-a-python-method-from-c-c-and-extracting-its-return-value
https://docs.python.org/3/c-api
*/

/* NOTE, MANUAL COMPILATION with gcc:
@gcc -pthread -Wno-unused-result -Wsign-compare -DNDEBUG -g -fwrapv -O3 -Wall -march=x86-64 -mtune=generic -O2 -pipe -fstack-protector-strong -march=x86-64 -mtune=generic -O2 -pipe -fstack-protector-strong -march=x86-64 -mtune=generic -O2 -pipe -fstack-protector-strong -fPIC -I/usr/include/python3.6m -c c.cpp -o c.cpp.o
@g++ -pthread -shared -Wl,-O1,--sort-common,--as-needed,-z,relro -Wl,-O1,--sort-common,--as-needed,-z,relro c.cpp.o -L/usr/lib -lpython3.6m -o mymodule.so
*/


static PyObject* callCppFromPython(PyObject* self, PyObject* args) {

	std::string libname = "pyfunc";
	std::string fcnname = "f";

	double x;

	// With Python float input parse to C double (Python exception returns NULL)
    if (!PyArg_ParseTuple(args, "d", &x)) return NULL;

	// We double input x (simulating that C manipulates the input data)
	x = 2*x;

	// Convert the double x_temp to use it with Python interpreter
	PyObject *py_arginst = PyFloat_FromDouble(x);

	// Now initialyze Python
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
	if (!PyObject_HasAttr(py_modinst, py_fcnname)) return NULL;

	// Get the function because py_modinst has the function named py_fcnname
	PyObject *py_fcninst = PyObject_GetAttr(py_modinst,py_fcnname);

	// Create a Python tuple
	PyObject *py_argtupl = PyTuple_Pack(1, py_arginst);

	// Evaluate function with py_argtupl as arguments
	PyObject *py_ansinst = PyObject_CallObject(py_fcninst, py_argtupl);

	// Return x
	return py_ansinst;

}

/* AFTER THE METHODS, ALL Python.h REQUIREMENTS */
// Methods inside the module
static PyMethodDef mymodule_methods[] = {
	// callCppFromPython(<float x>)
    {"callCppFromPython",	callCppFromPython,	METH_VARARGS,	"returns 2*x on C++, called from Python"},
	// Sentinel : without it, segmentation fault
	{NULL, NULL, 0, NULL}
};

// Python module definition (name, doc, state and methods inside)
static struct PyModuleDef mymodule_module = {
	PyModuleDef_HEAD_INIT,
	"mymodule",
	"", // documentation char string
	-1, // size inside interpreter, state of module (-1 stored as global)
	mymodule_methods // methods listed in the module
};

// Invoking from Python (import statement)
PyMODINIT_FUNC PyInit_mymodule(void) {
     return PyModule_Create(&mymodule_module);
}
