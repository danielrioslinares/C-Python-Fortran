
#include "c.h"

QPixmap callPythonImage(int W, int H, int DPI) {

    // Module name for p.py
    std::string libname = "p";
    std::string fcnname = "f";

    // Convert string to PyObject
    PyObject *py_arginstW = PyFloat_FromDouble(W);
    PyObject *py_arginstH = PyFloat_FromDouble(H);
    PyObject *py_arginstDPI = PyFloat_FromDouble(DPI);

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

    // Get the function because py_modinst has the function named py_fcnname
    PyObject *py_fcninst = PyObject_GetAttr(py_modinst,py_fcnname);

    // Create a Python tuple
    PyObject *py_argtupl = PyTuple_Pack(3, py_arginstW, py_arginstH,py_arginstDPI);

    // Evaluate function with py_argtupl as arguments
    PyObject *py_ansinst = PyObject_CallObject(py_fcninst, py_argtupl);

    // Fill int[][][] array of RGB components
    PyObject *py_ansinstR = PyList_GetItem(py_ansinst,0); // R component
    PyObject *py_ansinstG = PyList_GetItem(py_ansinst,1); // G component
    PyObject *py_ansinstB = PyList_GetItem(py_ansinst,2); // B component

    QImage image(W, H, QImage::Format_ARGB32);

    for(int i = 0; i < W*H; i++) {
        int r = (int)PyFloat_AsDouble(PyList_GetItem(py_ansinstR,i));
        int g = (int)PyFloat_AsDouble(PyList_GetItem(py_ansinstG,i));
        int b = (int)PyFloat_AsDouble(PyList_GetItem(py_ansinstB,i));
        QRgb rgb = qRgb(r,g,b);
        image.setPixel(i%W, i/W, rgb);
    }

    QPixmap plot = QPixmap::fromImage(image);

    return plot;
}
