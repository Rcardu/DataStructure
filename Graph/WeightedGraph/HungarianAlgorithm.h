#ifndef HUNGARIANALGORITHM_H
#define HUNGARIANALGORITHM_H
#include "../../utils/common.hpp"
enum Bool{Zero=0,One=1,Two=2};
class HunGarianAlgorithm{
private:
public:
    /*�������㷨,ʹ�ö�ά��������ʾ��������֮����ڽӾ���*/
    void HunGarian(vector<vector<int>>&Martex){
        vector<vector<pair<int,Bool>>>Martexs(Martex.size(),vector<pair<int,Bool>>(Martex[0].size(),pair<int,Bool>(0,Two)));//��ÿ��Ԫ�����ñ��λ�������ж�0Ԫ�ػ�������
        for(int i=0;i<Martex.size();i++){
            for(int j=0;j<Martex[i].size();j++){
                Martexs[i][j].first=Martex[i][j];
                Martexs[i][j].second=Two;
            }
        }
        /*�޸ľ���*/
        SetMartex(Martexs);
        while(1){
            /*����*/
            vector<vector<bool>>LineBool(2,vector<bool>(Martex[0].size(),0));
            int lineNum=TheLine(Martexs,LineBool);
            /*�ж��Ƿ����*/
            if(lineNum>=Martexs[0].size())break;
            /*Ѱ�Ҿ����е����з���Ԫ�ص���Сֵ���������з���Ԫ�ؼ�ȥ��Сֵ*/
            FindNoZero(Martexs,LineBool);
            /*��ջ������*/
            LineClear(Martexs);
        }
        vector<pair<int,int>>res;
        while(1){
            pair<int,int>Row=RowForZeroMin(Martexs);
            pair<int,int>Col=ColForZeroMin(Martexs);
            if(Row.first==INT_MAX)break;
            if(Row.first<=Col.first){
                int index=0;
                for(int i=0;i<Martexs[0].size();i++){
                    if(Martexs[Row.second][i].first==0&&Martexs[Row.second][i].second!=Zero)index=i;
                }
                pair<int,int>temp;
                temp.first=Row.second+1;
                temp.second=index+1;
                res.push_back(temp);
                for(int i=0;i<Martexs[0].size();i++){
                    Martexs[Row.second][i].second=Zero;
                    Martexs[i][index].second=Zero;
                }
                
            }else{
                int index=0;
                for(int i=0;i<Martexs[0].size();i++){
                    if(Martexs[i][Col.second].first==0&&Martexs[i][Col.second].second!=Zero)index=i;
                }
                pair<int,int>temp;
                temp.first=index+1;
                temp.second=Col.second+1;
                res.push_back(temp);
                for(int i=0;i<Martexs[0].size();i++){
                    Martexs[i][Col.second].second=Zero;
                    Martexs[index][i].second=Zero;
                }
            }
        }
        print(res);
    }
    /*���ߺ���*/
    int TheLine(vector<vector<pair<int,Bool>>>&Martexs,vector<vector<bool>>&LineBool){
        //���߼���
        int n=0;
        while(1){
            pair<int,int>Row=RowForZero(Martexs);
            pair<int,int>Col=ColForZero(Martexs);
            //����������е�0Ԫ�ؼ�����Ϊ0�����˳�
            if(Row.first==0&&Col.first==0)break;
            if(Row.first>=Col.first){
                for(int j=0;j<Martexs[0].size();j++){
                    //��Ԫ�ر��Ϊ1����ʾ�ѻ���
                    Martexs[Row.second][j].second=One;
                }
                LineBool[0][Row.second]=1;
                n++;
            }else{
                for(int i=0;i<Martexs[0].size();i++){
                    Martexs[i][Col.second].second=One;
                }
                LineBool[1][Col.second]=1;
                n++;
            }
        }
        return n;
    }
    /*��ѯ���е���Ԫ��*/
    pair<int,int> ColForZero(vector<vector<pair<int,Bool>>>&Martexs){
        vector<int>ColZeroNumm(Martexs.size(),0);
        pair<int,int>MaxZero(INT_MIN,0);
        for(int i=0;i<Martexs.size();i++){
            for(int j=0;j<Martexs[i].size();j++){
                if(Martexs[j][i].first==0&&Martexs[j][i].second==Zero)ColZeroNumm[i]++;
            }
            MaxZero.first=max(MaxZero.first,ColZeroNumm[i]);
            MaxZero.second=MaxZero.first>ColZeroNumm[i]?MaxZero.second:i;
        }
        return MaxZero;
    }
    /*��ѯ���е���Ԫ��*/
    pair<int,int> RowForZero(vector<vector<pair<int,Bool>>>&Martexs){
        vector<int>RowZeroNum(Martexs.size(),0);
        pair<int,int>MaxZero(INT_MIN,0);
        for(int i=0;i<Martexs.size();i++){
            for(int j=0;j<Martexs[i].size();j++){
                /*��ǰԪ��λ0Ԫ����û�б��߸��ǣ�������Ԫ�ظ�����1*/
                if(Martexs[i][j].first==0&&Martexs[i][j].second==Zero)RowZeroNum[i]++;
            }
            MaxZero.first=max(RowZeroNum[i],MaxZero.first);
            MaxZero.second=MaxZero.first>RowZeroNum[i]?MaxZero.second:i;
        }
        return MaxZero;
    }
    /*�޸ľ���*/
    int SetMartex(vector<vector<pair<int,Bool>>>&Martexs){ 
        //�޸���
        for(vector<pair<int,Bool>>&Row:Martexs){
            int Min=FindMin(Row);
            SetRowValue(Row,Min);
        }
        vector<pair<int,Bool>>colummn;
        //�޸���
        for(int i=0;i<Martexs.size();i++){
            for(int j=0;j<Martexs[i].size();j++){
                 colummn.push_back(Martexs[j][i]);
            }
            int Min=FindMin(colummn);
            for(int j=0;j<Martexs[i].size();j++){
                Martexs[j][i].first-=Min;
                if(Martexs[j][i].first==0)Martexs[j][i].second=Zero;
            }
            colummn.clear();
        }
        int n=0;//������ʾ������0Ԫ�صĸ���
        for(vector<pair<int,Bool>>line:Martexs){
            for(pair<int,Bool> li:line){
                if(li.first==0)n++;
            }
        }
        return n;
    }
    /*Ѱ����Сֵ*/
    int FindMin(vector<pair<int,Bool>>MinRow){
        int Min=INT_MAX;
        for(pair<int,int>i:MinRow){
            Min=min(i.first,Min);
        }
        return Min;
    }
    /*�޸�������*/
    void SetRowValue(vector<pair<int,Bool>>&Row,int Min){
        for(pair<int,Bool>&i:Row){
            i.first-=Min;
            if(i.first==0)i.second=Zero;
        }
    }
    /*Ѱ��û�б����ߵ�Ԫ�أ����ı����*/
    void FindNoZero(vector<vector<pair<int,Bool>>>&Martexs,vector<vector<bool>>&LineBool){
        int Min=INT_MAX;
        for(int i=0;i<Martexs[0].size();i++){
            for(int j=0;j<Martexs[0].size();j++){
                if(Martexs[i][j].second!=Two)continue;
                Min=min(Min,Martexs[i][j].first);
            }
        }
        for(int i=0;i<Martexs[0].size();i++){
            for(int j=0;j<Martexs[0].size();j++){
                if(Martexs[i][j].second!=Two)continue;
                Martexs[i][j].first-=Min;
            }
        }
        for(int i=0;i<LineBool[0].size();i++){
            for(int j=0;j<LineBool[0].size();j++){
                if(LineBool[0][j]==1&&LineBool[1][i]==1)
                Martexs[j][i].first+=Min;
            }
        }
        
    }
    /*��ջ������*/
    void LineClear(vector<vector<pair<int,Bool>>>&Martexs){
        for(auto&Mar:Martexs){
            for(auto&M:Mar){
                if(M.first==0)M.second=Zero;
                else M.second=Two;

            }
        }
    }
        /*��ѯ���е���Ԫ��*/
    pair<int,int> ColForZeroMin(vector<vector<pair<int,Bool>>>&Martexs){
        vector<int>ColZeroNum(Martexs.size(),0);
        pair<int,int>MaxZero(INT_MAX,0);
        for(int i=0;i<Martexs.size();i++){
            for(int j=0;j<Martexs[i].size();j++){
                if(Martexs[j][i].first==0&&Martexs[j][i].second==One)ColZeroNum[i]++;
            }
            if(ColZeroNum[i]==0)continue;
            MaxZero.first=min(MaxZero.first,ColZeroNum[i]);
            MaxZero.second=MaxZero.first<ColZeroNum[i]?MaxZero.second:i;
        }
        return MaxZero;
    }
    /*��ѯ���е���Ԫ��*/
    pair<int,int> RowForZeroMin(vector<vector<pair<int,Bool>>>&Martexs){
        vector<int>RowZeroNum(Martexs.size(),0);
        pair<int,int>MaxZero(INT_MAX,0);
        for(int i=0;i<Martexs.size();i++){
            for(int j=0;j<Martexs[i].size();j++){
                /*��ǰԪ��λ0Ԫ����û�б��߸��ǣ�������Ԫ�ظ�����1*/
                if(Martexs[i][j].first==0&&Martexs[i][j].second==One)RowZeroNum[i]++;
            }
            if(RowZeroNum[i]==0)continue;
            MaxZero.first=min(RowZeroNum[i],MaxZero.first);
            MaxZero.second=MaxZero.first<RowZeroNum[i]?MaxZero.second:i;
        }
        return MaxZero;
    }
    void print(vector<pair<int,int>>&res){
        for(pair<int,int>Re:res){
            cout<<"("<<Re.first<<","<<Re.second<<")   ";
        }
        cout<<endl;
    }
};



#endif