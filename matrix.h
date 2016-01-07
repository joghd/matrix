#ifndef MATRIX_H_
#define MATRIX_H_
#include <cmath>
#include <iostream>
template <class T>
class Matrix
{
private:
    unsigned const col;
    unsigned const row;
    T** data;


    T determinant(const unsigned n, T **matrix)
    {
        T sum = 0, **tmp;
        unsigned jt, s = 0;
        if(n == 2)
        {
            return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
        }else{
        for(unsigned x = 0; x < n; x++)
        {
            tmp = ( T **) malloc((n-1)* sizeof(T *)) ;
            for (unsigned i = 0 ; i < n-1 ; i++)
                tmp[i] = (T *) malloc((n-1)* sizeof(T));

            for(unsigned i = 1; i < n; i++)
            {
                jt = 0;
                for(unsigned j = 0; j < n; j++)
                {
                    if(j == x) continue;
                    tmp[i - 1][jt] = matrix[i][j];
                    jt++;
                }
            }
            sum += pow(-1, s) * matrix[0][x] * determinant(n-1, tmp);
            s++;
            for (unsigned i = 0 ; i < n-1 ; i++)
                free(tmp[i]) ;
            free(tmp) ;
        }
        return sum;
        }
    }
    friend std::ostream& operator<< (std::ostream &os, const Matrix <T> &matrix)
    {
            for(unsigned i = 0; i < matrix.row; i++)
            {
                for(unsigned j = 0; j < matrix.col; j++)
                {
                    std::cout << matrix.data[i][j] << "\t";
                }std::cout << std::endl;

            }
            return os;
     }
public:
    Matrix(): row(0), col(0), data(nullptr){}

    Matrix( const int& r, const int& c): col(c),row(r), data(nullptr){
        data = new T*[row];
        for (unsigned i = 0; i < row; i++ )
        {
            data[i] = new T[col];
        }
    }
    Matrix(const Matrix &other): col(other.col), row(other.row)
    {
        data = new T*[other.row];
        for (unsigned i = 0; i < other.row; i++ )
        {
            data[i] = new T[other.col];
        }
        for(unsigned i = 0; i < row; i++)
        {
            for(unsigned j = 0; j < row; j++)
            {
                data[i][j] = other.data[i][j];
            }
        }
    }

 ~Matrix(){
        if ( nullptr == data )
        {
            return;
        }
        for ( unsigned i = 0; i < row; i++ )
        {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }
    Matrix& operator= (const Matrix& other)
    {
        Matrix tmp(other);
        *this = std::move(tmp);
        return *this;
    }
    Matrix (Matrix&& other):col(other.col), row(other.row)
    {
        data = new T*[other.row];
        for (unsigned i = 0; i < other.row; i++ )
        {
            data[i] = new T[other.col];
        }
        for(unsigned i = 0; i < row; i++)
        {
            for(unsigned j = 0; j < col; j++)
            {
                data[i][j] = other.data[i][j];
            }

        }
        other.data = nullptr;
    }
    Matrix& operator=(const Matrix&& other)
    {
        std::swap(col, other.col);
        std::swap(row, other.row);
        std::swap(data, other.data);
        return *this;
    }

    T get( const int& x, const int& y ) {
        return data[x][y];
    }
    unsigned getCol() const {
        return col;
    }
    unsigned getRow() const {
        return row;
    }

    void set( const T& t, const int& x, const int& y ){
        data[x][y] = t;
    }
    void setAll( const T& t ){
        for ( unsigned  x = 0; x < row; x++ )
        {
            for ( unsigned y = 0; y < col; y++ )
            {
                data[x][y] = t;
            }
        }
    }
    void appIdentity()
    {
        if(row != col)
        {
            throw "[error] Matrix should be square.";
        }else{
            setAll(0);
            for(unsigned i = 0; i < row; i++)
            {
                for(unsigned j = 0; j < col; j++)
                {
                    if(i == j)
                    {
                        set(1, i ,j);
                    }
                }
            }
        }
    }
    T getDeterminant()
    {
        if(row != col)
        {
            throw "[error] Matrix should be sqaure.";
        }else
            return determinant(row, data);

    }
    T& operator()(unsigned row, unsigned col)
    {
        if(row > this->row || col > this->col)
        {
            throw "[error] Out of range.";
        }else{
            return data[row][col];
        }
    }

};
#endif
