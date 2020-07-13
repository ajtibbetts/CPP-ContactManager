/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Drew Tibbetts
 *
 * Created on February 25, 2019, 12:56 PM
 */

#include <cstdlib>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>

using namespace std;

/*
 * 
 */
const int MAX_CONTACTS = 10;
string contactName[MAX_CONTACTS] = {};
string contactNumber[MAX_CONTACTS]= {};

// initialize variables
const int TABLE_WIDTH = 20;

// create a contact structure that we can instance as needed
struct Contact{
        string name;
        string phoneNumber;
        string email;
        string address;
        string city;
        string state;
        string zipcode;
    };

// store created contact structs in a vector as opposed to array, so we can add additional contacts dynamically.
vector<Contact> contactList; 


void saveContactList(){
    
    /* this will save the contact list data to an external .txt or .csv file*/
    
    ofstream outFile;
    int index = 0;
    
    outFile.open("contactlist.txt");
    
   cin.ignore();
   cin.clear();
    // loop through contact list vector and save to file
    do {
        Contact contactToSave = contactList[index];
        
        outFile << contactToSave.name << endl;
        outFile << contactToSave.phoneNumber << endl;
        outFile << contactToSave.email << endl;
        outFile << contactToSave.address << endl;
        outFile << contactToSave.city << endl;
        outFile << contactToSave.state << endl;
        outFile << contactToSave.zipcode << endl;
        
        index++;
    } while(index < contactList.size());
    
    outFile.close();
    
    cout << "File is saved" << endl;
    
    return;
}

void loadContactList(){
    
    /* this will load the external contact list*/
    
    ifstream inFile;
    Contact contactToLoad;
    inFile.open("contactlist.txt");
    int debugcount = 0;
    
    
    // check for error
    if (inFile.fail()){
        cerr << "Error Opening File contactlist.txt.  Please check file and restart program." << endl;
        exit(1);
    }
    
    
        while(!inFile.eof()){
            getline(inFile,contactToLoad.name);
            getline(inFile,contactToLoad.phoneNumber);
            getline(inFile,contactToLoad.email);
            getline(inFile,contactToLoad.address);
            getline(inFile,contactToLoad.city);
            getline(inFile,contactToLoad.state);
            getline(inFile,contactToLoad.zipcode);
            contactList.push_back(contactToLoad);
            debugcount++;
            cout << "number of contacts loaded: " << debugcount << endl;
        }
    
    inFile.close();
    /* 
    int deletecount = 0;
    while (deletecount < (debugcount)){
    contactList.erase(contactList.begin());
    deletecount++;
    } */
    return;
}

void sortContactList() {
    bool sorted = false;   
     do { 
        // sort both arrays using phone number as the sort metric, using bubble sort method
        // swap flag to 0 on each pass in case there are no swaps performed
         bool hasSwapped = false;
        // run for loop with -1 the maximum so we don't try to read a null array index   
        for (int i = 0; i < contactList.size() - 1; i++){
            Contact tempContact; // placeholder for temporary
  
            // compare name in ascending order
            if(contactList[i].name > contactList[i + 1].name ) {
                // if a swap is performed, flag the boolean first so know run at least one more pass
                hasSwapped = true;
                // swap Contact structs
                tempContact = contactList[i+1];
                contactList[i + 1] = contactList[i];
                contactList[i] = tempContact;
         }           
        }  
        // if there were no swaps performed on this pass, we flag sorted to true to end the DO WHILE loop
        if (!hasSwapped){
                sorted = true;
            }
       } while(sorted == false); 
    return;
}

void createNewContact(){
    
    Contact newContact;
    
    cout << "CREATE NEW CONTACT" << endl;
    cout << "----------------" << endl << endl;
    cout << "Please enter the contact first and last name:" << endl;
    cin.ignore();
    cin.clear();
        getline(cin, newContact.name);
    cout << "Please enter the contact phone number:" << endl;
        getline(cin, newContact.phoneNumber);
    cout << "Please enter the contact email:" << endl;
        getline(cin, newContact.email);
    cout << "Please enter the contact street address:" << endl;
        getline(cin, newContact.address);
    cout << "Please enter the contact city: " << endl;
        getline(cin, newContact.city);
    cout << "Please enter the contact state initials:" << endl;
        getline(cin, newContact.state);
    cout << "Please enter the contact zip code:" << endl;
        getline(cin, newContact.zipcode);
    cin.clear();
    
    cout << "New contact created, please confirm:" << endl;
    cout << "Name: " << newContact.name << endl;
    cout << "Phone Number: " << newContact.phoneNumber << endl;
    cout << "Email Address: " << newContact.email << endl;
    cout << "Address: " << newContact.address << endl << newContact.city << ", " << newContact.state << ", " << newContact.zipcode << endl;
    
    
    // add the contact to contact list
    contactList.push_back(newContact);
    saveContactList(); // save the contact list
    cout << "New contact added to system.  Number of contacts: " << contactList.size() << endl;
    cout << "Returning to main menu..." << endl << endl;
    return;
}

void initTableHeader(){
    
    // initialize table headings that can be called when needed
    cout << "CONTACT LIST" << endl;
    cout << "----------------" << endl;
    cout << left << setw(TABLE_WIDTH) << "Name" << setw(TABLE_WIDTH) << "Phone Number" << setw(TABLE_WIDTH) << "Email Address" << setw(TABLE_WIDTH  + 10) << "Street Address" << setw(TABLE_WIDTH) << "City" << setw(TABLE_WIDTH) << "State" << setw(TABLE_WIDTH) <<"ZIP" << endl;
    
    return;
}

void displayContact(int index){
    // displays a contact based on the referenced index position
    Contact listItem = contactList[index];   
    cout << left << setw(TABLE_WIDTH) << listItem.name << setw(TABLE_WIDTH) << listItem.phoneNumber << setw(TABLE_WIDTH) << listItem.email << setw(TABLE_WIDTH  + 10) << listItem.address << setw(TABLE_WIDTH) << listItem.city << setw(TABLE_WIDTH) << listItem.state << setw(TABLE_WIDTH) << listItem.zipcode << endl; 
    return;
}

void displayContactList(){
    
    // only display list if there are contacts to display
    if(contactList.size() > 0){
        sortContactList(); // sorts contact list by name
        initTableHeader(); // creates table headers
        for(int i = 0; i < contactList.size(); i++){
            displayContact(i);
        }    
    }
    else {
        cout << "No contacts found.  Please create a contact to view list." << endl;
    }
    cout << endl;
    return;
}

void searchByName(){
    string searchQuery;
    bool foundMatch = false;
    char searchAgain;
    
    cout << "SEARCH BY NAME" << endl;
    cout << left <<setw(40) << "-----------------------------------------" << endl;
    do {
        foundMatch = false; // reset to false on a new search;
        cin.clear();
        cin.ignore();
        cout << "Please enter the full name of the contact you are searching for (case sensitive):" << endl;
        getline(cin, searchQuery);

        for (int i = 0; i < contactList.size(); i++) {
            if (searchQuery == contactList[i].name){
                cout << "User found based on search query. Displaying contact information..." << endl << endl;
                foundMatch = true;
                initTableHeader();
                displayContact(i);
                cout << endl;
            }
        }
        if (!foundMatch){
            cout << "No user was found by that name." << endl; 
        }
        // once search is complete, give user option to search again.
        cout <<  "Would you like to search again? (enter Y or y to search again)"<< endl;
        cin >> searchAgain;
        cin.ignore();
    } while (searchAgain == 'Y' or searchAgain == 'y');
    
    return;
}



void exitProgram(){
    cout << "Thank you for using the Contact Manager.  Exiting Program..." << endl;
    exit(0); 
}

void displayMainMenu(){
    
    int menuSelection;
    
    do{
        cout << "Welcome to the Contact Manager.  Please selection an option below." << endl;
        cout << "1. Create New Contact" << endl;
        cout << "2. Search For Contact" << endl;
        cout << "3. View Contact List" << endl;
        cout << "4. Exit Program" << endl;
        cout << "Please enter the number of the menu item you wish to select to proceed:" << endl;
        cin >> menuSelection;
        // cin.clear();
        
        switch(menuSelection){
            // create new contact
            case 1:
                createNewContact();
                break;
            // search for contact    
            case 2:
                searchByName();
                break;
                
            // view contact list
            case 3:
                displayContactList();
                break;
            // exit program
            case 4:
                exitProgram();
                break;  
            default:
                cout << "Please enter a valid menu option (Number 1-4)." << endl;
                break;
        }
    } while (menuSelection > 0 && menuSelection < 5);   
    return;
}





int main() { 
    
    loadContactList(); // loads existing contact list
    displayMainMenu();
    
    return 0;
}



