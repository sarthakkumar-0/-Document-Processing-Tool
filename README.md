# Document-Processing-Tool


## Introduction

In  this project, we have created a search engine that returns all matching answers to an input query in the provided corpus, similar to how search engines like Google or Bing return results. The search engine must handle queries that start and end in the middle of words, returning all sentences in the corpus that match the input query.

## 1. Dictionary

Our task in this part is to create a dictionary data structure using AVL Trees to store the word counts of the words in the document.

### Functions to Implement in `dict.cpp`

1. **`Dict()`**: Create a `Dict` instance. Initialize the data structures for storing word counts.
2. **`void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string s)`**: Split the given sentence `s` into its constituent words and increment the word count of each word.
3. **`int get_word_count(string word)`**: Given a word, return its count in the document. The word count should be case-insensitive.
4. **`void dump_dictionary(string filename)`**: Dump the dictionary into the given file name. All words should be in lower case. Each line in the output file must contain a word followed by a comma and its count. For example:
    ```plaintext
    $ cat dict.txt
    and, 5
    the, 10
    time, 2
    ```
5. **`~Dict()`**: Destroy the `Dict` instance created for the document.

## 2. Pattern Search

In the second part, we have to implement a search mechanism to find a string in the document. Given any pattern `p`, we obtain a list of all the offsets in the document where the pattern is present. The pattern can start and end in the middle of words in the document. This is implemented using the Horspool Algorithm for pattern searching. [Boyer–Moore–Horspool algorithm](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore%E2%80%93Horspool_algorithm)



### Functions to Implement in `search.cpp`

1. **`SearchEngine()`**: Create a `SearchEngine` instance. Initialize the data structures for pattern search.
2. **`void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string s)`**: Pre-process the given sentence `s` for search queries.
3. **`Node* search(string pattern, int &n_matches)`**: Given a pattern, create a linked list of nodes containing data about each match of the pattern in the text. The nodes should contain:
    - Book Code
    - Page Number
    - Paragraph
    - Sentence Number
    - Starting Offset (relative to the beginning of the sentence). For example, if the match starts at the first letter of the sentence, the starting offset must be 0.

    Note: Patterns will not span across sentence boundaries. You must not distinguish between upper-case and lower-case letters. Convert all patterns and sentences to lower-case strings. Use the `Node` class declared in `Node.h`.  Store the length of the linked list (number of matches) in the variable `n_matches` (passed by reference).

4. **`~SearchEngine()`**: Destroy the `SearchEngine` instance created for the document.

