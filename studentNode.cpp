#include "studentNode.h"

int max(int a, int b)
{
    return (a > b) ? a : b;
}

sNode::sNode(string aName, string aGrade)
{
    name = aName;
    grade = aGrade;
    height = 1;
    leftChild = nullptr;
    rightChild = nullptr;
    parent = nullptr;
}

sNode::sNode()
{
    name = "";
    grade = "";
    height = 1;
    leftChild = nullptr;
    rightChild = nullptr;
    parent = nullptr;
}

// checks height of the biggest child, and if we are strictly 1 greater than that, then return true, else return false
// if false, decrement height in SDB, else we done fam
bool sNode::checkHeight()
{
    if (this->getHeight() <= 1)
    {
        return true;
    }

    if (this->getRightChild()->getHeight() > this->getLeftChild()->getHeight())
    {
        if (this->getHeight() == this->getRightChild()->getHeight() + 1)
        {
            return true;
        }
    }
    else if (this->getRightChild()->getHeight() < this->getLeftChild()->getHeight())
    {
        if (this->getHeight() == this->getLeftChild()->getHeight() + 1)
        {
            return true;
        }
    }
    else if (this->getRightChild()->getHeight() == this->getLeftChild()->getHeight())
    {
        if (this->getHeight() == this->getLeftChild()->getHeight() + 1)
        {
            return true;
        }
    }

    return false;
}

sNode* sNode::reconnectNodes(sNode* aNode)
{
    while (aNode)
    {
        if (aNode->getParent())
        {
            aNode = aNode->getParent();
            aNode->correctHeight();
        }
        else
        {
            break;
        }

        if (!aNode->getParent())
        {
            break;
        }
    }
    return aNode;
}

string sNode::nodeIsBalanced() // didn't better name for this
{
    int dif = this->getLeftChild()->getHeight() - this->getRightChild()->getHeight();

    bool isBalanced = abs(dif) <= 1;

    sNode* greatestChild = nullptr;
    sNode* greatestGrandChild = nullptr;
    char preference = ' ';

    if (this->leftChild->getHeight() > this->rightChild->getHeight())
    {
        greatestChild = leftChild;
        preference = 'L';
    }
    else if (this->leftChild->getHeight() < this->rightChild->getHeight())
    {
        greatestChild = rightChild;
        preference = 'R';
    }
    else
    {
        return "==";
    }

    if (greatestChild->getLeftChild()->getHeight() > greatestChild->getRightChild()->getHeight())
    {
        greatestGrandChild = greatestChild->getLeftChild();
    }
    else if (greatestChild->getLeftChild()->getHeight() < greatestChild->getRightChild()->getHeight())
    {
        greatestGrandChild = greatestChild->getRightChild();
    }
    else if (greatestChild->getLeftChild()->getHeight() == greatestChild->getRightChild()->getHeight() && preference == 'R')
    {
        greatestGrandChild = greatestChild->getRightChild();
    }
    else if (greatestChild->getLeftChild()->getHeight() == greatestChild->getRightChild()->getHeight() && preference == 'L')
    {
        greatestGrandChild = greatestChild->getLeftChild();
    }
    else
    {
        cout << "Error in finding greatest grandchild" << endl;
        exit(0);
    }

    // left-right rotation needed
    if (this->getLeftChild() && greatestChild == this->getLeftChild() && (this->getLeftChild()->getRightChild() && greatestGrandChild == this->getLeftChild()->getRightChild() && !isBalanced))
    {
        return "LR";
    }
    // right left rotation needed
    else if (this->getRightChild() && greatestChild == this->getRightChild() && (this->getRightChild()->getLeftChild() && greatestGrandChild == this->getRightChild()->getLeftChild() && !isBalanced))
    {
        return "RL";
    }
    // right heavy -> left rotation needed
    else if (this->getLeftChild()->getHeight() < this->getRightChild()->getHeight() && !isBalanced)
    {
        return "R";
    }
    // left heavy -> right rotation needed
    else if (this->getLeftChild()->getHeight() > this->getRightChild()->getHeight() && !isBalanced)
    {
        return "L";
    }
    // children are equal height or parent node is balanced
    else if (this->getLeftChild()->getHeight() == this->getRightChild()->getHeight() || isBalanced)
    {
        return "==";
    }
    else
    {
        return "@(*_*)@"; // oo oo uh oh
    }
}

char sNode::leftOrRightChild()
{
    if (this->getParent()->getRightChild() == this)
    {
        return 'R';
    }
    else
    {
        return 'L';
    }

    return ' ';

}

sNode* sNode::doTheRotation()
{
    if (this->nodeIsBalanced() == "L")
    {
        // sNode *tempParent = this->getParent();

        this->setParent(nullptr);

        return this->rightRotation();
    }
    else if (this->nodeIsBalanced() == "R")
    {
        // sNode *tempParent = this->getParent();

        this->setParent(nullptr);

        return this->leftRotation();
    }
    else if (this->nodeIsBalanced() == "LR")
    {
        // sNode *tempParent = this->getParent();

        this->setParent(nullptr);

        return this->leftRightRotation();
    }
    else if (this->nodeIsBalanced() == "RL")
    {
        // sNode *tempParent = this->getParent();
        this->setParent(nullptr);

        return this->rightLeftRotation();
    }

    return this;
}

sNode* sNode::doTheRotationNotOnRoot() {
    sNode* savedParent = this->getParent();

    char child = ' ';
    if (savedParent->getLeftChild() == this) {
        child = 'L';
        savedParent->setLeftChild(nullptr);
    }
    else if (savedParent->getRightChild() == this) {
        child = 'R';
        savedParent->setRightChild(nullptr);
    }
    else {
        exit(30);
    }

    this->setParent(nullptr);


    
    if (this->nodeIsBalanced() == "L")
    {
        // sNode *tempParent = this->getParent();

        sNode* rotateNode = this;
        rotateNode = this->rightRotation();
        if (child == 'L') {
            savedParent->setLeftChild(rotateNode);
        }
        else if (child == 'R') {
            savedParent->setRightChild(rotateNode);
        }

        rotateNode->setParent(savedParent);
        return rotateNode;
        
    }
    else if (this->nodeIsBalanced() == "R")
    {
        // sNode *tempParent = this->getParent();

        sNode* rotateNode = this;
        rotateNode = this->leftRotation();
        if (child == 'L') {
            savedParent->setLeftChild(rotateNode);
        }
        else if (child == 'R') {
            savedParent->setRightChild(rotateNode);
        }

        rotateNode->setParent(savedParent);
        return rotateNode;
    }
    else if (this->nodeIsBalanced() == "LR")
    {
        // sNode *tempParent = this->getParent();
        sNode* rotateNode = this;
        rotateNode = this->leftRightRotation();
        if (child == 'L') {
            savedParent->setLeftChild(rotateNode);
        }
        else if (child == 'R') {
            savedParent->setRightChild(rotateNode);
        }

        rotateNode->setParent(savedParent);
        return rotateNode;
    }
    else if (this->nodeIsBalanced() == "RL")
    {
        // sNode *tempParent = this->getParent();
        sNode* rotateNode = this;
        rotateNode = this->rightLeftRotation();

        if (child == 'L') {
            savedParent->setLeftChild(rotateNode);
        }
        else if (child == 'R') {
            savedParent->setRightChild(rotateNode);
        }

        rotateNode->setParent(savedParent);
        return rotateNode;
        
    }
    if (child == 'L') {
        savedParent->setLeftChild(this);
    }
    else if (child == 'R') {
        savedParent->setRightChild(this);
    }

    this->setParent(savedParent);
    return this;
}

sNode* sNode::rightRotation()
{
    if (this->getParent())
    {
        this->getParent()->setHeight(this->getHeight()); // experimental
    }

    sNode* nodeRotatingAbout = this->getLeftChild();
    sNode* leftRightGrandChild = nodeRotatingAbout->rightChild;

    nodeRotatingAbout->rightChild = this;
    this->leftChild->rightChild = this;

    if (leftRightGrandChild)
    {
        leftRightGrandChild->setParent(this);
    }

    this->leftChild = leftRightGrandChild;

    // beware of oo oo uh oh for height
    this->height = max(this->leftChild->getHeight(), this->rightChild->getHeight()) + 1;
    nodeRotatingAbout->height = max(nodeRotatingAbout->leftChild->getHeight(), nodeRotatingAbout->rightChild->getHeight()) + 1;

    nodeRotatingAbout->parent = this->getParent(); // experimental

    if (nodeRotatingAbout->getLeftChild())
        nodeRotatingAbout->getLeftChild()->setParent(nodeRotatingAbout);

    if (nodeRotatingAbout->getRightChild())
        nodeRotatingAbout->getRightChild()->setParent(nodeRotatingAbout);

    return nodeRotatingAbout;
}

sNode* sNode::leftRotation()
{
    if (this->getParent())
    {
        this->getParent()->setHeight(this->getHeight()); // experimental
    }

    sNode* nodeRotatingAbout = this->rightChild;
    sNode* rightLeftGrandChild = nodeRotatingAbout->leftChild;

    nodeRotatingAbout->leftChild = this;
    this->rightChild->leftChild = this;

    if (rightLeftGrandChild)
    {
        rightLeftGrandChild->setParent(this);
    }

    this->rightChild = rightLeftGrandChild;

    this->height = max(this->leftChild->getHeight(), this->rightChild->getHeight()) + 1;
    nodeRotatingAbout->height = max(nodeRotatingAbout->leftChild->getHeight(), nodeRotatingAbout->rightChild->getHeight()) + 1;

    nodeRotatingAbout->parent = this->getParent(); // experimental

    if (nodeRotatingAbout->getLeftChild())
        nodeRotatingAbout->getLeftChild()->setParent(nodeRotatingAbout);

    if (nodeRotatingAbout->getRightChild())
        nodeRotatingAbout->getRightChild()->setParent(nodeRotatingAbout);

    // check for height and handle here
    // if noderotatingabout->parent->height != largestChildHeight+1
            // noderotatingabout->parent->height = largestChildHeight+1

    return nodeRotatingAbout; // if we add return nodeRotatingAbout -> sNode;
}

sNode* sNode::leftRightRotation()
{
    this->leftChild = this->leftChild->leftRotation();

    return this->rightRotation();
}

sNode* sNode::rightLeftRotation()
{
    this->rightChild = this->rightChild->rightRotation();

    return this->leftRotation();
}

void sNode::display(sNode* aNode, int pos)
{
    if (aNode)
    {
        cout << aNode->name << ", " << aNode->grade << " @ " << aNode->height << endl;
        if (aNode->rightChild == nullptr && aNode->leftChild == nullptr)
            return;
        cout << '|';
        for (int i = 0; i < pos; i++)
            cout << ' ';
        cout << "|_";
        display(aNode->rightChild, pos + 1);
        cout << '|';
        for (int i = 0; i < pos; i++)
            cout << ' ';
        cout << "|_";
        display(aNode->leftChild, pos + 1);
    }
    else
    {
        cout << '\b' << endl;
    }
}

void sNode::setName(string val)
{
    name = val;
}

void sNode::setGrade(string val)
{
    grade = val;
}

void sNode::setParent(sNode* aStudent)
{
    if (this == nullptr) {
        return;
    }
    parent = aStudent;
}

void sNode::setLeftChild(sNode* aStudent)
{
    leftChild = aStudent;
}

void sNode::setRightChild(sNode* aStudent)
{
    rightChild = aStudent;
}

void sNode::setHeight(int val)
{
    if (!this)
    {
        height = 0;
    }
    else
    {
        height = val;
    }
}

sNode* sNode::getRightChild()
{
    return rightChild;
}

sNode* sNode::getLeftChild()
{
    return leftChild;
}

sNode* sNode::getParent()
{
    return parent;
}

int sNode::getHeight()
{
    if (this)
    {
        return height;
    }
    return 0;
}

string sNode::getName()
{
    if (this)
    {
        return name;
    }
    return "";
}

string sNode::getGrade()
{
    if (this)
    {
        return grade;
    }

    return "";
}

void sNode::correctHeight()
{
    if (this->getLeftChild()->getHeight() < this->getRightChild()->getHeight())
    {
        this->setHeight(this->getRightChild()->getHeight() + 1);
    }
    else if (this->getLeftChild()->getHeight() > this->getRightChild()->getHeight())
    {
        this->setHeight(this->getLeftChild()->getHeight() + 1);
    }
    else if (this->getLeftChild()->getHeight() == this->getRightChild()->getHeight())
    {
        this->setHeight(this->getLeftChild()->getHeight() + 1);
    }
}

// still need root->print in SDB

void sNode::printAscending()
{
    if (leftChild)
    {
        leftChild->printAscending();
    }
    cout << name << " @ " << height << endl;
    if (rightChild)
    {
        rightChild->printAscending();
    }
    // here, delete the last comma
    /*
    if (!leftChild && !rightChild) {
        cout << '\b' << '\b';
    }
    */
}

void sNode::printDescending()
{
    if (rightChild)
    {
        rightChild->printDescending();
    }
    cout << name << ", ";
    if (leftChild)
    {
        leftChild->printDescending();
    }
    // here, delete the last comma
    // cout << endl;
}



string sNode::findPrev(string target)
{
    // return "";
    sNode* closestPrevFinder = this;
    string prev = "";

    // if tree is empty
    if (closestPrevFinder == nullptr)
    {
        return "";
    }

    // if the tree is just a root
    if (closestPrevFinder->getLeftChild() == nullptr && closestPrevFinder->getRightChild() == nullptr && closestPrevFinder->getParent() == nullptr)
    {
        return "";
    }

    // to find the previous, go left one, all the way right
    if (closestPrevFinder->getLeftChild())
    {
        closestPrevFinder = closestPrevFinder->getLeftChild();

        // while we can go right, go right
        while (closestPrevFinder->getRightChild())
        {
            closestPrevFinder = closestPrevFinder->getRightChild();
        }
        return closestPrevFinder->getName();
    }
    // we have no right child therefore, what child node r we?
    else
    {
        sNode* tracker = closestPrevFinder;
        if (closestPrevFinder->getParent())
        {
            closestPrevFinder = closestPrevFinder->getParent();
        }
        else
        {
            // there is no left, so prev is ""

            return "";
        }

        // are we trying to find the prev a left child?
        if (closestPrevFinder->getLeftChild() == tracker)
        {
            // try going up until we find something smaller than us
            // if we hit root, return the tracker, which was the bottom/left node we started going upward on

            // while we have a parent
            while (closestPrevFinder->getParent())
            {

                if (closestPrevFinder->getName() < tracker->getName() && prev == "")
                {
                    tracker = closestPrevFinder;
                    prev = closestPrevFinder->getName();
                }
                if (closestPrevFinder->getName() > prev && prev != "" && closestPrevFinder->getName() < target)
                {
                    tracker = closestPrevFinder;
                    prev = closestPrevFinder->getName();
                }
                // go up
                closestPrevFinder = closestPrevFinder->getParent();
            }
            // we are root, is root the prev
            if (closestPrevFinder->getName() < tracker->getName() && prev == "")
            {
                // LOLOLOLOLO
                tracker = closestPrevFinder;
                prev = closestPrevFinder->getName();
            }
            if (closestPrevFinder->getName() > prev && prev != "" && closestPrevFinder->getName() < target)
            {
                tracker = closestPrevFinder;
                prev = closestPrevFinder->getName();
            }
            return prev;
        }
        // are we trying to find the prev a right child?
        else if (closestPrevFinder->getRightChild() == tracker)
        {
            return closestPrevFinder->getName();
        }
    }
    return "We failed finding previous";
}

string sNode::findNext(string target)
{
    sNode* closestNextFinder = this;
    string next = "";

    // if tree is empty
    if (closestNextFinder == nullptr)
    {
        return "";
    }

    // if the tree is just a root
    if (closestNextFinder->getLeftChild() == nullptr && closestNextFinder->getRightChild() == nullptr && closestNextFinder->getParent() == nullptr)
    {
        return "";
    }

    // to find the next, go right one, all the way left
    if (closestNextFinder->getRightChild())
    {
        closestNextFinder = closestNextFinder->getRightChild();

        // while we can go left, go left
        while (closestNextFinder->getLeftChild())
        {
            closestNextFinder = closestNextFinder->getLeftChild();
        }
        return closestNextFinder->getName();
    }
    // we have no right child therefore, what child node r we?
    else
    {
        sNode* tracker = closestNextFinder;
        if (closestNextFinder->getParent())
        {
            closestNextFinder = closestNextFinder->getParent();
        }
        else
        {
            // there is no right child, so next is ""
            return "";
        }

        // are we trying to find the next of a right child?
        if (closestNextFinder->getRightChild() == tracker)
        {
            // try going up until we find something smaller than us
            // if we hit root, return the tracker, which was the bottom/left node we started going upward on

            // while we have a parent
            while (closestNextFinder->getParent())
            {

                if (closestNextFinder->getName() > tracker->getName() && next == "")
                {
                    tracker = closestNextFinder;
                }
                if (closestNextFinder->getName() < next && next != "" && closestNextFinder->getName() > target)
                {
                    tracker = closestNextFinder;
                }
                // go up
                closestNextFinder = closestNextFinder->getParent();
            }
            // we are root, is root the next?
            if (closestNextFinder->getName() > tracker->getName() && next == "")
            {
                tracker = closestNextFinder;
                next = closestNextFinder->getName();
            }
            if (closestNextFinder->getName() < next && next != "" && closestNextFinder->getName() > target)
            {
                tracker = closestNextFinder;
                next = closestNextFinder->getName();
            }
            return next;
        }
        // are we trying to find the prev a left child?
        else if (closestNextFinder->getLeftChild() == tracker)
        {
            return closestNextFinder->getName();
        }
    }
    return "We failed finding previous";
}

/*
char sNode::findLargestChild() {
    if (this->getRightChild()->getHeight() > this->getLeftChild()->getHeight()) {
        return 'R';
    }
    else if (this->getRightChild()->getHeight() < this->getLeftChild()->getHeight()) {
        return 'L';
    }
    else if (this->getRightChild()->getHeight() == this->getLeftChild()->getHeight()) {
        return '~';
    }
    else {
        cout << "Error in findLargestChild, sNode" << endl;
        return '@';
    }
}
*/

void sNode::correctHeightRemove()
{
    int largestChildHeight = 0;
    bool once = true;
    if (this->getRightChild()->getHeight() > this->getLeftChild()->getHeight())
    {
        largestChildHeight = this->getRightChild()->getHeight();
    }
    else if (this->getRightChild()->getHeight() < this->getLeftChild()->getHeight())
    {
        largestChildHeight = this->getLeftChild()->getHeight();
    }
    else
    {
        largestChildHeight = this->getLeftChild()->getHeight();
    }
    //second bool cond means that parent node height ain't larger than its kiddo
    while (this->getHeight() != largestChildHeight + 1 && this->getHeight() >= largestChildHeight)
    {
        // cout << "~: " << LNTP_PAR->getHeight() << ", L: " << LNTP_PAR->getLeftChild()->getHeight() << ", R: " << LNTP_PAR->getRightChild()->getHeight() << endl;
        this->setHeight(largestChildHeight + 1);
        once = false;
    }

    //if the parents height is bigger
    while (this->getHeight() != largestChildHeight + 1 && once)
    {
        // cout << "~: " << LNTP_PAR->getHeight() << ", L: " << LNTP_PAR->getLeftChild()->getHeight() << ", R: " << LNTP_PAR->getRightChild()->getHeight() << endl;
        this->setHeight(largestChildHeight + 1);
    }
}

/*
int sNode::whatever() {
    int total = 0;
    if (right) {
        total += right->whatever();
    }
    if (left) {
        toal + left->whatever;
        if (color)total -= key;
        else total += key;
        return total;
    }
}
*/

sNode* sNode::bothChildrenIsLeftChild() {
    sNode* replacementNode = this->getLeftChild();
    sNode* replacementNodeRightChild = replacementNode->getRightChild();
    sNode* nodeToProtect = this->getRightChild();
    sNode* replacementNodeRightChildsNewParent = nodeToProtect;
    sNode* replacementNodesNewParent = this->getParent();

    while (replacementNodeRightChildsNewParent->getLeftChild()) {
        replacementNodeRightChildsNewParent = replacementNodeRightChildsNewParent->getLeftChild();
    }

    //all ptrs set, now ptr manipulations
    replacementNodeRightChild->setParent(replacementNodeRightChildsNewParent);
    replacementNodeRightChildsNewParent->setLeftChild(replacementNodeRightChild);
    replacementNode->setParent(replacementNodesNewParent);
    replacementNodesNewParent->setLeftChild(replacementNode);
    replacementNode->setRightChild(nodeToProtect);
    nodeToProtect->setParent(replacementNode);
    this->setParent(nullptr);
    this->setLeftChild(nullptr);
    this->setRightChild(nullptr);
    
    if (replacementNodeRightChild) {
        while (replacementNodeRightChild) {
            replacementNodeRightChild->correctHeightRemove();

            if (replacementNodeRightChild->getParent()) {
                replacementNodeRightChild = replacementNodeRightChild->doTheRotationNotOnRoot();
            }
            else if (!replacementNodeRightChild->getParent()) {
                replacementNodeRightChild = replacementNodeRightChild->doTheRotation();
            }


            if (replacementNodeRightChild->getParent()) {
                replacementNodeRightChild = replacementNodeRightChild->getParent();
            }
            else {
                break;
            }
        }
        return replacementNodeRightChild;
    }
    else {
        while (replacementNode) {
            replacementNode->correctHeightRemove();

            if (replacementNode->getParent()) {
                replacementNode = replacementNode->doTheRotationNotOnRoot();
            }
            else if (!replacementNode->getParent()) {
                replacementNode = replacementNode->doTheRotation();
            }


            if (replacementNode->getParent()) {
                replacementNode = replacementNode->getParent();
            }
            else {
                break;
            }
        }
        return replacementNode;
    }
    return nullptr;
}

sNode* sNode::onlyRightChildIsIsLeftChild() {
    sNode* replacementNode = this->getRightChild();
    sNode* replacementNodeNewParent = this->getParent();
    
    replacementNode->setParent(replacementNodeNewParent);
    replacementNodeNewParent->setLeftChild(replacementNode);
    this->setParent(nullptr);
    this->setRightChild(nullptr);

    while (replacementNode) {
        replacementNode->correctHeightRemove();
        if (replacementNode->getParent()) {
            replacementNode = replacementNode->doTheRotationNotOnRoot();
        }
        else{
            replacementNode = replacementNode->doTheRotation();
        }

        if (replacementNode->getParent()) {
            replacementNode = replacementNode->getParent();
        }
        else {
            break;
        }
    }

    return replacementNode;
}
sNode* sNode::onlyLeftChildIsLeftChild() {
    sNode* replacementNode = this->getLeftChild();
    sNode* replacementNodeNewParent = this->getParent();

    replacementNode->setParent(replacementNodeNewParent);
    replacementNodeNewParent->setLeftChild(replacementNode);
    this->setParent(nullptr);
    this->setLeftChild(nullptr);

    while (replacementNode) {
        replacementNode->correctHeightRemove();
        if (replacementNode->getParent()) {
            replacementNode = replacementNode->doTheRotationNotOnRoot();
        }
        else {
            replacementNode = replacementNode->doTheRotation();
        }

        if (replacementNode->getParent()) {
            replacementNode = replacementNode->getParent();
        }
        else {
            break;
        }
    }

    return replacementNode;
}
sNode* sNode::bothChildrenIsRightChild() {
    sNode* replacementNode = this->getLeftChild();
    sNode* replacementNodeRightChild = replacementNode->getRightChild();
    sNode* nodeToProtect = this->getRightChild();
    sNode* replacementNodeRightChildsNewParent = nodeToProtect;
    sNode * replacementNodesNewParent = this->getParent();

    while (replacementNodeRightChildsNewParent->getLeftChild()) {
        replacementNodeRightChildsNewParent = replacementNodeRightChildsNewParent->getLeftChild();
    }

    //ptr to nodes set
    replacementNodeRightChild->setParent(replacementNodeRightChildsNewParent);
    replacementNodeRightChildsNewParent->setLeftChild(replacementNodeRightChild);
    replacementNode->setParent(replacementNodesNewParent);
    replacementNodesNewParent->setRightChild(replacementNode);
    replacementNode->setRightChild(nodeToProtect);
    nodeToProtect->setParent(replacementNode);
    this->setParent(nullptr);
    this->setLeftChild(nullptr);
    this->setRightChild(nullptr);

    if (replacementNodeRightChild) {
        while (replacementNodeRightChild) {
            replacementNodeRightChild->correctHeightRemove();

            if (replacementNodeRightChild->getParent()) {
                replacementNodeRightChild = replacementNodeRightChild->doTheRotationNotOnRoot();
            }
            else if (!replacementNodeRightChild->getParent()) {
                replacementNodeRightChild = replacementNodeRightChild->doTheRotation();
            }


            if (replacementNodeRightChild->getParent()) {
                replacementNodeRightChild = replacementNodeRightChild->getParent();
            }
            else {
                break;
            }
        }
        return replacementNodeRightChild;
    }
    else {
        while (replacementNode) {
            replacementNode->correctHeightRemove();

            if (replacementNode->getParent()) {
                replacementNode = replacementNode->doTheRotationNotOnRoot();
            }
            else if (!replacementNode->getParent()) {
                replacementNode = replacementNode->doTheRotation();
            }


            if (replacementNode->getParent()) {
                replacementNode = replacementNode->getParent();
            }
            else {
                break;
            }
        }
        return replacementNode;
    }
    return nullptr;
}

sNode* sNode::onlyRightChildIsIsRightChild() {

    sNode* replacementNode = this->getRightChild();
    sNode* replacementNodeNewParent = this->getParent();

    replacementNode->setParent(replacementNodeNewParent);
    replacementNodeNewParent->setRightChild(replacementNode);
    this->setParent(nullptr);
    this->setRightChild(nullptr);

    while (replacementNode) {
        replacementNode->correctHeightRemove();
        if (replacementNode->getParent()) {
            replacementNode = replacementNode->doTheRotationNotOnRoot();
        }
        else {
            replacementNode = replacementNode->doTheRotation();
        }
        if (replacementNode->getParent()) {
            replacementNode = replacementNode->getParent();
        }
        else {
            break;
        }
    }

    return replacementNode;
}
    sNode* sNode::onlyLeftChildIsRightChild() {

    sNode* replacementNode = this->getLeftChild();
    sNode* replacementNodeNewParent = this->getParent();

    replacementNode->setParent(replacementNodeNewParent);
    replacementNodeNewParent->setRightChild(replacementNode);
    this->setParent(nullptr);
    this->setLeftChild(nullptr);

    while (replacementNode) {
        replacementNode->correctHeightRemove();
        if (replacementNode->getParent()) {
            replacementNode = replacementNode->doTheRotationNotOnRoot();
        }
        else {
            replacementNode = replacementNode->doTheRotation();
        }

        if (replacementNode->getParent()) {
            replacementNode = replacementNode->getParent();
        }
        else {
            break;
        }
    }

    return replacementNode;
}