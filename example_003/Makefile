

compile:
	@echo -e "\033[33;1mCall Fortran 90 functions sin and cos from python through C++\e[0m"
	# Fortran compilation : gcc -c f.f90
	@gcc -c f.f90 -o f.f90.o
	# C compilation : gcc with "pkg-config --cflags --libs python3" flags
	@gcc -c c.cpp -I/usr/include/python3.6m -lpython3.6m -o c.cpp.o
	# Fortran + C shared compilation module creation : gcc f.o c.o
	@@g++ -pthread -shared -O1,--sort-common,--as-needed,-z,relro c.cpp.o f.f90.o -L/usr/lib -lpython3.6m -o mymodule.so
	# Cleaning *.o temporal build
	@rm *.o

test:
	@echo -e "\033[33;1mCall Fortran 90 functions mysin(x) and mycos(x) inside f.f90 through C++ printing out the results\e[0m"
	@python p.py

clean:
	@rm *.o

inspect:
	ldd mymodule.so
	nm mymodule.so
