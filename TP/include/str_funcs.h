#ifndef STRFUNCS
#define STRFUNCS

#include <iostream>
#include <fstream>
#include "memlog.h"
#include "msgassert.h"
extern int ordem[26];

class analisador
{
    private:
    const std::string punct = ",.!?:;_}";
    int ordem[26];
    int MAX = 100000;
    
    public:
    std::string *words;
    int len = 0;

    analisador();
    void normalize(std::string &str);
    void start_order(int old_order[26]);
    int add(std::string &str);      
    void conta_palavras(std::string &output_nome);
};

bool isLessEqual(std::string &stra, std::string &strb);
void quicksort(std::string arr[], int low, int high, int size, int m);
void insertionSort(std::string arr[], int start, int end);
#endif
