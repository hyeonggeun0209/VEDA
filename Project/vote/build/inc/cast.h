#pragma once
#include <string>
#include <iostream>

using namespace std;

class cast {
string name;               // 출연자 이름
int age;               // 출연자 나이
string Entertainment;               // 출연자 소속사
int votes = 0;               // 출연자 득표수
int rank = -1;               // 출연자 순위

public:
void set(string name, int age, string Entertainment);               // 출연자 정보 입력하기
void setname(string name);
void setage(int age);
void setEntertainment(string Entertainment);
void addvote();
int &getrank();
int getvote();
string getname();
int getage();
string getEntertainment();
};
