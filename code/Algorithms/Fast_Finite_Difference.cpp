#include "Fast_Finite_Difference.h"

Fast_Finite_Difference::Fast_Finite_Difference(Grid entry) : Algorithm(entry) {}

Fast_Finite_Difference::~Fast_Finite_Difference() {}

void Fast_Finite_Difference::solve(){
	matrix one,two;
	one = two = grid.get_values();
	matrix *current, *alternate, *temp;
	current = &one;
	alternate = &two;
	bool error = 1;
	double err = 0.;
	double betaSq = beta*beta;
	double divisor = 2*(1+betaSq);
	int n = current->size()-1;
	int m = (*current)[0].size()-1;
	for (its = 0;error && its < maxit;its++) {
		error = 0;
		temp = current;
		current = alternate;
		alternate = temp;
		for (int x = 1; x < n; x++) {
			for (int y = 1; y < m; y++) {
				if (!(*current)[x][y].boundary) { //&& (*current)[x][y].flag != 5) {
					(*alternate)[x][y].value = (
							(*current)[x-1][y].value + (*current)[x+1][y].value +
							betaSq*((*current)[x][y-1].value + (*current)[x][y+1].value))/divisor;
                    //err = std::abs((*alternate)[x][y].value - (*current)[x][y].value);
                    if (!error)error = std::abs((*alternate)[x][y].value - (*current)[x][y].value) > precision;
                    //if(err < precision) (*alternate)[x][y].flag = 5;
                    //if(err > precision) {(*alternate)[x-1][y].flag = 0; (*alternate)[x+1][y].flag = 0; (*alternate)[x][y-1].flag = 0; (*alternate)[x][y+1].flag = 0;}
				}
			}
		}
	}
	grid.set_values(one);
}
Grid Fast_Finite_Difference::get_solution() {
	Fast_Finite_Difference::solve();
	return grid;
}
