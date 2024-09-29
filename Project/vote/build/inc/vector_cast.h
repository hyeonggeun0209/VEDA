#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "cast.h"

using namespace std;

class vector_cast {
// 출연자들을 저장할 vector 선언
// 출연자 소속사

public:
void cast_add(vector<cast> &casts, string name, int age, string Entertainment);               // vector에 출연자 추가하기
void cast_delete(vector<cast>& casts, string name);               // vector에 출연자 삭제하기

void cast_modify(vector<cast>& casts, string name);               // vector에 있는 출연자 정보 수정하기
void show(vector<cast> &casts);
void end_vote(vector<cast> casts, int &end_vote);
void show_vote(vector<cast> &casts);
void sort(vector<cast> &casts);
void vote(vector<cast> &casts, string name);
void getname(vector<cast> &casts);
};
