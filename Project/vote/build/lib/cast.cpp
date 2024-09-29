#include "cast.h"

void cast::set(string name, int age, string Entertainment) {
        this->name = name;
        this->age = age;
        this->Entertainment = Entertainment;

}
void cast::setname(string name) {
        this->name = name;
}
void cast::setage(int age) {
        this->age = age;
}
void cast::setEntertainment(string Entertainment) {
        this->Entertainment = Entertainment;
}
string cast::getname() {
        return name;
}
int cast::getage() {
        return age;
}
string cast::getEntertainment() {
        return Entertainment;
}
void cast::addvote() {
        votes++;
}
int cast::getvote() {
        return votes;
}
int& cast::getrank() {
        return rank;
}
