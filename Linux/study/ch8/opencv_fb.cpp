#include <fcntl.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

#define FBDEV "/dev/fb0"
#define CAMERA_COUNT 100
#define CAM_WIDTH 640
#define CAM_HEIGHT 480

int main(int argc, char **argv)
{
    int fbfd;

    /* 프레임 버퍼 정보 처리를 위한 구조체 */
    struct fb_var_screeninfo vinfo;
    unsigned char *buffer, *pfbmap;
    unsigned int x, y, i, screensize;
    VideoCapture vc(0); /* 카메라를 위한 변수 */
    Mat image(CAM_WIDTH, CAM_HEIGHT, CV_8UC3, Scalar(255)); /* 영상을 위한 변수 */

    if (!vc.isOpened()) {
        perror("OpenCV : open WebCam\n");
        return EXIT_FAILURE;
    }

    /* 캡처할 영상의 속성을 설정한다. */
    vc.set(CAP_PROP_FRAME_WIDTH, CAM_WIDTH);
    vc.set(CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);

    /* 프레임 버퍼 열기 */
    fbfd = open(FBDEV, O_RDWR);
    if (fbfd == -1) {
        perror("open() : framebuffer device");
        return EXIT_FAILURE;
    }

    /* 프레임 버퍼의 정보 가져오기 */
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information.");
        close(fbfd);
        return EXIT_FAILURE;
    }

    /* mmap(): 프레임 버퍼를 위한 메모리 공간 확보 */
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
    pfbmap = (unsigned char *)mmap(NULL, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (pfbmap == (unsigned char *)-1) {
        perror("mmap() : framebuffer device to memory");
        close(fbfd);
        return EXIT_FAILURE;
    }

    memset(pfbmap, 0, screensize);
    for(i = 0; i < CAMERA_COUNT; i++) {
        int colors = vinfo.bits_per_pixel / 8;
        long location = 0;
        int istride = image.cols*colors;

        vc >> image; /* 카메라로부터 한 프레임의 영상을 가져온다 */
        buffer = (uchar *)image.data; /* Mat 클래스의 영상 데이터를 획득 */
        
        if (image.empty()) {
            perror("Failed to capture image from camera");
            break;
        }

        for (y = 0, location = 0; y < image.rows && y < vinfo.yres; y++) {
            for (x = 0; x < image.cols && x < vinfo.xres; x++) {
                long location = (y * vinfo.xres + x) * colors;
                // 이미지에서 RGB 값을 가져와 16비트(5:6:5) 형식으로 변환
                uchar r = buffer[(y * image.cols + x) * 3 + 2];
                uchar g = buffer[(y * image.cols + x) * 3 + 1];
                uchar b = buffer[(y * image.cols + x) * 3 + 0];

                // 5:6:5 형식으로 변환
                uint16_t pixel = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);

                // 프레임 버퍼에 기록 (Little Endian 방식)
                pfbmap[location + 0] = pixel & 0xFF;        // 하위 바이트
                pfbmap[location + 1] = (pixel >> 8) & 0xFF; // 상위 바이트
            }
        }
    }

    /* 사용이 끝난 자원과 메모리를 해제한다. */
    munmap(pfbmap, screensize);
    close(fbfd);

    return 0;
}
