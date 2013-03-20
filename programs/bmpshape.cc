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

int main() {

	int N = 10 ;     // number of eq.p. lines
	int n = 499;
	int m = 499;


	double Emax=50;
	double Emin=-50;

	Bmp_Reader bmp("shape.bmp");
	Grid first_grid = bmp.get_grid(conductor,Emax,Emin,10.);
	cout << "Shape parsed." << endl;

	//first_grid.set_flow_careful(Emax, Emin);


	Fast_Finite_Difference fd (first_grid);
	fd.set_precision(0.00001);
	fd.set_maxit(10000);
	cout << "Solving..." << endl;
	//timespec t0, t1;
	//clock_gettime(CLOCK_REALTIME, &t0);
    Grid sol = fd.get_solution();
    //clock_gettime(CLOCK_REALTIME, &t1);
    //cout << difftime(t1.tv_sec,t0.tv_sec) << endl;
    cout << "Done solving!" << endl;

    cout << "Plotting..." << endl;
    sol.set_figure_outline();
	sol.print_all_to("results.dat");


	Gnuplot gp(sol);
	sol.equip_values(N,1,1);
	sol.print_contours_to("eq_lines.dat", N);

	gp.add_command("set term postscript");
    gp.add_command("set ytics ('1000' 999)");
    gp.add_command("set xtics ('1000' 999)");
	gp.add_command("set output 'shape.ps'");
	gp.add_command("set palette defined");
    gp.add_command("unset key");
    //gp.add_plot();
	gp.add_command("plot 'results.dat' with image, 'eq_lines.dat' with lines ls -1");
	//, 'figure.dat' with lines ls -1"); // white = ls -3; black = ls -1; red = ls 1; green = 2; blue = ls 3; violet = ls 4;
	gp.sendString();

    cout << "Done plotting!" << endl;

	return 0;

	}
