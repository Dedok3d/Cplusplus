#include<iostream>
#include<vector>
double findMax(std::vector<double> a) {
	double tmp = a[0];
	for (int i = 0; i < a.size(); i++) {
		if ((abs(a[i])>tmp)) {
			tmp = abs(a[i]);
		}
	}
	return abs(tmp);
}

void swapString(std::vector<double>* a, std::vector<double>* b) {
	double cmp;
	for (int t = 0; t < (*a).size(); t++) {
		cmp = (*a)[t];
		(*a)[t] = (*b)[t];
		(*b)[t] = cmp;
	}
}

double funcXn(const std::vector<double> a, std::vector<double> x, double n) {
	double tmp = 0;
	for (int i = 0; i < (a.size() - 1); i++) {
		tmp = tmp + (a[i] * x[i]);
	}
	tmp = tmp - (a[(a.size()-1)]);
	
	
	return tmp;
}

void diff(std::vector<double>* difference, std::vector<double> newX, std::vector<double> oldX) {
	for (int t = 0; t < newX.size(); t++) {
		(*difference)[t] = abs(oldX[t] - newX[t]);
	}
}

int main() {
	int n;
	double count = 0;
	double E = 0.05;
	std::vector<std::vector<double>> a;
	std::vector<double> oldX;
	std::vector<double> newX;
	std::vector<double> difference;
	std::cout << "press num :";
	std::cin >> n;
	a.resize(n);
	oldX.resize(n);
	newX.resize(n);
	difference.resize(n);
	for (int i = 0; i < n; i++) {
		newX[i] = 2;
		oldX[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		a[i].resize(n+1);
		for (int j = 0; j <= n; j++) {
			std::cin >> a[i][j];
		}
	}
	while (true) {
		swapString(&newX, &oldX);
		for (int i = 0; i < oldX.size(); i++) {
			
			newX[i] = (oldX[i] - ((funcXn(a[i], oldX, i))*(-0.01)));
			std::cout << newX[i] << " ";
		}
		diff(&difference, newX, oldX);
		count = findMax(difference);
		if (count < E) {
			
			break;
		}
		std::cout << count << std::endl;
		std::cout << std::endl;
		
	}
	/*for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j <= a.size(); j++) {
			std::cout << a[i][j] << " ";
		}
		std::cout << std::endl;
	}*/
	std::cout << std::endl;
	system("pause");
	return 0;
}
