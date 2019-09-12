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
int findKthLargestElem(Node *nd, int k);
bool containsValue(Node *nd, int val);
void closestValOf(Node *nd, int val, int min, int *reqd);
int countInRange(Node*, int, int);
void countGreaterThan(Node*, int, int*);
Node* deleteFromAVL(int val, int param, Node* nd);
Node* leftRightRot(Node *nd);
Node* rightLeftRot(Node *nd);
Node* inorderSucc(Node *nd);
Node* _inorderSucc(Node *nd);


int main(){
	Node *rot=NULL;
	float median=0.0;
	int kthLargest;
	int elem, elem1;
	int k;
	int t, t1;

	//1. Insert
	cout<<"Enter #elem you wanna enter"<<endl;
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>elem;
		rot=insertInAVL(elem, rot);

		cout<<"Prorder :";
		preOrd(rot);
		cout<<endl;

		// cout<<"Inorder :";
		// inOrd(rot);ss
		// cout<<endl;
	}

	// //2. Kth Largest elem
	// cout<<"Enter #kth largest elems you wanna find"<<endl;
	// cin>>t1;
	// for(int i=1;i<=t1;i++){
	// 	cin>>elem;
	// if(rot==NULL){
	// cout<<"Given root is null!!"<<endl;	
	// continue;
	// }
	// int noOfNodes=root->count;
	// if(elem>noOfNodes || elem<1){
	// 	cout<<"Given root is null!!"<<endl;
	// 	continue;
	// }
	// 	kthLargest=findKthLargestElem(rot, elem);
	// 	cout<<"k "<<elem<<" kth largest elem "<<kthLargest<<endl;
	// }

	// //3.Check if contains val
	// cout<<"Enter #elems you wanna check the existence of"<<endl;
	// cin>>t;
	// for(int i=1;i<=t;i++){
	// 	cin>>elem;
	// 	bool bol=containsValue(rot, elem);
	// 	cout<<"elem "<<elem<<" Contains? "<<bol<<endl;
	// }

	// //4.Find elem closest to val
	// cout<<"Enter #elems you wanna find the closest val of"<<endl;
	// cin>>t;
	// for(int i=1;i<=t;i++){
	// 	cin>>elem;
	// 	int min=INT_MAX;
	// 	int reqd=-1;//TODO : are negative values allowed inside avl? if yes, then err msg here?
	// 	closestValOf(rot, elem, min, &reqd);
	// 	cout<<"elem "<<elem<<" Closest val: "<<reqd<<endl;
	// }

	// //5.Find no. of elem in range
	// cout<<"Enter #ranges "<<endl;
	// cin>>t;
	// for(int i=1;i<=t;i++){
	// 	cin>>elem>>elem1;
	// 	int num=countInRange(rot, elem, elem1);
	// 	cout<<"num in range "<<num<<endl;
	// }

	//5.Find no. of elem in range
	cout<<"Enter #elems to delete "<<endl;
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>elem;
		int par=0;
		rot=deleteFromAVL(elem, par, rot);
		// cout<<"num in range "<<num<<endl;
		cout<<"Prorder :";
		preOrd(rot);
		cout<<endl;
	}

	return 0;
}

Node* deleteFromAVL(int val, int param, Node* nd){
	if(!nd){
		return nd;
	}

	else if(nd->val<val){
		Node *r = deleteFromAVL(val, param, nd->right);
		nd->right=r;
	}

	else if(nd->val>val){
		Node *l=deleteFromAVL(val, param, nd->left);
		nd->left=l;
	}

	else{//found the value to be deleted
		Node *t;
		if(!(nd->left) && !(nd->right)){//both child null
			free(nd);
			return NULL;
		}
		else if(nd->left == NULL){//and nd->right!=null (As otherwise it'd have gone in first if)
			Node *x=nd->right;
			free(nd);
			return x;
		}
		else if(nd->right == NULL){//and nd->left!=null (As otherwise it'd have gone in first if)
			Node *x=nd->left;
			free(nd);
			return x;
		}
		else{//both non null children
			Node *x;
			x=inorderSucc(nd);

			nd->val=x->val;
			nd->right = deleteFromAVL(x->val, param, nd->right);
		}
	}

	if (!nd){
		return nd;
	}

	nd->height=newheight(nd);
	nd->count=newcount(nd);
	int bal = balFact(nd);

	if(bal > 1){
		if(balFact(nd->left) >= 0){
			Node *x = rr(nd);
			return x;
		}
		if(balFact(nd->left) < 0){
			Node *x = leftRightRot(nd);
			return x;
		}
	}
	else if(bal < -1){
		if(balFact(nd->right) <= 0){
			Node *x= lr(nd);  
    		return x;
		}
		if(balFact(nd->right) > 0){
			Node *x=rightLeftRot(nd); 
        	return x; 
		}
	}
  
    return nd; 
}

Node* leftRightRot(Node *nd){
    nd->left=lr(nd->left);
    return rr(nd);
}

Node* rightLeftRot(Node *nd){
    nd->right=rr(nd->right);
    return lr(nd);
}

Node* inorderSucc(Node *nd){
	if(!nd){
		return nd;
	}
	return _inorderSucc(nd->right);
}

Node* _inorderSucc(Node *nd){
	if(!nd){
		return nd;
	}
	Node* temp=nd;
	while(temp->left){
		temp=temp->left;
	}

	return temp;
}

//In range k1-k2, both k1 k2 are inclusive, if they exist in tree
int countInRange(Node *nd, int k1, int k2){
	int numGreaterThan_k1=0, numGreaterThan_k2=0;
	int k1closest=-1, k2closest=-1;
	//TODO : assuming -1(and negatives) not allowed in AVL
	// int min=INT_MAX;
	closestValOf(nd, k1, INT_MAX, &k1closest);
	closestValOf(nd, k2, INT_MAX, &k2closest);

	cout<<"k1closest "<<k1closest<<endl;
	cout<<"k2closest "<<k2closest<<endl;

	if(k1closest==k1){
		numGreaterThan_k1=1;
		/*as we're not counting "roots"(in equality condition), need to include k1closest if in range;
		also k2closest gets included automatically, owing to being counted in numGreaterThan_k1*/
	}

	countGreaterThan(nd, k1closest, &numGreaterThan_k1);
	countGreaterThan(nd, k2closest, &numGreaterThan_k2);

	cout<<"k1 "<<k1<<" #greater elem "<<numGreaterThan_k1<<endl;
	cout<<"k2 "<<k2<<" #greater elem "<<numGreaterThan_k2<<endl;
	int inRange=abs(numGreaterThan_k1-numGreaterThan_k2);
	return inRange;
}

void countGreaterThan(Node *nd, int p, int *count){
	if(!nd){
		return;
	}
	if(p<nd->val && nd->right){
		*count=*count+1+nd->right->count;
		//+1->for the curr val we're comparing with
		//also, nd->right->count already includes that subtree's root's count
		// cout<<"entered p<nd->val. count= "<<*count<<endl;
		countGreaterThan(nd->left, p, count);
	}
	else if(p==nd->val && nd->right){
		*count=*count+nd->right->count;//not counting root
		// cout<<"entered p==nd->val. count= "<<*count<<endl;
		return;
	}
	else{//if p>nd->val
		if(nd->right)
			countGreaterThan(nd->right, p, count);
	}
}


void closestValOf(Node *nd, int val, int min, int *reqd){
	if(!nd){
		return; //TODO: error msg??
	}
	// if(nd->val == val){
	// 	return val;
	// }
	//above is already handled by virtue of min being 0 for such a case

	int x;
	(nd->val-val)<1?(x=val-nd->val):(x=nd->val-val);
	if(x<min){
		min=x;
		*reqd=nd->val;
	}
	if(x==min && (*reqd)>nd->val){//Say we're searching for 9, and elems 8 and 10 present in tree but not 9.
								//- both 8 and 9 are equally close to 9, but we've to return the smaller of the 2 i.e 8
		min=x;
		*reqd=nd->val;
	}
	else if(nd->val<val){
		closestValOf(nd->right, val, min, reqd);
	}
	else{
		closestValOf(nd->left, val, min, reqd);
	}
}

bool containsValue(Node *nd, int val){
	if(!nd){
		return false;
	}
	if(val==nd->val){
		return true;
	}
	if(val<nd->val && nd->left==NULL){
		return false;
	}
	if(val>nd->val && nd->right==NULL){
		return false;
	}
	if(val<nd->val){
		return containsValue(nd->left, val);
	}
	if(val>nd->val){
		return containsValue(nd->right, val);
	}
	return false;
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

int findKthLargestElem(Node *nd, int k){
	// if(!nd){
	// 	// cout<<"Given node's null!!"<<endl;
	// 	return -1;// TODO: Erro message?
	// }
	// int noOfNodes=nd->count;
	// if(k>noOfNodes || k<1){
	// 	return -1;// TODO: Erro message?
	// }
	// else{
		int elem=findKthElem(nd, noOfNodes-k+1);
		return elem;
	// }
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
			nd->left=lr(nd->left);
			return rr(nd);
		}
		return nd;
	}
	else if(nd->val < k){ //Not including duplicates as ordered "set"
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
			nd->right=rr(nd->right);
			return lr(nd);
		}
		return nd;
	}
	return nd;
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
	// if(mkey==12){
	// 	cout<<"In rr: "<<" y "<<y<<" y "<< y->val ;
	// }
	Node  *x, *z;
	x=y->left;
	z=x->right;

	// cout<<"In rr 0.0: ";
	// cout<<"y "<<y<<" x "<<x<<" z "<<z<<endl;

	// cout<<"In rr:- "<< y->val<<endl;
	// if (y)
	// 	cout<<"y "<< y->val ;
	// if(x)
	// 	cout <<" x "<< x->val ;
	// if(z)
	// 	cout<<" z "<< z->val <<endl;

	x->right=y;
	y->left=z;

	// cout<<"In rr later 0.0: ";
	// cout<<"y "<<y<<" x "<<x<<" z "<<z<<endl;
	// cout<<"In rr later:- "<< y->val<<endl;
	// // if (y && x && z)
	// // 	cout<<"In rr Later: "<<"*y "<<y->val<<" *x "<<x->val<<" *z "<<z->val<<endl;
	// if (y)
	// 	cout<<"y "<< y->val ;
	// if(x)
	// 	cout <<" x "<< x->val ;
	// if(z)
	// 	cout<<" z "<< z->val <<endl;


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

	// cout<<"In lr 0.0: "<<"y "<<y<<" x "<<x<<" z "<<z<<endl;
	// cout<<"In lr:- ";
	// cout<< y->val<<endl;
	// if (y)
	// 	cout<<"y "<< y->val ;
	// if(x)
	// 	cout <<" x "<< x->val ;
	// if(z)
	// 	cout<<" z "<< z->val <<endl;
	// // if (y && x && z)
	// // 	cout<<"In lr:- "<<"*y "<<y->val<<" *x "<<x->val<<" *z "<<z->val<<endl;

	x->left=y;
	y->right=z;

	// cout<<"In lr later 0.0: ";
	// cout<<"y "<<y<<" x "<<x<<" z "<<z<<endl;
	// cout<<"In lr later:- "<< y->val<<endl;
	// if (y)
	// 	cout<<"y "<< y->val ;
	// if(x)
	// 	cout <<" x "<< x->val ;
	// if(z)
	// 	cout<<" z "<< z->val <<endl;
	// // if (y && x && z)
	// // 	cout<<"In lr Later:- "<<"*y "<<y->val<<" *x "<<x->val<<" *z "<<z->val<<endl;


	y->height=newheight(y);
	x->height=newheight(x);
	//Note, after reft roataton, height of the overall AVL remains same, 
	// but height of the nodes y and x in the subtree changes by 1

	y->count=newcount(y);
	x->count=newcount(x);

	return x;

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


