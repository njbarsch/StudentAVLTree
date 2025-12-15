#pragma once

#include <iostream>
#include <string>
#include "studentDatabase.h"

using namespace std;

class sNode
{

private:
    string name;
    string grade;
    int height;
    sNode *leftChild;
    sNode *rightChild;
    sNode *parent;

public:
    sNode *rightRotation();
    sNode *leftRotation();
    sNode *leftRightRotation();
    sNode *rightLeftRotation();

    sNode();
    sNode(string aName, string aGrade);

    string nodeIsBalanced();

    sNode *getRightChild();
    sNode *getLeftChild();
    sNode *getParent();
    int getHeight();
    string getName();
    string getGrade();

    void setHeight(int val);
    void setLeftChild(sNode *aStudent);
    void setRightChild(sNode *aStudent);
    void setParent(sNode *aStudent);
    void setName(string val);
    void setGrade(string val);

    void display(sNode *aNode, int pos);
    void correctHeight();
    bool checkHeight();

    sNode *reconnectNodes(sNode *temp);

    void printAscending();
    void printDescending();

    string findPrev(string target);
    string findNext(string target);

    // sNode* copyInOrder(sNode* orgTree, sNode* copyTree);
    // void balanceAVLTree();
    void correctHeightRemove();
    sNode *doTheRotation();
    sNode *doTheRotationNotOnRoot();
    char leftOrRightChild();
    char findLargestChild();

    // remove cases
    sNode *bothChildrenIsLeftChild();
    sNode *onlyRightChildIsIsLeftChild();
    sNode *onlyLeftChildIsLeftChild();
    sNode *bothChildrenIsRightChild();
    sNode *onlyRightChildIsIsRightChild();
    sNode *onlyLeftChildIsRightChild();
};