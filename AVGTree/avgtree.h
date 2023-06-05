#ifndef AVGTREE_H
#define AVGTREE_H
#include"../utils/common.hpp"
class AVGTree{
public:
    TreeNode*root;//���ڵ�
private:
    /*���½ڵ�߶�*/
    void updateHeight(TreeNode*node){
        //�ڵ�߶ȵ�����������߶�+1;
        node->height=max(height(node->left),height(node->right))+1;
    }
    /*��������*/
    TreeNode*rightRotate(TreeNode*node){
        TreeNode*child=node->left;
        TreeNode*grandchild=child->right;
        //��childΪԭ�㽫node������ת
        child->right=node;//��ʧ��ڵ���Ϊ��ڵ���ҽڵ�
        node->left=grandchild;//����ڵ�ԭ�����ҽڵ���Ϊʧ��ڵ����ڵ�
        //���½ڵ�߶�
        updateHeight(node);
        updateHeight(child);
        //������ת�������ĸ��ڵ�
        return child;
    }
    /*��������*/
    TreeNode*leftRotate(TreeNode*node){
        TreeNode*child=node->right;
        TreeNode*grandchild=child->left;
        //��childΪԭ�㽫node����
        child->left=node;//��ʧ��ڵ���Ϊ�ҽڵ������
        node->right=grandchild;//���ҽ��ԭ������ڵ���Ϊʧ��ڵ���ҽ��
        //���½ڵ�߶�
        updateHeight(node);
        updateHeight(child);
    }
    /*ִ����ת������ʹ���������»ָ�ƽ��*/
    TreeNode*rotate(TreeNode*node){
        //��ȡnode�ڵ��ƽ������
        int _balanceFactor=balanceFactor(node);
        //��ƫ��(��������߶ȴ���������)
        if(_balanceFactor>1){
            if(balanceFactor(node->left)>=0){
                //����(��߱��ұ߶�һ���ڵ㵼��ʧ��)
                return rightRotate(node);
            }else{
                //������������(�ȶ���ڵ�����)
                node->left=leftRotate(node->left);
                //�ٶ�ʧ��ڵ�����
                return rightRotate(node);
            }
        }
        //��ƫ��
        if(_balanceFactor<-1){
            if(balanceFactor(node->right)<=0){
                //����(��ڵ���ҽڵ���һ��)
                return leftRotate(node);
            }else{
                //��������������
                node->right=rightRotate(node->right);
                //�ٶ�ʧ��ڵ�����
                return leftRotate(node);
            }
        }
        //ƽ������������ת������
        return node;
    }
    /*�ݹ����ڵ�*/
    TreeNode*insertHelper(TreeNode*node,int val){
        if(node==nullptr)
            return new TreeNode(val);
        /*1.���Ҳ���λ�ã�������ڵ�*/
        if(val<node->val)
            node->left=insertHelper(node->left,val);
        else if(val>node->val)
            node->right=insertHelper(node->right,val);
        else
            return node;    //�ظ��ڵ㲻���룬ֱ�ӷ���
        updateHeight(node);//���½ڵ�߶�
        /*2.ִ����ת������ʹ�����ָ�ƽ��*/
        node=rotate(node);
        //���������ĸ��ڵ�
        return node;
    }
    /*ɾ���ڵ�*/
    TreeNode*removeHelper(TreeNode*node,int val){
        if(node==nullptr)
            return nullptr;
        /*1.���ҽڵ㣬��ɾ��*/
        if(val<node->val)
            node->left=removeHelper(node->left,val);
        else if(val>node->val)
            node->right=removeHelper(node->right,val);
        else{
            if(node->left==nullptr||node->right==nullptr){
                TreeNode*child=node->left!=nullptr?node->left:node->right;
                //�ӽڵ�����Ϊ0��ֱ��ɾ��node������
                if(child==nullptr){
                    delete node;
                    return nullptr;
                }else{//�ӽڵ�����Ϊ1��ֱ��ɾ��node
                    delete node;
                    node=child;
                }
            }else{
                //�ӽڵ�����Ϊ2��������������¸��ڵ�ɾ�������øýڵ��滻��ǰ�ڵ�
                TreeNode*temp=node->right;
                while(temp->left!=nullptr){
                    temp=temp->left;
                }
                int tempVal=temp->val;
                node->right=removeHelper(node->right,temp->val);
                node->val=tempVal;
            }
        }
        updateHeight(node);//���½ڵ�߶�
        /*2.ִ����ת������ʹ���������»ָ�ƽ��*/
        node=rotate(node);
        //���������ĸ��ڵ�
        return node;
    }
public:
    /*��ȡ�ڵ�߶�*/
    int height(TreeNode*node){
        //�ڵ�߶�Ϊ-1��Ҷ�ӽڵ�߶�Ϊ0
        return node==nullptr?-1:node->height;
    }
    /*��ȡƽ������*/
    int balanceFactor(TreeNode*node){
        //�սڵ�ƽ������Ϊ0
        if(node==nullptr)
            return 0;
        //�ڵ�ƽ������=�������߶�-�������߶�
        return height(node->left)-height(node->right);
    }
    /*����ڵ�*/
    void insert(int val){
        root=insertHelper(root,val);
    }
    /*ɾ���ڵ�*/
    void remove(int val){
        root=removeHelper(root,val);
    }
    /*���ҽڵ�*/
    TreeNode*search(int val){
        TreeNode*cur=root;
        //ѭ�����ң�Խ���ڵ������
        while(cur!=nullptr){
            //Ŀ��ڵ���cur����������
            if(cur->val<val)cur=cur->right;
            //Ŀ��ڵ���cur����������
            else if(cur->val>val)cur=cur->left;
            //�ҵ�Ŀ��ڵ㣬����ѭ��
            else break;
        }
        //����Ŀ��ڵ�
        return cur;
    }
    /*���췽��*/
    AVGTree():root(nullptr){
    }
    /*��������*/
    AVGTree(){
        freeMemoryTree(root);
    }
};




#endif