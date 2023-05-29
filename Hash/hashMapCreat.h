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
        //初始化数组，包含100个桶
        buckets=vector<Entry*>(100);
    }
    ~ArrayHashMap(){
        //释放内存
        for(const auto&bucket:buckets){
            delete bucket;
        }
        buckets.clear();
    }
    /*哈希函数*/
    int hashFunc(int key){
        int index=key%100;
        return index;
    }
    /*查询操作*/
    string get(int key){
        int index=hashFunc(key);
        Entry*pair=buckets[index];
        if(pair==nullptr)
            return nullptr;
        return pair->val;
    }
    /*添加操作*/
    void put(int key,string val){
        Entry*pair=new Entry(key,val);
        int index=hashFunc(key);
        buckets[index]=pair;
    }
    /*删除操作*/
    void remove(int key){
        int index=hashFunc(key);
        //释放内存并置为nullptr
        delete buckets[index];
        buckets[index]=nullptr;
    }
    /*获取所有键值对*/
    vector<Entry*>entrySet(){
        vector<Entry*>entry;
        for(Entry*pair:buckets){
            if(pair!=nullptr)
                entry.push_back(pair);
        }
        return entry;
    }
    /*获取所有键*/
    vector<int> keySet(){
        vector<int> keySet;
        for(Entry*pair:buckets){
            if(pair!=nullptr)
                keySet.push_back(pair->key);
        }
        return keySet;
    }
    /*获取所有值*/
    vector<string>ValSet(){
        vector<string>ValSet;
        for(Entry*pair:buckets){
            if(pair!=nullptr)
                ValSet.push_back(pair->val);
        }
        return ValSet;
    }
    /*打印哈希表*/
    void print(){
        for(Entry*kv:entrySet()){//这里遍历所有键值对
            cout<<kv->key<<" -> "<<kv->val<<endl;
        }
    }
};

#endif