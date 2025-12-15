#include "studentDatabase.h"
#include "dataRetrievalTool.h"
#include "studentNode.h"
#include <math.h>

SDB::SDB()
{
    root = nullptr;
}

SDB::SDB(sNode* aRoot)
{
    root = aRoot;
}

DRT SDB::search(string key)
{
    // DRT finder;
    sNode* aStudent = this->isInDB(key);

    string data = "";
    string next = "";
    string prev = "";

    if (key == "") // empty search
    {
        data = "";

        if (root != nullptr)
        {
            sNode* findBiggest = root;
            while (findBiggest->getRightChild() != nullptr)
            {
                findBiggest = findBiggest->getRightChild();
            }

            prev = findBiggest->getName();
            sNode* findSmallest = root;

            while (findSmallest->getLeftChild() != nullptr)
            {
                findSmallest = findSmallest->getLeftChild();
            }

            next = findSmallest->getName();
        }

        return DRT(next, prev, data);
    }
    else if (aStudent) // student exists
    {
        prev = findPrev(key);
        next = findNext(key);
        return DRT(next, prev, aStudent->getGrade());
    }
    else if (key != "" && !aStudent)
    { // student DNE
        sNode* searchNode = this->root;

        while (searchNode)
        {
            // changed these 2 if statments bool condition \/
            // but i think we can delete x2 code in here!
            if (next < key && searchNode->getName() > key)
            {
                next = searchNode->getName();
            }
            if (prev > key && searchNode->getName() > key)
            {
                prev = searchNode->getName();
            }
            //=======main search=======
            if (key > searchNode->getName() && searchNode->getRightChild())
            {
                if (searchNode->getName() < key && searchNode->getName() > prev)
                {
                    prev = searchNode->getName();
                }

                // the ideal next is greater than key but it is closer to the key than the next that is
                // already assigned therefore it is not as far away meaning it is closer meaning it is smaller
                // meaning it is less than
                if (searchNode->getName() < next && searchNode->getName() > key) {
                    next = searchNode->getName();
                }
                searchNode = searchNode->getRightChild();
            }
            else if (key < searchNode->getName() && searchNode->getLeftChild())
            {
                // to be the previous you need to be smaller than the key but greater (closer)
                // that the last previous
                if (searchNode->getName() < key && searchNode->getName() > prev)
                {
                    prev = searchNode->getName();
                }
                if (searchNode->getName() < next && searchNode->getName() > key)
                {
                    next = searchNode->getName();
                }
                searchNode = searchNode->getLeftChild();
            }
            else
            {
                if (key > searchNode->getName())
                {
                    // to be the previous you need to be smaller than the key but greater (closer)
                    // that the last previous
                    if (searchNode->getName() < key && searchNode->getName() > prev)
                    {
                        prev = searchNode->getName();
                    }
                    // next = "";
                    searchNode = nullptr;
                }
                else
                {
                    //<=?
                    if (searchNode->getName() < next && searchNode->getName() > key)
                    {
                        next = searchNode->getName();
                    }

                    // prev = "";
                    searchNode = nullptr;
                }
            }
        }
        return DRT(next, prev, "");
    }

    else
    {
        cout << "Error - from search()" << endl;
        exit(0);
    }

    return DRT(next, prev, data); // makes this return nullptr;
}

sNode* SDB::remove(string aName) {
    // 1 empty case + 5 root cases + 2 leaf cases + 6 middle man cases make a total of 14 cases in total.  :)


    //======================================EMPTY CASE==============================
    //empty tree
    if (root == nullptr) {
        cout << "Empty Tree" << endl;
        return nullptr;
    }
    //======================================ROOT CASES==============================
    
    sNode* nodeToRemove = this->isInDB(aName);
    //Is the root a leaf?
    if (!nodeToRemove->getParent() && !nodeToRemove->getLeftChild() && !nodeToRemove->getRightChild()) {
        root = nullptr;
        return nullptr;
    }
    //Does the root only have a left child?
    else if (!nodeToRemove->getParent() && !nodeToRemove->getRightChild() && nodeToRemove->getLeftChild()) {
        nodeToRemove = nodeToRemove->getLeftChild();
        nodeToRemove->setParent(nullptr);
        nodeToRemove->setHeight(1);
        root = nodeToRemove;
        return root;
    }
    //Does the root only have a right child?
    else if (!nodeToRemove->getParent() && nodeToRemove->getRightChild() && !nodeToRemove->getLeftChild()) {
        nodeToRemove = nodeToRemove->getRightChild();
        nodeToRemove->setParent(nullptr);
        nodeToRemove->setHeight(1);
        root = nodeToRemove;
        return root;
    }
    //Does the root have two children AND does the root's left child NOT contain a right child?
    else if (!nodeToRemove->getParent() && nodeToRemove->getRightChild() && nodeToRemove->getLeftChild() && !nodeToRemove->getLeftChild()->getRightChild()) {
        //preserveNode == replacementNodeNewRChild
        sNode* replacementNode = nodeToRemove->getLeftChild();
        sNode* preserveNode = nodeToRemove->getRightChild();

        replacementNode->setRightChild(preserveNode);
        preserveNode->setParent(replacementNode);
        replacementNode->setParent(nullptr);

        replacementNode->correctHeightRemove();
        root = replacementNode->doTheRotation();
        return root;

    }
    //Does the root have two children AND the roots left child DOES HAVE a right child?
    else if (!nodeToRemove->getParent() && nodeToRemove->getRightChild() && nodeToRemove->getLeftChild()) {
        //could be in method...
        sNode* replacementNode = nodeToRemove->getLeftChild();
        sNode* replacementNodeNewRChild = nodeToRemove->getRightChild();
        sNode* preserveNode = replacementNode->getRightChild();
        sNode* preserveNodeNewParent = replacementNodeNewRChild;
        while (preserveNodeNewParent->getLeftChild()) {
            preserveNodeNewParent = preserveNodeNewParent->getLeftChild();
        }
        preserveNode->setParent(preserveNodeNewParent);
        preserveNodeNewParent->setLeftChild(preserveNode);
        replacementNode->setRightChild(replacementNodeNewRChild);
        replacementNodeNewRChild->setParent(replacementNode);
        replacementNode->setParent(nullptr);

        //preserve node ends up being lowest node after pointer manipulations
        while (preserveNode) {
            preserveNode->correctHeightRemove();
            preserveNode = preserveNode->doTheRotation();

            if (preserveNode->getParent()) {
                preserveNode = preserveNode->getParent();
            }
            else {
                break;
            }
        }

        return preserveNode;
    }
    //======================================WHAT CHILD IS THIS?==============================
    char child = ' ';
    if (nodeToRemove->getParent()->getLeftChild() == nodeToRemove) {
        child = 'L';
    }
    else if (nodeToRemove->getParent()->getRightChild() == nodeToRemove) {
        child = 'R';
    }
    else {
        //this should never run plz ;)
        child = '*';
        cout << "Child error" << endl;
        exit(30);
    }
    //======================================LEAF CASES==============================
    //Does the leaf have no children (def), have a parent, and is the left child?
    if (!nodeToRemove->getLeftChild() && !nodeToRemove->getRightChild() && nodeToRemove->getParent() && child == 'L') {
        sNode* leafParent = nodeToRemove->getParent();
        leafParent->setLeftChild(nullptr);

        while (leafParent) {
            leafParent->correctHeightRemove();
            if (leafParent->getParent()) {
                leafParent = leafParent->doTheRotationNotOnRoot();
            }
            else if (!leafParent->getParent()) {
                leafParent = leafParent->doTheRotation();
            }
            if (leafParent->getParent()) {
                leafParent = leafParent->getParent();
            }
            else {
                break;
            }
        }
        return leafParent;
    }
    //Does the leaf have no children (def), have a parent, and is the right child?
    else if (!nodeToRemove->getLeftChild() && !nodeToRemove->getRightChild() && nodeToRemove->getParent() && child == 'R') {
        sNode* leafParent = nodeToRemove->getParent();
        leafParent->setRightChild(nullptr);
        
        while (leafParent) {
            leafParent->correctHeightRemove();
            if (leafParent->getParent()) {
                leafParent = leafParent->doTheRotationNotOnRoot();
            }
            else {
                leafParent = leafParent->doTheRotation();
            }
            if (leafParent->getParent()) {
                leafParent = leafParent->getParent();
            }
            else {
                break;
            }
        }
        return leafParent;
    }
    //======================================Middle-Man Cases==============================

    //middle man scenario in which he has both children AND a parent (def) AND middle man is a left child 
    if (nodeToRemove->getLeftChild() && nodeToRemove->getRightChild() && nodeToRemove->getParent() && child == 'L') {
        root = nodeToRemove->bothChildrenIsLeftChild();
        return root;
    }
    //middle man scenario in which he has only a right child AND a parent (def) AND middle man is a left child 
    else if (!nodeToRemove->getLeftChild() && nodeToRemove->getRightChild() && nodeToRemove->getParent() && child == 'L') {
        root = nodeToRemove->onlyRightChildIsIsLeftChild();
        return root;
    }
    //middle man scenario in which he has only a left AND a parent (def) AND middle man is a left child 
    else if (nodeToRemove->getLeftChild() && !nodeToRemove->getRightChild() && nodeToRemove->getParent() && child == 'L') {
        root = nodeToRemove->onlyLeftChildIsLeftChild();
        return root;
    }
    //middle man scenario in which he has both children AND a parent (def) AND middle man is a right child
    else if (nodeToRemove->getLeftChild() && nodeToRemove->getRightChild() && nodeToRemove->getParent() && child == 'R') {
        root = nodeToRemove->bothChildrenIsRightChild();
        return root;
    }
    //middle man scenario in which he has only a right child AND a parent (def) AND middle man is a right child 
    else if (!nodeToRemove->getLeftChild() && nodeToRemove->getRightChild() && nodeToRemove->getParent() && child == 'R') {
        root = nodeToRemove->onlyRightChildIsIsRightChild();
        return root;
    }
    //middle man scenario in which he has only a left child AND a parent (def) AND middle man is a right child 
    else if (nodeToRemove->getLeftChild() && !nodeToRemove->getRightChild() && nodeToRemove->getParent() && child == 'R') {
        root = nodeToRemove->onlyLeftChildIsRightChild();
        return root;
    }
    return nullptr;
}

DRT SDB::modify(string key, string data)
{
    DRT changeMe = { "", "", "" };

    sNode* aStudent = this->isInDB(key);

    if (key == "")
    {
        cout << "Error Message: Tried to Delete Student that DNE" << endl;
        cout << "Could not find " << aStudent->getName() << " was ";
        if (aStudent == nullptr) cout << "NULLPTR" << endl;
        return search(key);
    }
    else if (key != "" && !aStudent && data == "")
    {
        cout << "Error Message: Tried to Delete Student that DNE" << endl;
        cout << "Could not find " << aStudent->getName() << " was ";
        if (aStudent == nullptr) cout << "NULLPTR" << endl;
        return search(key);
    }
    else if (key != "" && !aStudent && data != "")
    {
        cout << "Added " << key << endl;

        changeMe = search(key);
        add(key, data);

        //cout << "root @ " << root->getHeight() << " w/ " << root->getName() << endl;
        return changeMe;
        // add a new node to the avl tree
    }
    else if (aStudent && data == "" && key != "")
    {
        // remove key from database
        cout << "Removed " << key << endl;
        changeMe = { aStudent->findNext(aStudent->getName()), aStudent->findPrev(aStudent->getName()), aStudent->getGrade() };
        root = remove(key);

        //cout << "root @ " << root->getHeight() << " w/ " << root->getName() << endl;
        return changeMe;
    }
    else if (aStudent && data != "")
    {
        cout << "Changing " << key << "'s grade" << endl;
        aStudent->setGrade(data);
        return DRT(aStudent->findNext(aStudent->getName()), aStudent->findPrev(aStudent->getName()), aStudent->getGrade());
    }
    else
    {
        cout << "Error - from modify()";
        exit(0);
    }
    return changeMe;
}

sNode* SDB::isInDB(string name)
{
    sNode* temp = root;

    if (temp->getName() == name)
    {
        return temp;
    }

    while (temp != nullptr)
    {
        if (temp->getName() > name)
        {
            temp = temp->getLeftChild();
        }
        else if (temp->getName() < name)
        {
            temp = temp->getRightChild();
        }
        else
        {
            return temp;
        }
    }
    return nullptr;
}

void SDB::add(string aName, string aGrade)
{
    sNode* aStudent = new sNode(aName, aGrade);

    sNode* temp = root;

    // BASE CASES:
    // adding to empty tree
    // adding children to root

    // empty tree
    if (!root)
    {
        root = aStudent;
        return;
    }

    // we only have a right child and we need to go left
    else if (!root->getLeftChild() && aName < root->getName())
    {
        aStudent->setParent(root);
        root->setLeftChild(aStudent);
        root->setHeight(root->getHeight() + 1);
    }

    // only have a left child and we need to go right
    else if (!root->getRightChild() && aName > root->getName())
    {
        aStudent->setParent(root);
        root->setRightChild(aStudent);
        root->setHeight(root->getHeight() + 1);
    }

    else
    {
        // first go down the tree until we get to a node whose child is nullptr and that nullptr is where we want to add the node
        while (temp)
        {
            // this takes us to the node that we will add a new child too
            if (aStudent->getName() > temp->getName() && temp->getRightChild())
            {
                if (temp->getRightChild()->getHeight() >= temp->getLeftChild()->getHeight())
                {
                    temp->setHeight(temp->getHeight() + 1);
                }
                temp = temp->getRightChild();
            }
            else if (aStudent->getName() < temp->getName() && temp->getLeftChild())
            {
                if (temp->getLeftChild()->getHeight() >= temp->getRightChild()->getHeight())
                {
                    temp->setHeight(temp->getHeight() + 1);
                }
                temp = temp->getLeftChild();
            }
            else
            {
                break;
            }
        }

        // then // add it
        if (aStudent->getName() > temp->getName())
        {
            aStudent->setParent(temp);
            temp->setRightChild(aStudent);
            temp->setHeight(temp->getHeight() + 1);
        }

        else if (aStudent->getName() < temp->getName())
        {
            aStudent->setParent(temp);
            temp->setLeftChild(aStudent);
            temp->setHeight(temp->getHeight() + 1);
        }
    }

    // weve added the node and now we need to go back up and change the height, we are also dealing with latter 2 base case

    // check the height

    // ===================== GOING UP, CORRECT HEIGHT ========================
    while (temp)
    {
        bool heightIsCorrect = temp->checkHeight();
        if (!heightIsCorrect)
        {
            temp->setHeight(temp->getHeight() - 1);
        }

        string nodeCondition = temp->nodeIsBalanced();
        sNode* tempParent = nullptr;
        char child = ' ';

        if (nodeCondition == "L")
        {
            tempParent = temp->getParent();
            temp->setParent(nullptr);

            if (tempParent)
            {
                if (temp->getName() > tempParent->getName())
                {
                    tempParent->setRightChild(nullptr);
                    child = 'R';
                }
                else if (temp->getName() < tempParent->getName())
                {
                    tempParent->setLeftChild(nullptr);
                    child = 'L';
                }
            }
            else
            {
                // cout << "We're dealing with a root" << endl;
                child = '~';
            }

            //===========================
            // cout << "Performing Right Rotation on " + temp->getName() + " " << endl;
            temp = temp->rightRotation();
            //===========================

            // ========== RECONNECTING NODES ==========
            temp->setParent(tempParent);
            if (tempParent)
            {
                if (child == 'R')
                {
                    tempParent->setRightChild(temp);
                    temp->setParent(tempParent);
                    root = temp->reconnectNodes(temp); // error possible here
                    break;
                }
                else if (child == 'L')
                {
                    tempParent->setLeftChild(temp);
                    temp->setParent(tempParent);
                    root = temp->reconnectNodes(temp); // error possible here
                    break;
                }
                else if (child == '~')
                {
                    // cout << "we are root" << endl;
                    root = temp->reconnectNodes(temp); // error possible here
                    break;
                }
            }
        }

        else if (nodeCondition == "R")
        {
            tempParent = temp->getParent();
            temp->setParent(nullptr);

            if (tempParent)
            {
                if (temp->getName() > tempParent->getName())
                {
                    tempParent->setRightChild(nullptr);
                    child = 'R';
                }
                else if (temp->getName() < tempParent->getName())
                {
                    tempParent->setLeftChild(nullptr);
                    child = 'L';
                }
            }
            else
            {
                // cout << "We're dealing with a root" << endl;
                child = '~';
            }

            //================================================
            // cout << "Performing Left Rotation on " + temp->getName() + " " << endl;
            temp = temp->leftRotation();
            //================================================

            // ========== RECONNECTING NODES ==========
            temp->setParent(tempParent);
            if (tempParent)
            {
                if (child == 'R')
                {
                    tempParent->setRightChild(temp);
                    temp->setParent(tempParent);
                    root = temp->reconnectNodes(temp); // error possible here
                    break;
                }
                else if (child == 'L')
                {
                    tempParent->setLeftChild(temp);
                    temp->setParent(tempParent);
                    root = temp->reconnectNodes(temp); // error possible here
                    break;
                }
                else if (child == '~')
                {
                    // cout << "we are root" << endl;
                    root = temp->reconnectNodes(temp); // error possible here
                    break;
                }
            }
        }
        else if (nodeCondition == "LR")
        {
            tempParent = temp->getParent();
            temp->setParent(nullptr);

            if (tempParent)
            {
                if (temp->getName() > tempParent->getName())
                {
                    tempParent->setRightChild(nullptr);
                    child = 'R';
                }
                else if (temp->getName() < tempParent->getName())
                {
                    tempParent->setLeftChild(nullptr);
                    child = 'L';
                }
            }
            else
            {
                // cout << "We're dealing with a root" << endl;
                child = '~';
            }

            //==============================
            // cout << "Performing Left-Right Rotation on " + temp->getName() + " " << endl;
            temp = temp->leftRightRotation();
            //==============================

            // ========== RECONNECTING NODES ==========
            temp->setParent(tempParent);

            if (tempParent)
            {
                if (child == 'R')
                {
                    tempParent->setRightChild(temp);
                    temp->setParent(tempParent);
                    root = temp->reconnectNodes(temp); // error possible here
                    break;
                }
                else if (child == 'L')
                {
                    tempParent->setLeftChild(temp);
                    temp->setParent(tempParent);
                    root = temp->reconnectNodes(temp); // error possible here
                    break;
                }
                else if (child == '~')
                {
                    // cout << "we are root" << endl;
                    root = temp->reconnectNodes(temp); // error possible here
                    break;
                }
            }
        }

        else if (nodeCondition == "RL")
        {
            tempParent = temp->getParent();
            temp->setParent(nullptr);

            if (tempParent)
            {
                if (temp->getName() > tempParent->getName())
                {
                    tempParent->setRightChild(nullptr);
                    child = 'R';
                }
                else if (temp->getName() < tempParent->getName())
                {
                    tempParent->setLeftChild(nullptr);
                    child = 'L';
                }
            }
            else
            {
                // cout << "We're dealing with a root" << endl;
                child = '~';
            }
            //=============================
            // cout << "Performing Right-Left Rotation on " + temp->getName() + " " << endl;
            temp = temp->rightLeftRotation();
            //=============================

            // ========== RECONNECTING NODES ==========
            temp->setParent(tempParent);

            if (tempParent)
            {
                if (child == 'R')
                {
                    tempParent->setRightChild(temp);
                    temp->setParent(tempParent);
                    root = temp->reconnectNodes(temp); // error possible here
                    break;
                }
                else if (child == 'L')
                {
                    tempParent->setLeftChild(temp);
                    temp->setParent(tempParent);
                    root = temp->reconnectNodes(temp); // error possible here
                    break;
                }
                else if (child == '~')
                {
                    // cout << "we are root" << endl;
                    root = temp->reconnectNodes(temp); // error possible here
                    break;
                }
            }
        }
        else if (nodeCondition == "==")
        {
            // cout << "was balanced, no need for rotation"
            //<< " @ " << temp->getName() << endl;
        }
        if (temp->getParent())
        {
            temp = temp->getParent();
        }
        else
        {
            root = temp;
            break;
        }
        // make sure parent is always one bigger than its larges childs height
    }
}

void SDB::display()
{
    root->display(root, 1);
}

void SDB::printAscending()
{
    if (root != nullptr)
    {
        root->printAscending();
        cout << '\b' << '\b' << ' ' << endl;
    }
    else
    {
        cout << "Empty Tree" << endl;
    }
}

void SDB::printDescending()
{
    if (root != nullptr)
    {
        root->printDescending();
        cout << '\b' << '\b' << ' ' << endl;
    }
    else
    {
        cout << "Empty Tree" << endl;
    }
}

int SDB::countNodes(sNode* aNode)
{
    if (aNode == nullptr)
    {
        return 0;
    }
    return 1 + countNodes(aNode->getLeftChild()) + countNodes(aNode->getRightChild());
}

string SDB::findPrev(string target)
{
    sNode* targetNode = isInDB(target);
    return targetNode->findPrev(target);
}

string SDB::findNext(string target)
{
    sNode* targetNode = isInDB(target);
    return targetNode->findNext(target);
}

/*
char SDB::findLargestChild() {
    return this->findLargestChild();
}
*/