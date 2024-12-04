// Do NOT add any other includes
#include "dict.h"

//note fstream was not included before  (
// (go to dict.h)
//note uppercase-lowercase not handled

Dict::Dict(){
    // Implement your function here
    root = NULL;
   
}

Dict::~Dict(){
    // Implement your function here   
    deleteDictionaryTree(root);
    root = NULL; 
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){

    vector<string>wordlist = generateWordList(sentence);
    for(int i=0;i<wordlist.size();i++){
        string Word = wordlist[i];
        root = insertWord(root,NULL,Word);
    }
}

int Dict::get_word_count(string word){
    // Implement your function here
    TreeNode* temp = root;
    while(temp!=NULL){
        if(word > temp->word){ temp = temp->right; } 

        else if(word < temp->word){ temp = temp->left; }

        //word== temp->word:
        else{ return temp->count; }
    }
    //else word does not exits 
    return -1;
}

void Dict::dump_dictionary(string filename){
    ofstream myfile(filename);

    string file;
    dump(file,root);
    myfile << file;
    myfile.close();
    return;
}
