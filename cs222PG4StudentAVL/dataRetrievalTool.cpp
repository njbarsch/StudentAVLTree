#include"dataRetrievalTool.h"

DRT::DRT() {
	next = "";
	prev = "";
	data = "";
} 

DRT::DRT(string aNextNode, string aPrevNode, string someData) {
	next = aNextNode;
	prev = aPrevNode;
	data = someData;
}
string DRT::getNext() {
	return next;
}

string DRT::getPrev() {
	return prev;
}

string DRT::getData() {
	return data;
}