parallel_pi:
	doxygen ./Doxyfile;
	gcc -g -Wall -o parallel_pi parallel_pi.c -lm -lpthread

clean:
	rm ./parallel_pi
	rm -rf ./doxygen_output