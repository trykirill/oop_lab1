#include <iostream>
#include <vector>
#include "head.h"

using namespace matrix;

int main(){
	Mtr *mtr = new Mtr;
	create_mtr(*mtr);
	cout << "old mtr:\n";
	print_matrix(*mtr);
	Mtr *new_mtr = new Mtr;
	processing(*mtr, *new_mtr);
	cout << "new mtr:\n";
	print_matrix(*new_mtr);
	delete mtr, new_mtr;
	return 0;
}
