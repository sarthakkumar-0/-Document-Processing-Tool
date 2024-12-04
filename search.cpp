// Do NOT add any other includes
#include "search.h"


SearchEngine::SearchEngine(){
    // Implement your function here
   list = new List();
}   

SearchEngine::~SearchEngine(){
    // Implement your function here
    delete list;

}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here
    list->insert(book_code,page,paragraph,sentence_no, sentence);
    
    return;
}

Node* SearchEngine::search(string pattern, int& n_matches){
    // Implement your function here
    Results res;
    
    SentenceNode* temp = list->getHead();

    int j=1;
    while(temp!=NULL){
       
        int book_code = temp->book_code;
        int page_no = temp->page_no;
        int para_no = temp->para_no;
        int sentence_no = temp->sentence_no;
        string sentence = temp->sentence;

       
        vector<int>offsets = Algorithm :: findOffsets(pattern,sentence);

        n_matches += offsets.size();
     
        for(int i=0;i<offsets.size();i++){
            res.insert(book_code,page_no,para_no,sentence_no, offsets[i]);
        }
        
        temp = temp->next;

    }

    // res.print();
    return res.getHead();
}


// int main(){

//     SearchEngine a;
//     a.insert_sentence(1,2,3,4,"hello! i will not@search for me!");
//     a.insert_sentence(3,4,5,6,"hello_ i willr not@search for me!");
//     int x=0;
//     a.search("rch for me",x);
//     cout << x << endl;
//     return 0;
// }