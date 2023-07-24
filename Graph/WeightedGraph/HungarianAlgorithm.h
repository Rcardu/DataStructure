#ifndef HUNGARIANALGORITHM_H
#define HUNGARIANALGORITHM_H
#include "../../utils/common.hpp"
enum Bool{Zero=0,One=1,Two=2};
class HunGarianAlgorithm{
private:
public:
    /*匈牙利算法,使用二维数组来表示这两个点之间的邻接矩阵*/
    void HunGarian(vector<vector<int>>&Martex){
        vector<vector<pair<int,Bool>>>Martexs(Martex.size(),vector<pair<int,Bool>>(Martex[0].size(),pair<int,Bool>(0,Two)));//给每个元素设置标记位，用来判断0元素画线问题
        for(int i=0;i<Martex.size();i++){
            for(int j=0;j<Martex[i].size();j++){
                Martexs[i][j].first=Martex[i][j];
                Martexs[i][j].second=Two;
            }
        }
        /*修改矩阵*/
        SetMartex(Martexs);
        while(1){
            /*画线*/
            vector<vector<bool>>LineBool(2,vector<bool>(Martex[0].size(),0));
            int lineNum=TheLine(Martexs,LineBool);
            /*判断是否继续*/
            if(lineNum>=Martexs[0].size())break;
            /*寻找矩阵中的所有非零元素的最小值，并将所有非零元素减去最小值*/
            FindNoZero(Martexs,LineBool);
            /*清空画线情况*/
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
    /*画线函数*/
    int TheLine(vector<vector<pair<int,Bool>>>&Martexs,vector<vector<bool>>&LineBool){
        //画线计数
        int n=0;
        while(1){
            pair<int,int>Row=RowForZero(Martexs);
            pair<int,int>Col=ColForZero(Martexs);
            //如果行与列中的0元素计数都为0，就退出
            if(Row.first==0&&Col.first==0)break;
            if(Row.first>=Col.first){
                for(int j=0;j<Martexs[0].size();j++){
                    //将元素标记为1，表示已画线
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
    /*查询列中的零元素*/
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
    /*查询行中的零元素*/
    pair<int,int> RowForZero(vector<vector<pair<int,Bool>>>&Martexs){
        vector<int>RowZeroNum(Martexs.size(),0);
        pair<int,int>MaxZero(INT_MIN,0);
        for(int i=0;i<Martexs.size();i++){
            for(int j=0;j<Martexs[i].size();j++){
                /*当前元素位0元素且没有被线覆盖，行中零元素个数加1*/
                if(Martexs[i][j].first==0&&Martexs[i][j].second==Zero)RowZeroNum[i]++;
            }
            MaxZero.first=max(RowZeroNum[i],MaxZero.first);
            MaxZero.second=MaxZero.first>RowZeroNum[i]?MaxZero.second:i;
        }
        return MaxZero;
    }
    /*修改矩阵*/
    int SetMartex(vector<vector<pair<int,Bool>>>&Martexs){ 
        //修改行
        for(vector<pair<int,Bool>>&Row:Martexs){
            int Min=FindMin(Row);
            SetRowValue(Row,Min);
        }
        vector<pair<int,Bool>>colummn;
        //修改列
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
        int n=0;//用来表示矩阵中0元素的个数
        for(vector<pair<int,Bool>>line:Martexs){
            for(pair<int,Bool> li:line){
                if(li.first==0)n++;
            }
        }
        return n;
    }
    /*寻找最小值*/
    int FindMin(vector<pair<int,Bool>>MinRow){
        int Min=INT_MAX;
        for(pair<int,int>i:MinRow){
            Min=min(i.first,Min);
        }
        return Min;
    }
    /*修改行数据*/
    void SetRowValue(vector<pair<int,Bool>>&Row,int Min){
        for(pair<int,Bool>&i:Row){
            i.first-=Min;
            if(i.first==0)i.second=Zero;
        }
    }
    /*寻找没有被画线的元素，并改变矩阵*/
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
    /*情空画线情况*/
    void LineClear(vector<vector<pair<int,Bool>>>&Martexs){
        for(auto&Mar:Martexs){
            for(auto&M:Mar){
                if(M.first==0)M.second=Zero;
                else M.second=Two;

            }
        }
    }
        /*查询列中的零元素*/
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
    /*查询行中的零元素*/
    pair<int,int> RowForZeroMin(vector<vector<pair<int,Bool>>>&Martexs){
        vector<int>RowZeroNum(Martexs.size(),0);
        pair<int,int>MaxZero(INT_MAX,0);
        for(int i=0;i<Martexs.size();i++){
            for(int j=0;j<Martexs[i].size();j++){
                /*当前元素位0元素且没有被线覆盖，行中零元素个数加1*/
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