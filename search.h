// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;



class SearchEngine{
private:
    // You can add attributes/helper functions here

    
    class SentenceNode{

        public:

        SentenceNode* next;
        SentenceNode * prev;
        int book_code;
        int page_no;
        int para_no;
        int sentence_no;
        string sentence;

        SentenceNode(int b_code, int pg, int para, int s_no,string s){
            book_code = b_code;
            page_no = pg;
            para_no = para;
            sentence_no = s_no;
            sentence = s;
            next = NULL;
            prev = NULL;
        }

        SentenceNode(){
            next = NULL;
            prev = NULL;
        }

        ~SentenceNode(){
        }

    };


    class List{

        private:
        SentenceNode* head;
        SentenceNode* tail;

        public:
        //public function to return the head of the list 

        List(){
            head = NULL;
            tail = NULL;
        }

        //returns the head of the list;
        SentenceNode* getHead(){
            return head;
        }

        //returns the tail of the list;
        SentenceNode* getTail(){
            return tail;
        }

        //insert
        void insert(int b_code, int pg, int para, int s_no, string s){

            SentenceNode* newNode = new SentenceNode(b_code,pg,para,s_no,s);

            if(tail == NULL){
                head = newNode;
                tail = newNode;
                return;
            }
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            return;
        }   

        //prints the list head to tail // remove when your're done with the assignment!
        void print(){
            SentenceNode* temp = head;
            while(temp!=NULL){
                cout<< temp->sentence << endl;
                temp = temp->next;
            }
            cout << endl<<endl;
        }

        ~List(){
            
            SentenceNode* temp= head;
            while(temp!=NULL){
                SentenceNode* n = temp->next;
                delete temp;
                temp = n;
            }
        }
    };

    //list of matched results:    
    class Results{

        private:
        Node* head;
        Node* tail;

        public:

        Results(){
            head = NULL;
            tail = NULL;
        }

        ~Results(){
        }

        Node* getHead(){
            return head;
        }

        void insert(int b_code, int pg, int para, int s_no, int off){

            Node* newNode = new Node(b_code,pg,para,s_no,off);
        
            if(head==NULL){
                head = newNode;
                tail = newNode;
                return;
            }

            tail->right = newNode;
            newNode->left = tail;
            tail = newNode;

        }
    
        void print(){
            Node* temp = head;
            while(temp!=NULL){
                cout << "Book code    : " <<  temp->book_code << endl;
                cout << "Page no.     : " << temp->page << endl;
                cout << "Para no.     : " << temp->paragraph << endl;
                cout << "sentence no. : " <<  temp->sentence_no << endl;
                cout << "offset       : " << temp->offset << endl;
                cout << "===============================================" << endl;
                temp = temp->right;
             }
        }
    };


    class Algorithm{

        private:

        static int generateIndex(char ch){
        //total 95 possible characters 32 = ' ' to 126 = '~';
        ch = tolower(ch); // covnert upper case to lower case when ch is an alphabet:
        int index = ch-' ';
        return index;
        }

        static int* getShiftTable(string pattern){

            int pattern_size = pattern.size();
            int* shift_table =new int[95];
            for(int i=0;i<95;i++){
                shift_table[i] = pattern_size;
            }

            for(int i=0;i<pattern_size-1;i++){
                char ch = pattern[i];
                int index = Algorithm :: generateIndex(ch);
                shift_table[index] = pattern_size -i -1;
            }

            return shift_table;
        }   

        public:

        static vector<int> findOffsets(string pattern, string SearchString){

            int*ShiftTable = Algorithm::getShiftTable(pattern);
            int off=-1;
            vector<int>offsets;
            int pattern_size = pattern.size();
            int j = pattern_size-1;

            while(j<SearchString.size()){

                int shift= 0;
                shift = ShiftTable[Algorithm::generateIndex(SearchString[j])];

                int temp = j;
                bool SearchFound = true;

                for(int k=pattern_size-1;k>=0;k--){

                    if(tolower(pattern[k]) != tolower(SearchString[temp])){
                        SearchFound = false;
                        break;
                    }
                    temp--;

                }

                if(SearchFound){
                    off = temp+1;
                    offsets.push_back(off);
                }

                j += shift;
                
            }

            delete []ShiftTable;

            return offsets;
        }

    };

    // List object list, to stores each sentence along with their parameters.
    List* list;



public: 
    /* Please do not touch the attributes and 

    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);

    /* -----------------------------------------*/
};