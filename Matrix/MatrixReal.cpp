#include"Header.h"

int Matrix::GetSizeСolumn()
{
	return sizeСolumn;
}

int Matrix::GetSizeString()
{
	return sizeString;
}

void Matrix::SetSizeСolumn(int size)
{
	sizeСolumn = size;
}

void Matrix::SetSizeString(int size)
{
	sizeString = size;
}

void Matrix::SetSize() {
	int t_sizeСolumn, t_sizeString;
	std::cout << "please enter column's size" << std::endl;
	std::cin >> t_sizeСolumn;
	SetSizeСolumn(t_sizeСolumn);
	mat = new double*[sizeСolumn];
	std::cout << "please enter string's size" << std::endl;
	std::cin >> t_sizeString;
	SetSizeString(t_sizeString);
	for (int i = 0; i < t_sizeСolumn; i++)
	{
		mat[i] = new double[t_sizeString];
	}
}

void Matrix::SetSize(int t_sizeСolumn, int t_sizeString)
{
	SetSizeСolumn(t_sizeСolumn);
	SetSizeString(t_sizeString);
	mat = new double*[t_sizeСolumn];
	for (int i = 0; i < t_sizeСolumn; i++) {
		mat[i] = new double[t_sizeString];
	}
}


void Matrix::inversion()
{
	int N = GetSizeСolumn();
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

Matrix * Matrix::operator*( Matrix & right) 
{
	
	if (this->GetSizeString() != right.GetSizeСolumn()) {
		std::cout << "Left matrix's string's size != right matrix's column's size" << std::endl;
		system("pause");
		return nullptr;
	}
	Matrix* C = new Matrix(this->GetSizeСolumn(),this->GetSizeString());
	double sum;
	for (int i = 0; i < this->GetSizeСolumn(); ++i) {
		for (int j = 0; j < this->GetSizeString(); ++j) {
			sum = 0;
			for (int k = 0; k < right.sizeСolumn; ++k)
				sum += mat[i][k] * right.mat[k][j];
			C->mat[i][j] = sum;
		}
	}
	return C;
}

Matrix * Matrix::operator+(Matrix & right)
{
	if (this->GetSizeString() != right.GetSizeString() || this->GetSizeСolumn()!= right.GetSizeСolumn()){
		std::cout << "Left matrix's string's size != right matrix's string's size" << std::endl;
		system("pause");
		return nullptr;
	}
	Matrix* C = new Matrix(this->GetSizeСolumn(), this->GetSizeString());
	for (int i = 0; i < this->GetSizeСolumn(); ++i){
		for (int j = 0; j < this->GetSizeString(); ++j) {
			C->mat[i][j] = this->mat[i][j] + right.mat[i][j];
		}
	}
	return C;
}

Matrix * Matrix::operator-(Matrix & right)
{
	if (this->GetSizeString() != right.GetSizeString() || this->GetSizeСolumn() != right.GetSizeСolumn()) {
		std::cout << "Left matrix's string's size != right matrix's string's size" << std::endl;
		system("pause");
		return nullptr;
	}
	Matrix* C = new Matrix(this->GetSizeСolumn(), this->GetSizeString());
	for (int i = 0; i < this->GetSizeСolumn(); ++i) {
		for (int j = 0; j < this->GetSizeString(); ++j) {
			C->mat[i][j] = this->mat[i][j] - right.mat[i][j];
		}
	}
	return C;
}

std::istream & operator>>(std::istream & in, Matrix & A)
{
	std::cout << "Please fill in the matrix:" << std::endl;
	for (int i = 0; i < A.GetSizeСolumn(); i++) {
		for (int j = 0; j < A.GetSizeString(); j++) {
			in >> A.mat[i][j];
		}
	}
	return in;
}

std::ostream & operator<<(std::ostream & out, Matrix & A)
{
	out << std::endl;
	for (int i = 0; i < A.GetSizeСolumn(); i++) {
		for (int j = 0; j < A.GetSizeString(); j++) {
			out << A.mat[i][j] << " ";
		}
		out << std::endl;
	}
	return out;
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
	system("cls");
}

void findInversion() {
	Matrix a(1, 1);
	a.SetSize();
	std::cin >> a;
	a.inversion();
	std::cout << a;
}

void findMultiplication() {
	Matrix a(1, 1), b(1,1);
	std::cout << "Matrix A:" << std::endl;
	a.SetSize();
	std::cin >> a;
	std::cout << "Matrix B:" << std::endl;
	b.SetSize();
	std::cin >> b;
	std::cout << "A*B" << std::endl;
	std::cout << *(a*b);
}

void findSum() {
	Matrix a(1, 1), b(1, 1);
	std::cout << "Matrix A:" << std::endl;
	a.SetSize();
	std::cin >> a;
	std::cout << "Matrix B:" << std::endl;
	b.SetSize();
	std::cin >> b;
	std::cout << "A+B" << std::endl;
	std::cout << *(a+b);
}

void findDifference() {
	Matrix a(1, 1), b(1, 1);
	std::cout << "Matrix A:" << std::endl;
	a.SetSize();
	std::cin >> a;
	std::cout << "Matrix B:" << std::endl;
	b.SetSize();
	std::cin >> b;
	std::cout << "A-B" << std::endl;
	std::cout << *(a-b);
}
