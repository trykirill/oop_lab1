#include <iostream>
#include <vector>
#include <algorithm>
#include "head.h"
//#include <limit>
namespace matrix{

using namespace std;

void getInt(int& val, const char* txt) {
	const char* err = "";
	int flag;
	do{
		cout << err;
		cout << txt;
		cin >> val;
		if(flag = cin.good()){
			cin.clear();
			cin.ignore(100, '\n');
			err = "wronge data\n";
		}
	} while(!flag);
}

void getDouble(double& val, const char* txt) {
	const char* err = "";
	int flag;
	do{
		cout << err;
		cout << txt;
		cin >> val;
		flag = cin.good();
		cin.clear();
		cin.ignore(1000, '\n');
		err = "wronge data\n";
	} while(!flag);
}

void print_vector(vector<Item> vctr){
	if (vctr.size() == 0){cout << endl; return;}
	for(int i = 0; i < vctr.size() - 1; ++i){
		cout << vctr[i].col_idx << ", "; 

	}
	cout << vctr[vctr.size() - 1].col_idx << endl << "            ";
	for(int i = 0; i < vctr.size() - 1; ++i){
		cout << vctr[i].val << ", ";
	}
	cout << vctr[vctr.size() - 1].val << endl;
}

void print_vector(vector<int> vctr){
	if (vctr.size() == 0){cout << endl; return;};	
	cout << "{";
	for(int i = 0; i < vctr.size() - 1; ++i){
		cout << vctr[i] << ", "; 

	}
	cout << vctr[vctr.size() - 1];
	cout << "}\n";
}

void print_matrix(Mtr &mtr){
	cout << "row_idx -> ";
	print_vector(mtr.row_idx);
	cout << "row_ptr -> ";
	print_vector(mtr.row_ptr);
	cout << "items   ->  ";
	print_vector(mtr.items);
}

void create_mtr(Mtr &mtr){
	int size;
	do{
		getInt(size, "enter count elements -> ");
       	} while(size < 0);
	double val;
	int row_idx, col_idx;
	for (int i = 0; i < size; ++i){
		getDouble(val, "enter val          -> ");
		do{
			getInt(row_idx, "enter row index    -> ");
		} while (row_idx < 0);
		do{
			getInt(col_idx, "enter column index -> ");
		} while (col_idx < 0);
		if(insert(mtr, val, row_idx, col_idx)){
			--i;
			cout << "error: the cell is already occupied!\n";
		}
		cout << endl;
	}
}

int find_item(Mtr &mtr, int col_idx, int row_pos){
	for(int i = mtr.row_ptr[row_pos]; i < mtr.row_ptr[row_pos + 1]; i++){
		if((mtr.items[i]).col_idx == col_idx){
			return 1;
		}
	}
	return 0;
}

int insert(Mtr &mtr, double val,int row_idx, int col_idx){
	
	if(mtr.row_idx.size() == 0){
        	mtr.row_idx.push_back(row_idx);
        	mtr.row_ptr.push_back(0);
		mtr.row_ptr.push_back(1);
		mtr.items.push_back({col_idx, val});
		return 0;
	}

	if(mtr.row_idx.end() != find(mtr.row_idx.begin(), mtr.row_idx.end(), row_idx)){ //строка по индексу  не нулевая
		int row_pos = 0;
		while(mtr.row_idx[row_pos] != row_idx){
			++row_pos;
		}
											
		int col_pos = mtr.row_ptr[row_pos];
	
		if(find_item(mtr, col_idx, row_pos)){ // ячейка уже занята
			return 1;
		}
        	
		while(col_pos < mtr.row_ptr[row_pos + 1] and (mtr.items[col_pos]).col_idx < col_idx){
			++col_pos;
		}
		for(int pos = row_pos + 1; pos < mtr.row_ptr.size(); pos++){
			mtr.row_ptr[pos] = mtr.row_ptr[pos] + 1;
		}
        	
		mtr.items.insert(mtr.items.begin() + col_pos, {col_idx, val});
		return 0;
	}

	int row_pos = 0;
	while(row_pos < mtr.row_idx.size() and mtr.row_idx[row_pos] < row_idx){
		++row_pos;
	}
	mtr.row_idx.insert(mtr.row_idx.begin() + row_pos, row_idx);
	
	int col_pos = mtr.row_ptr[row_pos];

	for(int pos = row_pos; pos < mtr.row_ptr.size(); pos++){
		mtr.row_ptr[pos] = mtr.row_ptr[pos] + 1; 
	}
     	
	while((mtr.items[col_pos]).col_idx < col_idx and col_pos < mtr.row_ptr[row_pos + 1]){
		++col_pos;
	}
	mtr.row_ptr.insert(mtr.row_ptr.begin() + row_pos, col_pos);
	mtr.items.insert(mtr.items.begin() + col_pos, {col_idx, val});
	
	return 0;
}

void processing(Mtr &mtr, Mtr &new_mtr){
	new_mtr.row_idx = mtr.row_idx;
	new_mtr.row_ptr = mtr.row_ptr;
	new_mtr.items = mtr.items;
	int  min_idx, max_idx;
	double min_val, max_val;
	for(int i = 0; i < new_mtr.row_idx.size(); ++i){
		min_idx = max_idx = mtr.row_ptr[i];
		for(int pos_ptr = new_mtr.row_ptr[i]; pos_ptr < new_mtr.row_ptr[i+1]; ++pos_ptr){ //находим min and max
			if((new_mtr.items[pos_ptr]).val > (new_mtr.items[max_idx]).val){
				max_idx = pos_ptr;
			}
			if((new_mtr.items[pos_ptr]).val < (new_mtr.items[min_idx]).val){
				min_idx = pos_ptr;
			}
		}
		min_val = (new_mtr.items[min_idx]).val;
		max_val = (new_mtr.items[max_idx]).val;
		for(int pos_ptr = new_mtr.row_ptr[i]; pos_ptr < new_mtr.row_ptr[i+1]; ++pos_ptr){ // меняем значения
			if((new_mtr.items[pos_ptr]).val == min_val){
				(new_mtr.items[pos_ptr]).val = max_val;
			}
			else if((new_mtr.items[pos_ptr]).val == max_val){
				(new_mtr.items[pos_ptr]).val = min_val;
			}
		}
	}
}

}
