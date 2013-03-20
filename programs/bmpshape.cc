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
    int size = sol.get_xmax();
    sol.efield();
    sol.set_equipotential_lines(N,1,1);
    sol.set_figure_outline();
  	sol.print_matrix_to("results.dat");
	sol.print_electric_field("efield.dat", size/30);

	Gnuplot gp(sol);
	std::string filename = file.substr(0,file.size()-4);
	gp.add_command("set term postscript");
	gp.add_command("set output '"+filename+".ps'");
	gp.add_command("set palette defined");
    gp.add_command("unset key");
    //gp.add_plot();
	gp.add_command("plot 'results.dat' matrix with image, 'efield.dat' using 1:2:3:4 with vectors head filled lt 2");
	gp.sendString();

	remove("results.dat");
	remove("efield.dat");

    cout << "Done plotting!" << endl;

	return 0;

	}
