
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main() {
    Mat image1 = imread("mandrill.bmp", IMREAD_COLOR);
    Mat image2 = imread("insta.png", IMREAD_COLOR);
    auto image = (image1 + image2) / 2;

    imshow("Add Images", image);
    waitKey(0);
    
    return 0;
}