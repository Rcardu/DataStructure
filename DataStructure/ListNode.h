#ifdef LISTNODE_H
#define LISTNODE_H
#include<iostream>
#endif
#define INIT_SIZE 100
#define INCTEMENT 20
using namespace std;

template<typename T>
class ListNodeSq{
private:
    /*顺序表的定义*/
    T *elem;//存储地址
    int size;//当前顺序表的容量
    int length;//当前顺序表的长度
public:
    ListNodeSq()=default;//默认构造函数
    bool Init_ListNodeSq();//初始化顺序表
    int GetSize();//获取顺序表的存储容量
    int Getlen();//获取顺序表的长度
    void Clear();//重置顺序表
    bool Empty();//判断表是否为空
    bool index(int idx,T&elem);//用于获取相应元素下标
    int index(T elem,bool(*compare)(T,T));//用于获取第一个相似元素的位置
    void traverse(void(*print)(T&elem));//用于打印顺序表中的元素
    bool insert(T elem);//用于在顺序表的最后添加元素
    bool insert(int idx,T elem);//用于在顺序表指定的位置添加元素
    bool remove(T&elem);//用于删除顺序表的最后一个元素
    bool remove(int idx,T&elem);//用于在顺序表的指定位置删除元素
    T operator[](int idx);// 重载下标运算符
    ~ListNodeSq();//重写顺序表的析构函数
};
/*初始化顺序表
分配内存空间
判断是否分配成功
分配大小
当前长度*/
template<typename T>
bool ListNodeSq<T>::Init_ListNodeSq(){
    this->elem=(T*)malloc(INIT_SIZE*sizeof(T));//分配内存空间
    if(!this->elem){
        cerr<<"Init Wrong!"<<endl;//分配失败
        return false;
    }
    this->size=INIT_SIZE;
    this->length=0;
    return true;
}
/*获得当前顺序表大小
返回当前size*/
template<typename T>
inline int ListNodeSq<T>::GetSize(){
    return this->size;
}
/*获得当前顺序表长度
返回当前length*/
template<typename T>
inline int ListNodeSq<T>::Getlen(){
    return this->length;
}
/*重置当前顺序表
长度设置为0*/
template<typename T>
inline void ListNodeSq<T>::Clear(){
    this->length=0;
}
/*判断当前顺序表是否为空*/
template<typename T>
inline bool ListNodeSq<T>::Empty(){
    if(this->length==0){
        return true;
    }
}
/*获取下标元素
返回当前下标元素*/
template<typename T>
bool ListNodeSq<T>::index(int idx,T&elem){
    if(idx<1||idx>this->length){
        return false;
    }
    elem=this->elem[idx-1];
    return true;
}
/*返回与输入元素相同的元素的下标，否则返回-1*/
template<typename T>
int ListNodeSq<T>::index(T elem,bool(*compare)(T,T)){
    for(int i=0;i!=this->length;i++){
        if(compare(elem,(this->elem)[i])){
            return i;
        }
    }
    return -1;
}
/*打印当前顺序表*/
template<typename T>
void ListNodeSq<T>::traverse(void(*print)(T&elem)){
    for(int i=0;i!=this->length;i++){
        print((this->elem)[i]);
    }
    cout<<endl;
}
/*在顺序表的后面插入元素*/
template<typename T>
bool ListNodeSq<T>::insert(T elem){
    if(this->length==this->size){//顺序表满了
        T*newelem=(T*)realloc(this->elem,(this->size+INCTEMENT)*sizeof(T));//将顺序表空间增大
        if(!newelem){//判断是否增大
            cerr<<"Error allocation memory!"<<endl;
            return false;
        }
        this->size+=INCTEMENT;//大小增大
        this->elem=newelem;//将新生成的顺序表加到原顺序表后面
    }
    (this->elem)[this->length]=elem;//将元素插入到顺序表后面
    this->length+=1;
    return true;
}
/*在指定位置插入元素*/
template<typename T>
bool ListNodeSq<T>::insert(int idx,T elem){
    if(idx<1||idx>this->size){//下标不合法
        return false;
    }
    if(this->length==this->size){//顺序表满了
        T*newelem=(T*)realloc(this->elem,(this->size+INCTEMENT)*sizeof(T));
        if(!newelem){
            cerr<<"Error allocating memory!"<<endl;
            return false;
        }
        this->size+=INCTEMENT;
        this->elem=newelem;
    }
    for(int i=this->length;i>=idx;i--){//将指定位置(idx)元素依次后移
        (this->elem)[i]=(this->elem)[i-1];
    }
    (this->elem)[idx-1]=elem;//插入元素
    this->length+=1;
    return true;
}
/*删除顺序表最后一个元素*/
template<typename T>
bool ListNodeSq<T>::remove(T&elem){
    if(this->length==0){
        return false;
    }
    elem=(this->elem)[--this->length];
    return true;
}
/*删除顺序表指定位置的元素*/
template<typename T>
bool ListNodeSq<T>::remove(int idx,T&elem){
    if(this->length==0){
        return false;
    }
    if(idx<1||idx>this->length){
        return false;
    }
    elem=(this->elem)[idx-1];
    for(int i=idx-1;i<this->length;i++){//将元素依次前移
        (this->elem)[i]=(this->elem)[i+1];
    }
    this->length--;
    return true;
}
/*重载 [] 运算符*/
template<typename T>
T ListNodeSq<T>::operator[](int idx){
    if(idx<1||idx>this->length){
        cerr<<"subscript worong!"<<endl;
    }
    return this->elem[idx-1];//[]接收到int类型的数据时，返回当前顺序表idx-1位置的数据
}
/*重载析构函数，删除顺序表，释放内存，大小长度重置为0*/
template<typename T>
ListNodeSq<T>::~ListNodeSq(){
    free(this->elem);
    this->elem=nullptr;
    this->size=0;
    this->length=0;
}
/*用来实现非成员函数的定义
打印函数*/
template<typename T>
void print(T&elem){
    cout<<elem<<" ";
}
/*判断两个相同类型的数据是否相同*/
template<typename T>
bool compare(T t1,T t2){
    /*T代表任意类型*/
    if(t1==t2){
        return true;
    }
    return false;
}
