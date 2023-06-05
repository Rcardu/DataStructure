#ifndef AVGTREE_H
#define AVGTREE_H
#include"../utils/common.hpp"
class AVGTree{
public:
    TreeNode*root;//根节点
private:
    /*更新节点高度*/
    void updateHeight(TreeNode*node){
        //节点高度等于最高子树高度+1;
        node->height=max(height(node->left),height(node->right))+1;
    }
    /*右旋操作*/
    TreeNode*rightRotate(TreeNode*node){
        TreeNode*child=node->left;
        TreeNode*grandchild=child->right;
        //以child为原点将node向右旋转
        child->right=node;//将失衡节点作为左节点的右节点
        node->left=grandchild;//将左节点原来的右节点作为失衡节点的左节点
        //更新节点高度
        updateHeight(node);
        updateHeight(child);
        //返回旋转后子树的根节点
        return child;
    }
    /*左旋操作*/
    TreeNode*leftRotate(TreeNode*node){
        TreeNode*child=node->right;
        TreeNode*grandchild=child->left;
        //以child为原点将node左旋
        child->left=node;//将失衡节点作为右节点的左结点
        node->right=grandchild;//将右结点原来的左节点作为失衡节点的右结点
        //更新节点高度
        updateHeight(node);
        updateHeight(child);
    }
    /*执行旋转操作，使该子树重新恢复平衡*/
    TreeNode*rotate(TreeNode*node){
        //获取node节点的平衡因子
        int _balanceFactor=balanceFactor(node);
        //左偏树(左边子树高度大于右子树)
        if(_balanceFactor>1){
            if(balanceFactor(node->left)>=0){
                //右旋(左边比右边多一个节点导致失衡)
                return rightRotate(node);
            }else{
                //先左旋后右旋(先对左节点左旋)
                node->left=leftRotate(node->left);
                //再对失衡节点右旋
                return rightRotate(node);
            }
        }
        //右偏树
        if(_balanceFactor<-1){
            if(balanceFactor(node->right)<=0){
                //左旋(左节点比右节点少一个)
                return leftRotate(node);
            }else{
                //先右旋，再左旋
                node->right=rightRotate(node->right);
                //再对失衡节点左旋
                return leftRotate(node);
            }
        }
        //平衡树，无需旋转，返回
        return node;
    }
    /*递归插入节点*/
    TreeNode*insertHelper(TreeNode*node,int val){
        if(node==nullptr)
            return new TreeNode(val);
        /*1.查找插入位置，并插入节点*/
        if(val<node->val)
            node->left=insertHelper(node->left,val);
        else if(val>node->val)
            node->right=insertHelper(node->right,val);
        else
            return node;    //重复节点不插入，直接返回
        updateHeight(node);//更新节点高度
        /*2.执行旋转操作，使子树恢复平衡*/
        node=rotate(node);
        //返回子树的根节点
        return node;
    }
    /*删除节点*/
    TreeNode*removeHelper(TreeNode*node,int val){
        if(node==nullptr)
            return nullptr;
        /*1.查找节点，并删除*/
        if(val<node->val)
            node->left=removeHelper(node->left,val);
        else if(val>node->val)
            node->right=removeHelper(node->right,val);
        else{
            if(node->left==nullptr||node->right==nullptr){
                TreeNode*child=node->left!=nullptr?node->left:node->right;
                //子节点数量为0，直接删除node并返回
                if(child==nullptr){
                    delete node;
                    return nullptr;
                }else{//子节点数量为1，直接删除node
                    delete node;
                    node=child;
                }
            }else{
                //子节点数量为2，则将中序遍历的下个节点删除，并用该节点替换当前节点
                TreeNode*temp=node->right;
                while(temp->left!=nullptr){
                    temp=temp->left;
                }
                int tempVal=temp->val;
                node->right=removeHelper(node->right,temp->val);
                node->val=tempVal;
            }
        }
        updateHeight(node);//更新节点高度
        /*2.执行旋转操作，使该子树重新恢复平衡*/
        node=rotate(node);
        //返回子树的根节点
        return node;
    }
public:
    /*获取节点高度*/
    int height(TreeNode*node){
        //节点高度为-1，叶子节点高度为0
        return node==nullptr?-1:node->height;
    }
    /*获取平衡因子*/
    int balanceFactor(TreeNode*node){
        //空节点平衡因子为0
        if(node==nullptr)
            return 0;
        //节点平衡因子=左子树高度-右子树高度
        return height(node->left)-height(node->right);
    }
    /*插入节点*/
    void insert(int val){
        root=insertHelper(root,val);
    }
    /*删除节点*/
    void remove(int val){
        root=removeHelper(root,val);
    }
    /*查找节点*/
    TreeNode*search(int val){
        TreeNode*cur=root;
        //循环查找，越过节点后跳出
        while(cur!=nullptr){
            //目标节点在cur的右子树中
            if(cur->val<val)cur=cur->right;
            //目标节点在cur的左子树中
            else if(cur->val>val)cur=cur->left;
            //找到目标节点，跳出循环
            else break;
        }
        //返回目标节点
        return cur;
    }
    /*构造方法*/
    AVGTree():root(nullptr){
    }
    /*析构方法*/
    AVGTree(){
        freeMemoryTree(root);
    }
};




#endif