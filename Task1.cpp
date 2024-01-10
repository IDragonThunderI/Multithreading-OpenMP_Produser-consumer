#include <iostream>
#include <random>
#include <vector>

#define matrixType std::vector<std::vector<int>>

void fillMatrix(matrixType& matrix, std::mt19937& randomGenerator) {
	for (int row = 0; row < matrix.size(); row++) {
		for (int column = 0; column < matrix.size(); column++) {
			std::uniform_int_distribution<int> distribution(-100, 100);
			matrix.at(row).at(column) = distribution(randomGenerator);
		}
	}
}

void printMatrix(const matrixType& matrix) {
	for (const auto& row : matrix) {
		for (const auto& column : row) {
			std::cout << column << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

matrixType matrixCopy(const matrixType& matrix) {
	matrixType buffer(matrix.size(), std::vector<int>(matrix.size()));
	// Представление матрицы
	/*												{matrix}
					 [row]				             [row]							 [row]
		{[(column), (column), (column)], [(column), (column), (column)], [(column), (column), (column)]}

	*/
	#pragma omp parallel for shared(buffer)
		for (int row = 0; row < matrix.size(); row++) {
			for (int column = 0; column < matrix.size(); column++) {
				buffer.at(row).at(column) = matrix.at(row).at(column);
			}
		}
	return buffer;
}

int main() {
	setlocale(LC_ALL, "ru_RU.UTF-8");
	std::mt19937 randomGenerator;
	std::random_device device;
	randomGenerator.seed(device());

	size_t matrixSize;
	std::cout << "Введите размерность матрицы: ";
	std::cin >> matrixSize;
	matrixType matrixA(matrixSize, std::vector<int>(matrixSize));
	matrixType matrixB(matrixSize, std::vector<int>(matrixSize));

	fillMatrix(matrixA, randomGenerator);
	std::cout << "matrixA: " << std::endl;
	printMatrix(matrixA);

	matrixB = matrixCopy(matrixA);
	std::cout << "matrixB: " << std::endl;
	printMatrix(matrixB);

	system("pause");
	return 0;
}