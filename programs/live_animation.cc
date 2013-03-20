#include "../code/Algorithms/Asymmetric_Finite_Volume.h"
#include "../code/Utils/Gnuplot.h"
#include "../code/Algorithms/Finite_Difference.h"
#include "../code/Algorithms/Fast_Finite_Difference.h"
#include "../code/Errors/Compare.h"
#include "../code/Utils/Animation.h"
#include "../code/Utils/Conductors.h"
#include "../code/Structures/Grid.h"
#include "../code/Utils/BmpReader.h"
#include <ctime>

using namespace std;


int main() {

	int N = 8;   // number of eq.p. lines
	int n = 999;
	int m = 999;

	double Emax=100;
	double Emin=-100;

	cout << "creating bmp figure.. ";
	Bmp_Reader bmp("shape.bmp");
	Grid first_grid = bmp.get_grid(conductor,Emax,Emin,100.);
	//first_grid.print_figure_to("figure.dat");

//	Grid first_grid(n,m);

//	first_grid.set_flow(Emax, Emin);
//	first_grid.set_boundary_shape(100,100,30,0,0,circle);
	cout << "done" << endl;

	Animation anim(first_grid);
	anim.set_lines(1, black, N);
	anim.set_figure(0, black, "lines");
	anim.set_outline(1);

	cout << "creating data.. ";
	anim.create_data();
	cout << "done" << endl;
	cout << "creating gif file.. ";
	anim.animate();
	cout << "done" << endl;
	cout << "removing data.. ";
	anim.delete_data();
	cout << "done" << endl;

}

