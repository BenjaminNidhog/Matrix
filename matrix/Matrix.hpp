/**
 * @file Matrix.hpp
 *
 * A simple matrix template library.
 *
 * @author James Goppert <james.goppert@gmail.com>
 */

#pragma once

#include <cstdio>
#include <cstring>

#if defined(SUPPORT_STDIOSTREAM)
#include <iostream>
#include <iomanip>
#endif // defined(SUPPORT_STDIOSTREAM)

#include "math.hpp"

namespace matrix
{

template <typename Type, size_t M>
class Vector;

template<typename Type, size_t M, size_t N>
class Matrix;

template <typename Type, size_t P, size_t Q, size_t M, size_t N>
class Slice;

template<typename Type, size_t M, size_t N>
class Matrix
{

    Type _data[M][N] {};

public:

    // Constructors
    Matrix() = default;

    explicit Matrix(const Type data_[M*N])
    {
        memcpy(_data, data_, sizeof(_data));
    }

    explicit Matrix(const Type data_[M][N])
    {
        memcpy(_data, data_, sizeof(_data));
    }

    Matrix(const Matrix &other)
    {
        memcpy(_data, other._data, sizeof(_data));
    }

    template<size_t P, size_t Q>
    Matrix(const Slice<Type, M, N, P, Q>& in_slice)
    {
        Matrix<Type, M, N>& self = *this;
        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                self(i, j) = in_slice(i, j);
            }
        }
    }

    /**
     * Accessors/ Assignment etc.
     */


    inline Type operator()(size_t i, size_t j) const
    {
        return _data[i][j];
    }

    inline Type &operator()(size_t i, size_t j)
    {
        return _data[i][j];
    }

    Matrix<Type, M, N> & operator=(const Matrix<Type, M, N> &other)
    {
        if (this != &other) {
            memcpy(_data, other._data, sizeof(_data));
        }
        return (*this);
    }

    void copyTo(Type dst[M*N]) const
    {
        memcpy(dst, _data, sizeof(Type)*M*N);
    }

    void copyToColumnMajor(Type dst[M*N]) const
    {
        const Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                dst[i+(j*M)] = self(i, j);
            }
        }
    }

    /**
     * Matrix Operations
     */

    // this might use a lot of programming memory
    // since it instantiates a class for every
    // required mult pair, but it provides
    // compile time size_t checking
    template<size_t P>
    Matrix<Type, M, P> operator*(const Matrix<Type, N, P> &other) const
    {
        const Matrix<Type, M, N> &self = *this;
        Matrix<Type, M, P> res;
        res.setZero();

        for (size_t i = 0; i < M; i++) {
            for (size_t k = 0; k < P; k++) {
                for (size_t j = 0; j < N; j++) {
                    res(i, k) += self(i, j) * other(j, k);
                }
            }
        }

        return res;
    }

    Matrix<Type, M, N> emult(const Matrix<Type, M, N> &other) const
    {
        Matrix<Type, M, N> res;
        const Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                res(i, j) = self(i, j)*other(i, j);
            }
        }

        return res;
    }

    Matrix<Type, M, N> edivide(const Matrix<Type, M, N> &other) const
    {
        Matrix<Type, M, N> res;
        const Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                res(i, j) = self(i, j)/other(i, j);
            }
        }

        return res;
    }

    Matrix<Type, M, N> operator+(const Matrix<Type, M, N> &other) const
    {
        Matrix<Type, M, N> res;
        const Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                res(i, j) = self(i, j) + other(i, j);
            }
        }

        return res;
    }

    Matrix<Type, M, N> operator-(const Matrix<Type, M, N> &other) const
    {
        Matrix<Type, M, N> res;
        const Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                res(i, j) = self(i, j) - other(i, j);
            }
        }

        return res;
    }

    // unary minus
    Matrix<Type, M, N> operator-() const
    {
        Matrix<Type, M, N> res;
        const Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                res(i, j) = -self(i, j);
            }
        }

        return res;
    }

    void operator+=(const Matrix<Type, M, N> &other)
    {
        Matrix<Type, M, N> &self = *this;
        self = self + other;
    }

    void operator-=(const Matrix<Type, M, N> &other)
    {
        Matrix<Type, M, N> &self = *this;
        self = self - other;
    }

    template<size_t P>
    void operator*=(const Matrix<Type, N, P> &other)
    {
        Matrix<Type, M, N> &self = *this;
        self = self * other;
    }

    /**
     * Scalar Operations
     */

    Matrix<Type, M, N> operator*(Type scalar) const
    {
        Matrix<Type, M, N> res;
        const Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                res(i, j) = self(i, j) * scalar;
            }
        }

        return res;
    }

    inline Matrix<Type, M, N> operator/(Type scalar) const
    {
        return (*this)*(1/scalar);
    }

    Matrix<Type, M, N> operator+(Type scalar) const
    {
        Matrix<Type, M, N> res;
        const Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                res(i, j) = self(i, j) + scalar;
            }
        }

        return res;
    }

    inline Matrix<Type, M, N> operator-(Type scalar) const
    {
        return (*this) + (-1*scalar);
    }

    void operator*=(Type scalar)
    {
        Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                self(i, j) = self(i, j) * scalar;
            }
        }
    }

    void operator/=(Type scalar)
    {
        Matrix<Type, M, N> &self = *this;
        self = self * (Type(1) / scalar);
    }

    inline void operator+=(Type scalar)
    {
        *this = (*this) + scalar;
    }

    inline void operator-=(Type scalar)
    {
        *this = (*this) - scalar;
    }

    bool operator==(const Matrix<Type, M, N> &other) const
    {
        const Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                if (!isEqualF(self(i, j), other(i, j))) {
                    return false;
                }
            }
        }

        return true;
    }

    bool operator!=(const Matrix<Type, M, N> &other) const
    {
        const Matrix<Type, M, N> &self = *this;
        return !(self == other);
    }

    /**
     * Misc. Functions
     */

    void write_string(char * buf, size_t n) const
    {
        buf[0] = '\0'; // make an empty string to begin with (we need the '\0' for strlen to work)
        const Matrix<Type, M, N> &self = *this;
        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                snprintf(buf + strlen(buf), n - strlen(buf), "\t%8.8g", double(self(i, j))); // directly append to the string buffer
            }
            snprintf(buf + strlen(buf), n - strlen(buf), "\n");
        }
    }

    void print(FILE *stream = stdout) const
    {
        // element: tab, point, 8 digits; row: newline; string: \0 end
        static const size_t n = 10*N*M + M + 1;
        char * buf = new char[n];
        write_string(buf, n);
        fprintf(stream, "%s\n", buf);
        delete[] buf;
    }

    Matrix<Type, N, M> transpose() const
    {
        Matrix<Type, N, M> res;
        const Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                res(j, i) = self(i, j);
            }
        }

        return res;
    }

    // tranpose alias
    inline Matrix<Type, N, M> T() const
    {
        return transpose();
    }

    template<size_t P, size_t Q>
    const Slice<Type, P, Q, M, N> slice(size_t x0, size_t y0) const
    {
        return Slice<Type, P, Q, M, N>(x0, y0, this);
    }

    template<size_t P, size_t Q>
    Slice<Type, P, Q, M, N> slice(size_t x0, size_t y0)
    {
        return Slice<Type, P, Q, M, N>(x0, y0, this);
    }

    const Slice<Type, 1, N, M, N> row(size_t i) const
    {
        return slice<1, N>(i,0);
    }

    Slice<Type, 1, N, M, N> row(size_t i)
    {
        return slice<1, N>(i,0);
    }

    const Slice<Type, M, 1, M, N> col(size_t j) const
    {
        return slice<M, 1>(0,j);
    }

    Slice<Type, M, 1, M, N> col(size_t j)
    {
        return slice<M, 1>(0,j);
    }

    void setRow(size_t i, const Matrix<Type, N, 1> &row_in)
    {
        slice<1,N>(i,0) = row_in.transpose();
    }


    void setCol(size_t j, const Matrix<Type, M, 1> &column)
    {
        slice<M,1>(0,j) = column;
    }

    void setZero()
    {
        memset(_data, 0, sizeof(_data));
    }

    inline void zero()
    {
        setZero();
    }

    void setAll(Type val)
    {
        Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                self(i, j) = val;
            }
        }
    }

    inline void setOne()
    {
        setAll(1);
    }

    inline void setNaN()
    {
        setAll(NAN);
    }

    void setIdentity()
    {
        setZero();
        Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M && i < N; i++) {
            self(i, i) = 1;
        }
    }

    inline void identity()
    {
        setIdentity();
    }

    inline void swapRows(size_t a, size_t b)
    {
        if (a == b) {
            return;
        }

        Matrix<Type, M, N> &self = *this;

        for (size_t j = 0; j < N; j++) {
            Type tmp = self(a, j);
            self(a, j) = self(b, j);
            self(b, j) = tmp;
        }
    }

    inline void swapCols(size_t a, size_t b)
    {
        if (a == b) {
            return;
        }

        Matrix<Type, M, N> &self = *this;

        for (size_t i = 0; i < M; i++) {
            Type tmp = self(i, a);
            self(i, a) = self(i, b);
            self(i, b) = tmp;
        }
    }

    Matrix<Type, M, N> abs() const
    {
        Matrix<Type, M, N> r;
        for (size_t i=0; i<M; i++) {
            for (size_t j=0; j<N; j++) {
                r(i,j) = Type(fabs((*this)(i,j)));
            }
        }
        return r;
    }

    Type max() const
    {
        Type max_val = (*this)(0,0);
        for (size_t i=0; i<M; i++) {
            for (size_t j=0; j<N; j++) {
                Type val = (*this)(i,j);
                if (val > max_val) {
                    max_val = val;
                }
            }
        }
        return max_val;
    }

    Type min() const
    {
        Type min_val = (*this)(0,0);
        for (size_t i=0; i<M; i++) {
            for (size_t j=0; j<N; j++) {
                Type val = (*this)(i,j);
                if (val < min_val) {
                    min_val = val;
                }
            }
        }
        return min_val;
    }

    bool isAllNan() const {
        const Matrix<float, M, N> &self = *this;
        bool result = true;
        for (size_t i = 0; i < M; i++) {
            for (size_t j = 0; j < N; j++) {
                result = result && isnan(self(i, j));
            }
        }
        return result;
    }
};

template<typename Type, size_t M, size_t N>
Matrix<Type, M, N> zeros() {
    Matrix<Type, M, N> m;
    m.setZero();
    return m;
}

template<typename Type, size_t M, size_t N>
Matrix<Type, M, N> ones() {
    Matrix<Type, M, N> m;
    m.setOne();
    return m;
}

template<size_t M, size_t N>
Matrix<float, M, N> nans() {
    Matrix<float, M, N> m;
    m.setNaN();
    return m;
}

template<typename Type, size_t  M, size_t N>
Matrix<Type, M, N> operator*(Type scalar, const Matrix<Type, M, N> &other)
{
    return other * scalar;
}

template<typename Type, size_t  M, size_t N>
bool isEqual(const Matrix<Type, M, N> &x,
             const Matrix<Type, M, N> &y, const Type eps=1e-4f) {
    return x == y;
}

#if defined(SUPPORT_STDIOSTREAM)
template<typename Type, size_t  M, size_t N>
std::ostream& operator<<(std::ostream& os,
                         const matrix::Matrix<Type, M, N>& matrix)
{
    for (size_t i = 0; i < M; ++i) {
        os << "[";
        for (size_t j = 0; j < N; ++j) {
            os << std::setw(10) << static_cast<double>(matrix(i, j));
            os << "\t";
        }
        os << "]" << std::endl;
    }
    return os;
}
#endif // defined(SUPPORT_STDIOSTREAM)

} // namespace matrix

/* vim: set et fenc=utf-8 ff=unix sts=0 sw=4 ts=4 : */
