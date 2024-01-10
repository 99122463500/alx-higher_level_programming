#include <Python.h>
#include <stdio.h>

void print_python_list(PyObject *p) {
    printf("[*] Python list info\n");
    printf("[*] Size of the Python List = %ld\n", PyList_Size(p));
    printf("[*] Allocated = %ld\n", ((PyListObject *)p)->allocated);

    for (Py_ssize_t i = 0; i < PyList_Size(p); ++i) {
        PyObject *elem = PyList_GetItem(p, i);
        printf("Element %ld: ", i);

        if (PyBytes_Check(elem)) {
            printf("bytes\n");
            print_python_bytes(elem);
        } else if (PyTuple_Check(elem)) {
            printf("tuple\n");
            // Implement tuple printing if needed
        } else if (PyList_Check(elem)) {
            printf("list\n");
            // Implement list printing if needed
        } else if (PyFloat_Check(elem)) {
            printf("float\n");
            // Implement float printing if needed
        } else if (PyLong_Check(elem)) {
            printf("int\n");
            // Implement integer printing if needed
        } else if (PyUnicode_Check(elem)) {
            printf("str\n");
            // Implement string printing if needed
        } else {
            printf("object\n");
            // Print information about other types if needed
        }
    }
}

void print_python_bytes(PyObject *p) {
    printf("[.] bytes object info\n");
    printf("  size: %ld\n", PyBytes_Size(p));
    
    char *str = PyBytes_AsString(p);
    if (!str) {
        PyErr_Print();
        printf("  [ERROR] Invalid Bytes Object\n");
        return;
    }

    printf("  trying string: %s\n", str);
    printf("  first 10 bytes: ");
    
    for (Py_ssize_t i = 0; i < 10 && i < PyBytes_Size(p); ++i) {
        printf("%02x ", (unsigned char)str[i]);
    }

    printf("\n");
}

// Example usage:
int main(void) {
    Py_Initialize();

    PyObject *s = PyBytes_FromString("Hello");
    PyObject *b = PyBytes_FromString("\xff\xf8\x00\x00\x00\x00\x00\x00");
    PyObject *l = PyList_New(2);
    PyList_SetItem(l, 0, s);
    PyList_SetItem(l, 1, b);

    print_python_bytes(s);
    print_python_bytes(b);
    print_python_list(l);

    Py_DECREF(s);
    Py_DECREF(b);
    Py_DECREF(l);

    Py_Finalize();

    return 0;
}

