#pragma once
#include<iostream>
#include<vector>

class Matrix {
public:
	std::vector<std::vector<double>> mat;
	
	Matrix(int size—olumn, int sizeString) {
		SetSize(size—olumn, sizeString);
	}
	void SetSize();
	void SetSize(int size—olumn, int sizeString);
	void SetMatrix();	
	void Print();
	void inversion();
	Matrix* operator*(const Matrix& right);
	Matrix* operator+(const Matrix& right);
	Matrix* operator-(const Matrix& right);
};

void DoIt();
void findInversion();
void findMultiplication();
void findSum();
void findDifference();
