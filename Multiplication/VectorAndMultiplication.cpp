#ifndef VECTORANDMULITIPLICATION_H
#define VECTPRANDMULITIPLICATION_H
#include"../utils/common.hpp"
template<typename T>
class VectorAndMultiplication{
//���������ӷ�
public:
    //�����ӷ�,����������������ͣ������ش�����
    vector<T>VectorPlus(vector<T>a,vector<T>b);
    //����ӷ�
    vector<vector<T>>MatrixPlus(vector<vector<T>>A,vector<vector<T>>B);

//���������˷�
public:
    //�����ĳ˷�
    vector<T>VectorInnerProduct(vector<T>a,vector<T>b);
    //�������Ծ���
    vector<T>Matrix_VectorProduct(vector<vector<T>>A,vector<T>b);
    //����˷�
    vector<vector<T>>Matrix_MatrixProduct(vector<vector<T>>A,vector<vector<T>>B);
public:
    //�����������
    void VectorPrint(vector<T>result){
        using std::cout;
        using std::endl;
        for(int i=0;i<result.size();i++) std::cout<<result[i]<<" ";
        std::cout<<std::endl;
    }
        //�����������
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
/*�����ӷ�O(n)
1.����nά������ӵõ�����c
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
/*����ӷ�O(mn)
���������С����m*n
C����Ĵ�СҲ������m*n
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
/*�����˷�O(n)
Ҳ����a��ת�ó���b
    For i = 1 to n:
        c=c+a(i)*c(i);*/
template<typename T>
vector<T>VectorAndMultiplication<T>::VectorInnerProduct(vector<T>a,vector<T>b){
    vector<T>c(a.size(),0);
    for(int i=0;i<c.size();i++) c[i]=c[i]+a[i]*b[i];

    return c;
}
/*�������Ծ���O(mn)
�����Ĵ�С������ھ��������
�˻�Ϊ����
c(m*1)=A(m*n)*b(n*1)
������c���� m��n�еľ������n��1�е�����
c(i)=A(i,1)*b(1)+...+A(i,j)*b(j);
For i = 1 to m:
    For��j = 1 to n:
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
/*����˷�
����AΪm��n��
����BΪn��p��
�˻�CΪm��p��
C(i,k)���Ǿ���A�ĵ�i���������Ծ���B�ĵ�k�е�����
For i =1 to m:
    For k = 1 to p:
        For j=1 to n:
            C(i,k)=C(i,k)+A(i,j)*B(j,k);*/
template<typename T>
vector<vector<T>>VectorAndMultiplication<T>::Matrix_MatrixProduct(vector<vector<T>>A,vector<vector<T>>B){
    vector<vector<T>>C(A.size(),vector<T>(B[0].size(),0));
    for(int i=0;i<A.size();i++){//����A������
        for(int k=0;k<B[0].size();k++){//����B������
            for(int j=0;j<A[0].size();j++){//����A�����������B������
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