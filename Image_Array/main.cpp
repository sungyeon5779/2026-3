#include <iostream>
using namespace std;

#define HEIGHT 8
#define WIDTH 8

int findMaxPixel(int image[][WIDTH], int h, int w) {
int maxValue = image[0][0];

for (int i = 0; i < h; i++) {
for (int j = 0; j < w; j++) {
if (image[i][j] > maxValue) {
maxValue = image[i][j];
}
}
}

return maxValue;
}

int main() {
int image[HEIGHT][WIDTH] = {
{10, 30, 55, 80, 120, 160, 200, 230},
{20, 45, 70, 100, 140, 180, 220, 215},
{35, 60, 90, 130, 170, 210, 240, 190},
{50, 80, 115, 150, 190, 230, 255, 170},
{40, 65, 105, 140, 175, 215, 235, 150},
{25, 50, 80, 115, 195, 250, 200, 130},
{15, 35, 60, 95, 130, 185, 205, 110},
{5, 20, 40, 70, 105, 140, 160, 90}
};

int maxPixel = findMaxPixel(image, HEIGHT, WIDTH);

cout << "최대 화소 밝기: " << maxPixel << endl;

return 0;
}
