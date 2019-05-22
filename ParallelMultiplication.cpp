#include "ParallelMultiplication.h"

MatrixTask*** PM::zadaci_m;
MatrixTaskRoot** PM::zadaci_p;

void ParallelMultiplication::multiply(Matrix & a, Matrix & b)
{
	tbb::empty_task* e = new (task::allocate_root()) tbb::empty_task();
	int red_matrica = a.red;
	e->set_ref_count(red_matrica + 1);

	zadaci_m = new MatrixTask**[red_matrica];
	zadaci_p = new MatrixTaskRoot*[red_matrica];

	for (int i = 0; i != red_matrica; i++) {
		zadaci_m[i] = new MatrixTask*[red_matrica];

		for (int j = 0; j != red_matrica; j++) {
			if (j == 0) {
				zadaci_p[i] = new (task::allocate_root()) MatrixTaskRoot(i, j, a, b, e);

			}
			else {
				zadaci_m[i][j] = new (task::allocate_root()) MatrixTask(i, j, a, b, zadaci_p[i]);
				task::spawn(*zadaci_m[i][j]);
			}	

		}

		//for (int j = 0; j != red_matrica; j++) {
		//	//ovde su zadaci vec svi napravljeni sad ih povezujemo
		//	for (int k = 0; k != red_matrica; k++) {
		//		if(k != j){
		//			zadaci[i][j]->successor[k] = zadaci[i][k];

		//		}

		//	}
		//	task::spawn(*zadaci[i][j]);
		//}
	}

	e->wait_for_all();
}
