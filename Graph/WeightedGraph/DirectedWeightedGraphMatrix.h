/*����ͼ��Ȩͼ���ڽӾ���*/
#ifndef DIRECTEDWEIGHTEDGRAPHMATRIX_H
#define DIRECTEDWEIGHTEDGRAPHMATRIX_H
#include"../../utils/common.hpp"
template<typename T>
class DriectedWeightedGraphMatrix{
/*��������*/
private:
    vector<int>Adjacency;//�����б�
    vector<vector<int>>Matrix;//�ڽӾ���
private:
    /*ͼ�Ĺ�����ȱ���*/
    /*
  [0, 1, 0, 2, 0],
  [0, 0, 3, 0, 0],
  [0, 0, 0, 1, 5],
  [2, 0, 0, 0, 1],
  [0, 0, 1, 0, 0]
    */
    /*����ʼ���㿪ʼ��ʹ�����������б���
    ��������Ӧ�Ķ���ֵ����������
    ����������в��ҽ����ϣ��
    ʹ������������ÿ����������Ӧ��������
    ���������е�ֵ�����ж�����Ϊ0ʱû�е����ϵ�����ߵ������еĵ����ϵ����
    ���������Ѿ��ڹ�ϣ���г��֣�˵������������Ӧ��ֵ�ѱ�����*/
    vector<int>MatrixBFS(DriectedWeightedGraphMatrix&graph,int index){
        //��ϣ����¼�ѱ�����������
        unordered_set<int>visits={index};
        //����ģ��������
        queue<int>que;
        //�����
        vector<int>res;
        //����һ���������
        que.push(index);
        while(!que.empty()){//����Ϊ��ʱ��ʾ��������
            index=que.front();//ȡ������������һ�������Ķ���
            que.pop();
            res.push_back(graph.Adjacency[index]);//�������������
            //ʹ��һ��������ȡ��ǰ�������ڽӾ����е�һ��
            vector<int>ThisNum(graph.Matrix[index].begin(),graph.Matrix[index].end());
            int i=0;//ʹ��������������һ��
            for(int Adj:ThisNum){//������������
                if(Adj==0||visits.count(i)){//��ǰ�����Ϊ0û�е����ϵ����ǰ�����������Ѵ���
                    i++;
                    continue;
                }
                que.push(i);//δ���������������
                visits.emplace(i);//�����ϣ��
                i++;
            }
        }
        return res;
    }
    /*����ͼ��������ȱ���*/
    /*ʹ�õݹ飬�����ݹ���󡢹�ϣ���ݹ������������*/
    void MatrixDFS(DriectedWeightedGraphMatrix&graph,unordered_set<int>&visits,int index,vector<int>&res){
        res.push_back(graph.Adjacency[index]);
        visits.emplace(index);
        for(int i=0;i<graph.Matrix[index].size();i++){
            if(graph.Adjacency[i]==0||visits.count(i))
            continue;
            MatrixDFS(graph,visits,i,res);
        }
    }
public:
    /*���췽��*/
    DriectedWeightedGraphMatrix(const vector<int>&Adj,const vector<vector<int>>&Mat){
        //��Ӷ���
        for(int val:Adj){
           addVertexMat(val);
        }
        //��ӱ�
        for(const vector<int>&edge:Mat){
            addEdgeMat(edge[0],edge[1],edge[2]);
        }
    }
    /*��ȡ��������*/
    int size(){return Adjacency.size();};
    /*��Ӷ���*/
    void addVertexMat(int val){
        int n=size();//�˶��������
        //�򶥵��б�������µĶ����ֵ
        Adjacency.push_back(val);
        //�����
        Matrix.emplace_back(n,0);
        //�����
        for(vector<int>&Mat:Matrix){
            Mat.push_back(0);
        }
    }
    /*��ӱ�*/
    /*Ҫ��ӵıߵ�����,�Լ�Ȩֵ*/
    void addEdgeMat(int i,int j,int vals){
        //����Խ������ȴ���
        if(i<0||j<0||i>=size()||j>=size()||i==j){
            throw out_of_range("���㲻����");
        }
        //����ͼ��ֻ���һ�����Լ�Ȩֵ
        Matrix[i][j]=vals;
    }
    /*ɾ������*/
    void removeVertexMat(int index){
        if((index>=size())){
            throw out_of_range("���㲻����");
        }
        //�ڶ����б����Ƴ��˶���
        Adjacency.erase(Adjacency.begin()+index);
        //�پ�����ɾ������
        Matrix.erase(Matrix.begin()+index);
        //�ھ�����ɾ����һ��
        for(auto&Mat:Matrix){
            Mat.erase(Mat.begin()+index);
        }
    }
    /*ɾ����*/
    /*�ߵ���������*/
    void removeEdgeMat(int i,int j){
        if(i<0||j<0||i>=size()||j>=size()||i=j){
            throw out_of_range("��������");
        }
        Matrix[i][j]=0;
    }
    /*��ӡ�ڽ�����*/
    void print(){
        cout<<" �����б� = ";
        printVector(Adjacency);
        cout<<" �ڽӾ��� = ";
        printVectorMatrix(Matrix);
    }
    /*������ȱ���*/
    vector<int>GraphBFSMat(DriectedWeightedGraphMatrix&graph,int start){
        return MatrixBFS(graph,start);
    }
    /*������ȱ���*/
    vector<int>GraphDFSMat(DriectedWeightedGraphMatrix&graph,int index){
        vector<int>res;
        unordered_set<int>visits;
        MatrixDFS(graph,visits,index,res);
        return res;
    }
};





#endif