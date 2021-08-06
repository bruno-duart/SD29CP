all: 
	factorial_paralel factorial_serial

paralelo: 
	g++ factorial_paralel.cpp -o factorial_paralel -fopenmp

serial: 
	g++ factorial_serial.cpp -o factorial_serial

clean: 
	rm -rf factorial_paralel factorial_serial

run_p: .
	time ./factorial_paralel

run_s: 
	time ./factorial_serial
