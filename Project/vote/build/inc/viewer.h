#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class viewer {
string PhoneNumber;     // 시청자의 휴대폰 번호 저장
int VotePresence;     // 시청자의 투표 여부 저장
string VoteWho[2];     // 시정자가 투표한 후보 저장
int donation;     // 시청자가 후원한 금액 저장
vector<string> my_star;
int pre =0;
public:
void set(string PhoneNumber, int VotePresence, int donation);
string getNumber();
string getName();
int getVotePresence();
int getDonation();
void vote(int num, string name);     // 최대 두명까지 가능한 투표 함수
void donate(int money);     // 출연자에게 후원 함수
vector<string> & getmystar();
int &getpre();
};
