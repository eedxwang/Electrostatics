#include "Algorithms/Asymmetric_Finite_Volume.h"
#include "Utils/Gnuplot.h"
#include "Algorithms/Finite_Difference.h"
#include "Algorithms/Fast_Finite_Difference.h"
#include "Errors/Compare.h"
#include "Utils/Conductors.h"
#include <ctime>
#include "Utils/BmpReader.h"

using namespace std;

int main() {

	int N = 10 ;     // number of eq.p. lines
	int n = 999;
	int m = 999;


	double Emax=50;
	double Emin=-50;

	Bmp_Reader bmp("shape.bmp");
	Grid first_grid = bmp.get_grid(conductor,Emax,Emin,10.);
	cout << "got shape" << endl;

	//first_grid.set_flow_careful(Emax, Emin);

	Fast_Finite_Difference fd (first_grid);
	fd.set_precision(0.00001);
	fd.set_maxit(10000);
    Grid sol = fd.get_solution();
    cout << "done solving" << endl;
    sol.set_figure_outline();
	sol.print_all_to("results.dat");



	Gnuplot gp(sol);
	sol.equip_values(N,n,m,Emax,1,1);
	sol.print_contours_to("eq_lines.dat", N);
    cout << "done calling lines" << endl;

	gp.add_command("set term postscript");
    gp.add_command("set ytics ('1000' 999)");
    gp.add_command("set xtics ('1000' 999)");
	gp.add_command("set output 'shape.ps'");
	gp.add_command("set palette defined");
    gp.add_command("unset key");
    //gp.add_plot();
	gp.add_command("plot 'results.dat' with image, 'eq_lines.dat' with lines ls -1, 'figure.dat' with lines ls -1"); // white = ls -3; black = ls -1; red = ls 1; green = 2; blue = ls 3; violet = ls 4;
	gp.sendString();

	return 0;

	}
