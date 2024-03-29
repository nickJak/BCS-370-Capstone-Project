/*
 BCS 370 Fall 2020
 Capstone Project
 Nicholas Jakobczyk
 Kiernan Kolano
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>


#include "Assignment.cpp"

//Nick
void mainMenu();
time_t theTime = time(NULL);
struct tm *aTime = localtime(&theTime);

int day = aTime->tm_mday;
int month = aTime->tm_mon + 1;
int year = aTime->tm_year + 1900;

//Nick
int calculateDaysUntilDue(int d, int m, int y)
{

    
    struct tm endtm = {0, 0, 0, d, m-1, y - 1900};
    
    time_t end = mktime(&endtm);
    
    
    int daysUntil =  abs(end - theTime) / 86400;
    return daysUntil;
}
using namespace std;

vector<Assignment> myVector;


//Extra Funtions

//Nick
void displayVector(vector<Assignment> v)
{
    for(int i = 0; i < v.size(); i++)
    {
        cout << "Assignment #" << i+1 << endl;
        Assignment temp = v[i];
        temp.displayAssignment();
        cout << endl;
    }
}
void clearScreen()
{
    for(int i = 0; i <=50; i++)
    {
        cout << "\n";
    }
}


//Kiernan
void writeVectorToSaveFile(vector<Assignment> v)
{
    ofstream saveFile;
    saveFile.open("savefile.dat");
    for(int i = 0; i < v.size(); i++)
    {
        Assignment temp = v[i];
        saveFile << temp.getCourse() << "\n" << temp.getDescription() << "\n" << temp.getDay()<< "\n" << temp.getMonth() << "\n" << temp.getYear() << "\n" << temp.getCompletion() << "\n";
    }
    saveFile.close();
}

//Nick
void searchByCourse(vector<Assignment> v)
{
    cout << "Enter course name: ";
    string name;
    cin >> name;
    for(int i = 0; i < v.size(); i++)
    {
        
        Assignment temp = v[i];
        if(temp.getCourse()==name)
        {
        cout << "Assignment #" << i+1 << endl;
        temp.displayAssignment();
        cout << endl;
        }
    }
    int press;
    cout << "Type any character and hit enter...";
    cin >> press;
    clearScreen();
    mainMenu();
}

//Kiernan
void searchByCompletion(vector<Assignment> v)
{
    for(int i = 0; i < v.size(); i++)
    {
        
        Assignment temp = v[i];
        if(temp.getCompletion()==false)
        {
        cout << "Assignment #" << i+1 << endl;
        temp.displayAssignment();
        cout << endl;
        }
    }
    int press;
    cout << "Type any character and hit enter...";
    cin >> press;
    clearScreen();
    mainMenu();
}


//Nick
void searchByDueDate(vector<Assignment> v)
{
    clearScreen();
    cout << "Days until due: ";
    int daysUntilDue;
    cin >> daysUntilDue;
    for(int i = 0; i < v.size(); i++)
    {
        
        Assignment temp = v[i];
        if(temp.getDaysUntilDue()==daysUntilDue)
        {
        cout << "Assignment #" << i+1 << endl;
        temp.displayAssignment();
        cout << endl;
        }
    }
    int press;
    cout << "Type any character and hit enter...";
    cin >> press;
    clearScreen();
    mainMenu();
}


//Kiernan
void searchMenu()
{
    cout << "1. Search by course" << endl << "2. Search by due date" << endl << "3. In Progress" << endl << "4. Main Menu" << endl;
    int choice = -1;
    cin >> choice;
    switch(choice)
    {
        case 1:
        {
            clearScreen();
            searchByCourse(myVector);
            break;
        }
        case 2:
        {
            clearScreen();
            searchByDueDate(myVector);
            break;
        }
        case 3:
        {
            clearScreen();
            searchByCompletion(myVector);
            break;
        }
        case 4:
        {
            clearScreen();
            mainMenu();
            break;
        }
    }
    
}


//Nick
void mainMenu()
{
    int choice = -1;
    cout << "Todays date: " << month << "/" << day << "/" << year << endl;
    cout << "-=-=-HOMEWORK MANAGER-=-=-" << endl;
    cout << "1. Add Assignment" << endl;
    cout << "2. Edit Assignment" << endl;
    cout << "3. View All Assignments" << endl;
    cout << "4. Remove Assignment" << endl;
    cout << "5. Search Assignment" << endl;
    cout << "6. Save to file" << endl;
    cout << "7. QUIT" << endl;
    cin >> choice;
    
    switch(choice)
    {
        case 1:
        {
            clearScreen();
            Assignment temp;
            temp.addAssignment();
            int dayDue = temp.getDay();
            int monthDue = temp.getMonth();
            int yearDue = temp.getYear();
            int daysUntil = calculateDaysUntilDue(dayDue, monthDue, yearDue);
            temp.setDaysUntilDue(daysUntil);
            myVector.push_back(temp);
            clearScreen();
            mainMenu();
            break;
        }
        case 2:
        {
            clearScreen();
            displayVector(myVector);
            cout << "Select Assignment to edit: ";
            int assignmentNum;
            cin >> assignmentNum;
            Assignment temp = myVector[assignmentNum-1];
            temp.updateAssignment();
            int dayDue = temp.getDay();
            int monthDue = temp.getMonth();
            int yearDue = temp.getYear();
            int daysUntil = calculateDaysUntilDue(dayDue, monthDue, yearDue);
            temp.setDaysUntilDue(daysUntil);
            myVector[assignmentNum-1] = temp;
            clearScreen();
            mainMenu();
            break;
        }
        case 3:
        {
            clearScreen();
            displayVector(myVector);
            int press;
            cout << "Type any character and hit enter...";
            cin >> press;
            clearScreen();
            mainMenu();
            break;
        }
        case 4:
        {
            clearScreen();
            displayVector(myVector);
            cout << "Select Assignment to remove: ";
            int assignmentNum;
            cin >> assignmentNum;
            myVector.erase(myVector.begin()+assignmentNum-1);
            clearScreen();
            mainMenu();
            break;
        }
        case 5:
        {
            clearScreen();
            searchMenu();
            break;
        }
        case 6:
        {
            clearScreen();
            writeVectorToSaveFile(myVector);
            mainMenu();
            break;
        }
    }
}



int main() {
    
    
    
    //Read current save file into myVector
    ifstream saveFileRead;
    saveFileRead.open("savefile.dat");
    if(saveFileRead)
    {
    string course;
    while(getline(saveFileRead, course))
    {
        string desc;
        getline(saveFileRead, desc);
        string day;
        getline(saveFileRead, day);
        string month;
        getline(saveFileRead, month);
        string year;
        getline(saveFileRead, year);
        string comp;
        getline(saveFileRead, comp);
        int Day = stoi(day);
        int Month = stoi(month);
        int Year = stoi(year);
        bool Comp = false;
        if(comp == "1")
        {
            Comp = true;
        }
        int daysUNTIL = calculateDaysUntilDue(Day, Month, Year);
        Assignment temp(course, desc, Day, Month, Year, daysUNTIL, Comp);
        myVector.push_back(temp);
        
    }
    }
    //Currently Test Code
    mainMenu();
 
    
    
}
