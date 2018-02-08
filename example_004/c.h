#ifndef C_H
#define C_H

#include <Python.h> // First include for avoiding "_POSIX_C_SOURCE" faults
#include <QMainWindow> // Qt C++
#include <iostream> // std::cout

QPixmap callPythonImage(int W, int H, int DPI);

#endif // C_H
