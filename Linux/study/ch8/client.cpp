#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

#define PORT 5000
#define CAM_WIDTH 640
#define CAM_HEIGHT 480
#define BUFFER_SIZE (CAM_WIDTH * CAM_HEIGHT * 3)  // RGB 3채널을 위한 버퍼 크기
#define FBDEV "/dev/fb0"

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    unsigned char buffer[BUFFER_SIZE];  // 서버로부터 수신할 데이터를 담을 버퍼

    // 소켓 생성
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cerr << "Socket creation error" << endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // 서버 주소 설정
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        cerr << "Invalid address/ Address not supported" << endl;
        return -1;
    }

    // 서버에 연결(connect)
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "Connection failed" << endl;
        return -1;
    }

    // 프레임버퍼 관련 설정
    int fbfd = open(FBDEV, O_RDWR);
    if (fbfd == -1) {
        perror("Error opening framebuffer device");
        return -1;
    }

    // 프레임버퍼 정보 가져오기
    struct fb_var_screeninfo vinfo;
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        close(fbfd);
        return -1;
    }

    // 프레임버퍼의 크기 계산
    unsigned int screensize = vinfo.yres * vinfo.xres * vinfo.bits_per_pixel / 8;

    // 프레임버퍼 메모리 맵핑
    unsigned char *pfbmap = (unsigned char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if (pfbmap == (unsigned char *)-1) {
        perror("Error mapping framebuffer device to memory");
        close(fbfd);
        return -1;
    }

    memset(pfbmap, 0, screensize);  // 프레임버퍼 초기화
    char buf[BUFFER_SIZE];
    // 프레임버퍼의 너비와 높이 확인
    int fb_width = vinfo.xres;
    int fb_height = vinfo.yres;
    int fb_bytes_per_pixel = vinfo.bits_per_pixel / 8;
    int cols, rows;

    // read(sock, buf, BUFFER_SIZE);
    // cols = atoi(buf);
    // read(sock, buf, BUFFER_SIZE);
    // rows = atoi(buf);
    
    // 수신한 이미지를 프레임버퍼에 쓰기
    while (1) {
        
        // 서버로부터 데이터 수신
        ssize_t received_bytes = read(sock, buffer, BUFFER_SIZE);
        if (received_bytes < 0) {
            perror("recv failed");
            break;
        }

        for (int y = 0; y < CAM_HEIGHT && y < fb_height; ++y) {
            for (int x = 0; x < CAM_WIDTH && x < fb_width; ++x) {
                // 3바이트(RGB)를 프레임버퍼의 포맷에 맞게 복사 (예: 16비트 5:6:5 포맷)
                int buf_index = (y * CAM_WIDTH + x) * 3;
                int fb_index = (y * fb_width + x) * fb_bytes_per_pixel;

                // RGB 데이터를 프레임버퍼 포맷에 맞게 변환 (5:6:5 형식)
                uchar r = buf[buf_index];
                uchar g = buf[buf_index + 1];
                uchar b = buf[buf_index + 2];

                // 5:6:5 형식으로 변환
                uint16_t pixel = ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);

                // 프레임버퍼에 저장 (리틀 엔디안)
                pfbmap[fb_index] = pixel & 0xFF;          // 하위 바이트
                pfbmap[fb_index + 1] = (pixel >> 8) & 0xFF; // 상위 바이트
            }
        }
    }

    // 사용이 끝난 자원과 메모리를 해제
    munmap(pfbmap, screensize);
    close(fbfd);
    close(sock);

    return 0;
}
