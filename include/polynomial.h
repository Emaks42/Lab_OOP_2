#pragma once
#include <ostream>
#include <algorithm>

class Polynomial {
    int degree_ = -1;
    double* coef = nullptr;

public:
    Polynomial();
    explicit Polynomial(double* ptr, int deg);
    Polynomial(const Polynomial& other);
    Polynomial(Polynomial&& other) noexcept;
    Polynomial& operator=(Polynomial other);
    friend void swap(Polynomial& p1, Polynomial& p2);

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