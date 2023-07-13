#ifndef SKIPLISTCOPY_H
#define SKIPLISTCOPY_H
#include"../utils/common.hpp"
#include<random>
template<typename T>
class SkipListNodeCopy{
public:
    //�������������ݡ������͵�����ָ��
    int key;
    T data;
    vector<SkipListNodeCopy*>next;
    //���캯�����������������ݡ�ȷ������ָ���С
    SkipListNodeCopy(int keys,T val,int Level):key(keys),data(val){
        for(int i=0;i<Level,i++){
            next.push_back(nullptr);
        }
    }
};
//��Ծ������
template<typename T>
class SkipListCopy{
//�������������붨��
public:
    //����һ����ʼ��ͷָ�룬����Ϊ��С
    SkipListNodeCopy<T>*head;
    //����������
    int maxLevel;
    //ȷ���������С����
    const int minInt=numeric_limits<int>::min();
    const int maxInt=numeric_limits<int>::max();
//���������붨��
public:
    //���캯�������������ʼ����
    //�������Լ���ֵ
    SkipListCopy(int maxLevel,T iniValue);
    //����������ɾ��ͷβ���
    ~SkipListCopy();

    //�����������
    int randomLevel();
    //���롢��ѯ��ɾ��
    SkipListNodeCopy<T>*insert(int keys,T val);
    SkipListNodeCopy<T>*find(int keys);
    SkipListNodeCopy<T>*deleteNode(int keys);
    //��ӡ
    void printNode();
private:
    //����һ��βָ�룬����β���
    SkipListNodeCopy<T>*tail;
    //���ص�ǰnode��������
    int nodeLevel(vector<SkipListNodeCopy<T>*>next){
        int nedelevel=0;
        if(node[0]->key==maxInt){
            return nedelevel;
        }
        for(int i=0;i<next.size();i++){
            if(next[i]!=nullptr&&next[i]->key!=maxInt){
                nedelevel++;
            }else{
                break;
            }
        }
        return nedelevel;
    }

};
/*���캯��
����ͷ�����β���
����ͷ���ָ��β���*/
template<typename T>
SkipListCopy<T>::SkipListCopy(int maxLevel,T iniValue):maxLevel(maxLevel){
    head=new SkipListNodeCopy<T>(minInt,iniValue,maxLevel);
    tail=new SkipListNodeCopy<T>(maxInt,iniValue,maxLevel);

    for(int i=0;i<maxLevel;i++){
        head->next[i]=tail;
    }
}
/*����������ɾ��ͷβ���*/
template<typename T>
SkipListCopy<T>::~SkipListCopy(){
    delete head;
    delete tail;
}
/*�������������ʹ��time��Ϊ��������ȡ0~1֮������ֵ
��ʼ����Ϊ1
���һ������ʹ֮��0~1֮������
Ϊ1���Ҳ���û�г�����������ʹ������1
*/
template<typename T>
int SkipListCopy<T>::randomLevel(){
    int levels=1;
    int seed=time(NULL);
    static default_random_engine e(seed);
    static uniform_int_distribution u(0,1);
    while(u(e)&&levels<maxLevel){
        levels++;
    }
    return levels;
}
/*����
�жϸýڵ��Ƿ���ڣ����������滻�������
���򣬻�ȡ�½ڵ���������
�ҵ����ʵĲ���λ��
���벢����ÿ��ǰ���node��ָ��*/
template<typename T>
SkipListNodeCopy<T>*SkipListCopy<T>::insert(int keys,T val){
    SkipListNodeCopy<T>*newNode=nullptr;
    newNode=find(keys);
    if(newNode){
        newNode->data=val;
        cout<<"�Ѹ��½ڵ�ֵ"<<endl;
        return head;
    }
    SkipListNodeCopy<T>*temp=head;
    int levels=randomLevel();
    //�����ڵ�
    newNode=new SkipListNodeCopy<T>(keys,val,levels);
    //����߲㿪ʼ����
    /*ע��Ͳ�λ��һ�㣬���ԣ���߲�λlevels-1������ֵС��-1ʱ
    ��ײ�Ҳ��������*/
    for(int i=(levels-1);i>-1;i--){
        //��ͷ��ʼѰ��Ŀ��ڵ�
        while(temp->next[i]!=nullptr&&temp->next[i]->key>keys){
            temp=temp->next[i];
        }
        //�ҵ������
        newNode->next[i]=temp->next[i];
        temp->next[i]=newNode;
    }
    return head;
}
/*����
�б������ҵ��ýڵ㸽���Ľڵ㣬�����һ���ڵ����Ŀ��ڵ�
�򷵻ظýڵ㣬���򷵻ؿ�ָ��*/
template<typename T>
SkipListNodeCopy<T>*SkipListCopy<T>::find(int keys){
    SkipListNodeCopy<T>*temp=head;
    //�ҵ���ǰ��Ծ�����������
    int curlevel=nodelevel(temp->next);
    for(int i=(curlevel);i>-1;i--){
        while(temp->next[i]!=nullptr&&temp->next[i]->key<keys){
            temp=temp->next[i];
        }
    }
    //��tempָ����һ���ڵ�
    temp=temp->next[0];
    if(temp->key==keys)return temp;
    else return nullptr;
}
/*ɾ��
�ж��Ƿ���ڣ����������֪
�����ҵ�С�ڸýڵ�����Ľڵ�
����ÿ��ǰ��Ľڵ�*/
template<typename T>
SkipListNodeCopy<T>*SkipListCopy<T>::deleteNode(int keys){
    SkipListNodeCopy<T>*node=find(keys);
    if(node==nullptr){
        cout<<"�ýڵ㲻����"<<endl;
        return head;
    }else{
        SkipListNodeCopy<T>*temp=head;
        int Levels=node->next.size();
        for(int i=(Levels-1);i>-1;i--){
            while(temp->next[i]!=nullptr&&temp->next[i]->key<keys){
                temp=temp->next[i];
            }
            temp->next[i]=temp->next[i]->next[i];
        }
        return head;
    }
}
template<typename T>
void SkipListCopy<T>::printNode(){
    for(int i=0;i<maxLevel;i++){
        SkipListNodeCopy<T>*temp=head;
        int lineLen=1;

        if(temp->next->key!=maxInt){
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




#endif