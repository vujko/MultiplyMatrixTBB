#include "ParallelMultiplication.h"

MatrixTask*** PM::zadaci;
void ParallelMultiplication::multiply(Matrix & a, Matrix & b)
{
	tbb::empty_task* e = new (task::allocate_root()) tbb::empty_task();
	int red_matrica = a.red;
	e->set_ref_count(red_matrica * red_matrica + 1);
	zadaci = new MatrixTask**[red_matrica];
	for (int i = 0; i != red_matrica; i++) {
		zadaci[i] = new MatrixTask*[red_matrica];

		for (int j = 0; j != red_matrica; j++) {
			zadaci[i][j] = new (task::allocate_root()) MatrixTask(i, j, a, e);
			if (j != 0 && j != a.red - 1) {
				//successor[0] - prethodni zadatak
				zadaci[i][j]->successor[0] = zadaci[i][j - 1];
				//successor[1] - sledeci zadatak
				zadaci[i][j]->successor[1] = zadaci[i][j + 1];
			}
			else if (j == 0) {
				zadaci[i][j]->successor[1] = zadaci[i][j + 1];
			}
			else {
				zadaci[i][j]->successor[0] = zadaci[i][j - 1];
			}

			for (int k = 0; k != red_matrica; k++) {
				zadaci[i][j]->input1[k] = a(i, k);
				zadaci[i][j]->input2[k] = b(k, j);
			}
			
		}

		for (int j = 0; j != red_matrica; j++) {
			task::spawn(*zadaci[i][j]);
		}
	}

	e->wait_for_all();
}
