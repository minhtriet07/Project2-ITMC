include <iostream>
include <conio.h>  // Thư viện hỗ trợ các hàm như _kbhit() và _getch()
include <windows.h>  // Thư viện để sử dụng Sleep()
using namespace std;

bool gameOver;  // Biến trạng thái trò chơi
const int width = 20;  // Chiều rộng của màn hình trò chơi
const int height = 17;  // Chiều cao của màn hình trò chơi
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];  // Mảng để lưu tọa độ đuôi
int nTail;  // Số lượng đuôi
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};  // Các hướng di chuyển
eDirection dir;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    system("cls");  // Xóa màn hình (chỉ dành cho Windows)

    for (int i = 0; i < width + 2; i++) cout << "#";  // Vẽ hàng trên cùng
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";  // Vẽ biên trái
            if (i == y && j == x) cout << "O";  // Vẽ đầu rắn
            else if (i == fruitY && j == fruitX) cout << "*";  // Vẽ quả
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";  // Vẽ đuôi rắn
                        print = true;
                    }
                }
                if (!print) cout << " ";  // Vẽ khoảng trống
            }

            if (j == width - 1) cout << "#";  // Vẽ biên phải
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++) cout << "#";  // Vẽ hàng dưới cùng
    cout << endl;
    cout << "Điểm số: " << score << endl;
}

void Input() {
    if (_kbhit()) {  // Kiểm tra nếu có phím nào được nhấn
        switch (_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }

    if (x < 0 || x >= width || y < 0 || y >= height) gameOver = true;

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) gameOver = true;
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

void Run() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(10);  // Thời gian chờ giữa các bước, có thể thay đổi để thay đổi tốc độ
    }
}

int main() {
    Run();
    return 0;
}