#include"Header.h"

void Matrix::SetSize() {
	int size—olumn, sizeString;
	std::cout << "please enter column's size" << std::endl;
	std::cin >> size—olumn;
	mat.resize(size—olumn);
	std::cout << "please enter string's size" << std::endl;
	std::cin >> sizeString;
	for (int i = 0; i < mat.size(); i++) 
	{
		mat[i].resize(sizeString);
	}
}

void Matrix::SetSize(int size—olumn, int sizeString)
{
	mat.resize(size—olumn);
	for (int i = 0; i < mat.size(); i++) {
		mat[i].resize(sizeString);
	}
}

void Matrix::SetMatrix() {
	std::cout << "Please fill in the matrix:" << std::endl;
	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < mat[0].size(); j++) {
			std::cin >> mat[i][j];
		}
	}
}

void Matrix::Print()
{
	std::cout << std::endl;
	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < mat[0].size(); j++) {
			std::cout << mat[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Matrix::inversion()
{
	int N = mat.size();
	double temp;

	double **E = new double *[N];

	for (int i = 0; i < N; i++)
		E[i] = new double[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			E[i][j] = 0.0;

			if (i == j)
				E[i][j] = 1.0;
		}

	for (int k = 0; k < N; k++)
	{
		temp = mat[k][k];

		for (int j = 0; j < N; j++)
		{
			mat[k][j] /= temp;
			E[k][j] /= temp;
		}

		for (int i = k + 1; i < N; i++)
		{
			temp = mat[i][k];

			for (int j = 0; j < N; j++)
			{
				mat[i][j] -= mat[k][j] * temp;
				E[i][j] -= E[k][j] * temp;
			}
		}
	}

	for (int k = N - 1; k > 0; k--)
	{
		for (int i = k - 1; i >= 0; i--)
		{
			temp = mat[i][k];

			for (int j = 0; j < N; j++)
			{
				mat[i][j] -= mat[k][j] * temp;
				E[i][j] -= E[k][j] * temp;
			}
		}
	}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			mat[i][j] = E[i][j];

	for (int i = 0; i < N; i++)
		delete[] E[i];

	delete[] E;
}

Matrix * Matrix::operator*(const Matrix & right)
{
	
	if (mat[0].size() != right.mat.size()) {
		std::cout << "Left matrix's string's size != right matrix's string's size" << std::endl;
		system("pause");
		exit(1);
	}
	Matrix* C = new Matrix(mat.size(), mat[0].size());
	int sum;
	for (int i = 0; i < mat.size(); ++i) {
		for (int j = 0; j < mat[0].size(); ++j) {
			sum = 0;
			for (int k = 0; k < right.mat.size(); ++k)
				sum += mat[i][k] * right.mat[k][j];
			C->mat[i][j] = sum;
		}
	}
	return C;
}

Matrix * Matrix::operator+(const Matrix & right)
{
	if (mat[0].size() != right.mat[0].size() || mat.size()!= right.mat.size()) {
		std::cout << "Left matrix's string's size != right matrix's string's size" << std::endl;
		system("pause");
		exit(1);
	}
	Matrix* C = new Matrix(mat.size(), mat[0].size());
	for (int i = 0; i < mat.size(); ++i){
		for (int j = 0; j < mat[0].size(); ++j) {
			C->mat[i][j] = this->mat[i][j] + right.mat[i][j];
		}
	}
	return C;
}

Matrix * Matrix::operator-(const Matrix & right)
{
	if (mat[0].size() != right.mat[0].size() || mat.size() != right.mat.size()) {
		std::cout << "Left matrix's string's size != right matrix's string's size" << std::endl;
		system("pause");
		exit(1);
	}
	Matrix* C = new Matrix(mat.size(), mat[0].size());
	for (int i = 0; i < mat.size(); ++i) {
		for (int j = 0; j < mat[0].size(); ++j) {
			C->mat[i][j] = this->mat[i][j] - right.mat[i][j];
		}
	}
	return C;
}

void DoIt() {
	int tmp = -1;
	while (tmp != 0) {
		std::cout << "What function you want to use?" << std::endl;
		std::cout << "Enter 1 if you want find inverse matrix" << std::endl;
		std::cout << "Enter 2 if you want find multiplication matrix" << std::endl;
		std::cout << "Enter 3 or 4 if you want find matrices sum or difference matrices" << std::endl;
		std::cout << "Enter 0 if you want exit programm" << std::endl;
		std::cin >> tmp;
		switch (tmp) {
		case 1:
			findInversion();
			break;
		case 2:
			findMultiplication();
			break;
		case 3:
			findSum();
			break;
		case 4:
			findDifference();
			break;
		case 0:
			tmp = 0;
			break;
		default: 
			std::cout << "Incorrect characters, please try again" << std::endl;
			break;
		}
	}
}

void findInversion() {
	Matrix a(1, 1);
	a.SetSize();
	a.SetMatrix();
	a.inversion();
	a.Print();
}

void findMultiplication() {
	Matrix a(1, 1), b(1,1);
	std::cout << "Matrix A:" << std::endl;
	a.SetSize();
	a.SetMatrix();
	std::cout << "Matrix B:" << std::endl;
	b.SetSize();
	b.SetMatrix();
	std::cout << "A*B" << std::endl;
	(a*b)->Print();
}

void findSum() {
	Matrix a(1, 1), b(1, 1);
	std::cout << "Matrix A:" << std::endl;
	a.SetSize();
	a.SetMatrix();
	std::cout << "Matrix B:" << std::endl;
	b.SetSize();
	b.SetMatrix();
	std::cout << "A+B" << std::endl;
	(a+b)->Print();
}

void findDifference() {
	Matrix a(1, 1), b(1, 1);
	std::cout << "Matrix A:" << std::endl;
	a.SetSize();
	a.SetMatrix();
	std::cout << "Matrix B:" << std::endl;
	b.SetSize();
	b.SetMatrix();
	std::cout << "A-B" << std::endl;
	(a-b)->Print();
}