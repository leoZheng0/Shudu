#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <set>

class SudokuGenerator {
public:
    SudokuGenerator() {
        srand(static_cast<unsigned>(time(0)));
        generate();
    }

    void print() const {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                std::cout << board[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }
    // Return a string representing the Sudoku board
    std::string getString() const {
        std::string str;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                str += std::to_string(board[i][j]);
            }
        }
        return str;
    }
// Create a game with a certain difficulty
void createGame(int difficulty) {
    int numHoles;
    switch (difficulty) {
        case 1:
            numHoles = 20;
            break;
        case 2:
            numHoles = 30;
            break;
        case 3:
            numHoles = 40;
            break;
        default:
            numHoles = 20;
            break;
    }
    digHoles(numHoles);
}
    bool isValid(int row, int col, int num) {
        // Check the number in the row
        for (int x = 0; x < 9; x++)
            if (board[row][x] == num)
                return false;

        // Check the number in the col
        for (int y = 0; y < 9; y++)
            if (board[y][col] == num)
                return false;

        // Check the number in the box
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i + startRow][j + startCol] == num)
                    return false;

        return true;
    }
    bool solve() {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (board[row][col] == 0) {
                    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                    std::random_shuffle(nums.begin(), nums.end());  // Randomly shuffle the numbers for each cell

                    for (int num : nums) {
                        if (isValid(row, col, num)) {
                            board[row][col] = num;
                            if (solve()) {
                                return true;
                            }
                            board[row][col] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    void generate() {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                board[i][j] = 0;
            }
        }

        solve();
    }

    int getBoard(int i, int j) {
        return board[i][j];
    }

    void writeToFile(const std::string& filePath) const {
        std::ofstream file(filePath);
        if (file.is_open()) {
            for (int i = 0; i < 9; ++i) {
                for (int j = 0; j < 9; ++j) {
                    if (board[i][j] == 0) {
                        file << '$' << ' ';
                    } else {
                        file << board[i][j] << ' ';
                    }
                }
                file << '\n';
            }
            file.close();
        } else {
            std::cout << "Unable to open file\n";
        }
    }

private:
    int board[9][9]{};

    // Create a game by digging holes in the completed board
    void digHoles(int numHoles) {
        int count = 0;
        while (count < numHoles) {
            int i = rand() % 9;
            int j = rand() % 9;
            if (board[i][j] != 0) {
                board[i][j] = 0;
                count++;
            }
        }
    }

};
class SudokuSolver {
public:
    SudokuSolver(int input[9][9]) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                board[i][j] = input[i][j];
            }
        }
    }
    SudokuSolver(std::vector<std::vector<int>> input) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                board[i][j] = input[i][j];
            }
        }
    }

    bool solve() {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                if (board[row][col] == 0) {
                    for (int num = 1; num <= 9; num++) {
                        if (isValid(row, col, num)) {
                            board[row][col] = num;
                            if (solve()) {
                                return true;
                            }
                            board[row][col] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    void print() const {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                std::cout << board[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }

// Check if the given sudoku has a unique solution
bool hasUniqueSolution() {
    int count = 0;
    for (int num = 1; num <= 9; num++) {
        if (isValid(0, 0, num)) {
            board[0][0] = num;
            if (solve()) {
                count++;
                if (count > 1) {
                    return false;
                }
            }
            board[0][0] = 0;
        }
    }
    return count == 1;
}

private:
    int board[9][9];

    bool isValid(int row, int col, int num) {
        // Check the number in the row
        for (int x = 0; x < 9; x++)
            if (board[row][x] == num)
                return false;

        // Check the number in the col
        for (int y = 0; y < 9; y++)
            if (board[y][col] == num)
                return false;

        // Check the number in the box
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i + startRow][j + startCol] == num)
                    return false;

        return true;
    }
};

std::vector<std::vector<int>> readSudokuFromFile(const std::string& filePath) {
    std::vector<std::vector<int>> sudoku(9, std::vector<int>(9, 0));
    std::ifstream file(filePath);

    if (file.is_open()) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                char ch;
                file >> ch;
                if (ch == '$') {
                    sudoku[i][j] = 0;
                } else {
                    sudoku[i][j] = ch - '0';
                }
            }
        }
        file.close();
    } else {
        std::cout << "Unable to open file\n";
    }

    return sudoku;
}
void writeSudokuToFile(const std::vector<std::vector<int>>& sudoku, const std::string& filePath) {
    std::ofstream file(filePath);

    if (file.is_open()) {
        for (const auto& row : sudoku) {
            for (int num : row) {
                if (num == 0) {
                    file << '$' << ' ';
                } else {
                    file << num << ' ';
                }
            }
            file << '\n';
        }
        file.close();
    } else {
        std::cout << "Unable to open file\n";
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    std::set<std::string> generatedSudokus;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            int num = std::stoi(argv[i + 1]);
            for (int j = 0; j < num; ++j) {
                SudokuGenerator generator;
                // Generate a unique Sudoku endgame
                while (true) {
                    generator.generate();
                    if (generatedSudokus.insert(generator.getString()).second) {
                        break;
                    }
                }
                generator.writeToFile(R"(C:\Users\ASUS\CLionProjects\Shudo\EndGames\game_)" + std::to_string(j) + ".txt");
                generator.print();
                std::cout << '\n';
            }
        } else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            std::vector<std::vector<int>> sudoku = readSudokuFromFile(argv[i + 1]);
            SudokuSolver solver(sudoku);
            if (solver.solve()) {
                solver.print();
            } else {
                std::cout << "No solution\n";
            }
        }  else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            int numGames = std::stoi(argv[i + 1]);
            for (int j = 0; j < numGames; ++j) {
                SudokuGenerator generator;
                generator.createGame(1);
                while (true) {
                    std::vector<std::vector<int>> board(9, std::vector<int>(9, 0));
                    for (int i = 0; i < 9; ++i) {
                        for (int j = 0; j < 9; ++j) {
                            board[i][j] = generator.getBoard(i, j);
                        }
                    }
                    SudokuSolver solver(board);
                    if (solver.hasUniqueSolution() && generatedSudokus.insert(generator.getString()).second) {
                        break;
                    }
                    generator.generate();
                    generator.createGame(1);
                }
                generator.writeToFile(R"(C:\Users\ASUS\CLionProjects\Shudo\Games\game_)" + std::to_string(j) + ".txt");
                generator.print();
                std::cout << '\n';
            }
        } else if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            if (i == 1 || strcmp(argv[i - 2], "-n") != 0) {
                std::cout << "The -m option cannot be used alone.\n";
                return 1;
            }

            int difficulty = std::stoi(argv[i + 1]);
            int numGames = std::stoi(argv[i - 1]);
            for (int j = 0; j < numGames; ++j) {
                SudokuGenerator generator;
                generator.createGame(difficulty);
                while (true) {
                    std::vector<std::vector<int>> board(9, std::vector<int>(9, 0));
                    for (int i = 0; i < 9; ++i) {
                        for (int j = 0; j < 9; ++j) {
                            board[i][j] = generator.getBoard(i, j);
                        }
                    }
                    SudokuSolver solver(board);
                    if (solver.hasUniqueSolution() && generatedSudokus.insert(generator.getString()).second) {
                        break;
                    }
                    generator.generate();
                    generator.createGame(difficulty);
                }
                generator.writeToFile(R"(C:\Users\ASUS\CLionProjects\Shudo\Games\game_)" + std::to_string(j) + "_" + std::to_string(difficulty) + ".txt");
                generator.print();
                std::cout << '\n';
            }
        }
    }

    return 0;
}
