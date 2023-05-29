#ifndef HASHMAP_H
#define HASHMAP_H
#include"../utils/common.hpp"
#include"hashMapCreat.h"
void usHash(){
    /*��ʼ����ϣ��*/
    unordered_map<int,string>map;
    /*���Ԫ��*/
    map[12836]="С��";
    map[15937]="С��";
    map[16750]="С��";
    map[13276]="С��";
    map[10583]="СѼ";
    cout<<"\n�����ɺ��ϣ��Ϊ:   \nKey->Value"<<endl;
    printHashMap(map);

    /*��ѯ����*/
    /*���ϣ���������ֵ����ѯ���� */
    string name=map[15937];
    cout<<name;

    /* ɾ������ */
    // �ڹ�ϣ����ɾ����ֵ�� (key, value)
    map.erase(10583);
    cout << "\nɾ�� 10583 �󣬹�ϣ��Ϊ\nKey -> Value" << endl;
    printHashMap(map);

    /*������ϣ��*/
    cout<<"\n������ֵ�� Key->Value"<<endl;
    for(auto kv:map){
        cout<<kv.first<<" -> "<<kv.second<<endl;
    }

    cout << "\n���������� Key" << endl;
    for (auto key : map) {
        cout << key.first << endl;
    }

    cout << "\n��������ֵ Value" << endl;
    for (auto val : map) {
        cout << val.second << endl;
    }

}

void hashMapUs(){
    /* ��ʼ����ϣ�� */
    ArrayHashMap map = ArrayHashMap();

    /* ��Ӳ��� */
    // �ڹ�ϣ������Ӽ�ֵ�� (key, value)
    map.put(12836, "С��");
    map.put(15937, "С��");
    map.put(16750, "С��");
    map.put(13276, "С��");
    map.put(10583, "СѼ");
    cout << "\n�����ɺ󣬹�ϣ��Ϊ\nKey -> Value" << endl;
    map.print();

    /* ��ѯ���� */
    // ���ϣ������� key ���õ�ֵ value
    string name = map.get(15937);
    cout << "\n����ѧ�� 15937 ����ѯ������ " << name << endl;

    /* ɾ������ */
    // �ڹ�ϣ����ɾ����ֵ�� (key, value)
    map.remove(10583);
    cout << "\nɾ�� 10583 �󣬹�ϣ��Ϊ\nKey -> Value" << endl;
    map.print();

    /* ������ϣ�� */
    cout << "\n������ֵ�� Key->Value" << endl;
    for (auto kv : map.entrySet()) {
        cout << kv->key << " -> " << kv->val << endl;
    }

    cout << "\n���������� Key" << endl;
    for (auto key : map.keySet()) {
        cout << key << endl;
    }

    cout << "\n��������ֵ Value" << endl;
    for (auto val : map.ValSet()) {
        cout << val << endl;
    }
}



#endif