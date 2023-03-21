parallel_pi:
	doxygen ./Doxyfile;
	mpicc -O3 -Wall -o parallel_pi parallel_pi.c -lm

clean:
	rm ./parallel_pi
	rm -rf ./doxygen_output