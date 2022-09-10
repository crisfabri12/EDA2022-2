#include <ctime>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

class point {
public:
	int n;
	vector<long long> dim;
	
	point(int dim) {
		this->n = dim;
		for (int i = 0; i < n; i++) {
			long long ran = rand();
			this->dim.push_back(ran);
		}
	}
};

void dimesion_3(int n) {
	vector<point> vec;
	for (int i = 0; i < n; i++) {
		point *aux = new point(3);
		vec.push_back(*aux);
	}
	
	unsigned t0, t1;
	
	t0 = clock();
	point p = vec[0];
	for (int i = 1; i < n; i++) {
		long long dist = 0;
		for (int j = 0; j < 3; j++) {
			long long dif = p.dim[j] - vec[i].dim[j];
			dist += pow(dif, 2);
		}
		dist = sqrt(dist);
	}
	
	t1 = clock();
	double time = (double(t1 - t0) / CLOCKS_PER_SEC);
	cout << "Execution Time: " << time << endl;
}

void distancia(int n, int dim) {
	vector<point> vec;
	for (int i = 0; i < n; i++) {
		point *aux = new point(dim);
		vec.push_back(*aux);
	}
	
	unsigned t0, t1;
	
	t0 = clock();
	point p = vec[0];
	for (int i = 1; i < n; i++) {
		long long dist;
		for (int j = 0; j < dim; j++) {
			long long dif = p.dim[j] - vec[i].dim[j];
			dist += pow(dif, 2);
		}
		dist = sqrt(dist);
	}
	
	t1 = clock();
	double time = (double(t1 - t0) / CLOCKS_PER_SEC);
	cout << "Execution Time: " << time << endl;
}

int main() { 
	
	cout<< "a: ";
	dimesion_3(1000); 
	cout<< "b: ";
	dimesion_3(10000);
	cout<< "c: ";
	dimesion_3(20000);
	
	cout<<endl;
	
	
	cout<< "a: ";
	distancia(100,1000);
	cout<< "b: ";
	distancia(100,10000);
	cout<< "c: ";
	distancia(100,50000);
	
}
