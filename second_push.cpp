/**
*
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Deyan Petrov
* @idnumber 0MI0600169
* @compiler VC
*
* <cpp file containing the full project>
*
*/




#include <iostream>
#include <fstream>
#include <iomanip>//only for the purpose of using setw()

using namespace std;
int score;
int turns;



int generate_number() {
	int res = rand() % 10 + 1;
	if (res == 0) {
		return 4;
	}
	else {
		return 2;
	}
}
int generate_index(int dimention) {
	int generated_index = rand() % dimention;
	return generated_index;
}

int is_win(int** board, int dimention) {
	for (int i = 0; i < dimention; i++) {
		for (int j = 0; j < dimention; j++) {
			if (board[i][j] == 2048) {
				return 1;
			}
		}
	}
	return 0;
}



int game_over(int** board, int dimention) {
	int is_game_over = 1;
	for (int i = 0; i < dimention; i++) {
		for (int j = 0; j < dimention - 1; j++) {
			if (board[i][j] == 0 || board[i][j + 1] == 0 || board[i][j] == board[i][j + 1]) {
				is_game_over = 0;
				break;
			}
		}
	}
	for (int j = 0; j < dimention; j++) {
		for (int i = 0; i < dimention - 1; i++) {
			if (board[i][j] == 0 || board[i + 1][j] == 0 || board[i][j] == board[i + 1][j]) {
				is_game_over = 0;
				break;
			}
		}
	}
	return is_game_over;
}

void include_new_element(int** board, int dimention) {
	int index_row = 0;
	int index_column;
	int checker = 0;
	while (true) {
		if (checker == 1) {
			break;
		}
		else {
			index_row = generate_index(dimention);
			index_column = generate_index(dimention);
			if (board[index_row][index_column] == 0) {
				board[index_row][index_column] = generate_number();
				checker = 1;
			}
		}
	}
}
int sum_of_score(int** board, int dimention) {

	int result = 0;
	for (int i = 0; i < dimention; i++) {
		for (int j = 0; j < dimention; j++) {
			result += board[i][j];
		}
	}
	return result;
}
void Board_Display(int** board, int dimention) {
	int row_index_1, column_index_1, row_index_2, column_index_2;

	while (1) {
		row_index_1 = generate_index(dimention);
		column_index_1 = generate_index(dimention);
		row_index_2 = generate_index(dimention);
		column_index_2 = generate_index(dimention);
		if (row_index_1 == row_index_2 && column_index_1 == column_index_2) {
			continue;
		}
		else
			break;
	}
	if (turns == 0) {
		for (int i = 0; i < dimention; i++) {

			for (int j = 0; j < dimention; j++) {

				if (i == row_index_1 && j == column_index_1) {
					board[i][j] = 2;
					std::cout << setw(5) << 2 << setw(5);
				}
				else if (i == row_index_2 && j == column_index_2) {
					int temp = generate_number();
					board[i][j] = temp;
					std::cout << setw(5) << temp << setw(5);
				}
				else {
					std::cout << setw(5) << board[i][j] << setw(5);

				}
			}
			std::cout << '\n';
		}

	}

	else {
		for (int i = 0; i < dimention; i++) {

			for (int j = 0; j < dimention; j++) {
				if (board[i][j] != 0) {
					if (board[i][j] == 1024 || board[i][j] == 2048) {
						std::cout << setw(5) << board[i][j];

					}
					if (board[i][j] == 128 || board[i][j] == 256 || board[i][j] == 512) {
						std::cout << setw(5) << board[i][j] << setw(5);
					}

					if (board[i][j] == 16 || board[i][j] == 32 || board[i][j] == 64) {
						std::cout << setw(5) << board[i][j] << setw(5);

					}
					if (board[i][j] == 2 || board[i][j] == 4 || board[i][j] == 8) {
						std::cout << setw(5) << board[i][j] << setw(5);

					}
				}
				else {
					std::cout << setw(5) << board[i][j] << setw(5);
				}
			}
			std::cout << '\n';
		}

	}

}
void A_Movement(int** board, int dimention) {
	int flag = 0;
	for (int i = 0; i < dimention; i++) {
		int n = 0;
		int prev = 0;
		for (int j = 0; j < dimention; j++)
		{
			if (n == board[i][j] && n != 0) {
				board[i][prev] = 2 * n;
				board[i][j] = 0;
				n = 0;
				flag++;
				continue;
			}
			if (board[i][j] != 0) {
				n = board[i][j];
				prev = j;
			}
		}
	}
	for (int i = 0; i < dimention; i++) {
		for (int j = 0; j < dimention; j++) {
			for (int k = 0; k < dimention - 1; k++) {
				if (board[i][k] == 0 && board[i][k + 1] != 0) {
					board[i][k] = board[i][k] ^ board[i][k + 1];
					board[i][k + 1] = board[i][k] ^ board[i][k + 1];
					board[i][k] = board[i][k] ^ board[i][k + 1];
					flag++;
				}
			}
		}
	}
	if (flag != 0) {

		include_new_element(board, dimention);
		score = sum_of_score(board, dimention);
		turns++;
	}
	Board_Display(board, dimention);
}

void D_Movement(int** board, int dimention) {
	int flag = 0;
	for (int i = 0; i < dimention; i++) {
		int n = 0;
		int prev = 0;
		for (int j = dimention - 1; j >= 0; j--)
		{
			if (n == board[i][j] && n != 0) {
				board[i][prev] = 2 * n;
				board[i][j] = 0;
				n = 0;
				flag++;
				continue;
			}
			if (board[i][j] != 0) {
				n = board[i][j];
				prev = j;
			}
		}
	}
	for (int i = 0; i < dimention; i++) {
		for (int j = 0; j < dimention; j++) {
			for (int k = dimention - 1; k > 0; k--) {
				if (board[i][k] == 0 && board[i][k - 1] != 0) {
					board[i][k] = board[i][k] ^ board[i][k - 1];
					board[i][k - 1] = board[i][k] ^ board[i][k - 1];
					board[i][k] = board[i][k] ^ board[i][k - 1];
					flag++;
				}
			}
		}
	}
	if (flag != 0) {
		include_new_element(board, dimention);
		score = sum_of_score(board, dimention);
		turns++;
	}
	Board_Display(board, dimention);
}

void W_Movement(int** board, int dimention) {
	int flag = 0;
	for (int i = 0; i < dimention; i++) {
		int n = 0;
		int prev = 0;
		for (int j = 0; j < dimention; j++)
		{
			if (n == board[j][i] && n != 0) {
				board[prev][i] = 2 * n;
				board[j][i] = 0;
				n = 0;
				flag++;
				continue;
			}
			if (board[j][i] != 0) {
				n = board[j][i];
				prev = j;
			}
		}
	}
	for (int i = 0; i < dimention; i++) {
		for (int j = 0; j < dimention; j++) {
			for (int k = 0; k < dimention - 1; k++) {
				if (board[k][i] == 0 && board[k + 1][i] != 0) {
					board[k][i] = board[k][i] ^ board[k + 1][i];
					board[k + 1][i] = board[k][i] ^ board[k + 1][i];
					board[k][i] = board[k][i] ^ board[k + 1][i];
					flag++;
				}
			}
		}
	}
	if (flag != 0) {

		include_new_element(board, dimention);
		score = sum_of_score(board, dimention);
		turns++;
	}
	Board_Display(board, dimention);
}

void S_Movement(int** board, int dimention) {
	int flag = 0;
	for (int i = 0; i < dimention; i++) {
		int n = 0;
		int prev = 0;
		for (int j = dimention - 1; j >= 0; j--)
		{
			if (n == board[j][i] && n != 0) {
				board[prev][i] = 2 * n;
				board[j][i] = 0;

				n = 0;
				flag++;
				continue;
			}
			if (board[j][i] != 0) {
				n = board[j][i];
				prev = j;
			}
		}
	}
	for (int i = 0; i < dimention; i++) {
		for (int j = 0; j < dimention; j++) {
			for (int k = dimention - 1; k > 0; k--) {
				if (board[k][i] == 0 && board[k - 1][i] != 0) {
					board[k][i] = board[k][i] ^ board[k - 1][i];
					board[k - 1][i] = board[k][i] ^ board[k - 1][i];
					board[k][i] = board[k][i] ^ board[k - 1][i];
					flag++;
				}
			}
		}
	}
	if (flag != 0) {
		include_new_element(board, dimention);
		score = sum_of_score(board, dimention);
		turns++;
	}
	Board_Display(board, dimention);
}
