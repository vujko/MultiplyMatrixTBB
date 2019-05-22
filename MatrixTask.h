#pragma once
#include<tbb\task.h>
#include<tbb\tbb.h>
#include "ParallelMultiplication.h"

using namespace tbb;
using namespace std;



class MatrixTask : public task {
public:
	int i, j;
	//successor[0] prethodni zadatak; successor[1] sledeci zadatak
	MatrixTask** successor;
	int* input1;
	int* input2;
	Matrix& a;
	tbb::empty_task* e;

	MatrixTask() :i(-1), j(-1),a(Matrix()) {};
	MatrixTask(int i_, int j_, Matrix& a_, tbb::empty_task* e_) :i(i_), j(j_), a(a_), e(e_) {
		////ako su zadaci sa kraja
		//if (j == 0 || j == a.red - 1) {
		//	set_ref_count(1);
		//}
		//else {
		//	set_ref_count(2);	
		//	//2 za komsije + 1 za sebe
		//}
		set_ref_count(a.red - 1);
		successor = new MatrixTask*[a.red];
		input1 = new int[a.red];
		input2 = new int[a.red];
	}

	task* execute() {
		int result = 0;

		for (int k = 0; k < a.red; k++) {
			result += input1[k] * input2[k];
		}

		for (int k = 0; k < a.red; k++) {
			successor[k]->decrement_ref_count();
			while (successor[k]->ref_count() != 0) {}

		}

		/*if (j != 0 && j != a.red - 1) {
			successor[0]->decrement_ref_count();
			successor[1]->decrement_ref_count();
			while (successor[0]->ref_count() != 0 && successor[1]->ref_count() != 0) {}
		}
		else if (j == 0){
			successor[1]->decrement_ref_count();
			while (successor[1]->ref_count() != 0) {}
		}
		else {
			successor[0]->decrement_ref_count();
			while (successor[0]->ref_count() != 0) {}
		}*/


		a(i, j) = result;

		__TBB_ASSERT(ref_count() == 0, NULL);

		e->decrement_ref_count();
		
		return NULL;

	}
		
	
};