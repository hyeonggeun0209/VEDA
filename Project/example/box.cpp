#include "box.h"

#include <iostream>

using namespace std;

Box::Box(int id, string name, string phoneNumber, string address, bool state)
          : m_id(id), m_name(name), m_phoneNumber(phoneNumber), m_address(address), m_state(state)
{
}

string Box::getName() const
{
    return m_name;
}

void Box::setName(string& name)
{
    m_name = name;
}

string Box::getPhoneNumber() const
{
    return m_phoneNumber;
}

void Box::setPhoneNumber(string& phoneNumber)
{
    m_phoneNumber = phoneNumber;
}

string Box::getAddress() const
{
    return m_address;
}

void Box::setAddress(string& address)
{
    m_address = address;
}

int Box::id() const
{
    return m_id;
}

bool Box::getState() const 
{
    return m_state;
}

void Box::setState(bool& state)
{
    m_state = state;
}

// Define copy assignment operator.
bool Box::operator==(const Box &other) const {
    return (this->m_name == other.m_name);
}
