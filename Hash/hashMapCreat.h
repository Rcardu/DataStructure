#ifndef HASHMAPCREAT_H
#define HASHMAPCREAT_H
#include"../utils/common.hpp"

struct Entry
{
    int key;
    string val;
    Entry(int key,string val){
        this->key=key;
        this->val=val;
    }
};


class ArrayHashMap{
private:
    vector<Entry*>buckets;
public:
    ArrayHashMap(){
        //��ʼ�����飬����100��Ͱ
        buckets=vector<Entry*>(100);
    }
    ~ArrayHashMap(){
        //�ͷ��ڴ�
        for(const auto&bucket:buckets){
            delete bucket;
        }
        buckets.clear();
    }
    /*��ϣ����*/
    int hashFunc(int key){
        int index=key%100;
        return index;
    }
    /*��ѯ����*/
    string get(int key){
        int index=hashFunc(key);
        Entry*pair=buckets[index];
        if(pair==nullptr)
            return nullptr;
        return pair->val;
    }
    /*��Ӳ���*/
    void put(int key,string val){
        Entry*pair=new Entry(key,val);
        int index=hashFunc(key);
        buckets[index]=pair;
    }
    /*ɾ������*/
    void remove(int key){
        int index=hashFunc(key);
        //�ͷ��ڴ沢��Ϊnullptr
        delete buckets[index];
        buckets[index]=nullptr;
    }
    /*��ȡ���м�ֵ��*/
    vector<Entry*>entrySet(){
        vector<Entry*>entry;
        for(Entry*pair:buckets){
            if(pair!=nullptr)
                entry.push_back(pair);
        }
        return entry;
    }
    /*��ȡ���м�*/
    vector<int> keySet(){
        vector<int> keySet;
        for(Entry*pair:buckets){
            if(pair!=nullptr)
                keySet.push_back(pair->key);
        }
        return keySet;
    }
    /*��ȡ����ֵ*/
    vector<string>ValSet(){
        vector<string>ValSet;
        for(Entry*pair:buckets){
            if(pair!=nullptr)
                ValSet.push_back(pair->val);
        }
        return ValSet;
    }
    /*��ӡ��ϣ��*/
    void print(){
        for(Entry*kv:entrySet()){//����������м�ֵ��
            cout<<kv->key<<" -> "<<kv->val<<endl;
        }
    }
};

#endif