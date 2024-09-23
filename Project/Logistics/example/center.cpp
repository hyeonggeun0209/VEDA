#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "center.h"
using namespace std;

Center::Center(DockManager& dm, ProductManager& pm, StockManager& sm)
    : dm(dm), pm(pm), sm(sm) {}

void Center::run() {
    int num;
    while (true) {
        displayMainMenu();
        cin >> num;
        switch (num) {
            case 1:
                DockManagement();
                break;
            case 2:
                StockManagement();
                break;
            case 3:
                ProductManagement();
                break;
            case 4:
                cout << "\033[1;33m프로그램을 종료합니다.\033[0m" << endl;
                return;
        }
    }
}
void Center::displayMainMenu() {
    cout << "\033[2J\033[1;1H";
    printVEDA();
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                 Center                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Dock Manager                     " << endl;
    cout << "  2. Stock Manager                     " << endl;
    cout << "  3. Product Manager                            " << endl;
    cout << "  4. Quit this Program                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
}

void Center::displayDockMenu() {
    cout << "\033[2J\033[1;1H"; // 화면을 지우고 커서를 맨 위로 이동합니다.
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "              Dock Manager                   " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Dock List                       " << endl;
    cout << "  2. Dock Check In                           " << endl;
    cout << "  3. Dock Check Out                          " << endl;
    cout << "  4. Modify DockList                         " << endl;
    cout << "  5. Remove Dock From DockList               " << endl;
    cout << "  6. Quit this Program                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
}

void Center::displayStockMenu() {
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                 Stock Manager                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Stock List                     " << endl;
    cout << "  2. input Stock                            " << endl;
    cout << "  3. Store Product                          " << endl;
    cout << "  4. Delete Stock                           " << endl;
    cout << "  5. Modify Stock                           " << endl;
    cout << "  6. Show Stock                           " << endl;
    cout << "  7. Quit Stock Manager                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
}

void Center::displayProductMenu() {
    cout << "\033[2J\033[1;1H";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "                 Product Manager                 " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "  1. Display Product List                     " << endl;
    cout << "  2. Receive Product                            " << endl;
    cout << "  3. Delete Product                           " << endl;
    cout << "  4. Modify Product                           " << endl;
    cout << "  5. Quit Product Manager                       " << endl;
    cout << "+++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " What do you wanna do? ";
}

void Center::DockManagement() {
    int choice, dockId, itemQuantity;
    string vehicleNumber, itemType;
    while(true) {
        displayDockMenu();
        cin >> choice;
        switch (choice) {
        case 1:
            dm.displayDockList(); // 도크 목록을 출력합니다.
            cin.ignore();
            cout<<"If you go back, pleas press Enter!"<<endl;
            getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
            break;
        case 2:
            cout << "Enter Dock ID to check in: "; cin >> dockId;
            cout << "Enter Vehicle Number: "; cin >> vehicleNumber;
            cout << "Enter Item Quantity: "; cin >> itemQuantity;
            cout << "Enter Item Type: "; cin >> itemType;
            dm.checkIn(dockId, vehicleNumber, itemQuantity, itemType); // 입고 처리
            waitdock();
            pauseScreen();
            break;
        case 3:
            dm.displayDockList(); // 도크 목록을 출력합니다.
            cin.ignore();
            cout << "\nEnter Dock ID to check out : "; cin >> dockId;
            dm.checkOut(dockId); // 출고 처리
            cout<<"If you go back, pleas press Enter!"<<endl;
            cin.ignore();
            getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
            break;
        case 4:
            dm.displayDockList(); // 도크 목록을 출력합니다.
            cin.ignore();
            cout << "Enter Dock ID to modify: "; cin >> dockId;
            dm.modifyDock(dockId); // 도크 수정
            cout<<"If you go back, pleas press Enter!"<<endl;
            cin.ignore();
            getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
            break;
        case 5:
            dm.displayDockList(); // 도크 목록을 출력합니다.
            cin.ignore();
            cout << "Enter Dock ID to remove: "; cin >> dockId;
            dm.removeDockFromList(dockId); // 도크 삭제
            cout<<"If you go back, pleas press Enter!"<<endl;
            cin.ignore();
            getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
            break;
        case 6:
            return; // 프로그램 종료
        default:
            cout << "\nInvalid option. Please try again." << endl;
            cout<<"If you go back, pleas press Enter!"<<endl;
            cin.ignore();
            getchar(); // 사용자가 엔터를 누를 때까지 기다립니다.
        }
    }
}

void Center::StockManagement() {
    int num, key;
    while(true) {
        displayStockMenu();
        cin >> num;
        switch(num) {
            case 1: default:
                sm.displayInfo();
                cin.ignore();
                getchar();
                break;
            case 2:
                sm.inputStock();
                break;
            case 3:
                sm.storeProduct(pm);
                animateConveyorAndSorting();
                pauseScreen();
                break;
            case 4:
                sm.displayInfo();
                cout << "   Choose Key : ";
                cin >> key;
                sm.deleteStock(key);
                break;
            case 5:
                sm.displayInfo();
                cout << "   Choose Key : ";
                cin >> key;
                sm.modifyStock(key);
                break;
            case 6:
                sm.find_id(pm);
                pauseScreen();
                break;
            case 7:
                return;
        }
    }
}

void Center::ProductManagement() {
    int num, key;
    while(true) {
        displayProductMenu();
        cin >> num;
        switch(num) {
            case 1: default:
                pm.displayInfo();
                cin.ignore();
                getchar();
                break;
            case 2:
                pm.receiveProduct(dm);
                animateBoxFromTruck();
                pauseScreen();
                break;
            case 3:
                pm.displayInfo();
                cout << "   Choose Key : ";
                cin >> key;
                pm.deleteProduct(key);
                break;
            case 4:
                pm.displayInfo();
                cout << "   Choose Key : ";
                cin >> key;
                pm.modifyProduct(key);
                break;
            case 5:
                return;
        }
    }
}

void Center::pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void Center::waitdock() {
    int maxOffset = 20;  // 트럭이 이동할 최대 거리
    int warehouseOffset = 10;  // 창고의 위치 (트럭 기준 왼쪽)

    for (int frame = maxOffset; frame >= 0; --frame) {
        // 화면 지우기
        std::system("clear");

        // 창고 그리기 (트럭 기준 왼쪽에 위치)
        if (frame <= warehouseOffset) {
            std::cout << "  ______________________" << std::endl;
            std::cout << " |                      |" << std::endl;
            std::cout << " |        CENTER        |" << std::endl;
            std::cout << " |______________________|" << std::endl;
        } else {
            std::cout << std::endl << std::endl << std::endl;
        }

        // 트럭 이동을 위한 공백 출력
        if (frame > warehouseOffset) {
            for (int i = 0; i < frame - warehouseOffset; ++i) std::cout << " ";
        }

        // 트럭 상단부 (운전석 포함)
        std::cout << "       ______________" << std::endl;
        if (frame > warehouseOffset) {
            for (int i = 0; i < frame - warehouseOffset; ++i) std::cout << " ";
        }
        std::cout << "      /|            |\\ " << std::endl;
        if (frame > warehouseOffset) {
            for (int i = 0; i < frame - warehouseOffset; ++i) std::cout << " ";
        }
        std::cout << " ____/ |   _______  | \\____________________" << std::endl;
        if (frame > warehouseOffset) {
            for (int i = 0; i < frame - warehouseOffset; ++i) std::cout << " ";
        }
        std::cout << "|    | |  |       | |         \\           |" << std::endl;

        // 트럭 중간 부분 (화물칸)
        if (frame > warehouseOffset) {
            for (int i = 0; i < frame - warehouseOffset; ++i) std::cout << " ";
        }
        std::cout << "|    |_|__|_______|_|__________\\__________|" << std::endl;
        if (frame > warehouseOffset) {
            for (int i = 0; i < frame - warehouseOffset; ++i) std::cout << " ";
        }
        std::cout << "|                                         |" << std::endl;
        if (frame > warehouseOffset) {
            for (int i = 0; i < frame - warehouseOffset; ++i) std::cout << " ";
        }
        std::cout << "|_________________________________________|" << std::endl;

        // 바퀴 부분 (창고에 가까워지면서 트럭이 들어가는 것처럼)
        if (frame > warehouseOffset) {
            for (int i = 0; i < frame - warehouseOffset; ++i) std::cout << " ";
            std::cout << "   O         O          O           O" << std::endl;
        }

        // 0.1초 대기
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Center::printVEDA() {
    // ANSI 코드로 주황색 출력 (ANSI 38;5;214는 주황색에 가까운 색상)
    std::string orange = "\033[38;5;214m";
    std::string reset = "\033[0m";

    // VEDA를 블록 스타일로 출력
    std::cout << orange;
    cout << "      " << "██╗   ██╗███████╗██████╗  █████╗  " << endl; 
    cout << "      " << "██║   ██║██╔════╝██╔══██╗██╔══██╗ "<< endl;
    cout << "      " << "██║   ██║█████╗  ██║  ██║███████║ "<< endl;
    cout << "      " << "╚██╗ ██╔╝██╔══╝  ██║  ██║██╔══██║ "<< endl;
    cout << "      " << " ╚████╔╝ ███████╗██████╔╝██║  ██║ "<< endl;
    cout << "      " << "  ╚═══╝  ╚══════╝╚═════╝ ╚═╝  ╚═╝ "<< endl;
    std::cout << reset;
}
void Center::animateBoxFromTruck() {
    int maxPosition = 5;  // 상자가 내려가는 최대 위치

    for (int pos = 0; pos <= maxPosition; ++pos) {
        // 화면 지우기
        std::system("clear");

        // 트럭 출력 (상자는 트럭 위에 있으므로 트럭은 고정)
        std::cout << "       ____________" << std::endl;
        std::cout << "      /|          |\\___________" << std::endl;
        std::cout << " ____/ |__________| \\        /" << std::endl;
        std::cout << "|    | |          |  \\______/___" << std::endl;
        std::cout << "|    |_|__________|______________|" << std::endl;
        std::cout << "|                                 " << std::endl;
        std::cout << "|_________________________________" << std::endl;
        std::cout << "   O       O         O        O" << std::endl;

        // 상자가 내려가는 위치 출력
        for (int i = 0; i < pos; ++i) {
            std::cout << std::endl;  // 상자가 내려올 위치까지 빈 줄을 출력
        }

        // 상자 그림 (크게 만든 상자)
        std::cout << "    ###########" << std::endl;
        std::cout << "   #           #" << std::endl;
        std::cout << "   #   BOX     #" << std::endl;
        std::cout << "   #           #" << std::endl;
        std::cout << "   #           #" << std::endl;
        std::cout << "    ###########" << std::endl;

        // 약간의 지연 (애니메이션 속도 제어)
        std::this_thread::sleep_for(std::chrono::milliseconds(300));  // 0.3초 대기
    }
}

void Center::animateConveyorAndSorting() {
    int maxPosition = 10;       // 상자가 내려가는 최대 위치
    int storageAreaA = 8;       // 첫 번째 상자가 저장되는 위치 (Storage Area A)
    int storageAreaC = 5;       // 두 번째 상자가 저장되는 위치 (Storage Area C)
    std::string box1 = "[#####]"; // 첫 번째 상자
    std::string box2 = "[#####]"; // 두 번째 상자

    for (int pos = 0; pos <= maxPosition; ++pos) {
        // 화면 지우기
        std::system("clear");

        // 컨베이어 벨트 그리기
        std::cout << "==================== CONVEYOR BELT ====================" << std::endl;

        // 상자가 이동하는 부분 출력
        for (int i = 0; i < pos; ++i) {
            std::cout << "                                                      " << std::endl;
        }

        // 상자 1이 이동 중일 때 출력
        if (pos < storageAreaA) {
            std::cout << "    Box 1:              " << box1 << std::endl;  // 컨베이어 벨트 위의 첫 번째 상자
        }

        // 상자 2가 이동 중일 때 출력
        if (pos < storageAreaC) {
            std::cout << "    Box 2:              " << box2 << std::endl;  // 컨베이어 벨트 위의 두 번째 상자
        }

        // 상자가 도착한 후, 저장 구역 출력
        for (int i = pos + 1; i < maxPosition; ++i) {
            std::cout << "                                                      " << std::endl;
        }

        std::cout << "======================================================" << std::endl;

        // 분류된 상자 저장 구역 출력
        std::cout << "    Storage Area A: " << (pos >= storageAreaA ? box1 : "[     ]") << std::endl;
        std::cout << "    Storage Area B: [     ]" << std::endl;
        std::cout << "    Storage Area C: " << (pos >= storageAreaC ? box2 : "[     ]") << std::endl;

        // 약간의 지연 (애니메이션 속도 제어)
        std::this_thread::sleep_for(std::chrono::milliseconds(300));  // 0.3초 대기
    }

    // 상자가 저장된 후 잠시 멈춤
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}