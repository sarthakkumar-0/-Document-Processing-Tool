// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include<fstream>

//note fstream was not included before  
using namespace std;



class Dict {
private:
    
    //class TreeNode
    class TreeNode{

        public:
        TreeNode*left;
        TreeNode*right;
        TreeNode* parent;
        int count;
        int height;
        string word;

        //TreeNode constructor
        TreeNode(string w){
            left=NULL;
            right=NULL;
            parent=NULL;
            count=1;
            height=1;
            word=w;

            }

        ~TreeNode(){
            left = NULL;
            right = NULL;
            parent = NULL;
        }

    };
    // You can add attributes/helper functions her

    //root node of dictionary
    TreeNode* root;

    //return the height of the node, height of leaf node is 1
    int getHeight(TreeNode* node){
        if(node== NULL){ return 0; }
        return node->height;
    }

    //returns the balance factor of node, left-right;
    int getBf(TreeNode* node){
        if(node == NULL){ return 0;}
        return getHeight(node->left) - getHeight(node->right); 
    }

    //updates the height of a give node
    void updateHeight(TreeNode*node){
        node->height = max(getHeight(node->left), getHeight(node->right))+1;
    }

    //helper for left roation   
    TreeNode* rotateleft(TreeNode*x){
        TreeNode* y = x->right;
        TreeNode* temp =y->left;
        TreeNode* parentX = x->parent;

        y->left = x;
        y->parent = parentX;
        
        x->parent = y;
        x->right = temp;

        if(temp!=NULL){temp->parent = x;}

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    //helper for right rotation
    TreeNode* rotateright(TreeNode*y){
        TreeNode* x= y->left;
        TreeNode* temp = x->right;
        TreeNode* parentY = y->parent;

        x->right = y;
        x->parent = parentY;

        y->parent = x;
        y->left = temp;

        if(temp!=NULL){temp->parent = y;}

        updateHeight(y);
        updateHeight(x);

        return x;

    }

    // right right case 
    TreeNode* RightRight(TreeNode* node){
        return rotateleft(node);
    }

    // left left case
    TreeNode* LeftLeft(TreeNode* node){
        return rotateright(node);
    }

    //left right case
    TreeNode* LeftRight(TreeNode*node){
        node->left = rotateleft(node->left);
        return rotateright(node);
    }

    //right left case
    TreeNode* RightLeft(TreeNode* node){
        node->right = rotateright(node->right);
        return rotateleft(node);
    }

    //inserts a given word in a tree
    TreeNode* insertWord(TreeNode*node, TreeNode* par,string word){

        if(node == NULL){
           TreeNode* newnode = new TreeNode(word);
           newnode->parent = par;
            return newnode;
        }

        if(word > node->word){
            node->right = insertWord(node->right,node,word);
        }

        else if(word < node->word){
            node->left = insertWord(node->left,node,word);
        }

        else if(word == node->word){
            node->count++;
            return node;
        }

        updateHeight(node);

        int bf = getBf(node);

        if(bf>1 && word < node->left->word){
            //leftleft
            node = LeftLeft(node);
        }

        else if(bf>1 && word > node->left->word){
            //left right:
            node = LeftRight(node);
        }

        else if(bf <-1 && word > node->right->word){
            //right right
            node =  RightRight(node);
        }

        else if(bf <-1 && word < node->right->word){

            node = RightLeft(node);
        }
        return node;
    }

    bool Seperate(char ch, string&seperators){
    for(int i=0;i<seperators.size();i++){
        if(ch==seperators[i]){
            return true;
        }
    }
    return false;

    }

    //returns a vector of the words in the sentence 
    vector<string>generateWordList(string sentence){

        //   . , - : ! " ' ( ) ? — [ ] “ ” ‘ ’ ˙ ; @
        
        sentence+=' ';
        vector<string>WordList;
        string word = "";
        bool flag= false;

        for(int i =0;i<sentence.size();i++){

            char ch = sentence[i];

            string seperators = ". , - : ! \' \" ( ) ?—[]“”‘’˙;@";

            bool isPresent = Seperate(ch,seperators);

            ch = tolower(ch);

            if(isPresent == false){
                word+=ch;
                flag = true;
            }
            

            else{
                if(flag == true){
                    WordList.push_back(word);
                }
                    word="";
                    flag= false;
            }

        }    
    return WordList;
    }

    void dump(string&file, TreeNode*root){
        if(root==NULL){return;}
        dump(file,root->left);
        string line =  root->word + ", " + to_string(root->count) + "\n";
        file += line;
        dump(file,root->right);
    }
   
    //inorder
    void inorder(TreeNode*root){

    if(root==NULL){return;}

    inorder(root->left);

    string rootword = root->word;
    string leftchildword = "NULL";
    string rightchildword = "NULL";
    string parentword = "NULL";
    if(root->parent!=NULL){
        parentword = root->parent->word;
    }
    if(root->left!=NULL ){
        leftchildword = root->left->word;
    }
    if(root->right!=NULL){
        rightchildword = root->right->word;
    }
    
    cout << "node is " << rootword << " parent is " << parentword << " left child is " << leftchildword << " right child is " << rightchildword << " height is " << root->height  << " count : "  << root->count << endl;

    inorder(root->right);
}

    void deleteDictionaryTree(TreeNode* root){

        if(root==NULL){ return; }
        deleteDictionaryTree(root->left);
        deleteDictionaryTree(root->right);
        root->~TreeNode();
    }
    
    public:
    //print tree
    void printTree(){
        inorder(root);
        cout << endl;
    }

    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */

    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};