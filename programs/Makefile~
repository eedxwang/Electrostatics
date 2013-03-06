code = ../code/
libname = $(code)theoretical.a
CC = g++ -std=c++11 -Ofast

multiple_conductors : $(libname) multiple_conductors.cc
	$(CC) -I $(code) multiple_conductors.cc $(libname) -o multiple_conductors
	
integrating_test : $(libname) integrating_test.cc
	$(CC) -I $(code) integrating_test.cc $(libname) -o integrating_test

$(libname) : ../code/Makefile
	cd $(code); make
	
clean : 
	rm $(program); cd $(code); make clean
