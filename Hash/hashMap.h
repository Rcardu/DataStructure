#ifndef HASHMAP_H
#define HASHMAP_H
#include"../utils/common.hpp"
#include"hashMapCreat.h"
void usHash(){
    /*初始化哈希表*/
    unordered_map<int,string>map;
    /*添加元素*/
    map[12836]="小哈";
    map[15937]="小罗";
    map[16750]="小算";
    map[13276]="小法";
    map[10583]="小鸭";
    cout<<"\n添加完成后哈希表为:   \nKey->Value"<<endl;
    printHashMap(map);

    /*查询操作*/
    /*向哈希表中输入键值，查询姓名 */
    string name=map[15937];
    cout<<name;

    /* 删除操作 */
    // 在哈希表中删除键值对 (key, value)
    map.erase(10583);
    cout << "\n删除 10583 后，哈希表为\nKey -> Value" << endl;
    printHashMap(map);

    /*遍历哈希表*/
    cout<<"\n遍历键值对 Key->Value"<<endl;
    for(auto kv:map){
        cout<<kv.first<<" -> "<<kv.second<<endl;
    }

    cout << "\n单独遍历键 Key" << endl;
    for (auto key : map) {
        cout << key.first << endl;
    }

    cout << "\n单独遍历值 Value" << endl;
    for (auto val : map) {
        cout << val.second << endl;
    }

}

void hashMapUs(){
    /* 初始化哈希表 */
    ArrayHashMap map = ArrayHashMap();

    /* 添加操作 */
    // 在哈希表中添加键值对 (key, value)
    map.put(12836, "小哈");
    map.put(15937, "小啰");
    map.put(16750, "小算");
    map.put(13276, "小法");
    map.put(10583, "小鸭");
    cout << "\n添加完成后，哈希表为\nKey -> Value" << endl;
    map.print();

    /* 查询操作 */
    // 向哈希表输入键 key ，得到值 value
    string name = map.get(15937);
    cout << "\n输入学号 15937 ，查询到姓名 " << name << endl;

    /* 删除操作 */
    // 在哈希表中删除键值对 (key, value)
    map.remove(10583);
    cout << "\n删除 10583 后，哈希表为\nKey -> Value" << endl;
    map.print();

    /* 遍历哈希表 */
    cout << "\n遍历键值对 Key->Value" << endl;
    for (auto kv : map.entrySet()) {
        cout << kv->key << " -> " << kv->val << endl;
    }

    cout << "\n单独遍历键 Key" << endl;
    for (auto key : map.keySet()) {
        cout << key << endl;
    }

    cout << "\n单独遍历值 Value" << endl;
    for (auto val : map.ValSet()) {
        cout << val << endl;
    }
}



#endif