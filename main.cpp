#include <iostream>
#include "./include/polynomial.h"

Polynomial read_poly() {
    int degree;
    std::cout << "введите степень полинома\n";
    std::cin >> degree;
    double* c = new double[degree + 1];
    std::cout << "введите коэфициенты\n";
    for (int i{}; i < degree + 1; ++i) {
        std::cin >> c[i];
    }
    Polynomial p(c, degree);
    delete[] c;
    return p;
}

void dialogue_cycle() {
    bool running = true;
    int inp{};
    double value{};
    int size{};
    Polynomial p, p_;
    double precision = 1e-9;
    int answer{};
    while (running) {
        std::cout << "Введите 1 из 9 опций:\n";
        std::cout << "0 - выход из меню\n";
        std::cout << "1 - создать полином\n";
        std::cout << "2 - напечатать полином\n";
        std::cout << "3 - сложить полином с другим\n";
        std::cout << "4 - умножить полином на другой\n";
        std::cout << "5 - убрать из полинома ведущие нули\n";
        std::cout << "6 - сравнить полином с другим\n";
        std::cout << "7 - вывести значение полинома в точке\n";
        std::cout << "8 - установить точность сравнения\n";
        std::cin >> inp;
        switch (inp)
        {
            case 0:
                std::cout << "работа завершена, спасибо, что выбираете нас\n";
                running = false;
                break;
            
            case 1:
                p = read_poly();
                std::cout << "успешно создан полином\n";
                break;
            
            case 2:
                if (p.get_degree() == -1) { std::cout << "для того, чтобы вывести полином сначала создайте его\n"; break;}
                p.print(std::cout, precision);
                break;
            
            case 3:
                if (p.get_degree() == -1) { std::cout << "для того, чтобы сложить полином с другим создайте полином\n"; break;} 
                std::cout << "введите полином для сложения\n";
                p_ = read_poly();
                p.add(p_);
                break;
            
            case 4:
                if (p.get_degree() == -1) { std::cout << "для того, чтобы умножить полином на другой создайте полином\n"; break;} 
                std::cout << "введите полином для умножения\n";
                p_ = read_poly();
                p.mul(p_);
                break;
            
            case 5:
                if (p.get_degree() == -1) { std::cout << "для того, чтобы очистить полином от ведущих нулей сначала создайте его\n"; break;}
                p.trim(precision);
                break;
            
            case 6:
                if (p.get_degree() == -1) { std::cout << "для того, чтобы сравнить полином с другим создайте полином\n"; break;} 
                std::cout << "введите полином для сравнения\n";
                p_ = read_poly();
                if (p.is_equal(p_, precision)) {
                    std::cout << "полиномы равны\n";
                } else {
                    std::cout << "полиномы не равны\n";
                }
                break;
            
            case 7:
                if (p.get_degree() == -1) { std::cout << "для того, чтобы вычислить значение полинома в точке надо его создать\n"; break;}
                std::cout << "введите точку на действительной оси\n";
                std::cin >> value;
                std::cout << p.evaluate(value);
                break;
            
            case 8:
                std::cout << "введите точность для сравнения\n";
                std::cin >> precision;
                break;
        
            default:
                std::cout << "неверный номер команды\n";
                break;
        }
    }

}


int main() {
    dialogue_cycle();
    return 0;
}