#ifndef HEAPCREAT_H
#define HEAPCREAT_H
#include"..//utils//common.hpp"
class HeapMax{
private:
    vector<int>maxHeap;//ʹ�����齨��

    /*��ȡ���ӽڵ�����*/
    int left(int i){
        return i*2+1;
    }
    /*��ȡ���ӽ������*/
    int right(int i){
        return i*2+2;
    }
    /*��ȡ���ڵ�����*/
    int parent(int i){
        return (i-1)/2;//����ȡ��
    }
    /*�ӽڵ�i��ʼ���Ե��򶥶ѻ�*/
    void siftUp(int i){
        while(true){
            //��ȡ���ڵ�����
            int p=parent(i);
            //������Խ�磬���߽�������޸�ʱ���˳�ѭ��
            if(p<0||maxHeap[i]<=maxHeap[p])//���󶥶ѣ�����ӽڵ�ȸ��ڵ�С������Ҫ����
            break;
            //��Ҫ�޸��򽻻���������ֵ
            swap(maxHeap[i],maxHeap[p]);
            //ѭ�����϶ѻ�
            i=p;
        }
    }
    /*��i��ʼ���Զ����¶ѻ�*/
    void siftDown(int i){
        while(true){
            //�жϽڵ�l,r,i��Ϊln;
            int l=left(i),r=right(i),ln=i;
            //���ڵ�i��󣬻���l��rԽ��������ѻ�
            if(l<maxHeap.size()&&maxHeap[l]>maxHeap[ln])
                ln=l;
            if(r<maxHeap.size()&&maxHeap[r]>maxHeap[ln])
                ln=r;
            if(ln==i)
                break;
            //�ѻ�
            swap(maxHeap[i],maxHeap[ln]);
            //�Զ�����
            i=ln;
        }
    }
public:
    /*���췽��,�������飬��ʼ�ѻ�*/
    HeapMax(vector<int>nums){
        //������Ԫ�أ�ԭ�ⲻ����ӽ�����
        maxHeap=nums;
        //�ѻ���Ҷ�ڵ��������������Ԫ��
        for(int i=parent(maxHeap.size()-1);i>=0;i--){
            siftDown(i);
        }
    }
    /*��ȡ�Ѵ�С*/
    int size(){return maxHeap.size();};
    /*�ж϶��Ƿ�Ϊ��*/
    bool empty(){return size()==0;};
    /*���ʶѶ�Ԫ��*/
    int peek(){return maxHeap[0];};
    /*Ԫ�����*/
    void push(int val){
        //��ӽڵ㵽��
        maxHeap.push_back(val);
        //�ӵ������ѻ�
        siftUp(size()-1);
    }
    /*Ԫ�س���*/
    void pop(){
        //�նѴ���
        if(empty())
            throw out_of_range("��Ϊ��");
        //�����Ѷ���ѵ�Ԫ��
        swap(maxHeap[0],maxHeap[size()-1]);
        //ɾ����Ԫ��
        maxHeap.pop_back();
        //�Ӷ����׶ѻ�
        siftDown(0);
    }
    /*��ӡ�ѣ���������*/
    void print(){
        cout<<"�ѵ������ʾ: ";
        printVector(maxHeap);
        /*
        cout<<"�ѵĶ�������ʾ: "<<endl;
        TreeNode*root=vecToTree(maxHeap);
        printTree(root);
        freeMemoryTree(root);
        */
    }
};





#endif