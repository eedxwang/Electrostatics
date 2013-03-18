code = ../code/
libname = $(code)theoretical.a
CC = g++ -std=c++11 -Ofast
programs = multiple_conductors eqlines animation bmpshape
export CC

all : $(programs)

multiple_conductors : multiple_conductors.cc
	$(MAKE) -C $(code); $(CC) -I $(code) multiple_conductors.cc $(libname) -o multiple_conductors

eqlines : eqlines.cc
	$(MAKE) -C $(code); $(CC) -I $(code) eqlines.cc $(libname) -o eqlines

animation : animation.cc
	$(MAKE) -C $(code); $(CC) -I $(code) animation.cc $(libname) -o animation

bmpshape : bmpshape.cc
	$(MAKE) -C $(code); $(CC) -I $(code) bmpshape.cc $(libname) -o bmpshape

clean :
	rm $(programs); cd $(code); make clean
