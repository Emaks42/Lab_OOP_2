#include "../include/polynomial.h"
#include <math.h>

Polynomial::Polynomial(): degree_(-1), coef(nullptr) {}

Polynomial::Polynomial(double* ptr, int deg): degree_(deg) {    
    if (deg == -1) {
        return;
    }
    coef = new double[deg+1];
    for (int i{}; i < degree_ + 1; ++i) {
        coef[i] = ptr[i];
    }
}
    
Polynomial::Polynomial(const Polynomial& other) {
    if (other.get_degree() == -1) {
        degree_ = -1;
        coef = nullptr;
        return;
    }
    degree_ = other.get_degree();
    coef = new double[other.get_degree()+1];
    for (int i{}; i < degree_ + 1; ++i) {
        coef[i] = other.get_coef(i);
    }
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        delete[] coef;       

        degree_ = other.degree_;
        coef = (degree_ + 1 > 0) ? new double[degree_ + 1] : nullptr;

        for (int i{}; i < degree_ + 1; ++i) {
            coef[i] = other.get_coef(i);
        }
    }
    return *this;
}

Polynomial::Polynomial(Polynomial&& other) {
    degree_ = other.degree_;
    coef = other.coef;
    
    other.degree_ = -1;
    other.coef = nullptr;
}

Polynomial::~Polynomial() {
    delete[] coef;
    coef = nullptr;
}

bool Polynomial::is_equal(const Polynomial& other, double eps) {
    for (int i{}; i < degree_ + 1; ++i) {
        if (fabs(coef[i] - other.get_coef(i)) > eps) {
            return false;
        }
    }
    return true;
}

void Polynomial::add(const Polynomial& other) {
    if (other.degree_ > degree_) {
        double* new_coef = new double[other.get_degree() + 1];
        for (int i{}; i < other.degree_ + 1; ++i) {
            new_coef[i] = other.coef[i] + this->get_coef(i);
        }
        delete[] coef;
        coef = new_coef;
        degree_ = other.degree_;
        return;
    }
    for (int i{}; i < degree_ + 1; ++i) {
        coef[i] += other.get_coef(i);
    }
}

void Polynomial::mul(const Polynomial& other) {
    double* new_coef = new double[other.get_degree() * degree_ + 2];
    for (int i{}; i < other.get_degree() + 1; ++i) {
        for (int j{}; j < degree_ + 1; ++j) {
            new_coef[i + j] = coef[j] * other.get_coef(i);
        }
    }
    delete[] coef;
    coef = new_coef;
    degree_ *= other.get_degree();
}

double Polynomial::evaluate(double value) {
    double result{}, val_pow{1};
    for (int i{}; i < degree_ + 1; ++i) {
        result += coef[i] * val_pow;
        val_pow *= value;
    }
    return result;
}

void Polynomial::print(std::ostream& stream, double eps) {
    for (int i{}; i < degree_ + 1; ++i) {
        if (coef[i] < eps && coef[i] > -eps) {
            break;
        }
        if (i > 0) {
            stream << " + ";
        }
        if (coef[i] < 0) {
            stream << "(" << coef[i] << ")";
        } else {
            stream << coef[i];
        }
        if (i > 0) {
            stream << " * x^" << i;
        }
    }
    stream << std::endl;
}

void Polynomial::trim(double eps) {
    int zero_coef_count{};
    for (int i{}; i < degree_ + 1; ++i) {
        if (coef[i] < eps && coef[i] > -eps) {
            zero_coef_count += 1;
        } else {
            break;
        }
    }
    if (zero_coef_count == degree_ + 1) {
        delete[] coef;
        coef = nullptr;
        degree_ = -1;
    }
    double* new_coef = new double[degree_ + 1 - zero_coef_count];
    degree_ -= zero_coef_count;
    for (int i{}; i < degree_ + 1; ++i) {
        new_coef[i] = coef[i];
    }
    delete[] coef;
    coef = new_coef;
}

const int Polynomial::get_degree() const {
    return degree_;
}

const double Polynomial::get_coef(int degree) const {
    if (degree > degree_ || degree < 0) {
        return 0;
    }
    return coef[degree];
}