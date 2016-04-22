#pragma once
#include<iostream>
//using std::istream;

class Matrix {
public:
	double **mat;
	int sizeСolumn, sizeString;

	/*t_... - temporary variable*/
	Matrix(int t_sizeСolumn, int t_sizeString) {
		mat = nullptr;
		SetSize(t_sizeСolumn, t_sizeString);
	}
	int GetSizeСolumn();
	int GetSizeString();
	void SetSizeСolumn(int size);
	void SetSizeString(int size);
	void SetSize();
	void SetSize(int t_sizeСolumn, int t_sizeString);
	void inversion();
	/*перезагрузка должна быть дружественной, т.к. используеться класс iostream и пользовательский*/
	friend std::istream& operator>>(std::istream &in, Matrix &A);
	friend std::ostream& operator<<(std::ostream &out, Matrix &A);
	Matrix* operator*(Matrix& right);
	Matrix* operator+(Matrix& right);
	Matrix* operator-(Matrix& right);
	~Matrix() {
		for (int i = 0; i < GetSizeСolumn(); i++) {
			delete [] mat[i];
		}
		delete[] mat;
	}
};

void DoIt();
void findInversion();
void findMultiplication();
void findSum();
void findDifference();
