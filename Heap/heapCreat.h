#ifndef HEAPCREAT_H
#define HEAPCREAT_H
#include"..//utils//common.hpp"
class HeapMax{
private:
    vector<int>maxHeap;//使用数组建堆

    /*获取左子节点索引*/
    int left(int i){
        return i*2+1;
    }
    /*获取右子结点索引*/
    int right(int i){
        return i*2+2;
    }
    /*获取父节点索引*/
    int parent(int i){
        return (i-1)/2;//向下取整
    }
    /*从节点i开始，自底向顶堆化*/
    void siftUp(int i){
        while(true){
            //获取父节点索引
            int p=parent(i);
            //若索引越界，或者结点无需修复时，退出循环
            if(p<0||maxHeap[i]<=maxHeap[p])//（大顶堆）如果子节点比父节点小，则不需要处理
            break;
            //需要修复则交换两个结点的值
            swap(maxHeap[i],maxHeap[p]);
            //循环向上堆化
            i=p;
        }
    }
    /*从i开始，自顶向下堆化*/
    void siftDown(int i){
        while(true){
            //判断节点l,r,i记为ln;
            int l=left(i),r=right(i),ln=i;
            //若节点i最大，或者l，r越界则无需堆化
            if(l<maxHeap.size()&&maxHeap[l]>maxHeap[ln])
                ln=l;
            if(r<maxHeap.size()&&maxHeap[r]>maxHeap[ln])
                ln=r;
            if(ln==i)
                break;
            //堆化
            swap(maxHeap[i],maxHeap[ln]);
            //自顶向下
            i=ln;
        }
    }
public:
    /*构造方法,传入数组，开始堆化*/
    HeapMax(vector<int>nums){
        //将数组元素，原封不动添加进堆中
        maxHeap=nums;
        //堆化除叶节点以外的其他所有元素
        for(int i=parent(maxHeap.size()-1);i>=0;i--){
            siftDown(i);
        }
    }
    /*获取堆大小*/
    int size(){return maxHeap.size();};
    /*判断堆是否为空*/
    bool empty(){return size()==0;};
    /*访问堆顶元素*/
    int peek(){return maxHeap[0];};
    /*元素入堆*/
    void push(int val){
        //添加节点到堆
        maxHeap.push_back(val);
        //从底至顶堆化
        siftUp(size()-1);
    }
    /*元素出堆*/
    void pop(){
        //空堆处理
        if(empty())
            throw out_of_range("堆为空");
        //交换堆顶与堆滴元素
        swap(maxHeap[0],maxHeap[size()-1]);
        //删除此元素
        maxHeap.pop_back();
        //从顶至底堆化
        siftDown(0);
    }
    /*打印堆（二叉树）*/
    void print(){
        cout<<"堆的数组表示: ";
        printVector(maxHeap);
        /*
        cout<<"堆的二叉树表示: "<<endl;
        TreeNode*root=vecToTree(maxHeap);
        printTree(root);
        freeMemoryTree(root);
        */
    }
};





#endif