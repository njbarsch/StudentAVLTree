// Nathen B + Jeremy J

#include <iostream>
#include <string>
#include "studentDatabase.h"
#include "studentNode.h"
#include <fstream>

int main()
{

    SDB aSDB;
    DRT aDRT;
    string command = "";
    ifstream inFile("input.txt");

    while (getline(inFile, command))
    {

        cout << "ADD || REMOVE || PRINT || RPRINT || EXIT || LOOKUP" << endl;
        // getline(cin, command);

        if (command.substr(0, 3) == "ADD")
        {
            aSDB.modify(command.substr(3, command.find('9') - 4), command.substr(command.find('9')));
        }
        else if (command.substr(0, 6) == "REMOVE")
        {
            aSDB.modify(command.substr(6, command.size() - 1), "");
        }
        else if (command.substr(0, 6) == "PRINT")
        {

            cout << "Printing forward" << endl;
            aDRT = aSDB.search("");
            string name = aDRT.getNext();

            if (aDRT.getNext() == "")
            {
                cout << "Empty Database" << endl;
            }

            while (aDRT.getNext() != "")
            {
                aDRT = aSDB.search(name);
                cout << name << " @ " << aDRT.getData() << endl; // print error
                name = aDRT.getNext();
            }
        }
        else if (command.substr(0, 7) == "RPRINT")
        {

            cout << "Printing backwards" << endl;
            aDRT = aSDB.search("");
            string name = aDRT.getPrev();

            if (aDRT.getNext() == "")
            {
                cout << "Empty Database" << endl;
            }

            while (aDRT.getPrev() != "")
            {
                aDRT = aSDB.search(name);
                cout << name << " @ " << aDRT.getData() << endl; // print error
                name = aDRT.getPrev();
            }
        }
        else if (command.substr(0, 5) == "EXIT")
        {
            exit(0);
        }
        else if (command.substr(0, 6) == "LOOKUP")
        {
            aDRT = aSDB.search(command.substr(6, command.size() - 3));
            cout << aDRT << endl;
        }
        else
        {
            cout << "FAILURE IN COMMAND" << endl;
            // exit(30);
        }
    }

    return 0;
}