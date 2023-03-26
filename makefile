parallel_pi:
	doxygen ./Doxyfile;
	gcc -g -Wall -o parallel_pi parallel_pi.c -lpthread

clean:
	rm ./parallel_pi
	rm -rf ./doxygen_output
	rm -rf ./parallel_pi.dSYM