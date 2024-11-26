#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define PORT 5000
#define BUFFER_SIZE 1024

#define FBDEV "/dev/fb0"
#define CAMERA_COUNT 100
#define CAM_WIDTH 640
#define CAM_HEIGHT 480

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buf[BUFFER_SIZE] = {0};

    // 소켓 생성
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // 서버 주소 설정
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        return -1;
    }

    // 서버에 연결(connect)
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return -1;
    }

    int fbfd;

    /* 프레임 버퍼 정보 처리를 위한 구조체 */
    struct fb_var_screeninfo vinfo;
    unsigned char *buffer, *pfbmap;
    unsigned int x, y, i, screensize;
    VideoCapture vc(0); /* 카메라를 위한 변수 */
    Mat image(CAM_WIDTH, CAM_HEIGHT, CV_8UC3, Scalar(255)); /* 영상을 위한 변수 */

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

    while(1) {
        // read(sock, buf, BUFFER_SIZE);
        // copy_n(buf, BUFFER_SIZE, pfbmap);
    }

    /* 사용이 끝난 자원과 메모리를 해제한다. */
    munmap(pfbmap, screensize);
    close(fbfd);

    // 소켓 닫기
    close(sock);

    return 0;
}
