#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

typedef vector<double> Vec;
typedef vector<vector<pair<int, double>>> Matrix;

int m, n, th;
Vec operator*(const Vec &v, const Matrix &m)
{
	Vec r(m.size(), 0);
#pragma omp parallel for num_threads(th)
	for (int i = 0; i < m.size(); i++)
		for (const auto &p : m[i])
			r[i] += v[p.first] * p.second;
	return r;
}
int main()
{
	//ifstream fin("492_bus.mtx");
	//ifstream fin("662_bus.mtx");
	//ifstream fin("685_bus.mtx");
	ifstream fin("1138_bus.mtx");
	while (fin.peek() == '%')
		while (fin.get() != '\n')
			;
	fin >> m >> n >> th;
	Matrix mat(m);
	for (int x, y, i = 0; i < th; i++)
	{
		double t;
		fin >> x >> y >> t;
		mat[x - 1].emplace_back(y - 1, t);
	}
	Vec vect(n);
	for (int i = 0; i < n; i++)
		vect[i] = rand();
	cout << "please input the number of threads: ";
	cin >> th;
	auto begin = std::chrono::system_clock::now();
	for (int i = 1e5; i; i--)
		vect *mat;
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - begin;
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}


