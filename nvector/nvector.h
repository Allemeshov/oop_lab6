#ifndef LAB4_NVECTOR_H
#define LAB4_NVECTOR_H

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

template<typename T>
class Nvector {
private:
    vector<T> _vector;

    void saveElement(string &stringBuilder) {
        T element; // переменная для временного хранения элемента матрицы (Для его сохранения)

        std::istringstream ss(
                stringBuilder); // мы берем нашу строку с записанными данными и делаем из него поток данных для того, чтобы потом можно было сделать проверку, а можно ли его вообще записать в наше временную переменную.
        stringBuilder.clear(); // очищаем собранный из символов элемент матрицы
        if (ss >> element) { // Пытаемся записать строку, собранную до того посимвольно, во временную переменную
            // Если успешно, то:

            // сохраняем новый элемент
            _vector.push_back(element);
        } else {
            // Если не удалось записать собранную строчку во временную переменную, то:

            // очистить элементы. Они уже не нужны, потому что матрица неправильно пришла на обработку.
            _vector.clear();

            throw std::invalid_argument("Error! Value is invalid: " + std::to_string(
                    element)); // вызываем (выбрасываем) ошибку, где говорим, что значение некорректное и показываем, что за значение мы получили.
        }
    }

public:
    explicit Nvector() = default;

    explicit Nvector(const string &vStr) {
        auto errorProtocolMsg = "Ошибка! Строка должна иметь вид: [1,2,3,4,5,10,-10]"; // запишем текст ошибки, чтобы потом его выводить много раз

        if (vStr[0] != '[') // если множество не начинается с [
            throw std::invalid_argument(errorProtocolMsg); // то нужно вызвать исключение


        if (vStr[0] == '[' && vStr.find(']') !=
                              std::string::npos) { // Прежде всего нужно проверить какую строчку нам передали в конструктор: если в этой срочке нет, как минимум, символов { и }, то она уже неправильная и нет смысла её парсить(обрабатывать).
            if (vStr[1] ==
                ']') { // Если второй символ в строчке является }, то она пустая, а кто у нас пустую матрицу создает..? Правильно!
                Nvector<T>();
            } else {

                // Если все нормуль, то начием считывать элементы:

                std::string stringBuilder;
                bool isBracetClosed = false;

                for (int i = 1; !isBracetClosed; ++i) { // начинаем считывать элементы строки
                    if (vStr[i] == '[') { // Постоянная проверка, что если скобка открывается снова, то это ошибка.
                        throw std::invalid_argument(errorProtocolMsg);
                    }

                    switch (vStr[i]) {
                        case ']': { // Если линия закрывается, то надо:
                            if (!stringBuilder.empty()) {
                                saveElement(stringBuilder);
                            } else {
                                throw std::invalid_argument(errorProtocolMsg);
                            }

                            isBracetClosed = true;

                            break;
                        }
                        case ',': { // Если запитая, то надо сохранить новый элемент матрицы
                            if (!stringBuilder.empty()) { // если в сборщике строки ничего нет, и текущий симвлол запятая, то это ошибка
                                saveElement(stringBuilder);
                            } else {
                                throw std::invalid_argument(errorProtocolMsg);
                            }

                            break;
                        }
                        case ' ': // Пустота она и в Африке пустота, а тут и подабно. Короче на пробел ничего делать не надо.
                            break;
                        default: { // Если у нас ничего из выше упомянутого не было, то запишем новый символ нового элемента матрицы
                            stringBuilder.push_back(vStr[i]);
                            break;
                        }
                    }

                }
            }
        } else {
            throw std::invalid_argument(errorProtocolMsg);
        }
    }

    ~Nvector() {
        _vector.clear();
    }

    friend Nvector<T> operator+(const Nvector<T> &v1, const Nvector<T> &v2) {
        auto result = new Nvector<T>();
        const int len = v1._vector.size() > v2._vector.size() ?
                v1._vector.size() : v2._vector.size();
        for (int i = 0; i < len; ++i)
            result->_vector.push_back(v1._vector[i] + v2._vector[i]);
        return *result;
    }

    friend T operator*(const Nvector<T> &v1, const Nvector<T> &v2) {
        T result = 0;
        const int len = v1._vector.size() < v2._vector.size() ?
                        v1._vector.size() : v2._vector.size();
        for (int i = 0; i < len; ++i)
            result += v1._vector[i] * v2._vector[i];

        return result;
    }

    double GetModule() {
        int sumSqrs = 0;
        const int len = _vector.size();
        for (int i = 0; i < len; ++i)
            sumSqrs += _vector[i] * _vector[i];

        return sqrt(sumSqrs);
    }

    void outputNvector(const string& name = "") {
        cout << "\n\tNvector " << name << " elements: ";

        const int len = _vector.size();
        for (int i = 0; i < len; ++i) {
            cout << _vector[i] << ' ';
        }
        cout << endl;
    }
};

#endif //LAB4_NVECTOR_H
