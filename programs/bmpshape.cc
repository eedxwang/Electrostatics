#include "Algorithms/Asymmetric_Finite_Volume.h"
#include "Utils/Gnuplot.h"
#include "Algorithms/Finite_Difference.h"
#include "Algorithms/Fast_Finite_Difference.h"
#include "Errors/Compare.h"
#include "Utils/Conductors.h"
#include <ctime>
#include <unistd.h>
#include "Utils/BmpReader.h"

using namespace std;

int main(int argc,char * argv[]) {

	int N = 10 ;     // number of eq.p. lines
	double Emax=50;
	double Emin=-50;

	std::string file = "shape.bmp";
	if (argc == 2) {
		file = argv[1];
	}

	Bmp_Reader bmp(file);
	Grid first_grid = bmp.get_grid(conductor,Emax,Emin,10.);
	cout << "Shape parsed." << endl;

	Fast_Finite_Difference fd (first_grid);
	fd.set_precision(0.00001);
	fd.set_maxit(10000);
	cout << "Solving..." << endl;
    Grid sol = fd.get_solution();
    cout << "Done solving!" << endl;

    cout << "Plotting..." << endl;
    sol.set_figure_outline();
	sol.set_equipotential_lines(N,1,1);

	Gnuplot gp(sol);
	gp.add_command("set term postscript");
    gp.add_command("set ytics ('500' 499)");
    gp.add_command("set xtics ('500' 499)");
	gp.add_command("set output 'shape.ps'");
	gp.add_command("set palette defined");
    gp.add_command("unset key");
    //gp.add_plot();
	gp.add_plot();
	//, 'figure.dat' with lines ls -1"); // white = ls -3; black = ls -1; red = ls 1; green = 2; blue = ls 3; violet = ls 4;
	gp.sendString();

    cout << "Done plotting!" << endl;

	return 0;

	}
