#ifndef VECTORANDMULITIPLICATION_H
#define VECTPRANDMULITIPLICATION_H
#include"../utils/common.hpp"
template<typename T>
class VectorAndMultiplication{
//向量与矩阵加法
public:
    //向量加法,输入两个向量求其和，并返回此向量
    vector<T>VectorPlus(vector<T>a,vector<T>b);
    //矩阵加法
    vector<vector<T>>MatrixPlus(vector<vector<T>>A,vector<vector<T>>B);

//向量与矩阵乘法
public:
    //向量的乘法
    vector<T>VectorInnerProduct(vector<T>a,vector<T>b);
    //向量乘以矩阵
    vector<T>Matrix_VectorProduct(vector<vector<T>>A,vector<T>b);
    //矩阵乘法
    vector<vector<T>>Matrix_MatrixProduct(vector<vector<T>>A,vector<vector<T>>B);
public:
    //向量输出函数
    void VectorPrint(vector<T>result){
        using std::cout;
        using std::endl;
        for(int i=0;i<result.size();i++) std::cout<<result[i]<<" ";
        std::cout<<std::endl;
    }
        //矩阵输出函数
    void MatrixPrint(vector<vector<T>>result){
        using std::cout;
        using std::endl;
        for(int i=0;i<result.size();i++){
            for(int j=0;j<result[0].size();j++){
                std::cout<<result[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
    }
};
/*向量加法O(n)
1.两个n维向量相加得到向量c
c[0,0,0,...,0]
For i=1 to n:
        c(i)=a(i)+b(i).*/
template<typename T>
vector<T>VectorAndMultiplication<T>::VectorPlus(vector<T>a,vector<T>b){
    vector<T>c(a.size(),0);
    for(int i=0;i<c.size();i++)
        c[i]=a[i]+b[i];
    return c;
}
/*矩阵加法O(mn)
两个矩阵大小都是m*n
C矩阵的大小也必须是m*n
For i=1 to m:
    For j=1 to n:
            c(i,j)=a(i,j)+b(i,j);
*/
template<typename T>
vector<vector<T>>VectorAndMultiplication<T>::MatrixPlus(vector<vector<T>>A,vector<vector<T>>B){
    vector<vector<T>>C(A.size(),(vector<T>(A[0].size(),0)));
    for(int i=0;i<A.size();i++){
        for(int j=0;j<A[0].size();j++){
            C[i][j]=A[i][j]+B[i][j];
        }
    }
    return C;
}
/*向量乘法O(n)
也就是a的转置乘以b
    For i = 1 to n:
        c=c+a(i)*c(i);*/
template<typename T>
vector<T>VectorAndMultiplication<T>::VectorInnerProduct(vector<T>a,vector<T>b){
    vector<T>c(a.size(),0);
    for(int i=0;i<c.size();i++) c[i]=c[i]+a[i]*b[i];

    return c;
}
/*向量乘以矩阵O(mn)
向量的大小必须等于矩阵的列数
乘积为向量
c(m*1)=A(m*n)*b(n*1)
即向量c就是 m行n列的矩阵乘以n行1列的向量
c(i)=A(i,1)*b(1)+...+A(i,j)*b(j);
For i = 1 to m:
    For　j = 1 to n:
        c(i)=c(i)+A(i,j)*b(j);*/
template<typename T>
vector<T>VectorAndMultiplication<T>::Matrix_VectorProduct(vector<vector<T>>A,vector<T>b){
    vector<T>c(A.size(),0);
    for(int i=0;i<A.size();i++){
        for(int j=0;j<A[0].size();j++){
            c[i]=c[i]+A[i][j]*b[j];
        }
    }
    
    return c;
}
/*矩阵乘法
矩阵A为m行n列
矩阵B为n行p列
乘积C为m行p列
C(i,k)就是矩阵A的第i行向量乘以矩阵B的第k列的向量
For i =1 to m:
    For k = 1 to p:
        For j=1 to n:
            C(i,k)=C(i,k)+A(i,j)*B(j,k);*/
template<typename T>
vector<vector<T>>VectorAndMultiplication<T>::Matrix_MatrixProduct(vector<vector<T>>A,vector<vector<T>>B){
    vector<vector<T>>C(A.size(),vector<T>(B[0].size(),0));
    for(int i=0;i<A.size();i++){//矩阵A的行数
        for(int k=0;k<B[0].size();k++){//矩阵B的列数
            for(int j=0;j<A[0].size();j++){//矩阵A的列数与矩阵B的行数
                C[i][k]=C[i][k]+A[i][j]*B[j][k];
            }
        }
    }
    return C;
}

int main(){


    vector<int>a={1,3,5,9};
    vector<int>b={2,8,3,6};
    vector<vector<int>>A={{1,2,6,7},{1,6,9,7},{0,6,9,7}};
    //vector<vector<int>>B={{0,8,6,9},{1,6,5,9},{1,9,6,3}};
    vector<vector<int>>B={{1,3,4},{2,6,4},{5,6,7},{1,3,7}};
    VectorAndMultiplication<int>c;

    //c.VectorPrint(c.VectorInnerProduct(a,b));
    //c.VectorPrint(c.VectorPlus(a,b));
    //c.VectorPrint(c.Matrix_VectorProduct(A,b));
    c.MatrixPrint(c.Matrix_MatrixProduct(A,B));



    //VectorAndMultiplication<int>C;
    //C.MatrixPrint(C.MatrixPlus(A,B));

   


    while(getchar()!='\n')
    continue;
    getchar();
    return 0;
}

#endif