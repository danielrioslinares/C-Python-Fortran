

compile:
	@echo -e "\033[33;1mCall Python function from C++ that prints out answer\e[0m"
	# Compilation of c.cpp to c.cpp.o
	@gcc -c c.cpp -I/usr/include/python3.6m -lpython3.6m -o c.cpp.o
	# Compilation of c.cpp.o to the module to be called
	@gcc c.cpp.o -lstdc++ -I/usr/include/python3.6m -lpython3.6m -o mymodule
	# Clean the temporal compilation c.cpp.o
	@rm c.cpp.o

test:
	@echo -e "\033[33;1mCall Python function f(x) inside p.py from C++ printing out the result\e[0m"
	# Returns double of 4 (check out p.py, you can modify function f(x) as normal)
	@./mymodule func 4

clean:
	# Cleaning *.o and __pycache__
	@rm *.o ; rm -rf __pycache__
