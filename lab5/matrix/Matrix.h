//
// Created by michal on 12.04.18.
//

#ifndef JIMP_EXERCISES_MATRIX_H
#define JIMP_EXERCISES_MATRIX_H

#include <complex>
#include <initializer_list>
#include <string>
#include <vector>

namespace algebra
{

    class Matrix {


        std::vector<std::complex<double>> v_;
        size_t rows;
        size_t columns;


    public:
        std::pair<size_t, size_t> Size();
        Matrix();
        Matrix(size_t, size_t);
        Matrix (Matrix &wzor)= default;
        Matrix(std::initializer_list<std::vector<std::complex<double>>>);
        explicit Matrix (std::string);
        std::string Print() const;
        Matrix Add(const Matrix &wzor) const;
        Matrix Sub(const Matrix &wzor);
        Matrix Mul(const Matrix &wzor);
        Matrix Pow(int);

    };
}



#endif //JIMP_EXERCISES_MATRIX_H
