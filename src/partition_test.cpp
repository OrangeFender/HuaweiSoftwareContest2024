#include <iostream>
using namespace std;
#include <vector>
#include <random>
#include <fstream>
#include <string>

struct Square
{
    int rdx, rdy;
    int length;
};



class Solution {
public:
    vector<vector<char>> readMatrixFromFile(const string& filename) {
        vector<vector<char>> matrix;

        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Failed to open the file: " << filename << endl;
            return matrix;
        }

        string line;
        while (getline(file, line)) {
            vector<char> row;
            for (char symbol : line) {
                if (symbol == '.' || symbol == 'A') {
                    row.push_back('1');
                }
                else {
                    row.push_back('0');
                }
            }
            matrix.push_back(row);
        }

        file.close();
        return matrix;
    }




    vector<vector<char>> create()
    {
        vector<vector<char>> matrix(200, vector<char>(200, '0'));

        // 设置随机数生成器
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(0, 1);

        // 随机设置矩阵元素
        for (int i = 0; i < 200; ++i) {
            for (int j = 0; j < 200; ++j) {
                matrix[i][j] = dis(gen) == 0 ? '0' : '1';
            }
        }
        return matrix;
    }


    bool isMatrixAllZeros(const vector<vector<char>>& matrix) {
        // 遍历矩阵中的每个元素
        for (const auto& row : matrix) {
            for (const auto& element : row) {
                // 如果有任何一个元素不为 '0'，则返回 false
                if (element != '0') {
                    return false;
                }
            }
        }

        // 如果所有元素都为 '0'，则返回 true
        return true;
    }

    void print(const vector<vector<char>>& matrix)
    {
        // 遍历矩阵中的每个元素并输出
        for (const auto& row : matrix) {
            for (const auto& element : row) {
                cout << element << " ";
            }
            cout << endl;
        }
    }

    void replaceOnes(vector<vector<char>>& matrix,int bex,int endx,int bey,int endy) {
        // 检查矩阵是否为空
        if (matrix.empty() || matrix[0].empty()) {
            return;
        }

        // 获取矩阵的行数和列数
        int rows = matrix.size();
        int columns = matrix[0].size();

        // 遍历第一行和第二行的第一列和第二列
        for (int i = bex; i < endx+1; i++) {
            for (int j = bey; j < endy+1; j++) {
                // 如果元素为 '1'，将其替换为 '0'
                if (matrix[i][j] == '1') {
                    matrix[i][j] = '0';
                }
            }
        }
    }

    Square maximalSquare(vector<vector<char>>& matrix) {
        Square square;
        square.rdx = square.rdy = square.length = 0;
        //int maxSide = 0;
        int rows = matrix.size(), columns = matrix[0].size();
        vector<vector<int>> dp(rows, vector<int>(columns));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (matrix[i][j] == '1') {
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1;
                    }
                    else {
                        dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
                    }
                    if (dp[i][j] > square.length)
                    {
                        square.length = dp[i][j];
                        square.rdx = i;
                        square.rdy = j;
                    }
                    //square.length= max(square.length, dp[i][j]);
                    //maxSide = max(maxSide, dp[i][j]);
                }
            }
        }
        return square;
    }

    vector<Square> Partition(vector<vector<char>>& matrix)
    {
        Solution solution;
        vector<Square> SquareArray;
        while (solution.isMatrixAllZeros(matrix) != 1)
        {
            Square square = solution.maximalSquare(matrix);
            SquareArray.push_back(square);
            //solution.print(matrix);
            //cout << endl;
            solution.replaceOnes(matrix, square.rdx - square.length + 1, square.rdx, square.rdy - square.length + 1, square.rdy);
        }
        return SquareArray;
    }

};




int main() {
    //// 创建一个二维矩阵作为输入数据
    //vector<vector<char>> matrix = {
    //    {'1', '0', '1', '0', '0'},
    //    {'1', '0', '1', '1', '1'},
    //    {'1', '1', '1', '1', '1'},
    //    {'1', '0', '0', '1', '0'}
    //};


    //Solution solution;

    //vector<Square> SquareArray = solution.Partition(matrix);

    //for (const auto& element : SquareArray) {
    //    cout << element.rdx << " " << element.rdy << " " << element.length;
    //    cout << endl;
    //}


    //// 输出矩阵的部分内容
    //for (int i = 0; i < 200; ++i) {
    //    for (int j = 0; j < 200; ++j) {
    //        cout << matrix[i][j] << " ";
    //    }
    //    cout << endl;
    //}

    Solution solution;

    string filename = "map2.txt";
    vector<vector<char>> matrix = solution.readMatrixFromFile(filename);

    vector<Square> SquareArray = solution.Partition(matrix);

    for (const auto& element : SquareArray) {
        cout << element.rdx << " " << element.rdy << " " << element.length;
        cout << endl;
    }

    return 0;
}
