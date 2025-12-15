#pragma once

#include "dataRetrievalTool.h"
#include <iostream>
#include <string>

using namespace std;

class sNode;

class SDB
{

private:
    // sNode *root;
    sNode* isInDB(string name);

    // void printDescending();
    // void printAscending();
public: //<-tko l8r
    int countNodes(sNode* child);

public:
    void printDescending();
    void printAscending();

    // SDB(sNode *aRoot);

    sNode* root;
    SDB();
    SDB(sNode* aRoot);
    DRT search(string key);
    DRT modify(string key, string data);
    void add(string aName, string aGrade); // was private
    sNode* remove(string aName);
    void display();
    string findPrev(string target);
    string findNext(string target);
    char findLargestChild();
};