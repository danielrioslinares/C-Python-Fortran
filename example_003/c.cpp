
#include <Python.h> // First include for avoiding "_POSIX_C_SOURCE" faults
#include <iostream> // std::cout


// Functions inside f.f90 extension
extern "C" double cos_f90(double *x);
extern "C" double sin_f90(double *x);


/* HERE GOES ALL THE METHODS */
// mycos(x) function
static PyObject* mycos(PyObject* self, PyObject* args) {
    double x;
    double ans;

    // With Python float input parse to C double (Python exception returns NULL)
    if (!PyArg_ParseTuple(args, "d", &x)) return NULL;

    ans = cos_f90(&x);

    // Parse C double to Python float
    return Py_BuildValue("f", ans);
}

// mysin(x) function
static PyObject* mysin(PyObject* self, PyObject* args) {
    double x;
    double ans;

    // With Python float input parse to C double (Python exception returns NULL)
    if (!PyArg_ParseTuple(args, "d", &x)) return NULL;

    ans = sin_f90(&x);

    // Parse C double to Python float
    return Py_BuildValue("f", ans);
}

/* AFTER THE METHODS, ALL Python.h REQUIREMENTS */
// Methods inside the module
static PyMethodDef mymodule_methods[] = {
	// mycos(<float x>)
    {"mycos",	mycos,	METH_VARARGS,	"evaluate the cosine"},
	// mysin(<float x>)
    {"mysin",	mysin,	METH_VARARGS,	"evaluate the sine"},
	// Sentinel : without it, segmentation fault
	{NULL, NULL, 0, NULL}
};

// Python module definition (name, doc, state and methods inside)
static struct PyModuleDef mymodule_module = {
	PyModuleDef_HEAD_INIT,
	"mymodule",
	"Python with Fortran90 mymodules", // documentation char string
	-1, // size inside interpreter, state of module (-1 stored as global)
	mymodule_methods // methods listed in the module
};

// Invoking from Python (import statement)
PyMODINIT_FUNC PyInit_mymodule(void) {
     return PyModule_Create(&mymodule_module);
}
