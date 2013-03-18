#include "../code/Algorithms/Asymmetric_Finite_Volume.h"
#include "../code/Utils/Gnuplot.h"
#include "../code/Algorithms/Finite_Difference.h"
#include "../code/Algorithms/Fast_Finite_Difference.h"
#include "../code/Errors/Compare.h"
#include "../code/Utils/Animation.h"
#include "../code/Utils/Conductors.h"
#include "../code/Structures/Grid.h"
#include <ctime>

using namespace std;


int main() {

	int N = 8;   // number of eq.p. lines
	int n = 200;
	int m = 200;

	double Emax=100;
	double Emin=-100;

	Grid first_grid(n,m);

	first_grid.set_flow(Emax, Emin);
	first_grid.set_conductor(120,120,15,0,circle);
    //first_grid.print_figure_to("figure.dat", 1);
    Fast_Finite_Difference fd(first_grid);
    fd.set_precision(0.);
    fd.set_maxit(10000);
    Grid sol = fd.get_solution();
    sol.set_conductor(80,80,15,0,circle);
    sol.print_figure_to("figure.dat", 2);

	Animation anim(sol);
	anim.set_lines(1, black, N); // 0 - if you dont need eq.p lines. possible colors: black, white, green, blue, violet, red
	anim.set_figure(1, black, "lines");  // same here for first two variables. possible types of figure: "filledcurve" , "lines" , "points"
	anim.set_iterations(4000);
	anim.set_time(10.0); // for which your animation will run, in seconds
//	anim.set_precision(0.00001);
//	anim.set_heatmap(0); // 0 - if you dont need heatmap on the background
//	anim.set_algorithm(FFD); // possible: FD, FFD, AFV, though Works only for FFD :/
	anim.create_data();
	anim.animate();
	anim.delete_data();

}

