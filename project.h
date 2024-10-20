#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <streambuf>
#include <regex>
#include <windows.h> // Include Windows-specific header for console functions
#include <conio.h>

using namespace std;
using namespace std::chrono;



// User Class
class User
{
protected:
    string username;
    string password;
    string emailAddress;
    string name;
    string contact;
    bool loginStatus;
    int index;

public:
    User()
    {
        username = "";
        password = "";
        loginStatus = false;
    }

    User(string user, string pass)
    {
        username = user;
        password = pass;
        loginStatus = false;
        index = 0;
    }



    bool isValidUsername(const string& username) {
    // Check for spaces in the username
    for (char ch : username) {
        if (ch == ' ') {
            return false;
        }
    }

    // Check for capital letters in the username
    for (char ch : username) {
        if (isupper(ch)) {
            return false;
        }
    }

    // If no spaces or capital letters found, the username is valid
    return true;
}


    //Funtion to check password    
    bool checkPassword(const string &pass){
    // Check the length of the password
    if (pass.length()<6) {
        return false;
    }

    bool hasUpperCase = false;
    bool hasLowerCase = false;
    bool hasDigit = false;
    bool hasSpecialChar = false;

    // Check each character of the password
    for (char c : pass) {
        if (isspace(c)) {
            return false;  // Check for spaces
        }
        if (isupper(c)) {
            hasUpperCase = true;  // Check for uppercase letters
        }
        if (islower(c)) {
            hasLowerCase = true;  // Check for lowercase letters
        }
        if (isdigit(c)) {
            hasDigit = true;  // Check for digits
        }
    }

    // Check if all requirements are met
    return (hasUpperCase && hasLowerCase && hasDigit);
  }


    bool validateEmail(const string&email ) const {
  
    bool atfound = false, dotfound = false;
    int atindex = -1, dotindex = -1;  //I initialized atindex and dotindex variables to -1 to indicate that these symbols have not been found in the email address yet.

    // Check if email has "@" symbol and a valid domain name
    for (int i = 0; i < email.length(); i++) {
        //when @ wil be found first time atfound becomes true. then on further itterations if we ever found @ rate then the below if() condition will run and will return false because there cannot betwo @ in email address.
        if (email[i]=='@') {
            if (atfound) {
            return false; // More than one '@' symbol found
            }
            atfound = true;
            atindex = i;
        }
        //now for cecking dot 
        else if (email[i] == '.') {
            if (dotfound) {
                return false;   // More than one '.' symbol found
            }
            dotfound = true;
            dotindex = i;
        }
    }

    // if '@' or '.' symbol not found
    if ((!atfound)||(!dotfound)) {
        return false; 
    }

     // if  '.' symbol appears before '@' symbolor if '.' appears right after the '@' 
    if (dotindex<=atindex+1) {
        return false;
    }
    
     // if '.' symbol is found on the last character
    if (dotindex==email.length() - 1) {
        return false;
    }

    if(atindex==0){
     return false;   //if '@' found at first index
     }
    
    return true;
}

//make a function to validate ppakistani contact number
  bool validatePhone(const string& phoneNumber) {
    // Regular expression to match valid Pakistani phone numbers
    std::regex regexPattern("^03\\d{2}-?\\d{7}$");

    return std::regex_match(phoneNumber, regexPattern);
}


    string getUsername()
    {
        return username;
    }

    string getPassword()
    {
        return password;
    }

    bool getLoginStatus()
    {
        return loginStatus;
    }

    int getIndex()
    {
        return index;
    }

    string getEmailAddress(){
        return emailAddress;
    }

    void setUsername(string user)
    {
     username = user;
    }

    void setEmailAddress(string email){
        emailAddress = email;
    }

    
    void setPassword(string pass)
    {
        password = pass;
    }

//to hide the password with steriks
string getHiddenPassword()
{
    string password;
    char ch;

    while (true)
    {
        ch = _getch();

        if (ch == '\r' || ch == '\n') // Enter key pressed, break the loop
        {
            cout << endl;
            break;
        }
        else if (ch == '\b') // Backspace key pressed
        {
            if (!password.empty())
            {
                cout << "\b \b"; // Move the cursor back, write a space to overwrite the last character, move the cursor back again
                password.pop_back(); // Remove the last character from the password string
            }
        }
        else
        {
            password.push_back(ch);
            cout << '*'; // Display an asterisk for each character
        }
    }

    return password;
}



    bool loginStudent()
    {
        ifstream credentials;
        credentials.open("CredentialsStudents.csv");

        if (!(credentials.is_open()))
        {
            cout << "Error opening credentials file." << endl;
            return false;
        }

        string line;
        const int ROWS = 500;
        int row = 0;
        bool userStatus;
        bool passwordStatus;
        int temp = -1;

        while (getline(credentials, line))
        {
            userStatus = false;
            passwordStatus = false;

            if (row >= ROWS)
            {
                break;
            }

            stringstream lineStream(line);
            string cell;
            int column = 0;

            while (getline(lineStream, cell, ','))
            {
                if (column >= 500)
                {
                    break;
                }

                if (column == 0)
                {
                    if (cell == username)
                    {
                        userStatus = true;
                        temp = row;
                    }

                    else
                    {
                        userStatus = false;
                    }
                }

                if (column == 1)
                {
                    if (cell == password && userStatus == true)
                    {
                        passwordStatus = true;
                        temp = row;
                    }

                    else
                    {
                        passwordStatus = false;
                    }
                }

                column++;
            }

            if (userStatus && passwordStatus)
            {
                loginStatus = true;
                index = row;
                return true;
            }

            row++;
        }

        return false;
    }


bool isValidDeadline(const string &deadline)
    {
        // Get the current date and time
        auto now = system_clock::now();
        time_t currentTime = system_clock::to_time_t(now);

        // Convert the deadline string to time_t
        tm tmDeadline = {};
        istringstream deadlineStream(deadline);
        deadlineStream >> get_time(&tmDeadline, "%Y-%m-%d % H:%M:%S");

        // Convert the deadline time_t to seconds
        time_t deadlineTime = mktime(&tmDeadline);

        // Check if the deadline is in the future
        return (deadlineTime > currentTime);
    }




    bool loginTeacher()
    {
        ifstream credentials;
        credentials.open("CredentialsTeacher.csv");

        if (!credentials.is_open())
        {
            cout << "Error opening credentials file." << endl;
            return false;
        }

        string line;
        const int ROWS = 200;
        int row = 0;
        bool userStatus;
        bool passwordStatus;
        int temp = -1;

        while (getline(credentials, line))
        {
            userStatus = false;
            passwordStatus = false;

            if (row >= ROWS)
            {
                cout << "Maximum number of rows exceeded!" << endl;
                break;
            }

            stringstream lineStream(line);
            string cell;
            int column = 0;

            while (getline(lineStream, cell, ','))
            {
                if (column >= 500)
                {
                    cout << "Maximum number of columns exceeded!" << endl;
                    break;
                }

                if (column == 0)
                {
                    if (cell == username)
                    {
                        userStatus = true;
                        temp = row;
                    }

                    else
                    {
                        userStatus = false;
                    }
                }

                if (column == 1)
                {
                    if (cell == password && userStatus == true)
                    {
                        passwordStatus = true;
                        temp = row;
                    }

                    else
                    {
                        passwordStatus = false;
                    }
                }

                column++;
            }

            if (userStatus && passwordStatus)
            {
                loginStatus = true;
                return true;
            }

            row++;
        }

        return false;
    }

    bool registerStudent()
    {
        ofstream credentials;
        credentials.open("CredentialsStudents.csv", ios::app);

        if (!credentials.is_open())
        {
            cout << "Error opening credentials file." << endl;
            return 0;
        }

        credentials << username << "," << password <<","<< emailAddress<<","<<contact <<","<<name <<endl; //writing  in csv file

        credentials.close();
        return true;
    }

    bool registerTeacher()
    {
        ofstream credentials;
        credentials.open("CredentialsTeacher.csv", ios::app);

        if (!credentials.is_open())
        {
            cout << "Error opening credentials file." << endl;
            return 0;
        }

        credentials << username << "," << password <<","<< emailAddress <<","<<contact <<","<<name<< endl;  //writing  in csv file

        credentials.close();
        return true;
    }

    void displayInfo()
    {
        cout << "Name : "<< name << "\nEmail Address : "<<emailAddress <<"\n Contact No : "<<contact<< endl;
    }

    void logout()
    {
        if (loginStatus == true)
        {
            loginStatus = false;
        }
    }
};


// Teacher Class
class Teacher : public User
{
int newTeacher;
public:
    Teacher() : User()
    {
        name = "";
    }

    Teacher(string name,string contact, string user, string pass) : User(user, pass)
    {
        this->name = name;
        this->contact = contact;
    }

    void setName(string name)
    {
        this->name = name;  //this-> name variable will be inehrited from parent class
    }


    void setContact(string contact){
        this->contact = contact;  //this->contact variable will be inehrited from parent class
    }


    string getName()
    {
        return name;   // name variable  inehrited from parent class
    }

    //function to get contact
    string getContact(){
        return contact;   // contact variable  inehrited from parent class
    }




    friend ostream &operator<<(ostream &, Teacher);
};

ostream &operator<<(ostream &out, Teacher T)
{
    out << "\nTeacher Name: " << T.getName();

    return out;
}

// Student Class
class Student : public User
{
string newStudent;
public:
    Student() : User()
    {
        name = "";
        contact = "";
        // attendance = new Attendance();
    }

    Student(string name,string contact, string user, string pass) : User(user, pass)
    {
        this->name = name;
        this->contact = contact;
     
    }


    void setName(string name)
    {
        this->name = name;  //this-> name variable will be inehrited from parent class
    }


    void setContact(string contact){
        this->contact = contact;  //this->contact variable will be inehrited from parent class
    }

    void setNewStudent(string newStudent){
        this->newStudent = newStudent;  
    }

    string getNewStudent()const{
        return newStudent;
    }


    string getName()
    {
        return name;   // name variable  inehrited from parent class
    }

    //function to get contact
    string getContact(){
        return contact;   // contact variable  inehrited from parent class
    }


   void displayStudentInfo()
    {
        cout << "Name : "<< name << "\nEmail Address : "<<emailAddress <<"\n Contact No : "<<contact<< endl;
    }

    bool operator==(Student &S)
    {
        if (name == S.name)
        {
            return true;
        }

        return false;
    }

friend ostream &operator<<(ostream &out, Student &S);

};
    ostream &operator<<(ostream &out, Student &S)
    {
        out << S.getName() << " - " << S.getEmailAddress();
        return out;
    }



// Class Class
class ClassesManager {
private:
    string className;
    string currentTeacher;
    string subject;
    string description;
    Student enrolledStudents[5];
    int noOfStudents;
    
public:
    ClassesManager() {}

    ClassesManager(string& className, string& subject, string& currentTeacher, string& description) {
        this->className = className;
        this->subject = subject;
        this->currentTeacher = currentTeacher;
        this->description = description; 
        this->noOfStudents = 0; // Initialize the number of students to 0   
    }

    string getClassName() { return className; }
    string getSubject() { return subject; }
    string getTeacher() const{ return currentTeacher; }
    string getDescription() { return description; }
    int getNoOfStudents() { return noOfStudents; }

    void DisplayErolledStudents(){
           cout << "Enrolled Students: ";
            for (int i = 0; i < noOfStudents; i++) {
             cout << enrolledStudents[i].getNewStudent();
             if (i < noOfStudents - 1) {
                 cout << ", ";
             }
         }
    cout<<endl;
    }



    void setClassName(string className) { this->className=className; }
    void setSubject(string subject) {  this->subject=subject; }
    void setTeacher(string currentTeacher) {  this->currentTeacher=currentTeacher; }
    void setDescription(string description) {this->description=description;  }
       


    void displayClassInfo() {
        cout << "Class Name: " << className << endl;
        cout << "Subject: " << subject << endl;
        cout << "Teacher: " << currentTeacher << endl;
        cout << "Description: " << description << endl;
            
    }


    // Function to add a student to the class
    void addStudent(string& studentName) {
        
        if (noOfStudents < 5) {
            
            enrolledStudents[noOfStudents].setNewStudent(studentName);
            noOfStudents++;
        }
        else{
            cout<<"ClassRoom is Full. Maximum number of students is 5\n";
        }
    }

    // Function to remove a student from the class
    void removeStudent(string& studentName) {
        for (int i = 0; i < noOfStudents; i++) {
            if (enrolledStudents[i].getNewStudent()== studentName) {
                for (int j = i; j < noOfStudents - 1; j++) {
                    enrolledStudents[j] = enrolledStudents[j + 1];
                }
                noOfStudents--;
                return;
            }
        }
    }
 

};



class AssignmentsManager {
private:

    int numAssignments;
    Teacher &teacher; //aggregted with TEACHER CLASS
    Student &student; //Aggregated with STUDENT CLASS
    string title;
    string description;
    string deadline;
    string attachedFiles;
    int pointValue;
    string currentTeacher;
    string currentStudent;

public:



    AssignmentsManager(Teacher &temp1, Student& temp2):teacher(temp1),student(temp2)
    {
        
        title = "";
        description = "";
        deadline = "";
        attachedFiles = "";
        pointValue = 0;
    }


    



    AssignmentsManager(const string& title, const string& description, const string& deadline, const string& attachedFiles, int pointValue, Teacher &temp1, Student& temp2):teacher(temp1),student(temp2)
    {
        this->currentTeacher = teacher.getUsername();
        this->currentStudent = student.getUsername();
        this->title = title;
        this->description = description;
        this->deadline = deadline;
        this->attachedFiles = attachedFiles;
        this->pointValue = pointValue;
    }

    string getTitle() const
    {
        return title;
    }

    string getDescription() const
    {
        return description;
    }

    string getDeadline() const
    {
        return deadline;
    }

    string getAttachedFiles() const
    {
        return attachedFiles;
    }

    int getPointValue() const
    {
        return pointValue;
    }
    string getcurrentTeacher ()const{
        return currentTeacher;
    }

    string getcurrentStudent ()const {
        return currentStudent;
    }

    void setTitle(string title){
        this->title = title;
    }
    void setDescription(string description){
        this->description = description;
    }
    void setDeadline(string deadline){
        this->deadline = deadline;
    }
    void setAttachedFiles(string attachedFiles){
        this->attachedFiles = attachedFiles;
    }
    void setPointValue(int pointValue){
        this->pointValue = pointValue;
    }


    //FOR STUDENT INFORMATION   
    void displayAssignmentInfo(){
        cout<<"Assignment by Sir/Ma'am: "<<teacher.getUsername()<<endl;
        cout << "Title: " << title << endl;
        cout << "Description: " << description << endl;
        cout << "Deadline: " << deadline << endl;
        cout << "Attached Files: " << attachedFiles << endl;
        cout << "Points: " << pointValue << endl;
    }

//FOR STUDENT INFORMATION   
    void displayStudentAssignmentInfo(){
        cout<<"Assignment by Sir/Ma'am: "<<teacher.getUsername()<<endl;
        cout << "Title: " << title << endl;
        cout << "Description: " << description << endl;
        cout << "Uploading Time: " << deadline << endl;
        cout << "Attached Files: " << attachedFiles << endl;
    }    
   
 

//FUNCTION TO RETURN THE CURRENT TIME IN FORMAT YYYY-MM-DD|HH:MM
        string getCurrentTimeAsString() {
    // Get the current time
    time_t currentTime = time(nullptr);

    // Convert the current time to a local time (human-readable format)
    tm* localTime = localtime(&currentTime);

    // Format the current date and time
    stringstream ss;
    ss << localTime->tm_year + 1900 << "-" << setfill('0') << setw(2) << localTime->tm_mon + 1 << "-" << setfill('0') << setw(2) << localTime->tm_mday << "|";
    ss << setfill('0') << setw(2) << localTime->tm_hour << ":" << setfill('0') << setw(2) << localTime->tm_min;
    
    return ss.str();
}

            bool isValid(const string &deadline){

                // Regular expression to validate the date format "yyyy-mm-dd hh:mm"
                    regex dateRegex(R"(\b\d{4}-\d{2}-\d{2}\|\d{2}:\d{2}\b)");

                    smatch match;
                    if (regex_match(deadline, match, dateRegex)) {
                        // Convert the input deadline to a time_point
                        tm tm{};
                        istringstream iss(deadline);
                        iss >> get_time(&tm, "%Y-%m-%d|%H:%M");
                        if (iss.fail()) {
                            cerr << "Error parsing the deadline: " << deadline << endl;
                            return false;
                        }


                        chrono::system_clock::time_point deadlineTime = chrono::system_clock::from_time_t(mktime(&tm));

                        // Get the current time
                        chrono::system_clock::time_point currentTime = chrono::system_clock::now();

                        // Compare the deadline time with the current time
                        if (deadlineTime > currentTime) {
                            return true; // The deadline is after the current time
                        }
                        else {
                            cout<<"Cannot set Deadline before Current Time\n";
                            return false; // The deadline is before or equal to the current time
                        }
                    } 
                    else {
                        cerr << "Invalid date format: " << deadline << endl;
                        return false;
                    }

            }



 


    

    int Marks(const string& deadlineStr) {
    // Get the current time
    auto currentTime = system_clock::now();
    time_t currentTime_t = system_clock::to_time_t(currentTime);

    // Convert the deadline string to time_t
    tm tmDeadline = {};
    istringstream deadlineStream(deadlineStr);
    deadlineStream >> get_time(&tmDeadline, "%Y-%m-%d %I:%M %p");
    time_t deadlineTime_t = mktime(&tmDeadline);

    // Calculate the difference between the current time and the deadline time in seconds
    int timeDifference = static_cast<int>(difftime(currentTime_t, deadlineTime_t));

    // Check if the assignment was uploaded before the deadline
    if (timeDifference <= 0) {
        return 100;
    }
    // Check if the assignment was uploaded within 3 hours after the deadline
    else if (timeDifference <= 3 * 60 * 60) {
        return 50;
    }
    // Assignment uploaded after the grace period (more than 3 hours after the deadline)
    else {
        return 0;
    }
}
 friend ostream &operator<<(ostream &, AssignmentsManager&);
    
};
ostream &operator<<(ostream &out, AssignmentsManager& A)
{
    out << "Assignment Title: " << A.getTitle() << endl;
    out << "Description: " << A.getDescription() << endl;
    out << "Deadline: " << A.getDeadline() << endl;
    out << "Attached Files: " << A.getAttachedFiles() << endl;
    out << "Point Value: " << A.getPointValue() << endl;
    return out;
}



class ClassRoomFiles{
    public:



    // Functions to handle file I/O for class information
void saveClassToFile(ClassesManager& classObj) {
    ofstream classFile("classes.txt", ios::app);
    if (classFile.is_open()) {
        classFile << classObj.getClassName() << ", " << classObj.getSubject() << ", " << classObj.getTeacher() << ", " << classObj.getDescription() << endl;
        classFile.close();
    }
    else{
        cout<<"ERROR opening file"<<endl;
    }
}

// void saveStudentToFile(Student& classObj) {
//     ofstream classFile("Student.txt", ios::app);
//     if (classFile.is_open()) {
//         classFile << classObj.getUsername() << ", " << classObj.getPassword() << ", " << classObj.getEmailAddress() << ", " << classObj.getContact() <<", " << classObj.getName() << endl;
//         classFile.close();
//     }
//     else{
//         cout<<"ERROR opening file"<<endl;
//     }
// }





//TO VIEW ALL CLASSES
void readFromFile(string filename) {
    ifstream classFile(filename);
    if (classFile.is_open()) {
        string line;

        if(filename == "assignments.txt"){
        while (getline(classFile, line)) {
        stringstream ss(line);
        string title, description, deadline, attachedFile,totalMarks, teacher;
        getline(ss, title, ',');
        getline(ss, description, ',');
        getline(ss, deadline, ',');
        getline(ss, attachedFile, ',');
        getline(ss, totalMarks, ',');
        getline(ss, teacher, ',');

        cout<<"Assignment by Sir/Ma'am: "<<teacher<<endl;
        cout << "Title: " << title << endl;
        cout << "Description: " << description << endl;
        cout << "Deadline: " << deadline << endl;
        cout << "Attached Files: " << attachedFile << endl;
        cout << "Points: " << totalMarks << endl;

        cout<<endl;
        }
    }

    else{
        while (getline(classFile, line)) {
        stringstream ss(line);
        string className, subject, teacher, description;
        getline(ss, className, ',');
        getline(ss, subject, ',');
        getline(ss, teacher, ',');
        getline(ss, description, ',');

        cout << "Class Name: " << className << endl;
        cout << "Subject: " << subject << endl;
        cout << "Teacher Sir/Ma'am: " << teacher << endl;
        cout << "Description: " << description << endl;

        cout<<endl;
        }

    }
        classFile.close();
    }

    else{
        cout<<"ERROR opening file"<<endl;
    }
}

//Function to delete class from file
void deleteClass(string& className){
    // Search the class by its name in the file and delete it
            {
                ifstream classFile("classes.txt");
                ofstream tempFile("temp_classes.txt"); // Temporary file to store modified data
                if (classFile.is_open() && tempFile.is_open()) {
                    string line;
                    bool classFound = false;
                    while (getline(classFile, line)) {
                        stringstream ss(line);
                        string token;
                        getline(ss, token, ',');
                        if (token == className) {
                            classFound = true;
                        } else {
                            tempFile << line << endl; // Write lines that don't match the class name to the temp file
                        }
                    }
                    classFile.close();
                    tempFile.close();

                    if (classFound) {
                        // Delete the original file and rename the temporary file
                        remove("classes.txt"); //Deleting classses.txt file
                        rename("temp_classes.txt", "classes.txt");  //renaming "temp_classes.txt" to classes.tx
                        cout << "\nClass Deleted Successfully!\n";
                    } else {
                        // The class was not found in the file
                        remove("temp_classes.txt");
                        cout << "\nClass not found!\n";
                    }
                }

                else
                {
                    cout << "ERROR opening file" << endl;
                }
            }
}




//Function to delete cAssignment from file
void deleteAssignment(string& className){
    // Search the class by its name in the file and delete it
            {
                ifstream classFile("assignments.txt");
                ofstream tempFile("temp_assignments.txt"); // Temporary file to store modified data
                if (classFile.is_open() && tempFile.is_open()) {
                    string line;
                    bool classFound = false;
                    while (getline(classFile, line)) {
                        stringstream ss(line);
                        string token;
                        getline(ss, token, ',');
                        if (token == className) {
                            classFound = true;
                        } else {
                            tempFile << line << endl; // Write lines that don't match the class name to the temp file
                        }
                    }
                    classFile.close();
                    tempFile.close();

                    if (classFound) {
                        // Delete the original file and rename the temporary file
                        remove("assignments.txt"); //Deleting classses.txt file
                        rename("temp_assignments.txt", "assignments.txt");  //renaming "temp_classes.txt" to classes.tx
                        cout << "\nCAssignment Deleted Successfully!\n";
                    } else {
                        // The class was not found in the file
                        remove("temp_assignments.txt");
                        cout << "\nClass not found!\n";
                    }
                }

                else
                {
                    cout << "ERROR opening file" << endl;
                }
            }
}



bool ClassOrAssignExists(const string&name, const string& filename){
    ifstream classFile(filename);
    if (classFile.is_open()) {
        string line;
        while (getline(classFile, line)) {
            stringstream ss(line);
            string token;
            getline(ss, token, ',');
            if (token == name) {
                classFile.close();
                return true;
            }
        }
        classFile.close();
        return false;
    }
    else{
        cout<<"ERROR opening file"<<endl;
        return false;
    }
}  



void updateClass(const string& className, const string& NameToUpdate, int choice){
 ifstream classFile("classes.txt");
    ofstream tempFile("temp_classes.txt"); // Temporary file to store modified data

    if (classFile.is_open() && tempFile.is_open()) {
        string line;
        bool classFound = false;
/*
: This while loop reads lines from the classFile until there are no more lines left to read. The getline function 
reads a line from the file and stores it in the line string variable. If there are more lines to read, the loop 
continues. If there are no more lines, the loop exits
*/       
        while (getline(classFile, line)) {
            stringstream ss(line);
            string token;
/*this means that we will start reading entire string stream till endof lines but i have put a delimeter here which
  is comma means when I willreach to comma the string before comma will be stored in token variable . After that I
   have moved ext to comma and will read file till next comma and will extraxt the next string*/            
            getline(ss, token, ',');  
            if (token == className) {
                classFound = true;

                if(choice == 1){
                tempFile << NameToUpdate <<", ";
                getline(ss, token); // Now storing Rest of the whole file in token like till endl (here teacher and description)
                tempFile << token << endl; // Writing the line stored in token variable here the teacher and description to the temp file
                }

                else if(choice == 2){
                tempFile <<  className << ", " << NameToUpdate << ", "; // Write the updated class entry to the temp file
                getline(ss, token, ','); // Skip the old subject
                getline(ss, token); // Now storing Rest of the whole file in token like till endl (here teacher and description)
                tempFile << token << endl; // Writing the line stored in token variable here the teacher and description to the temp file
                }

                //TO UPDATE TEACHER NAME
                else if(choice == 3){
                string previousSubject;
                getline(ss, previousSubject, ',');  //saving previous subject name 
                tempFile <<  className << ", "<<previousSubject<<", "<<NameToUpdate<<", "; // Write the updated class entry to the temp file
                getline(ss, token, ','); // Skip the old Teacher
                getline(ss, token); // Now storing Rest of the whole file in token like till endl (here teacher and description)
                tempFile << token << endl; // Writing the line stored in token variable here the teacher and description to the temp file     
                }

                else if(choice == 4){
                string previousSubject;
                string previousTeacher;
                getline(ss, previousSubject, ',');  //saving previous subject name 
                getline(ss, previousTeacher, ',');  //saving previous Teacher name 
                tempFile <<  className << ", "<<previousSubject<<", "<<previousTeacher<<", "<<NameToUpdate<<", "; // Write the updated class entry to the temp file
                getline(ss, token, ','); // Skip the old Teacher
                getline(ss, token); // Now storing Rest of the whole file in token like till endl (here teacher and description)
                tempFile << token << endl; // Writing the line stored in token variable here the teacher and description to the temp file    
                }
                        
            } 
            else {
                tempFile << line << endl; // Write lines that don't match the class name to the temp file
            }
        }
        classFile.close();
        tempFile.close();

        if (classFound) {
            // Delete the original file and rename the temporary file
            remove("classes.txt");  //Deleting classses.txt file
            rename("temp_classes.txt", "classes.txt");   //renaming "temp_classes.txt" to classes.tx
            cout << "\nClass Updated Successfully!\n";
        } 
        else {
            // The class was not found in the file
            remove("temp_classes.txt");
            cout << "\nClass not found!\n";
        }

    }

    else{
        cout<<"ERROR opening file"<<endl;
    }   
}


// Function to update classes.txt after adding student in it. we will com here only when students are less than 5
// against te eneterd class name
void AddingStudent(const string& className, const string& newSudent) {
    ifstream classFile("classes.txt");
    ofstream tempFile("temp_classes.txt"); // Temporary file to store modified data
    if (classFile.is_open() && tempFile.is_open()) {
        string line;
        bool classFound = false;
        while (getline(classFile, line)) {
            stringstream ss(line);
            string token;
            getline(ss, token, ',');  ///className from classes.txt is stored in token because first string before comma si class name
            if (token == className) {
                classFound = true;
                tempFile << className << ", "; // Write the updated class entry to the temp file
                getline(ss, token); // Rest of the line (teacher and description)
//now writing rest of the line (which is stored in token variable) to temp file and then after that putting comma andthen writing new student 
                tempFile << token << ", " << newSudent << endl; 
            } 
            else {
                tempFile << line << endl; // Write lines that don't match the class name to the temp file
                                         //means it will write all the previousfile to temp file
            }
        }
        classFile.close();
        tempFile.close();

        if (classFound) { //if class is found
            // Delete the original file and rename the temporary file
            remove("classes.txt");  //Deleting classses.txt file
            rename("temp_classes.txt", "classes.txt");   //renaming "temp_classes.txt" to classes.tx
            cout << "\nStudent Added Successfully!\n";
        } 
        else {
            // The class was not found in the file
            remove("temp_classes.txt");
            cout << "\nClass not found!\n";
        }
    }

     else{
        cout<<"ERROR opening file"<<endl;
    }
}


void RemovingStudent(const string& className, const string& newStudent) {
    int len= newStudent.length();
    ifstream classFile("classes.txt");
    ofstream tempFile("temp_classes.txt");
    bool studentFound = false;
    if (classFile.is_open() && tempFile.is_open()) {
        string line;
        
        bool classFound = false;
        while (getline(classFile, line)) {
            stringstream ss(line);
            string token;           
            getline(ss, token, ',');  
            if (token == className) 
                classFound = true;
            // Check if the line contains the target string 
            size_t found = line.find(newStudent);
            if (found != string::npos) {
                 studentFound = true; // Set the flag as the student is found
                // Remove that name and , with it from the line
                line.erase(found, len+1);  //+1 is to remove the comma after student name too
            }

            // Write the modified line to the temporary file
            tempFile << line << endl;
        }

        // Close the files
        classFile.close();
        tempFile.close();

        // Replace the original file with the temporary file
        remove("classes.txt");
        rename("temp_classes.txt", "classes.txt");

        if (studentFound) {
            cout << "Student removed from the class." << endl;
        } else {
            cout << "Error: Student not found in the class." << endl;
        }

        if(!classFound) {
            cout << "Error: Class not found." << endl;
        }

    } 
    else {
        cout << "Error opening files!" << endl;
    }
}

int noOfStudents(string &className) {
    ifstream file("classes.txt");
    string line;
    int commaCount = 0;

    while (getline(file, line)) {
        // Find the position of the class name in the line
        size_t pos = line.find(className);
        if (pos != string::npos) {
            // Count the commas in the line after the class name
            for (size_t i = pos + className.length(); i < line.length(); i++) {
                if (line[i] == ',') {
                    commaCount++;
                }
            }
            break; // We found the class, no need to continue searching
        }
    }

    return commaCount;
}


    // Functions to handle file I/O for class information
void saveAssignToFile(AssignmentsManager*classObj) {
    ofstream classFile("assignments.txt", ios::app);
   
    if (classFile.is_open()) {
        classFile <<classObj->getTitle() << ", " << classObj->getDescription() << ", " << classObj->getDeadline() << ", " << classObj->getAttachedFiles()<< ", " << classObj->getPointValue()<<", "<< classObj->getcurrentTeacher() <<endl;
   classFile.close();
    }
    else{
        cout<<"ERROR opening file"<<endl;
    }
}

    // Functions to handle file I/O for class information
void uploadAssignByStudent(AssignmentsManager*classObj) {
    ofstream classFile("uploadAssignments.txt", ios::app);
   
    if (classFile.is_open()) {
        classFile <<classObj->getTitle() << ", " << classObj->getDescription() << ", " << classObj->getDeadline() << ", " << classObj->getAttachedFiles()<< ", " << classObj->getcurrentTeacher() <<endl;
   classFile.close();
    }
    else{
        cout<<"ERROR opening file"<<endl;
    }
}

void updateAssignment(const string& assignTitle, const string& NameToUpdate, int choice){
 ifstream classFile("assignments.txt");
    ofstream tempFile("temp_assignments.txt"); // Temporary file to store modified data

    if (classFile.is_open() && tempFile.is_open()) {
        string line;
        bool assignmentTitle = false;
/*
: This while loop reads lines from the classFile until there are no more lines left to read. The getline function 
reads a line from the file and stores it in the line string variable. If there are more lines to read, the loop 
continues. If there are no more lines, the loop exits
*/       
        while (getline(classFile, line)) {
            stringstream ss(line);
            string token;
/*this means that we will start reading entire string stream till endof lines but i have put a delimeter here which
  is comma means when I willreach to comma the string before comma will be stored in token variable . After that I
   have moved ext to comma and will read file till next comma and will extraxt the next string*/            
            getline(ss, token, ',');  
            if (token == assignTitle) {
                assignmentTitle = true;

                if(choice == 1){
                tempFile << NameToUpdate <<", ";
                getline(ss, token); // Now storing Rest of the whole file in token like till endl (here teacher and description)
                tempFile << token << endl; // Writing the line stored in token variable here the teacher and description to the temp file
                }

                //FOR UPDATING DESCRIPTION
                else if(choice == 2){
                tempFile <<  assignTitle << ", " << NameToUpdate << ", "; // Write the updated class entry to the temp file
                getline(ss, token, ','); // Skip the old subject
                getline(ss, token); // Now storing Rest of the whole file in token like till endl (here teacher and description)
                tempFile << token << endl; // Writing the line stored in token variable here the teacher and description to the temp file
                }

                //TO UPDATE DUE DATE
                else if(choice == 3){
                string previousSubject;
                getline(ss, previousSubject, ',');  //saving previous subject name 
                tempFile <<  assignTitle << ", "<<previousSubject<<", "<<NameToUpdate<<", "; // Write the updated class entry to the temp file
                getline(ss, token, ','); // Skip the old Teacher
                getline(ss, token); // Now storing Rest of the whole file in token like till endl (here teacher and description)
                tempFile << token << endl; // Writing the line stored in token variable here the teacher and description to the temp file     
                }

                //FOR UPDATING Attached File
                else if(choice == 4){
                string previousDescription;
                string previousdDate;
                getline(ss, previousDescription, ',');  //saving previous Description  
                getline(ss, previousdDate, ',');  //saving previous Date 
                tempFile <<  assignTitle << ", "<<previousDescription<<", "<<previousdDate<<", "<<NameToUpdate<<", "; // Write the updated class entry to the temp file
                getline(ss, token, ','); // Skip the old Teacher
                getline(ss, token); // Now storing Rest of the whole file in token like till endl (here teacher and description)
                tempFile << token << endl; // Writing the line stored in token variable here the teacher and description to the temp file    
                }

                //FOR UPDATING MARKS 
                else if(choice == 5){
                string previousDescription;
                string previousdDate;
                string previousAttachedFile;
                getline(ss, previousDescription, ',');  //saving previous Description  
                getline(ss, previousdDate, ',');  //saving previous Date
                getline(ss, previousAttachedFile, ',');  //saving previous attached file name
                tempFile <<  assignTitle << ", "<<previousDescription<<", "<<previousdDate<<", "<<previousAttachedFile<<", "<<NameToUpdate<<", "; // Write the updated class entry to the temp file
                getline(ss, token, ','); // Skip the old Teacher
                getline(ss, token); // Now storing Rest of the whole file in token like till endl (here teacher and description)
                tempFile << token << endl; // Writing the line stored in token variable here the teacher and description to the temp file    
                }

                
                        
            } 
            else {
                tempFile << line << endl; // Write lines that don't match the class name to the temp file
            }
        }
        classFile.close();
        tempFile.close();

        if (assignmentTitle) {
            // Delete the original file and rename the temporary file
            remove("assignments.txt");  //Deleting classses.txt file
            rename("temp_assignments.txt", "assignments.txt");   //renaming "temp_classes.txt" to classes.tx
            cout << "\nAssignment Updated Successfully!\n";
        } 
        else {
            // The class was not found in the file
            remove("temp_assignments.txt");
            cout << "\nAssignment not found!\n";
        }

    }

    else{
        cout<<"ERROR opening file"<<endl;
    }   
}


};



//NOT WORKING 
class Submission {
private:
    int submissionID;
    string submissionTimestamp;
    string attachedFiles;
    string evaluationStatus;
    string feedback;
    Student &student;
    Teacher &teacher;

public:
// Function definitions for Submission class

 Submission(Student &student, Teacher &teacher) : student(student), teacher(teacher) {
    // Constructor
    // Implement initialization of submissionID and submissionTimestamp here
}

int getSubmissionID() const {
    return submissionID;
}

string getSubmissionTimestamp() const {
    return submissionTimestamp;
}

string getAttachedFiles() const {
    return attachedFiles;
}

string getEvaluationStatus() const {
    return evaluationStatus;
}

string getFeedback() const {
    return feedback;
}

Student& getStudent() {
    return student;
}

Teacher& getTeacher() {
    return teacher;
}
    void displaySubmissionInfo();
    string getCurrentTimeAsString();
};

class Grading {
private:
    int gradingID;
    int points;
    Submission &submission;

public:
    Grading(Submission &submission):submission(submission){}
    
int getGradingID() const {
    return gradingID;
}

int getPoints() const {
    return points;
}

Submission& getSubmission() {
    return submission;
}

void setPoints(int points) {
    this->points = points;
}
};

class Gradebook {
private:
     Grading* gradings; //for 100 students grade
    ClassesManager &classObj;

public:
    // Function definitions for Gradebook class
Gradebook(ClassesManager &classObj) : classObj(classObj) {
    // Constructor

}

void addGrading(Submission &submission) {
    //FOR ADDING A NEW GRADE ENTRY
}

void displayGradebook() {
    // displaying the gradebook here
}

double calculateClassAverage() {
    // calculating the class average and returning it as a float here
}
};

class Notification {
private:
    int notificationID;
    string notificationTimestamp;
    string notificationContent;
    User &user;

public:
    // Function definitions for Notification class
Notification(User &user) : user(user) {
    // Constructor
    // Implement initialization of notificationID and notificationTimestamp here
}

int getNotificationID() const {
    return notificationID;
}

string getNotificationTimestamp() const {
    return notificationTimestamp;
}

string getNotificationContent() const {
    return notificationContent;
}

User& getUser() {
    return user;
}

void setNotificationContent(string content) {
    notificationContent = content;
}

void displayNotification() {
    // Implement displaying the notification information here
}
   string getCurrentTimeAsString() {
    // DIDIN;T HAVE TIME FOR IMPLEMENTATION
}

};
