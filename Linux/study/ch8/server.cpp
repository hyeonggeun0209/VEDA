#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

#define PORT 5000
#define CAM_WIDTH 640
#define CAM_HEIGHT 480
#define BUFFER_SIZE (CAM_WIDTH * CAM_HEIGHT * 3)  // RGB 3채널을 위한 버퍼 크기

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // 소켓 생성
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 주소 설정
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // 소켓에 주소 할당(bind)
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 연결 대기(listen)
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    cout << "Server is listening on port " << PORT << endl;

    // 클라이언트 연결 수락(accept)
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // OpenCV VideoCapture 객체를 사용해 카메라에서 이미지 캡처
    VideoCapture vc(0);  // 카메라 장치 0번
    if (!vc.isOpened()) {
        cerr << "Error opening camera" << endl;
        return -1;
    }

    // 카메라 해상도 설정
    vc.set(CAP_PROP_FRAME_WIDTH, CAM_WIDTH);
    vc.set(CAP_PROP_FRAME_HEIGHT, CAM_HEIGHT);

    unsigned char buffer[BUFFER_SIZE];  // 전송할 데이터를 담을 버퍼
    char buf1[BUFFER_SIZE];
    char buf2[BUFFER_SIZE];
    Mat image;
    
    // vc >> image;
    // sprintf(buf1,"%d",image.cols);
    // write(new_socket, buf1, BUFFER_SIZE);

    // sprintf(buf2,"%d",image.rows);
    // write(new_socket, buf2, BUFFER_SIZE);

    while (1) {
        // 카메라에서 이미지 캡처
        vc >> image;
        if (image.empty()) {
            cerr << "Error capturing frame" << endl;
            break;
        }

        // 이미지를 RGB 형태로 변환
        memcpy(buffer, image.data, BUFFER_SIZE);

        // 클라이언트로 데이터 전송
        write(new_socket, buffer, BUFFER_SIZE);
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
