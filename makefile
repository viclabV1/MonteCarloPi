parallel_pi:
	doxygen ./Doxyfile;
	gcc -g -Wall -o parallel_pi parallel_pi.c -lm -lpthread
	gcc -g -Wall -o no_mutex parallel_pi_no_mutex.c -lm -lpthread

with_mutex:
	gcc -g -Wall -o parallel_pi parallel_pi.c -lm -lpthread

no_mutex:
	gcc -g -Wall -o no_mutex parallel_pi_no_mutex.c -lm -lpthread

clean:
	rm ./no_mutex
	rm ./parallel_pi
	rm -rf ./doxygen_output