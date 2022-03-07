#include<iostream>
#include<vector>
#define Matrix vector<vector<int>>
using namespace std;


void print_matrix(Matrix M);
Matrix Naive_mult(Matrix A, Matrix B);
vector<Matrix> Split(Matrix a);
Matrix Concatinate(vector<Matrix> c);
Matrix Divide_Conquer(Matrix A, Matrix B);
Matrix Add_matrix(Matrix A, Matrix B);
Matrix Subtract_matrix(Matrix A, Matrix B);
Matrix Strassen(Matrix A, Matrix B);

int main()
{
    Matrix X = {  {5, 0}, {10, 6}  };
    Matrix Y = {  {2, 1}, {2, 4}  };
    Matrix Z = {  {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}  };
    Matrix L = Add_matrix(Z, Z);
    Matrix Ans = Naive_mult(Z, L);
    cout<<"Naive:"<<endl;
    print_matrix(Ans);
    cout<<endl;
    Matrix Ans2 = Divide_Conquer(Z, L);
    cout<<"Divide&Conquer:"<<endl;
    print_matrix(Ans2);
    cout<<endl;
    Matrix Ans3 = Strassen(Z, L);
    cout<<"Strassen:"<<endl;
    print_matrix(Ans3);
    return 0;
}

void print_matrix(Matrix M)
{
    for(auto row:M)
    {
        for(auto element:row)
            cout << element << " ";
        cout<<endl;
    }
}


Matrix Naive_mult(Matrix A, Matrix B)
{
    Matrix C;
    size_t n = A.size();
    for(size_t i=0; i<n; i++)
    {
        C.push_back({});
        for(size_t j=0; j<n; j++)
        {
            int sum{};
            for(size_t k=0; k<n; k++)
            {
                sum += A[i][k] * B[k][j];
            }
            C[i].push_back(sum);
        }
    }
    return C;
}


Matrix Divide_Conquer(Matrix A, Matrix B)
{

    if(A.size()==1)
    {
        Matrix c_min = {{A[0][0] * B[0][0]}};
        return c_min;
    }

    vector<Matrix> split_A = Split(A);
    vector<Matrix> split_B = Split(B);
    Matrix C1 = Add_matrix(Divide_Conquer(split_A[0], split_B[0]) , Divide_Conquer(split_A[1], split_B[2]));
    Matrix C2 = Add_matrix(Divide_Conquer(split_A[0], split_B[1]) , Divide_Conquer(split_A[1], split_B[3]));
    Matrix C3 = Add_matrix(Divide_Conquer(split_A[2], split_B[0]) , Divide_Conquer(split_A[3], split_B[2]));
    Matrix C4 = Add_matrix(Divide_Conquer(split_A[2], split_B[1]) , Divide_Conquer(split_A[3], split_B[3]));
    vector<Matrix> c_array = {C1, C2, C3, C4};
    Matrix C = Concatinate(c_array);
    return C;
}



Matrix Strassen(Matrix A, Matrix B)
{
    if(A.size()==1)
    {
        Matrix c_min = {{A[0][0] * B[0][0]}};
        return c_min;
    }
    vector<Matrix> split_A = Split(A);
    vector<Matrix> split_B = Split(B);
    Matrix P1 = Strassen(split_A[0], Subtract_matrix(split_B[1], split_B[3]));
    Matrix P2 = Strassen(Add_matrix(split_A[0], split_A[1]), split_B[3]);
    Matrix P3 = Strassen(Add_matrix(split_A[2], split_A[3]), split_B[0]);
    Matrix P4 = Strassen(split_A[3], Subtract_matrix(split_B[2], split_B[0]));
    Matrix P5 = Strassen(Add_matrix(split_A[0], split_A[3]), Add_matrix(split_B[0], split_B[3]));
    Matrix P6 = Strassen(Subtract_matrix(split_A[1], split_A[3]), Add_matrix(split_B[2], split_B[3]));
    Matrix P7 = Strassen(Subtract_matrix(split_A[0], split_A[2]), Add_matrix(split_B[0], split_B[1]));
    
    Matrix C1 = Add_matrix(Add_matrix(P5, P6), Subtract_matrix(P4, P2));
    Matrix C2 = Add_matrix(P1, P2);
    Matrix C3 = Add_matrix(P3, P4);
    Matrix C4 = Subtract_matrix(Add_matrix(P1, P5), Add_matrix(P3, P7));
    vector<Matrix> c_array = {C1, C2, C3, C4};
    Matrix C = Concatinate(c_array);
    return C;

}



vector<Matrix> Split(Matrix a)
{
    vector<Matrix> c;
    size_t n = a.size()/2;
    Matrix min_c;
    for(size_t e=0; e<=n; e+=n)
    {
        for(size_t f=0; f<=n; f+=n)
        {
            size_t count{};
            for(size_t i=e; i<n+e; i++)
            {   
                min_c.push_back({});
                for(size_t j=f; j<n+f; j++)
                    min_c[count].push_back(a[i][j]);
                count++;
            }
            c.push_back(min_c);
            min_c.clear();
        }
    }
    return c;
}


Matrix Concatinate(vector<Matrix> c)
{
    size_t n = c[0].size();
    Matrix b;
    vector<int> vect(2*n, 0);
    for(size_t p=0; p<2*n; p++)
        b.push_back(vect);
    size_t count{};
    for(size_t e=0; e<=n; e+=n)
    {
        for(size_t f=0; f<=n; f+=n)
        {
            for(size_t i=e; i<n+e; i++)
            {   
                for(size_t j=f; j<n+f; j++)
                    b[i][j] = c[count][i-e][j-f];
            }
            count++;
        }
    }
    return b;
}




Matrix Add_matrix(Matrix A, Matrix B)
{
    Matrix C;
    for(size_t i=0; i<A.size(); i++)
    {
        C.push_back({});
        for(size_t j=0; j<A.size(); j++)
            C[i].push_back(A[i][j] + B[i][j]);
    }
    return C;
}

Matrix Subtract_matrix(Matrix A, Matrix B)
{
    Matrix C;
    for(size_t i=0; i<A.size(); i++)
    {
        C.push_back({});
        for(size_t j=0; j<A.size(); j++)
            C[i].push_back(A[i][j] - B[i][j]);
    }
    return C;
}