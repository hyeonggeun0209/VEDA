#include "dock.h"

using namespace std;

// Dock 클래스의 생성자 정의
// 이 생성자는 Dock 객체를 초기화하는 데 사용됩니다.
// 각 매개변수는 Dock 객체의 다양한 속성을 설정하는 데 사용됩니다.
Dock::Dock(int dockId, const string& vehicleNumber, int itemQuantity, const string& itemType, const string& dockStatus, time_t entryTime, time_t exitTime)
    : m_dockId(dockId), // 도크의 ID를 설정합니다.
    m_vehicleNumber(vehicleNumber), // 차량 번호를 설정합니다.
    m_itemQuantity(itemQuantity), // 물품 수량을 설정합니다.
    m_itemType(itemType), // 물품 종류를 설정합니다.
    m_dockStatus(dockStatus), // 도크의 현재 상태를 설정합니다.
    m_entryTime(entryTime), // 물품이 도크에 입고된 시간을 설정합니다.
    m_exitTime(exitTime) // 물품이 도크에서 출고된 시간을 설정합니다.
{
}

// 차량 번호를 반환하는 메서드
string Dock::getVehicleNumber() const
{
    return m_vehicleNumber; // 차량 번호를 반환합니다.
}

// 차량 번호를 설정하는 메서드
void Dock::setVehicleNumber(const string& vehicleNumber)
{
    m_vehicleNumber = vehicleNumber; // 주어진 차량 번호로 도크의 차량 번호를 설정합니다.
}

// 물품 수량을 반환하는 메서드
int Dock::getItemQuantity() const
{
    return m_itemQuantity; // 물품 수량을 반환합니다.
}

// 물품 수량을 설정하는 메서드
void Dock::setItemQuantity(int itemQuantity)
{
    m_itemQuantity = itemQuantity; // 주어진 수량으로 도크의 물품 수량을 설정합니다.
}

// 물품 종류를 반환하는 메서드
string Dock::getItemType() const
{
    return m_itemType; // 물품 종류를 반환합니다.
}

// 물품 종류를 설정하는 메서드
void Dock::setItemType(const string& itemType)
{
    m_itemType = itemType; // 주어진 물품 종류로 도크의 물품 종류를 설정합니다.
}

// 도크 상태를 반환하는 메서드
string Dock::getDockStatus() const
{
    return m_dockStatus; // 도크의 상태를 반환합니다.
}

// 도크 상태를 설정하는 메서드
void Dock::setDockStatus(const string& dockStatus)
{
    m_dockStatus = dockStatus; // 주어진 상태로 도크의 상태를 설정합니다.
}

// 입고 시간을 반환하는 메서드
time_t Dock::getEntryTime() const
{
    return m_entryTime; // 입고 시간을 반환합니다.
}

// 입고 시간을 설정하는 메서드
void Dock::setEntryTime(time_t entryTime)
{
    m_entryTime = entryTime; // 주어진 입고 시간으로 도크의 입고 시간을 설정합니다.
}

// 출고 시간을 반환하는 메서드
time_t Dock::getExitTime() const
{
    return m_exitTime; // 출고 시간을 반환합니다.
}

// 출고 시간을 설정하는 메서드
void Dock::setExitTime(time_t exitTime)
{
    m_exitTime = exitTime; // 주어진 출고 시간으로 도크의 출고 시간을 설정합니다.
}

// 도크의 ID를 반환하는 메서드
int Dock::getDockId() const
{
    return m_dockId; // 도크의 ID를 반환합니다.
}

// 동등 비교 연산자 정의
// 두 Dock 객체가 동일한지 비교합니다. 모든 속성값이 동일하면 true를 반환합니다.
bool Dock::operator==(const Dock &other) const {
    return (m_dockId == other.m_dockId && // ID 비교
            m_vehicleNumber == other.m_vehicleNumber && // 차량 번호 비교
            m_itemQuantity == other.m_itemQuantity && // 물품 수량 비교
            m_itemType == other.m_itemType && // 물품 종류 비교
            m_dockStatus == other.m_dockStatus && // 상태 비교
            m_entryTime == other.m_entryTime && // 입고 시간 비교
            m_exitTime == other.m_exitTime); // 출고 시간 비교
}