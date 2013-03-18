#include "Algorithms/Asymmetric_Finite_Volume.h"
#include "Utils/Gnuplot.h"
#include "Algorithms/Finite_Difference.h"
#include "Algorithms/Fast_Finite_Difference.h"
#include "Errors/Compare.h"
#include "Utils/Conductors.h"
#include "Utils/Utils.h"

using namespace std;

int main() {

	int n = 200;
	int m = 200;

	Grid first_grid(n,m);

	first_grid.set_flow(50, -50);

	cout << "Integrated field before conductors: " << sum_grid(first_grid) << endl;

    first_grid.set_conductor(105, 100, 5, 0, circle);
	first_grid.set_conductor(95,100,2,0,circle);

	//first_grid.set_conductor(150,130,40,50,star);
	//first_grid.set_conductor(50,70,15,0,circle);

	Finite_Difference fd (first_grid);
	fd.set_precision(0);
	fd.set_maxit(30000);
	Grid sol_fd = fd.get_solution();

	Gnuplot gp(sol_fd);
	gp.add_command("set term postscript");
	gp.add_command("set ytics ('200' 200)");
    gp.add_command("set xtics ('200' 200)");
	gp.add_command("set output 'single_conductor.ps'");
	gp.add_command("unset key");
	gp.add_command("set palette color");
	gp.add_command("set palette defined");
	gp.add_plot();
	gp.sendString();

	Conductors conductors(n,m,50.,-50.);
	conductors.new_conductor(105,100,5,0,circle);
	conductors.new_conductor(95,100,2,0,circle);
	conductors.set_precision(0);
	conductors.set_maxit(30000);
	Grid sol_new = conductors.get_solution(FFD);

	Gnuplot gp2(sol_new);
	gp2.add_command("set term postscript");
    gp2.add_command("set ytics ('200' 200)");
    gp2.add_command("set xtics ('200' 200)");
	gp2.add_command("set output 'two_conductors_new.ps'");
	gp2.add_command("unset key");
	gp2.add_command("set palette color");
	gp2.add_command("set palette defined");
	gp2.add_plot();
	gp2.sendString();

	Grid diff = find_err_relative(sol_fd, sol_new);

	Gnuplot gp3(diff);
	gp3.add_command("set term postscript");
    gp3.add_command("set ytics ('200' 200)");
    gp3.add_command("set xtics ('200' 200)");
	gp3.add_command("set output 'difference.ps'");
	gp3.add_command("unset key");
	gp3.add_command("set palette color");
	gp3.add_command("set palette defined");
	gp3.add_plot();
	gp3.sendString();


	cout << "Integrated field in old method: " << sum_grid(sol_fd) << endl;
	cout << "Integrated field in new method: " << sum_grid(sol_new) << endl;

	return 0;

	}
