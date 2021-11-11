#ifndef LAB4_CITIZEN_H
#define LAB4_CITIZEN_H

#include <iostream>
#include <vector>
#include <string>
#include <exception>

#define MALE 0
#define FEMALE 1
#define X 2


using namespace std;

class Citizen {
private:
    string _name;
    string _date_of_birth;
    int _sex;

public:
    Citizen(const string &name = "", const string &date_of_birth = "", const int sex = X);
    ~Citizen();

    string name();
    void name(const string &_n);

    string date_of_birth();
    void date_of_birth(const string _dob);

    string sex_s();
    int sex_i();
    void sex(const int _s);
    void sex(const string &_s);

    static std::vector<Citizen> *slice(std::vector<Citizen> &citizens, const int begin = 0, const int end = -1);
};

#endif //LAB4_CITIZEN_H
