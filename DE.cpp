#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime> 

using namespace std;
ofstream fout("record.csv");//開啟檔案  

class vector {//製造出2維向量 
public:
	double dim[2];//dim[0]是x，dim[1]是y 
};

double magicbox_sphere(vector arr) {//magicbox_sphere是sphere方程式的公式 
	double result = 0.0;
	int i;

	for (i = 0; i < 2; i++) {
		result = result + pow(arr.dim[i], 2);
	}

	return result;
}
double magicbox_rastrigin(vector ar) {/*magicbox_rastrigin是rastrigin方程式的公式*/
	double result = 0.0;
	double pi = 3.141592653589793116;

	result = 20.0 + pow(ar.dim[0], 2.0) - 10.0 * cos(2.0 * pi * ar.dim[0]) +
		pow(ar.dim[1], 2.0) - 10.0 * cos(2.0 * pi * ar.dim[1]);

	return result;
}

double Differential_Evolution_sp(double left, double right) {

	int i, j, k;
	double F = 1.0;
	double CR = 0.8;
	double prob;
	double output;
	double file_out;
	int q;
	int rand_1, rand_2, rand_3;
	vector particle[10];//產生10個向量 
	vector particle_mu[10];//突變後的向量
	vector particle_cr[10];//trial vector
	vector particle_best;//目前最好的結果 

	srand(time(NULL));//以系統時間作為亂數種子 

	//initialization
	for (i = 0; i < 10; i++) {//對10個向量進行隨機的數值初始化 
		particle[i].dim[0] = (right - left) * rand() / RAND_MAX + left;
		particle[i].dim[1] = (right - left) * rand() / RAND_MAX + left;
	}

	//cout<<"x = "<<particle[3].dim[0]<<", y = "<<particle[3].dim[1];
	/*可以用陣列當作物件內的屬性*/

	particle_best = particle[0];

	for (j = 0; j < 1000; j++) {//1000次迭代開始 

		F = F / 1.0001;

		//mutation_fundamental 		
		/*for(i=0;i < 10;i++){
			while(1){//隨機選取0~9之間的10個數字
				rand_1 = rand() % 10;
				rand_2 = rand() % 10;
				rand_3 = rand() % 10;

				if(rand_1 != rand_2 && rand_1 != rand_3 && rand_2 != rand_3){
					break;
				}
			}

			particle_mu[i].dim[0] = particle[rand_1].dim[0] + F * (particle[rand_2].dim[0] - particle[rand_3].dim[0]);
			particle_mu[i].dim[1] = particle[rand_1].dim[1] + F * (particle[rand_2].dim[1] - particle[rand_3].dim[1]);
		}*/

		//mutation_advanced
		//論出現的最小數字，感覺mutation之基礎法和改進法沒差多少，但是改進法
		//的數字比較穩定，基礎法數字跳動的幅度大 
		for (i = 0; i < 10; i++) {
			while (1) {//隨機選取0~9之間的10個數字 
				rand_1 = rand() % 10;
				rand_2 = rand() % 10;


				if (rand_1 != rand_2) {
					break;
				}
			}

			particle_mu[i].dim[0] = particle[i].dim[0] + F * (particle_best.dim[0] - particle[i].dim[0]) +
				F * (particle[rand_1].dim[0] - particle[rand_2].dim[0]);
			particle_mu[i].dim[1] = particle[i].dim[1] + F * (particle_best.dim[1] - particle[i].dim[1]) +
				F * (particle[rand_1].dim[1] - particle[rand_2].dim[1]);
		}

		//crossover
		for (i = 0; i < 10; i++) {
			prob = (double)rand() / RAND_MAX;
			q = rand() % 2;
			for (k = 0; k < 1; k++) {
				if (prob <= CR || k == q) {
					particle_cr[i].dim[k] = particle_mu[i].dim[k];
					if (particle_cr[i].dim[k] > 100.0) {//處理邊界問題 
						particle_cr[i].dim[k] = 100.0;
					}
					else if (particle_cr[i].dim[k] < -100.0) {
						particle_cr[i].dim[k] = -100.0;
					}
				}
				else {
					particle_cr[i].dim[k] = particle[i].dim[k];
				}
			}
		}

		//selection
		for (i = 0; i < 10; i++) {
			if (magicbox_sphere(particle[i]) > magicbox_sphere(particle_cr[i])) {
				particle[i].dim[0] = particle_cr[i].dim[0];
				particle[i].dim[1] = particle_cr[i].dim[1];
			}
			else {//維持原樣 
				;
			}
		}

		for (i = 0; i < 10; i++) {//挑選出目前10個向量中，fitness最好的那個 
			if (magicbox_sphere(particle[i]) < magicbox_sphere(particle_best)) {
				particle_best.dim[0] = particle[i].dim[0];
				particle_best.dim[1] = particle[i].dim[1];
			}
		}

		file_out = magicbox_sphere(particle_best);
		fout << file_out << ',';

	}

	output = magicbox_sphere(particle_best);
	fout << endl;

	return output;
}

double Differential_Evolution_ra(double left, double right) {

	int i, j, k;
	double F = 1.0;
	double CR = 0.8;
	double prob;
	double output;
	double file_out;
	int q;
	int rand_1, rand_2, rand_3;
	vector particle[10];//產生10個向量 
	vector particle_mu[10];//突變後的向量
	vector particle_cr[10];//trial vector
	vector particle_best;//目前最好的結果 

	srand(time(NULL));//以系統時間作為亂數種子 

	//initialization
	for (i = 0; i < 10; i++) {//對10個向量進行隨機的數值初始化 
		particle[i].dim[0] = (right - left) * rand() / RAND_MAX + left;
		particle[i].dim[1] = (right - left) * rand() / RAND_MAX + left;
	}

	particle_best = particle[0];

	for (j = 0; j < 1000; j++) {

		F = F / 1.0001;

		//mutation_fundamental 		
		/*for(i=0;i < 10;i++){
			while(1){//隨機選取0~9之間的10個數字
				rand_1 = rand() % 10;
				rand_2 = rand() % 10;
				rand_3 = rand() % 10;

				if(rand_1 != rand_2 && rand_1 != rand_3 && rand_2 != rand_3){
					break;
				}
			}

			particle_mu[i].dim[0] = particle[rand_1].dim[0] + F * (particle[rand_2].dim[0] - particle[rand_3].dim[0]);
			particle_mu[i].dim[1] = particle[rand_1].dim[1] + F * (particle[rand_2].dim[1] - particle[rand_3].dim[1]);
		}*/

		//mutation_advanced 
		for (i = 0; i < 10; i++) {
			while (1) {//隨機選取0~9之間的10個數字 
				rand_1 = rand() % 10;
				rand_2 = rand() % 10;

				if (rand_1 != rand_2) {
					break;
				}
			}

			particle_mu[i].dim[0] = particle[i].dim[0] + F * (particle_best.dim[0] - particle[i].dim[0]) +
				F * (particle[rand_1].dim[0] - particle[rand_2].dim[0]);
			particle_mu[i].dim[1] = particle[i].dim[1] + F * (particle_best.dim[1] - particle[i].dim[1]) +
				F * (particle[rand_1].dim[1] - particle[rand_2].dim[1]);
		}

		//crossover
		for (i = 0; i < 10; i++) {
			prob = (double)rand() / RAND_MAX;
			q = rand() % 2;
			for (k = 0; k < 1; k++) {
				if (prob <= CR || k == q) {
					particle_cr[i].dim[k] = particle_mu[i].dim[k];
					if (particle_cr[i].dim[k] > 1.5) {//處理邊界問題 
						particle_cr[i].dim[k] = 1.5;
					}
					else if (particle_cr[i].dim[k] < -1.5) {
						particle_cr[i].dim[k] = -1.5;
					}
				}
				else {
					particle_cr[i].dim[k] = particle[i].dim[k];
				}
			}
		}

		//selection
		for (i = 0; i < 10; i++) {
			if (magicbox_rastrigin(particle[i]) > magicbox_rastrigin(particle_cr[i])) {
				particle[i].dim[0] = particle_cr[i].dim[0];
				particle[i].dim[1] = particle_cr[i].dim[1];
			}
			else {//維持原樣 
				;
			}
		}

		for (i = 0; i < 10; i++) {//挑選出目前10個向量中，fitness最好的那個 
			if (magicbox_rastrigin(particle[i]) < magicbox_rastrigin(particle_best)) {
				particle_best.dim[0] = particle[i].dim[0];
				particle_best.dim[1] = particle[i].dim[1];
			}
		}

		file_out = magicbox_rastrigin(particle_best);
		fout << file_out << ',';

	}

	output = magicbox_rastrigin(particle_best);
	fout << endl;

	return output;

}

int main() {

	double result;
	int p;

	result = Differential_Evolution_sp(-100, 100);

	cout << "Sphere " << "Z(fitness) = " << result << endl;
	cout << "---------------------------------------------" << '\n';
	for (p = 0; p < 9; p++) {
		Differential_Evolution_sp(-100, 100);
	}

	fout << endl;
	fout << endl;
	fout << endl;

	result = Differential_Evolution_ra(-1.5, 1.5);

	cout << "Rastrigin " << "Z(fitness) = " << result << endl;
	cout << "---------------------------------------------" << '\n';
	for (p = 0; p < 9; p++) {
		Differential_Evolution_ra(-1.5, 1.5);
	}

	fout.close();//關閉檔案  

	return 0;
}