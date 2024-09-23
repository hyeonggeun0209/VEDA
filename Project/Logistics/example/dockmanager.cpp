#include "dockmanager.h"
#include <fstream>
#include <sstream>
#include <iomanip>      // 매개변수를 가지는 조작자 헤더파일
#include <ctime>
#include <iostream>
using namespace std;

// DockManager 생성자
// DockManager 객체를 초기화합니다.
// 현재는 기본 생성자로 초기화 작업이 추가되어 있지 않습니다.
DockManager::DockManager() {
    // 초기화 작업을 여기에 추가할 수 있음
    ifstream file("docklist.csv");
    if (file) {
        while (file) {
            vector<string> row = parseCSV(file, ',');
            if (!row.empty()) {
                int id = stoi(row[0]);
                const string& vehicleNumber = row[1];
                int quantity = stoi(row[2]);
                const string& itemType = row[3];
                const string& status = row[4];
                // std::tm 구조체로 시간 파싱
                std::tm entryTm = {};
                std::tm exitTm = {};
                std::istringstream entryStream(row[5]);
                int a;
                if(row[6] == "N/A") {
                    a = -1;
                } else {
                    a = 0;
                }
                std::istringstream exitStream(row[6]);
                exitStream >> std::get_time(&exitTm, "%Y-%m-%d %H:%M:%S");
                entryStream >> std::get_time(&entryTm, "%Y-%m-%d %H:%M:%S");
                if (entryStream.fail() || exitStream.fail()) {
                    std::cerr << "시간 파싱에 실패했습니다.\n";
                }
                // std::tm 구조체를 time_t로 변환
                std::time_t entryTime = std::mktime(&entryTm);
                std::time_t exitTime = std::mktime(&exitTm);
                if(a == -1) {
                    exitTime = a;
                }
    
                // 도크 객체를 생성하고 도크 목록에 추가
                auto dock = make_unique<Dock>(id, vehicleNumber, quantity, itemType, status, entryTime, exitTime);
                dockList.insert({ id, std::move(dock) });
            }
        } 
    }
}

// DockManager 소멸자
// DockManager 객체가 소멸될 때 도크 목록을 파일에 저장하거나 정리 작업을 수행할 수 있습니다.
// 현재는 특별한 작업이 추가되어 있지 않습니다.
DockManager::~DockManager() {
    // 소멸자에서 파일 저장 작업을 할 수 있음
    ofstream file("docklist.csv");
    if (file) {
        for (const auto& entry : dockList) {
            const Dock* dock = entry.second.get();
            time_t entryTime = dock->getEntryTime();
            time_t exitTime = dock->getExitTime();
            tm entryTm;
            tm exitTm;
            localtime_r(&entryTime,&entryTm);
            localtime_r(&exitTime,&exitTm);
            file << dock->getDockId() << ","
                 << dock->getVehicleNumber() << ","
                 << dock->getItemQuantity() << ","
                 << dock->getItemType() << ","
                 << dock->getDockStatus() << ","
                << put_time(&entryTm, "%Y-%m-%d %H:%M:%S") << ",";
                if(exitTime == -1) {
                    file << "N/A" << endl;
                } else file << put_time(&exitTm, "%Y-%m-%d %H:%M:%S") << endl;  // time_t를 그대로 출력
        }
    }
        // 도크의 입차 및 출차 시간을 로컬 시간으로 변환합니다.

    file.close( );
}

// 새로운 도크를 도크 목록에 추가합니다.
// @param dock 추가할 도크 객체의 고유 포인터
void DockManager::addDockToList(unique_ptr<Dock> dock) {
    dockList.insert({ dock->getDockId(), std::move(dock) });
}

void DockManager::addDockOutToList(unique_ptr<Dock> dock) {
    dockOutList.insert({ dock->getDockId(), std::move(dock) });
}

// 주어진 ID의 도크를 도크 목록에서 제거합니다.
// @param id 제거할 도크의 고유 ID
void DockManager::removeDockFromList(int dockId) {

    if(dockList.erase(dockId)>0)
    {
        cout<<"Successfully deleted"<<endl;
    }
    else
        cout << "Dock not found." << endl;
}

// 주어진 ID의 도크 정보를 수정합니다.
// 도크의 현재 정보를 출력하고 새로운 정보를 입력받아 업데이트합니다.
// @param id 수정할 도크의 고유 ID
void DockManager::modifyDock(int dockId) {
    Dock* dock = searchDock(dockId);
    if (dock) {
        // 도크의 현재 정보를 출력합니다.
        cout << "ID: " << dock->getDockId() << endl;
        cout << "Vehicle Number: " << dock->getVehicleNumber() << endl;
        cout << "Quantity: " << dock->getItemQuantity() << endl;
        cout << "Item Type: " << dock->getItemType() << endl;
        cout << "Status: " << dock->getDockStatus() << endl;

        // 새로운 정보를 입력받아 도크 객체를 갱신합니다.
        string vehicleNumber, itemType, status;
        int quantity;
        cout << "Enter new vehicle number: "; cin >> vehicleNumber;
        cout << "Enter new quantity: "; cin >> quantity;
        cout << "Enter new item type: "; cin >> itemType;
        cout << "Enter new status: "; cin >> status;

        // 도크의 속성 업데이트
        dock->setVehicleNumber(vehicleNumber);
        dock->setItemQuantity(quantity);
        dock->setItemType(itemType);
        dock->setDockStatus(status);

        cout << "Successfully modified"<<endl;
    } else {
        cout << "Dock not found." << endl;
    }
}

// 주어진 ID의 도크를 검색하여 반환합니다.
// @param id 검색할 도크의 고유 ID
// @return 주어진 ID의 도크 객체 포인터. ID가 존재하지 않으면 nullptr
Dock* DockManager::searchDock(int dockId) const {
    auto it = dockList.find(dockId);
    return it != dockList.end() ? it->second.get() : nullptr;
    cout<< dockId <<" ID is wrong!"<<endl;

}

// 모든 도크의 정보를 출력합니다.
// 도크 목록에 있는 모든 도크의 정보를 포맷에 맞춰 출력합니다.
void DockManager::displayDockList() const {
    cout << endl;
    cout<<setw(5) <<  setfill(' ')   <<  left   <<  "ID"                <<" | "
            <<setw(16) <<  setfill(' ')   <<  left   <<  "Vehicle Numver"    <<" | "
            <<setw(14)  <<  setfill(' ')   <<  left   <<  "Item Quantity"     <<" | "
            <<setw(10) <<  setfill(' ')   <<  left   <<  "Item type"         <<" | "
            <<setw(12) <<  setfill(' ')   <<  left   <<  "Dock Status"       <<" | "
            <<setw(19)  <<  setfill(' ')   <<  left   <<  "Entry Time"        <<" | "
            <<setw(19)  <<  setfill(' ')   <<  left   <<  "Exit Time"         <<" | " <<endl;

    for (const auto& entry : dockList) {
        const Dock* dock = entry.second.get();

        // 도크의 입차 및 출차 시간을 로컬 시간으로 변환합니다.
        time_t entryTime = dock->getEntryTime();
        time_t exitTime = dock->getExitTime();



        tm entryTm;
        tm exitTm;

        // localtime_s 함수는 첫 번째 매개변수로 tm* 구조체를 받고, 두 번째 매개변수로 time_t*를 받습니다.
#ifdef _WIN32
        localtime_s(&entryTm, &entryTime);
        localtime_s(&exitTm, &exitTime);
#else
        localtime_r(&entryTime,&entryTm);
        localtime_r(&exitTime,&exitTm);
#endif


        // 도크 정보를 포맷에 맞춰 출력합니다.
        cout << setw(5)   << setfill(' ') << left  << dock->getDockId()              << " | "
                  << setw(16)  << setfill(' ') << left  << dock->getVehicleNumber()       << " | "
                  << setw(14)   << setfill(' ') << left  << dock->getItemQuantity()        << " | "
                  << setw(10)  << setfill(' ') << left  << dock->getItemType()            << " | "
                  << setw(12)  << setfill(' ') << left  << dock->getDockStatus()          << " | "
                  << put_time(&entryTm, "%Y-%m-%d %H:%M:%S")  << " | ";
        if(exitTime != -1)
            cout <<put_time(&exitTm, "%Y-%m-%d %H:%M:%S")   << " | " << endl;
        else
            cout << "N/A" << endl;
    }
}

// 도크를 입고 처리합니다.
// 도크의 상태를 '입고'로 변경하고, 입차 시간을 현재 시간으로 설정합니다.
// @param id 입고 처리할 도크의 고유 ID
// @param vehicleNumber 입고되는 차량 번호
// @param quantity 입고되는 물품의 수량
// @param itemType 물품의 종류
void DockManager::checkIn(int dockId, const string& vehicleNumber, int itemQuantity, const string& itemType) {
    // 새로운 도크 객체를 생성하고 도크 목록에 추가합니다.
    auto dock = make_unique<Dock>(dockId, vehicleNumber, itemQuantity, itemType, "Checked In", time(nullptr), -1);
    addDockToList(std::move(dock));
}

// 도크를 출고 처리합니다.
// 도크의 상태를 '출고'로 변경하고, 출차 시간을 현재 시간으로 설정합니다.
// @param id 출고 처리할 도크의 고유 ID
void DockManager::checkOut(int dockId) {
    Dock* dock = searchDock(dockId);
    if (dock) {
        // 도크의 상태를 '출고'로 변경하고 출차 시간을 현재 시간으로 설정합니다.
        dock->setDockStatus("Checked Out");
        dock->setExitTime(time(nullptr));
        cout<< dockId <<" Dock has been cheched out!"<<endl;
    } else {
        cout << "Dock not found." << endl;
    }
    // if(dockList.erase(dockId)>0)
    //     cout<<"Successfully deleted"<<endl;
}
// CSV 형식의 데이터를 파싱하여 벡터로 반환합니다.
// @param file 입력 스트림
// @param delimiter CSV 데이터의 구분자
// @return 파싱된 데이터가 담긴 문자열 벡터
vector<string> DockManager::parseCSV(istream& file, char delimiter) {
    stringstream ss;
    vector<string> row;
    string token;
    char c;

    // 파일에서 문자를 읽어와서 토큰으로 분리합니다.
    while (file.get(c)) {
        if (c == delimiter || c == '\r' || c == '\n') {
            if (c == '\n' && file.peek() == '\r') file.get(); // Windows의 '\r'을 무시합니다.
            token = ss.str();
            row.push_back(token);
            ss.str("");
            ss.clear();
            if (c == '\n') break;
        } else {
            ss << c;
        }
    }
    if (!ss.str().empty()) {
        row.push_back(ss.str());
    }
    return row;
}

// 새로운 도크에 할당할 고유 ID를 생성합니다.
// 도크 목록이 비어 있으면 1을 반환하고, 그렇지 않으면 마지막 ID보다 1 큰 값을 반환합니다.
// @return 새 도크의 고유 ID
int DockManager::makeId() const {
    return dockList.empty() ? 1 : dockList.rbegin()->first + 1;
}

int DockManager::getDockSize() {
    return dockList.size();
}