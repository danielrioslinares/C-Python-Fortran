

compile:
	@echo -e "\033[33;1mCall Python function from C++ called from Python\e[0m"
	# Compilation of c.cpp to c.cpp.o
	@gcc -pthread -DNDEBUG -I/usr/include/python3.6m -c c.cpp -o c.cpp.o
	# Library generation of mymodule
	@g++ -pthread -shared -O1,--sort-common,--as-needed,-z,relro c.cpp.o -L/usr/lib -lpython3.6m -o mymodule.so
	# Clean the temporal compilation c.cpp.o
	@rm c.cpp.o

test:
	@echo -e "\033[33;1mThe method callCppFromPython(x) duplicates x in C++ and then applies the function f(x) stored in pyfunc.py\e[0m"
	@python p.py

clean:
	# Cleaning *.o and __pycache__
	@rm *.o ; rm -rf __pycache__

inspect:
	ldd mymodule.so
	nm mymodule.so
