#include "citizen.h"

Citizen::Citizen(const string &name, const string &date_of_birth, const int sex) {
    _name = name;
    _date_of_birth = date_of_birth;
    if (0 <= sex && sex <= 2)
        _sex = sex;
    else
        _sex = X;
}

string Citizen::name() {
    return _name;
}

void Citizen::name(const string &_n) {
    _name = _n;
}

string Citizen::date_of_birth() {
    return _date_of_birth;
}

void Citizen::date_of_birth(const string _dob) {
    _date_of_birth = _dob;
}

int Citizen::sex_i() {
    return _sex;
}

string Citizen::sex_s() {
    string result;
    switch (_sex) {
        case MALE:
            result = "Male";
            break;
        case FEMALE:
            result = "Female";
            break;
        case X:
        default:
            result = "X";
            break;
    }

    return result;
}

void Citizen::sex(const int _s) {
    if (0 <= _s && _s <= 2)
        _sex = _s;
    else
        _sex = X;
}

void Citizen::sex(const string &_s) {
    if (_s == "Male")
        _sex = MALE;
    else if (_s == "Female")
        _sex = FEMALE;
    else
        _sex = X;
}

std::vector<Citizen> *Citizen::slice(std::vector<Citizen> &citizens, const int begin, const int end) {
    if (begin > citizens.size())
        throw std::invalid_argument("Begin idx cannot be greater than length of a vector.");

    const int bound = end == -1 ? citizens.size() : end;
    if (bound < begin)
        throw std::invalid_argument("End idx cannot be lower than begin one.");


    auto result = new vector<Citizen>();
    for (int i = begin; i < bound; ++i) {
        result->push_back(citizens[i]);
    }

    return result;
}

Citizen::~Citizen() {
    _name.clear();
    _date_of_birth.clear();
}

