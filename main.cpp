#include <iostream>
#include <sstream>
#include <algorithm>
#include <time.h>
#include "nvector/nvector.h"
#include "citizen/citizen.h"
#include "fort/fort.hpp"

void intro();
void lifeHook();


void task1();

void testNvectorOutput();
void testNvectorModule();
void testNvectorSum();
void testNvectorScalarMultiply();


void task2();


void outputCitizens(vector<Citizen> *citizens);

void fillDataHard(vector<Citizen> *citizens);
void fillDataConsole(vector<Citizen> *citizens);

void sortContainer1(vector<Citizen> *citizens);
void sortContainer2(vector<Citizen> *citizens);
void sortContainer(vector<Citizen> *citizens);

void sortByName(vector<Citizen> *citizens);

void sortByDates(vector<Citizen> *citizens);

void sortBySex(vector<Citizen> *citizens);

void filterCitizens(vector<Citizen> *citizens);

bool isYoung(Citizen &citizen);

using namespace std;

int main() {

    intro();

    lifeHook();

    return 0;
}

void intro() {
    cout << "\n\tHello. Welcome to Laboratory work #4 by Alexander Lemeshov" << endl;
}

void lifeHook() {
    int task = 0;
    string input;
    bool isFinished = false;

    while(true) {
        while (true) {
            cout << "Select task [1 / 2]: ";
            cin >> input;
            if (input == "exit") {
                isFinished = true;
                break;
            }
            {
                istringstream ss(input);
                if (ss >> task) {
                    if (task == 1 || task == 2)
                        break;
                    else
                        cout << "Task with " << task << " number does not exist. Try again." << endl;
                } else
                    cout << "invalid input. Try again." << endl;
            }
        }

        if (isFinished)
            break;

        task == 1 ? task1() : task2();
    }
}


void task1() {
    testNvectorOutput();

    testNvectorModule();

    testNvectorSum();

    testNvectorScalarMultiply();
}

void testNvectorOutput() {
    auto nv1 = new Nvector<double>("[1.2,2,3,4,5.223]");
    nv1->outputNvector("nv1");
}

void testNvectorModule() {
    auto nv1 = new Nvector<double>("[1.2,2,3,4,5.223]");
    cout << "\n\tnv1 module is " << nv1->GetModule() << endl;
}

void testNvectorSum() {
    auto nv1 = new Nvector<double>("[1.2,2,3,4,5.223]");
    nv1->outputNvector("nv1");

    auto nv2 = new Nvector<double>("[2.12,3.22,8.1]");
    nv2->outputNvector("nv2");


    auto sum = *nv1 + *nv2;
    cout << "\n\tSum of nv1 and nv2 is" << endl;
    sum.outputNvector("sum");
}

void testNvectorScalarMultiply() {
    auto nv1 = new Nvector<double>("[1.2,2,3,4,5.223]");
    nv1->outputNvector("nv1");

    auto nv2 = new Nvector<double>("[2.12,3.22,8.1]");
    nv2->outputNvector("nv2");

    cout << "\n\tScalar multiplication is " << *nv1 * *nv2 << endl;
}


void task2() {
    auto citizens1 = new vector<Citizen>();

    fillDataHard(citizens1);
//    fillDataConsole(citizens1);

    outputCitizens(citizens1);

    auto citizens2 = new vector<Citizen>();
    fillDataHard(citizens2);

    cout << "\nHow many citizens remove: ";
    int n;
    cin >> n;
    citizens1 = Citizen::slice(*citizens1, n);

    citizens1->insert(citizens1->end(), citizens2->begin(), citizens2->end());

    outputCitizens(citizens1);
    outputCitizens(citizens2);

    sortContainer1(citizens1);
    outputCitizens(citizens1);

    sortContainer2(citizens2);
    outputCitizens(citizens2);

    auto citizens3 = new vector<Citizen>();
    citizens3->insert(citizens3->begin(), citizens1->begin(), citizens1->end());
    citizens3->insert(citizens3->end(), citizens2->begin(), citizens2->end());

    outputCitizens(citizens3);

    filterCitizens(citizens3);
    outputCitizens(citizens3);
}

void filterCitizens(vector<Citizen> *citizens) {
    auto result = new vector<Citizen>();
    vector<Citizen>::iterator i;
    for (i = citizens->begin(); i != citizens->end(); ++i) {
        if (isYoung(*i) || i->sex_i() == FEMALE)
            result->push_back(*i);
    }

    *citizens = *result;
    result->clear();
}

bool isYoung(Citizen &citizen) {
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);

    const int day_cur = aTime->tm_mday;
    const int month_cur = aTime->tm_mon + 1; // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
    const int year_cur = aTime->tm_year + 1900; // Year is # years since 1900

    //2002-10-31
    const int cit_day = stoi(citizen.date_of_birth().substr(8, 2));
    const int cit_month = stoi(citizen.date_of_birth().substr(5, 2));
    const int cit_year = stoi(citizen.date_of_birth().substr(0, 4));

    int yo = year_cur - cit_year - 1;

    if (month_cur > cit_month)
        ++yo;
    else if(month_cur == cit_month && day_cur > cit_day)
        ++yo;

    return yo < 16;
}

void sortContainer1(vector<Citizen> *citizens) {
    cout << "\n\tWe are sorting container #1." << endl;
    sortContainer(citizens);
}
void sortContainer2(vector<Citizen> *citizens) {
    cout << "\n\tWe are sorting container #2." << endl;
    sortContainer(citizens);
}
void sortContainer(vector<Citizen> *citizens) {
    int type = -1;
    string input;
    while (true) {
        cout << "Enter the type of sorting (Name = 0, Date of birth = 1, Sex = 2): ";
        cin >> input;
        {
            std::istringstream ss(input);
            if (ss >> type){
                switch (type) {
                    case 0:
                        sortByName(citizens);
                        break;
                    case 1:
                        sortByDates(citizens);
                        break;
                    case 2:
                        sortBySex(citizens);
                        break;
                    default:
                        cout << "Incorrect type. Enter 0, 1 or 2." << endl;
                        break;
                }
                break;
            } else {
                cout << "invalid type. Enter a number." << endl;
            }
        }
    }
}

void sortBySex(vector<Citizen> *citizens) {
    sort(citizens->begin(), citizens->end(), [](Citizen &a, Citizen &b) { return a.sex_i() < b.sex_i(); });
}

void sortByDates(vector<Citizen> *citizens) {
    sort(citizens->begin(), citizens->end(), [](Citizen &a, Citizen &b) { return a.date_of_birth() < b.date_of_birth(); });
}

void sortByName(vector<Citizen> *citizens) {
    sort(citizens->begin(), citizens->end(), [](Citizen &a, Citizen &b) { return a.name() < b.name(); });
}

void fillDataHard(vector<Citizen> *citizens) {
    citizens->push_back(*(new Citizen("Maria", "1989-07-15", FEMALE)));
    citizens->push_back(*(new Citizen("Ilon", "2007-10-13", X)));
    citizens->push_back(*(new Citizen("Alexander", "2002-10-31", MALE)));
    citizens->push_back(*(new Citizen("Valentina", "2021-11-10", FEMALE)));
    citizens->push_back(*(new Citizen("Egor", "1999-03-22", MALE)));
}

void fillDataConsole(vector<Citizen> *citizens) {
    string input;
    auto temp = new Citizen();
    while (true) {
        cout << "\nSaving new citizen (input \"stop\" to finish the process):" << endl;

        cout << "\tEnter name: ";
        cin >> input;
        if (input == "stop")
            break;
        temp->name(input);

        cout << "\tEnter date of birth (yyyy-mm-dd): ";
        cin >> input;
        if (input == "stop")
            break;
        temp->date_of_birth(input);

        cout << "\tEnter sex (Male = 0, Female = 1, X = 2): ";
        cin >> input;
        if (input == "stop")
            break;
        {
            std::istringstream ss(input);
            int sex_i;
            if (ss >> sex_i)
                temp->sex(sex_i);
            else
                temp->sex(input);
        }

        citizens->push_back(*temp);
        cout << "\n\tCitizen saved: " << temp->name() << " | "
        << temp->date_of_birth() << " | "
        <<temp->sex_s() << endl;
    }
}

void outputCitizens(vector<Citizen> *citizens) {
    fort::char_table table;
    table.set_cell_text_align(fort::text_align::center);
    table.set_cell_min_width(8);
    vector<Citizen>::iterator i;
    int x = 0;

    table << fort::header << "No." << "Name" << "Date of birth" << "Sex" << fort::endr;

    for (i = citizens->begin(); i != citizens->end(); ++i) {
        x++;

        table << std::to_string(x) + '.'
              << i->name()
              << i->date_of_birth()
              << i->sex_s() << fort::endr;
    }

    cout << table.to_string() << endl;
}

