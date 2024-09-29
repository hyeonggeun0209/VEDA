
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "viewer.h"
#include "cast.h"

class vector_viewer {
   
public:
int add(vector<viewer> &viewers, string PhoneNumber);   // 휴대폰 번호로 시청자 구분 후 벡터 저장
void vote(vector<viewer> &viewers, vector<cast> &cast, int num);
void donation(vector<viewer> &viewers, int num, int money);
void v_show(vector<viewer> &viewers, int num);
int check(vector<viewer> &viewers, string PhoneNumber);
void show(vector<cast> cast);
void addmy_star(vector<viewer> &viewers, vector<cast> &casts, int num);

};