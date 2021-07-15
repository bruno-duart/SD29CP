all: 
	paralelo serial

paralelo: 
	g++ paralelo.cpp -o paralelo -fopenmp

serial: 
	g++ serial.cpp -o serial

clean: 
	rm -rf paralelo serial

run_p: .
	./paralelo

run_s: 
	./serial
