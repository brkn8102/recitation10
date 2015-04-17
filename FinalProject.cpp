// FinalProject.cpp created by Brandon Knutson on 4/13/2015

#include "InputUtilities.h"
#include "HashTable.h"
#include <iostream>

using namespace std;

int main()
{
    cout << "Welcome to the Customizable and Dynamic Hash Table." << endl << endl;
    
    string input = "";
    
    cout << "Enter the initial table size: ";
    cin >> input;
    while ( !isPositiveInteger( input ) )
    {
        cout << "Invalid input. Please enter a positive integer." << endl;
        cout << "Enter the initial table size: ";
        cin >> input;
    }
    int initialTableSize = stoi( input );
    
    cout << endl << "Dynamic table resizing allows for the number of hash table collisions to be kept below a set threshold by increasing the table size. ";
    cout << "Would you like to enable the dynamic table resizing capability?" << endl;
    cout << "Enter input (Y/N): ";
    cin >> input;
    while ( !isValidResponse( input ) )
    {
        cout << "Invalid input. Please enter \"Y\" or \"N\" to answer yes or no, respectively." << endl;
        cout << "Enter response (Y/N): ";
        cin >> input;
    }
    bool dynamicCapability = getResponse( input );
    
    int maximumAllowedChainLength;
    if ( dynamicCapability )
    {
        cout << endl << "Enter the maximum allowed chain length: ";
        cin >> input;
        while ( !isPositiveInteger( input ) )
        {
            cout << "Invalid input. Please enter a positive integer." << endl;
            cout << "Enter the maximum allowed chain length: ";
            cin >> input;
        }
        maximumAllowedChainLength = stoi( input );
    }
    else
    {
        maximumAllowedChainLength = -1;
    }
    
    HashTable *hashTable = new HashTable( initialTableSize, dynamicCapability, maximumAllowedChainLength );
    
    while ( true )
    {
        cout << endl;
        cout << "______MAIN___MENU______" << endl;
        cout << "1. Insert data element" << endl;
        cout << "2. Remove data element" << endl;
        cout << "3. Find data element" << endl;
        cout << "4. Switch " << ( hashTable->getDynamicCapability() ? "OFF" : "ON" ) << " dynamic resizing capability" << endl;
        cout << "5. Print table properties" << endl;
        cout << "6. Print table data elements" << endl;
        cout << "7. Quit" << endl;
        
        cin >> input;
        
        if ( input == "1" )
        {
            string key = getKey();
            int value = getValue();
            
            hashTable->insertElement( key, value );
            
            int doublings = hashTable->resize();
            if ( doublings > 0 ) cout << "Doubled table size " << doublings << " times." << endl;
        }
        else if ( input == "2" )
        {
            string key = getKey();
            
            bool elementRemoved = hashTable->removeElement( key );
            
            if ( !elementRemoved ) cout << "Element not found." << endl;
        }
        else if ( input == "3" )
        {
            string key = getKey();
            
            Element *element = hashTable->getElement( key );
            
            if ( element == nullptr )
                cout << "Element not found." << endl;
            else
                std::cout << "Index " << hashTable->hashFunction( element->key ) << ": ( " << element->key << ", " << element->value << " )" << std::endl;
        }
        else if ( input == "4" )
        {
            hashTable->setDynamicCapability( !hashTable->getDynamicCapability() );
            
            if ( hashTable->getDynamicCapability() )
            {
                cout << "Enter the maximum allowed chain length: ";
                cin >> input;
                while ( !isPositiveInteger( input ) )
                {
                    cout << "Invalid input. Please enter a positive integer." << endl;
                    cout << "Enter the maximum allowed chain length: ";
                    cin >> input;
                }
                cout << endl;
                int maximumAllowedChainLength = stoi( input );
                
                hashTable->setMaximumAllowedChainSize( maximumAllowedChainLength );
            }
            
            int doublings = hashTable->resize();
            if ( doublings > 0 ) cout << "Doubled table size " << doublings << " times." << endl;
        }
        else if ( input == "5" )
        {
            cout << "Table size: " << hashTable->getTableSize() << endl;
            
            cout << "Dynamic table resizing capability: " << ( dynamicCapability ? "ON" : "OFF" ) << endl;
            
            if ( hashTable->getDynamicCapability() ) cout << "Maximum allowed chain size: " << hashTable->getMaximumAllowedChainSize() << endl;
            
            cout << "Largest chain size: " << hashTable->getLargestChainSize() << endl;
            
            cout << "Number of elements: " << hashTable->getNumberOfElements() << endl;
        }
        else if ( input == "6" )
        {
            cout << hashTable->getElementsString();
        }
        else if ( input == "7" )
        {
            delete hashTable;
            
            cout << "Goodbye." << endl;
            break;
        }
        else
        {
            cout << "Invalid input. Please enter an option number (1-5) from the menu below." << endl;
        }
    }
    
    return 0;
}
