#include <iostream>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    Mat image;
    int x1, y1, x2, y2;

    image = imread("biel.png", IMREAD_GRAYSCALE);
    if (!image.data) {
        cout << "nao abriu biel.png" << endl;
        return -1;
    }

    cout << "Escolha o X do p1: ";
    cin >> x1;

    cout << "Escolha o Y do p1: ";
    cin >> y1;

    cout << "Escolha o X do p2: ";
    cin >> x2;

    cout << "Escolha o Y do p2: ";
    cin >> y2;

    for (int i = x1; i < x2; i++) {
        for (int j = y1; j < y2; j++) {
            image.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);
        }
    }

    imshow("biel invertido", image);
    imwrite("invertido.png", image);
    waitKey();

    return 0;
}