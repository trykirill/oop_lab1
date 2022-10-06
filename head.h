#ifndef HEAD_H
#define HEAD_H

#include <vector>

namespace matrix{
    using namespace std;
    struct Item{
		int col_idx;
		double val;
	};

	struct Mtr{
		vector<int> row_idx;
		vector<int> row_ptr;
		vector<Item>  items;
	};
    
    void processing(Mtr &mtr, Mtr &new_mtr);
    void create_mtr(Mtr &mtr);
    int insert(Mtr &mtr, double val,int row_idx, int col_idx);
    void print_matrix(Mtr &mtr);
}

#endif
