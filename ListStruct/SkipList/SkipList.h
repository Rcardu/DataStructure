#ifndef SKIPLIST_H
#define SKIPLIST_H
#include"../utils/common.hpp"
#include<random>
using namespace std;
template<typename T>
class SkipListNode{
public:
//�������ݽṹ���������������ݡ��Լ��ȼ�ָ�루�����洢��ǰ���������в��ϵ���һ����㣩
    int key;
    T data;
    vector<SkipListNode*>next;
//�������췽������ȷ����ʼֵ
    SkipListNode(int key,T data,int maxLevel):key(key),data(data){
        for(int i=0;i<maxLevel;i++){
            next.push_back(nullptr);
        }
    }

};
template <typename T>
class SkipList{
public:
    SkipListNode<T>*head;//ͷ���
    int maxLevel;//�б�������
    //���͵����ֵ����Сֵ
    const int minInt=numeric_limits<int>::min();
    const int maxInt=numeric_limits<int>::max();
    
    
public:
    //���캯��
    SkipList(int maxLevel,T iniValue);
    //��������
    ~SkipList();
    //�����������
    int randomLevel();
    //���롢���ҡ�ɾ��
    SkipListNode<T>*insert(int k,T val);
    SkipListNode<T>*find(int k);
    SkipListNode<T>*deleteNode(int k);

    //��ӡ
    void printNode();

private:
    SkipListNode<T>*tail;//β���

    //�ҵ���ǰ�б����node��������
    int nodeLevel(vector<SkipListNode<T>*> next);
};
/*���캯����Ĭ�ϵ����������Լ���ʼ������ֵ*/
template<typename T>
SkipList<T>::SkipList(int maxLevel,T iniVale):maxLevel(maxLevel){
    //��ʼ��ͷ�����β����������ֵ���Լ�������
    head=new SkipListNode<T>(minInt,iniVale,maxLevel);
    tail=new SkipListNode<T>(maxInt,iniVale,maxLevel);

    //�����в����ϵ�ͷ���ָ��β���
    for(int i=0;i<maxLevel;i++){
        head->next[i]=tail;
    }
}
/*��������*/
template<typename T>
SkipList<T>::~SkipList(){
    delete head;
    delete tail;
}
/*�������������ʹ��time��Ϊ��������ȡ0~1֮������ֵ��ֱ��levelΪ0���߳���������*/
template<typename T>
int SkipList<T>::randomLevel(){
    int random_level=1;
    int seed=time(NULL);
    static default_random_engine e(seed);
    static uniform_int_distribution<int> u(0,1);

    while(u(e)&&random_level<maxLevel){
        random_level++;
    }
    return  random_level;
}
/*����
�Ȳ��Ҳ��жϸýڵ��Ƿ��Ѿ����ڣ�����������¸ý���ֵ
��ȡ�½����������
�ҵ����ʵĲ���λ��
���벢����ÿ��ǰ��node��ָ��*/
template<typename T>
SkipListNode<T>* SkipList<T>::insert(int k,T val){
    int x_level=randomLevel();
    SkipListNode<T>*newNode=nullptr;
    SkipListNode<T>*temp=head;

    newNode=find(k);
    if(newNode){
        newNode->data=val;
        cout<<"\n������"<<k<<" ������Ϊ��"<<val<<endl;
        return head;
    }
    cout<<"\n������: "<<k<<" �Ĳ���Ϊ��"<<x_level<<endl;
    newNode=new SkipListNode<T>(k,val,x_level);
    //����߲㿪ʼ����
    for(int i=(x_level-1);i>-1;i--){
        //��ͷ��㿪ʼ����Ѱ��Ŀ����
        while(temp->next[i]!=nullptr&&temp->next[i]->key<k){
            temp=temp->next[i];
        }
        newNode->next[i]=temp->next[i];
        temp->next[i]=newNode;
    }
    return head;
}
/*����
�����б����������ҵ�С�ڸýڵ㸽���Ľ�㣬�����һ��������Ŀ���㣬�򷵻ظýڵ�*/
template<typename T>
SkipListNode<T>* SkipList<T>::find(int k){
    //�ҵ���ǰ���������������������ʼ���²���
    SkipListNode<T>*temp=head;
    int curLevel=nodeLevel(temp->next);

    for(int i=(curLevel-1);i<-1;i--){
        while(temp->next[i]!=nullptr&&temp->next[i]->key<k){
            temp=temp->next[i];
        }
    }
    temp=temp->next[0];
    if(temp->key==k)return temp;
    else return nullptr;
}
/*ɾ��
���Ҹýڵ��Ƿ���ڣ���������ڷ��ص�ǰ���list������֪
�ҵ�С�ڸý������Ľ��
����ÿ��ǰ��Ľ���ָ��*/
template<typename T>
SkipListNode<T>* SkipList<T>::deleteNode(int k){
    SkipListNode<T>*node=find(k);
    if(!node){
        cout<<"\n�ýڵ㲻����"<<endl;
        return head;
    }else{
        SkipListNode<T>*temp=head;
        //��ȡ��ǰ���ָ���С
        int xLevel=node->next.size();
        //��ȡ��ǰ���ÿһ���ǰһ�����
        for(int i=(xLevel-1);i<-1;i--){
            while(temp->next[i]!=nullptr&&temp->next[i]->key<k){
                temp=temp->next[i];
            }
            temp->next[i]=temp->next[i]->next[i];
        }
        return head;
    }
}
/*��ӡ*/
template<typename T>
void SkipList<T>::printNode(){
    for(int i=0;i<maxLevel;i++){
        SkipListNode<T>*temp=head;
        int lineLen=1;

        if(temp->next[i]->key!=maxInt){
            cout<<"\n";
            cout<<"��"<<i<<"��"<<endl;
        }
        while(temp->next[i]!=nullptr&&temp->next[i]->key!=maxInt){
            cout<<"("<<temp->next[i]->key<<" , "<<temp->next[i]->data<<")";
            temp=temp->next[i];
            if(temp->next[i]!=nullptr&&temp->next[i]->key!=maxInt){
                cout<<" -> ";
            }
        }
        cout<<endl;
    }
}
/*���ص�ǰnode����������СֵΪ1*/
template<typename T>
int SkipList<T>::nodeLevel(vector<SkipListNode<T>*>next){
    int nodelevel=0;
    if(next[0]->key==maxInt){
        return nodelevel;
    }
    for(int i=0;i<next.size();i++){
        if(next[i]!=nullptr&&next[i]->key!=maxInt){
            nodelevel++;
        }else{
            break;
        }
    }
    return nodelevel;
}





#endif