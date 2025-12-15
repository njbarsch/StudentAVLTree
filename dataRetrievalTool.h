#pragma once
#include <string>
#include <iostream>

using namespace std;

class DRT
{
private:
    string next;
    string prev;
    string data;

public:
    DRT(string aNextNode, string aPrevNode, string someData);
    DRT();

    string getNext();
    string getPrev();
    string getData();

    friend ostream& operator<<(ostream& os, DRT& drt)
    {
        return os << "[ Previous: " + drt.prev + ", Current: " + drt.data + ", Next: " + drt.next + " ]";
    }
};