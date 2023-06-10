/*
Program for Binary Search Tree Operations
Author: Yoganand Kanhed
*/

#include<iostream>
using namespace std;
class BST;
class Node
{
    Node *left;
    Node * right;
    int data;
    friend class BST;
public:
    Node()
    {
        this->left = nullptr;
        this->right=nullptr;
    }
};

class BST
{
    Node * root;
    
public:
    void createBST();
    Node * binarySearch(int);
    void deleteNode(int);
    Node * inorderPre(Node * temp)
    {
        //inorder pre is the rightmost node in left subtree of the node for which inorder pre has to be finded
            temp = temp->left;
            while(temp->right!=nullptr)
                temp = temp->right;

            cout<<"Inorder pre is :"<<temp->data;
            return temp;
    }
    void inorder()
    {
        inorder(this->root);
    }
    void inorder(Node*);
    BST()
    {
        this->root = nullptr;
    }
    void invertTree(){
        invertTree(this->root);
    }
    Node * invertTree(Node *);
};

Node * BST::invertTree(Node * root)
{
    if(root==nullptr)
    return nullptr;
    
    Node * tmp = root->left;
    root->left = root->right;
    root->right = tmp;
    
    Node * rvalue = invertTree(root->left);
    if(rvalue) cout<<rvalue->data<<endl;
    invertTree(root->right);
    
    return root;   

}
/*void BST::deleteNode(int value){

// Traverse a node to be deleted
Node * temp = root;
if(root==nullptr)
return nullptr;

if(value > temp->data)
    temp = temp->right;
else if(value < temp->data)
    temp = temp->left;
//Node to be deleted reached
else{



}


}


}*/
void BST::createBST()
{
    Node * curr = new Node();
    cout<<"Enter the data :";
    cin>>curr->data;

    if(root==nullptr)
    {
        this->root = curr;
        cout<<"Root is null"<<endl;
    }
    else
    {
        Node * temp = this->root;
        int flag = 0;
         cout<<"Root data :"<<temp->data<<endl;
        while(flag!=1)
        {
            if(curr->data > temp->data)
            {
               if(temp->right==nullptr)
                {
                    flag = 1;
                    temp->right=curr;
                      cout<<"right to "<<temp->data<<endl;
                }    
                else
                    temp = temp->right;
                
            }    
            else
            {
               if(temp->left==nullptr)
                {
                    flag = 1;
                    temp->left=curr;
                     cout<<"left to "<<temp->data<<endl;
                }    
                else
                    temp = temp->left;
            }    
            
        }
    }

   // delete curr;
}

void BST::inorder(Node* aroot)
{
    if(aroot!=nullptr)
    {
        inorder(aroot->left);
        cout<<aroot->data<<"  ";
        inorder(aroot->right);
    }
}

Node * BST::binarySearch(int key)
{
    int flag = 0;
        if(root==nullptr)
        {
            cout<<"Key is not found!!"<<endl;
            return nullptr;
        }   
        else
        {
            Node * temp = root;
            while(temp!=nullptr)
            {
                if(temp->data == key)
                {
                    cout<<"Key Found "<<temp->data<<endl;
                    flag=1;
                    return temp;
                    //break;
                }  
                else if(temp->data < key)
                    temp = temp->right;
                else
                    temp = temp->left;
            }
            if(flag==0)
            {
                cout<<"Key is not found"<<endl;
                return nullptr;
            }    
        }
        return nullptr;
}

int main()
{
    BST bstTree;
    char choice;
    do
    {
        int opr;
        cout<<"1. Insert Node \n2. Print Inorder \n3. Binary Search"<<endl;
        cout<<"Enter your choice:";
        cin>>opr;

        switch (opr)
        {
        case 1:
            bstTree.createBST();
            break;
        case 2:
            bstTree.inorder();
            break;
        case 3:
            {
                cout<<"Enter the ket to search:";
                int key;
                cin>>key;
                Node * temp = bstTree.binarySearch(key);
                bstTree.inorderPre(temp);
            }
            break;
        case 4:
        {
            bstTree.invertTree();
        }
        break;
        default:
            cout<<"\nNot a valid operation, please try again from valid options!!"<<endl;
            break;
        }

        //cout<<"Do you want to continue? y/n :";
       // cin>>choice;

    } while (1 /*choice!='n' || choice!='N'*/);
    

    return 0;

}