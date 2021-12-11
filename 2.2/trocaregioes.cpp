#include <iostream>
#include <opencv2/opencv.hpp>
#include <random> 


using namespace cv;
using namespace std;
using namespace chrono;

int main(int argc, char** argv) {
    Mat image;

    image = imread("biel.png", IMREAD_GRAYSCALE);
    if (!image.data) {
        cout << "nao abriu biel.png" << endl;
        return -1;
    }

    Mat embaralhada = image.clone();
    int largura_central = image.cols/2;
    int altura_central = image.rows/2;

    Rect im1_region = Rect(0, 0, largura_central, altura_central);
    Rect im2_region = Rect(largura_central, 0, largura_central, altura_central);
    Rect im3_region = Rect(0, altura_central, largura_central, altura_central);
    Rect im4_region = Rect(largura_central, altura_central, largura_central, altura_central);

    Mat im1 = image(im1_region);
    Mat im2 = image(im2_region);
    Mat im3 = image(im3_region);
    Mat im4 = image(im4_region);

    Rect region_array[4] = { im1_region , im2_region , im3_region , im4_region };
    int order_array[4] = { 0 , 1 , 2 , 3 };
    shuffle(begin(order_array), end(order_array), default_random_engine(system_clock::now().time_since_epoch().count()));

    im1.copyTo(embaralhada(region_array[order_array[0]]));
    im2.copyTo(embaralhada(region_array[order_array[1]]));
    im3.copyTo(embaralhada(region_array[order_array[2]]));
    im4.copyTo(embaralhada(region_array[order_array[3]]));

    cv::imshow("embaralhado", embaralhada);
    cv::imwrite("embaralhado.png", embaralhada);
    cv::waitKey();

    return 0;
}