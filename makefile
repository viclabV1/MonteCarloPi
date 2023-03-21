parallel_pi:
	mpicc -O3 -Wall -o parallel_pi parallel_pi.c -lm

clean:
	rm ./parallel_pi