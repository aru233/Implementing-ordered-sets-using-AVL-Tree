#include<bits/stdc++.h> 
using namespace std; 


class Node {
public:
    int val;
    int height;
    int count;
    Node *left;
    Node *right;
};

Node *createNewNode(int key);
Node* rr(Node *y);
Node* lr(Node *y);
int height(Node *nd);
int newheight(Node *nd);
int count(Node *nd);
int newcount(Node *nd);
int balFact(Node *nd);
Node* insertInAVL(int key, Node *nd);
int checkIfLeftLeft(int bal, int key, Node *nd);
int checkIfLeftRight(int bal, int key, Node *nd);
int checkIfRightLeft(int bal, int key, Node *nd);
int checkIfRightRight(int bal, int key, Node *nd);
void preOrd(Node *nd);
void inOrd(Node *nd);
float findMedian(Node *nd);
int findKthElem(Node *nd, int k);
float retMedian(float m);
Node* leftRightRot(Node *nd);
Node* rightLeftRot(Node *nd);

// int mkey;

int main(){
    Node *rot=NULL;
    float median=0.0;
    int k, t;
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>k;
        rot=insertInAVL(k, rot);
        // cin>>mkey;
        // rot=insertInAVL(mkey, rot);
        median=findMedian(rot);

        // cout<<"Prorder :";
        // preOrd(rot);
        // cout<<endl;

        // cout<<"Inorder :";
        // inOrd(rot);
        // cout<<endl;

        cout<<median<<endl;

        // retMedian(median);
    }

    return 0;
}

float retMedian(float median){
    return median;
}

float findMedian(Node *nd){
    // cout<<"in findMedian() "<<endl;
    // cout<<"node: "<<nd<<endl;
    if(!nd){
        // cout<<"Given node's null!!"<<endl;
        return -1;
    }
    int noOfNodes=nd->count;
    // cout<<"No. of nodes in tree "<<noOfNodes<<endl;
    float med1, med2;
    if(noOfNodes%2 == 0){//even no. of elemnts
        // cout<<"Even num of elem"<<endl;
        med1=findKthElem(nd, noOfNodes/2);
        med2=findKthElem(nd, 1+noOfNodes/2);
        // cout<<"med1 "<<med1<<endl;
        // cout<<"med2 "<<med2<<endl;
        return (med1+med2)/2;
    }
    else{//odd no. of elemnts
        // cout<<"Odd num of elem"<<endl;
        med1=findKthElem(nd, (noOfNodes+1)/2);
        return med1;
    }
    
}

int findKthElem(Node *nd, int k){
    int numOfLeftSubtreeNode=0, numOfRightSubtreeNode=0;
    // cout<<"node1: "<<nd<<endl;
    if(!nd){
        // cout<<"find main null,.."<<endl;
        return -1;
    }
    if(nd->left==NULL && nd->right==NULL){
        return nd->val;
    }
    if(nd->left!=NULL){
        numOfLeftSubtreeNode = nd->left->count;
    }
    if(nd->right!=NULL){
        numOfRightSubtreeNode = nd->right->count;
    }
    if(numOfLeftSubtreeNode==k-1){//root is media
        return nd->val;
    }
    else if(numOfLeftSubtreeNode>=k){//median is in left subtree
        return findKthElem(nd->left, k);
    }
    else{//median is in right subtree
        return findKthElem(nd->right, k-numOfLeftSubtreeNode-1);
    }
    
}

Node* insertInAVL(int key, Node *nd){
    int k=key, bal;

    // cout<<"key "<<k <<" node "<<nd<<endl;
    //Step 1-> Insert in BST
    if(!nd){
        // cout<<"here1"<<endl;
        Node *newn= createNewNode(key);
        // cout<<"here"<<endl;
        // cout<<"newn "<<newn<<endl<<" val "<<newn->val<<endl;;
        return newn;
    }

    else if(nd->val > k){//left insertion
        nd->left=insertInAVL(k, nd->left);
        //Step2->height
        nd->height=newheight(nd);
        //Step3->count
        nd->count=newcount(nd);
        //Step4->balFact
        bal=balFact(nd);
        //Step 5->Check for imabalance and rotate accordingly
        if(checkIfLeftLeft(bal, key, nd)){
            return rr(nd);
        }
        if(checkIfLeftRight(bal, key, nd)){
            return leftRightRot(nd);
        }
        return nd;
    }
    else{ //When k>=nd->val
        nd->right=insertInAVL(k, nd->right);
        //Step2->height
        nd->height=newheight(nd);
        //Step3->count
        nd->count=newcount(nd);
        //Step4->balFact
        bal=balFact(nd);
        //Step 5->Check for imabalance and rotate accordingly
        if(checkIfRightRight(bal, key, nd)){
            return lr(nd);
        }
        if(checkIfRightLeft(bal, key, nd)){            
           return rightLeftRot(nd);
        }
        return nd;
    }
}

Node* createNewNode(int key){
    // cout<<"in createNewNode() "<<endl;
    Node *nnode=new Node();
    nnode->val=key;
    nnode->height=1;
    nnode->count=1;//keeps count of nodes in left and right subtree
    nnode->left=NULL;
    nnode->right=NULL;

    return nnode;
}

Node* rr(Node *y){//right rotation
    Node  *x, *z;
    x=y->left;
    z=x->right;

    x->right=y;
    y->left=z;

    y->height=newheight(y);
    x->height=newheight(x);
    //Note, after reft roataton, height of the overall AVL remains same, 
    // but height of the nodes y and x in the subtree changes by 1

    y->count=newcount(y);
    x->count=newcount(x);
    return x;
}

Node* lr(Node *y){//left rotation
    Node  *x, *z;
    x=y->right;
    z=x->left;

    x->left=y;
    y->right=z;

    y->height=newheight(y);
    x->height=newheight(x);
    //Note, after reft roataton, height of the overall AVL remains same, 
    // but height of the nodes y and x in the subtree changes by 1

    y->count=newcount(y);
    x->count=newcount(x);

    return x;

}

Node* leftRightRot(Node *nd){
    nd->left=lr(nd->left);
    return rr(nd);
}

Node* rightLeftRot(Node *nd){
    nd->right=rr(nd->right);
    return lr(nd);
}

int height(Node *nd){
    int ht;
    if(nd){
        ht=nd->height;
    }
    else{
        ht=0;
    }
    return ht;
}
int count(Node *nd){
    int ct;
    if(nd){
        ct=nd->count;
    }
    else{
        ct=0;
    }
    return ct;
}

int newheight(Node *nd){
    int ht1, ht2;
    ht1=height(nd->left);
    ht2=height(nd->right);
    return 1+max(ht1,ht2);
}
int newcount(Node *nd){
    int ht1, ht2;
    ht1=count(nd->left);
    ht2=count(nd->right);
    return 1+ht1+ht2;
}

int balFact(Node *nd){
    int bf;
    if(nd){
        bf=height(nd->left) - height(nd->right);
    }
    else{
        bf=0;
    }
    return bf;
}

int checkIfLeftLeft(int bal, int key, Node *nd){
    if(bal>1 && key<nd->left->val){
        return 1;
    }
    else return 0;
}

int checkIfLeftRight(int bal, int key, Node *nd){
    if(bal>1 && key>nd->left->val){
        return 1;
    }
    else return 0;
}

int checkIfRightRight(int bal, int key, Node *nd){
    if(bal<-1 && key>nd->right->val){
        return 1;
    }
    else return 0;
}

int checkIfRightLeft(int bal, int key, Node *nd){
    if(bal<-1 && key<nd->right->val){
        return 1;
    }
    else return 0;
}

void preOrd(Node *nd)  
{  
    if(nd != NULL)  
    {  
        cout << nd->val << ":"<<nd->count<<":"<<nd->height<<" ";  
        preOrd(nd->left);  
        preOrd(nd->right);  
    }  
}  
void inOrd(Node *nd)  
{  
    if(nd != NULL)  
    {  
        inOrd(nd->left);  
        cout << nd->val << ":"<<nd->count<<":"<<nd->height<<" ";          
        inOrd(nd->right);  
    }  
}


