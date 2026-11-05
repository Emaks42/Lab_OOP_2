#pragma once
#include <ostream>

class Polynomial {
    int degree_ = -1;
    double* coef = nullptr;

public:
    Polynomial();
    explicit Polynomial(double* ptr, int deg);
    Polynomial(const Polynomial& other);
    Polynomial(Polynomial&& other);
    Polynomial& operator=(const Polynomial& other);

    ~Polynomial();

    bool is_equal(const Polynomial& other, double eps = 1e-9);
    void add(const Polynomial& other);
    void mul(const Polynomial& other);
    double evaluate(double value);
    void print(std::ostream& stream, double eps = 1e-14);
    void trim(double eps = 1e-9);
    const int get_degree() const;
    const double get_coef(int position) const;
};