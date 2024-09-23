#ifndef DOCK_MANAGER_H
#define DOCK_MANAGER_H

#include <map>
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include "dock.h"
#include "productmanager.h"
using namespace std;

class DockManager {
public:
    // 생성자: DockManager 객체를 초기화합니다.
    // 초기화 과정에서 도크 목록을 파일에서 로드하거나, 초기 상태를 설정할 수 있습니다.
    DockManager();

    // 소멸자: DockManager 객체가 소멸될 때 도크 목록을 파일에 저장합니다.
    // 도크 목록을 저장하여 다음 프로그램 실행 시 도크 상태를 유지할 수 있도록 합니다.
    ~DockManager();

    // 새로운 도크를 도크 목록에 추가합니다.
    // @param dock 추가할 도크 객체의 고유 포인터
    void addDockToList(unique_ptr<Dock> dock);

    void addDockOutToList(unique_ptr<Dock> dock);

    // 주어진 ID의 도크를 도크 목록에서 제거합니다.
    // @param id 제거할 도크의 고유 ID
    void removeDockFromList(int dockId);

    // 주어진 ID의 도크 정보를 수정합니다.
    // 도크의 현재 상태를 출력하고 새로운 정보를 입력받아 업데이트합니다.
    // @param id 수정할 도크의 고유 ID
    void modifyDock(int dockId);

    // 주어진 ID의 도크를 검색하여 반환합니다.
    // @param id 검색할 도크의 고유 ID
    // @return 주어진 ID의 도크 객체 포인터. ID가 존재하지 않으면 nullptr
    Dock* searchDock(int dockId) const;

    // 모든 도크의 정보를 출력합니다.
    void displayDockList() const;

    // 도크를 입고 처리합니다. 도크의 상태를 '입고'로 변경하고 필요한 정보를 업데이트합니다.
    // @param id 입고 처리할 도크의 고유 ID
    // @param vehicleNumber 입고되는 차량 번호
    // @param quantity 입고되는 물품의 수량
    // @param itemType 물품의 종류
    void checkIn(int dockId, const string& vehicleNumber, int itemQuantity, const string& itemType);

    // 도크를 출고 처리합니다. 도크의 상태를 '출고'로 변경하고 출차 시간을 업데이트합니다.
    // @param id 출고 처리할 도크의 고유 ID
    void checkOut(int dockId);

    // CSV 형식의 데이터를 파싱하여 벡터로 반환합니다.
    // @param input 입력 스트림
    // @param delimiter CSV 데이터의 구분자
    // @return 파싱된 데이터가 담긴 문자열 벡터
    vector<string> parseCSV(istream& input, char delimiter);

    int getDockSize();
    

private:
    // 도크 목록을 저장하는 맵 (ID -> 도크 객체)
    map<int, unique_ptr<Dock>> dockList;
    map<int, unique_ptr<Dock>> dockOutList;

    // 새로운 도크에 할당할 고유 ID를 생성합니다.
    // 도크 목록이 비어 있으면 0을 반환하고, 그렇지 않으면 마지막 ID보다 1 큰 값을 반환합니다.
    // @return 새 도크의 고유 ID
    int makeId() const;
};

#endif // DOCK_MANAGER_H