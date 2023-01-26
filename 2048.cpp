/**
*
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Deyan Petrov
* @idnumber 0MI0600169
* @compiler Visual Studio
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
void myScoreSwap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void myStrCpy(char* a, char* b)
{
	int index = 0;
	while (a[index] != '\0')
	{
		b[index] = a[index];
		++index;
	}
	b[index] = '\0';
}

void myNameSwap(char* a, char* b)
{
	char temp[32];
	myStrCpy(a, temp);
	myStrCpy(b, a);
	myStrCpy(temp, b);
}


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

int Contains(char command[], const char Search[])
{
	int LoopOne = 0;
	int LoopTwo;
	int LoopThree;
	size_t MyCharSize = strlen(command);
	size_t SearchSize = strlen(Search);
	int Yes = 0;

	while (LoopOne < MyCharSize)
	{
		if (command[LoopOne] == Search[0])
		{
			LoopTwo = 0;
			LoopThree = LoopOne;
			while (LoopTwo < SearchSize)
			{
				if (command[LoopThree] == Search[LoopTwo])
					Yes++;

				LoopTwo++;
				LoopThree++;
			}
			if (Yes == SearchSize)
				return 1;
		}
		LoopOne++;
	}
	return 0;
}

void Info_sort(int leaderboard_scores[], char names[][111], const int size)
{


	for (size_t i = 0; i < size-1; i++)
	{
		for (size_t j = 0; j < size - 1 - i; j++)
		{
			if (leaderboard_scores[j + 1] > leaderboard_scores[j])
			{
				myNameSwap(names[j + 1], names[j]);
				myScoreSwap(leaderboard_scores[j + 1], leaderboard_scores[j]);
			}
		}
	}
}


int game_over(int** board, int dimention) {
	int is_game_over = 1;
	for (int i = 0; i < dimention; i++) {
		for (int j = 0; j < dimention -1; j++) {
			if (board[i][j] == 0 || board[i][j + 1] == 0 || board[i][j] == board[i][j + 1]) {
				is_game_over = 0;
				break;
			}
		}
	}
	for (int j = 0; j < dimention ; j++) {
		for (int i = 0; i < dimention -1; i++) {
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
		for (int j = 0; j < dimention ; j++) {
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

bool CreateDefaultFile(const char* filename)
{
	ofstream file(filename);
	if (!file)
	{
		std::cout << "Error! Failed to open file and failed to create default file!\n";
		return false;
	}

	for (int i = 0; i < 5; i++)
	{
		file << "DEFAULT NAMESPACE\n";
		file << 0;
		file << "\n";
	}

	file.close();
}

bool SortAndAddPlayerToLeaderboard(const char* filename, const char* name_of_player, int score)
{
 char names[6][111]{};
	int score_keeper[6]{};
	int counter = 0;
	ifstream inputFile(filename);
	if (!inputFile)
	{
		inputFile.close();
		if (!CreateDefaultFile(filename))
		{
			std::cout << "Error! Failed to create or open file: " << filename << "!\n";
			return false;
		}
		inputFile.open(filename);
	}
	while (inputFile.getline(names[counter], 1024, '\n') &&
		inputFile >> score_keeper[counter] &&
		counter < 5)
	{
		
		inputFile.get();
		++counter;
	}
	strcpy_s(names[5], name_of_player); 
	score_keeper[5] = score;

	inputFile.close();
	Info_sort(score_keeper, names, counter);

	ofstream outputFile_4;
	outputFile_4.open(filename);
	if (!outputFile_4)
	{
		std::cout << "Error! Failed to open file\n";
		return false;
	}

	for (int i = 0; i < counter - 1; ++i)
	{
		outputFile_4 << names[i] << '\n' << score_keeper[i] << '\n';
	}

	outputFile_4.close();

	return true;
}

bool PrintLeaderboard(const char* filename)
{
	FILE* file;
	fopen_s(&file, filename, "r");
	if (!file) {
		std::cout << "cant be opened ";
		return false;
	}
	char c;
	char score[32]{};
	char name[111];
	int leaderboard_score=0;
	int counter = 0;
	int pos = 0;
    fread(&c, sizeof(char),1,file);
	while (!feof(file) && counter < 10) {
		if (c == '\n') {
			if (counter % 2 == 0) {
				name[pos] = '\0';
				std::cout << name <<'\n';

			}
			else {
				score[pos] = '\0';
				std::cout << atoi(score) << '\n';
			}
			counter++;
			pos = 0;
			fread(&c, sizeof(char), 1, file);
			continue;
	    }

		if (counter % 2 == 0) {
			name[pos++] = c;

		}
		else {
			score[pos++] = c;
		}
		fread(&c, sizeof(char), 1, file);
	}

	if (counter % 2 == 0) {
		name[pos] = '\0';
		std::cout << name << '\n';

	}
	else {
		score[pos] = '\0';
		std::cout << atoi(score) << '\n';
	}

	

	std::cout << '\n' << '\n';
	return true;
}

int main()
{

	const char filename_4[] = "dimen4_score.txt";
	const char filename_5[] = "dimen5_score.txt";
	const char filename_6[] = "dimen6_score.txt";
	const char filename_7[] = "dimen7_score.txt";
	const char filename_8[] = "dimen8_score.txt";
	const char filename_9[] = "dimen9_score.txt";
	const char filename_10[] = "dimen10_score.txt";

	const unsigned char MAX_COMMAND_SIZE = 11;

	srand((unsigned)time(NULL));
	std::cout << "Write down one of the following commands" << '\n';
	std::cout << "PlayGame" << '\n';
	std::cout << "LeaderBoard" << '\n';
	std::cout << "Quit" << '\n';
	char command[MAX_COMMAND_SIZE + 1] = {};
	char name_of_player[101] = {};
	std::cin.getline(command, MAX_COMMAND_SIZE+1);
	if (Contains(command, "PlayGame") == 1) {
		char direction;

		std::cout << "Enter your Nickname:";
		std::cin.getline(name_of_player, 100);
		int dimention;
		std::cout << "Enter the Dimension:";
		std::cin >> dimention;
		if (dimention > 10 || dimention < 4) {
			std::cout << "Wrong Dimention";
			return -1;
		}
		int** board = new int* [dimention] {};
		for (int i = 0; i < dimention; ++i) {
			board[i] = new int[dimention] {};
		}

		std::cout << '\n';
		Board_Display(board, dimention);
		while (1) {
			if (is_win(board, dimention) == 1||game_over(board,dimention)==1) {
				if (dimention == 4) {
					if (!SortAndAddPlayerToLeaderboard(filename_4, name_of_player, score)) 
					{ 
						return -1;
					}
				}
				if (dimention == 5) {
					if (!SortAndAddPlayerToLeaderboard(filename_5, name_of_player, score))
					{ 
						return -1; }
				    }
				if (dimention == 6) {
					if (!SortAndAddPlayerToLeaderboard(filename_6, name_of_player, score)) 
					{ 
						return -1; 
					}
				}
				if (dimention == 7) {
					if (!SortAndAddPlayerToLeaderboard(filename_7, name_of_player, score)) 
					{ 
						return -1; 
					}
				}
				if (dimention == 8) {
					if (!SortAndAddPlayerToLeaderboard(filename_8, name_of_player, score))
					{ 
						return -1;
				    }
				}
				if (dimention == 9) {
					if (!SortAndAddPlayerToLeaderboard(filename_9, name_of_player, score)) 
					{ 
						return -1;
					}
				}
				if (dimention == 10) {
					if (!SortAndAddPlayerToLeaderboard(filename_10, name_of_player, score)) 
					{ 
						return -1; 
					}
				}
				exit(1);
			}

			std::cout << '\n';
			std::cin >> direction;
			switch (direction) {
			case 'w':
				W_Movement(board, dimention);
				break;
			case 's':
				S_Movement(board, dimention);
				break;
			case 'a':
				A_Movement(board, dimention);
				break;
			case 'd':
				D_Movement(board, dimention);
				break;

			default:
				std::cout << "wrong command!" << '\n';
				break;
			}
			
			std::cout << "score: " << score << '\n';
		}
		return 0;
	}
	if (Contains(command, "LeaderBoard") == 1) {
		int scoreboard_dimention;
		std::cout << "choose a dimension from 4 to 10:" << '\n';
		std::cin >> scoreboard_dimention;
		if (scoreboard_dimention == 4) {
			if(!PrintLeaderboard(filename_4)) return -1;
		}
		if (scoreboard_dimention == 5) {
			if (!PrintLeaderboard(filename_5)) return -1;
		}
		if (scoreboard_dimention == 6) {
			if(!PrintLeaderboard(filename_6)) return -1;
		}
		if (scoreboard_dimention == 7) {
			if(!PrintLeaderboard(filename_7)) return -1;
		}
		if (scoreboard_dimention == 8) {
			if(!PrintLeaderboard(filename_8)) return -1;
		}
		if (scoreboard_dimention == 9) {
			if(!PrintLeaderboard(filename_9)) return -1;
		}
		if (scoreboard_dimention == 10) {
			if(!PrintLeaderboard(filename_10)) return -1;
		}
		std::cin.get();
		std::cin.get();


	}
	if (Contains(command, "Quit") == 1) {
		exit(1);
	}



}

