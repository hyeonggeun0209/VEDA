#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main()
{
    Mat image = imread("mandrill.bmp", IMREAD_COLOR);

    image *= 2;

    imshow("Mat : Multiply", image); 	/* "Mat : Multiply" 창에 이미지 표시 */

    waitKey(0); 			/* 사용자의 키 입력을 대기한다. */

    return 0;
}