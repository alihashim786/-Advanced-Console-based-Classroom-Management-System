#include <iostream>
#include "project.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <streambuf>


using namespace std;
//using namespace std::chrono;

int main()
{

    Student *students;
    students = new Student[500];

    Teacher *teachers;
    teachers = new Teacher[200];

    Student student;
    Teacher teacher;
    string username, password, name, emailAddress, contactNumber;
    bool login = false, regist = false;
    char choice, again;
    char quit;
    int choose, loginAs, teacherChoice, studentChoice;
    int studentIndex = 0, teacherIndex = 0;
    int loggedIn;
    string className, subject,description,currentTeacher;
    string assignmentTitle, assignmentDescription, deadlineDate, deadlineTime, assignmentDueDate, assignmentDueTime,attachedFileName;
    int setMarks;
    Student loggedInStudent;
    Teacher loggedInTeacher;
    ClassRoomFiles file; //to retrieve the function of file handling (for classrooms name, subject etc reading and writing)) 
    ClassesManager enrolledObject;
    AssignmentsManager *assignments = new AssignmentsManager(teacher, student);

    int noOfStudents = 0;


    system("cls");
    do
    {

        menu:
        cout << "\n\t---------------------- Menu ----------------------\n";
        cout << "\n\n1. Login";
        cout << "\n2. Register";
        cout << "\n3. Quit";
        cout << "\nChoice: ";
        cin >> choose;

        system("cls");
        switch (choose)
        {
        case 1:
        {

                again:
                cout << "\n\t---------------------- Login As ----------------------\n";

                cout << "\n\n1.Student";
                cout << "\n2.Teacher\n";
                cout << "Choice: ";
                cin >> loginAs;

                system("cls");

          switch (loginAs)
          {
            case 1:
            {
                cout << "\n\t---------------------- Login ----------------------\n";
                cout << "\n\nEnter Username: ";
                cin.ignore();
                getline(cin, username);
                
                cout << "\nEnter Password: ";
                password = student.getHiddenPassword();
                
                
                //student is the object of the student class
                student.setUsername(username); //goes in user class because student class is a subclass of user class
                student.setPassword(password);  //goes in user class because student class is a subclass of user class
                
                login = student.loginStudent();

                do
                {
                    if (login)
                    {
                        
                        cout << "\n\nSuccessful Login!\n\n";
                    //saving students within program by saving in pointer array of
                        for (int j = 0; j < 500; j++)
                        {
                            if ((students[j].getUsername()) == (student.getUsername()))
                            {
                                studentIndex = j;
                                break;
                            }
                        }
                    
                        loggedInStudent = students[studentIndex];
                        loggedIn = 1;
                    }

                    else
                    {
                        cout << "\nLogin Failed!\n\nTry Again!\n\n";
                        system("pause");
                        system("cls");

                        cout << "\n\t---------------------- Login ----------------------\n";
                        cout << "\nEnter Username: ";
                        cin.ignore();
                        getline(cin, username);

                        cout << "\nEnter Password: ";
                        password = student.getHiddenPassword();
                    
                        student.setUsername(username);
                        student.setPassword(password);
                        
                        login = student.loginStudent(); 
                    }

                } while (login != true);

                system("cls");

            //we will approach here only when student success to login    
                cout<<"WELCOME "<<teacher.getUsername()<<"\n\n";
                do{

                system("pause");
                system("cls");

                cout << "\n\t---------------------- ClassRoom ----------------------\n";
                cout<<"\n1.  View Class Details"; //here we can also see enrolled students in a class
                cout<<"\n2.  View All Classes";
                cout<<"\n3.  Join Class";
                cout<<"\n4.  Leave Class";
                cout<<"\n5.  View Assignment Details";
                cout<<"\n6.  View Assignments";
                cout<<"\n7.  Upload Assignment";
                cout<<"\n8.  Change Password";
                cout<<"\n9.  See Password";
                cout<<"\n10. See Notifications";
                cout<<"\n11. Logout";
                cout<<"\n0.  Quit Program"; //to finish the program
                cout<<"\n\nChoice: ";
                cin>>studentChoice;


                system("cls");

                switch(studentChoice){
                    
                    
                    case 1:
                    {
                            // SHOWING THIS THROUGH THE DISPLAY FUNCTION OF ClassManager
                            cout << "\n\t---------------------- View Class Details ----------------------\n";
                            cout << "Enter Class Name: ";
                            cin.ignore();
                            getline(cin, className);

                            // THIS THING IS EXPLAINED ON PAPER WRITTEN PROJECT ON TOP
                            noOfStudents = file.noOfStudents(className);
                            noOfStudents = noOfStudents - 3;
                            bool classFound = false;

                            string enrollStudents; // to store the line after description from classes.txt
                            // Search the class by its name in the file and display its details
                            {
                                
                                ifstream classFile("classes.txt");
                                if (classFile.is_open())
                                {
                                    string line;

                                    
                                    while (getline(classFile, line))
                                    {
                                        stringstream ss(line);
                                        string token;

                                        /*this means that we will start reading entire string stream till endof lines but i have put a delimeter here which
                                        is comma means when I willreach to comma the string before comma will be stored in token variable . After that I
                                        have moved ext to comma and will read file till next comma and will extraxt the next string*/
                                        getline(ss, token, ',');
                                        if (token == className)
                                        {
                                            classFound = true;
                                            string subject, teacher, description;
                                            getline(ss, subject, ',');
                                            getline(ss, teacher, ',');
                                            getline(ss, description, ',');
                                            getline(ss, enrollStudents);
                                            ClassesManager foundClass(token, subject, teacher, description);
                                            foundClass.displayClassInfo();
                                            cout << "Number of Enrolled Students in " << className << " : " << noOfStudents << "\n";
                                            break;
                                        }
                                    }

                                    if (!classFound)
                                    {
                                        cout << "\n\" Class not found \"\n";
                                    }
                                    classFile.close();
                                }
                                else
                                {
                                    cout << "\nError opening class file\n";
                                }
                            }


                            if(classFound){
                            string choice;
                            cout << "Do you want to see Enrolled Students in " << className << "? (y/n) : ";
                            cin >> choice;
                            if (choice == "y" || choice == "Y" || choice == "yes" || choice == "Yes")
                            {
                                cout << "\n\t---------------------- View Enrolled Students ----------------------\n";
                                cout << enrollStudents << "\n\n";
                            }
                            }
                            break;
                    }

                    case 2:
                    {
                            cout << "\n\t---------------------- All Classes ----------------------\n";
                            // Read all classes from the file and display them
                            file.readFromFile("classes.txt"); 
                            break;
                    }

                    case 3:{
                        cout << "\n\t---------------------- Join Class ----------------------\n";
                        cout << "\nEnter Class Name: ";
                        cin.ignore();
                        getline(cin, className);

                            enrolledObject.setClassName(className);
                            string studentName;
                            cout << "Enter Your Full Name: ";
                            getline(cin, studentName);

                            /*  IMPORTANT ( EXPLAINED IN PAPER TOO )
                            Counting no of students on the basis of no of commas in a  spacific line. 4 names are fixed for classname , subject,
                            teacher and description and 4 names means 3 so if theer are only 4 names ina line that means there will be 3 commas
                            and none of them ae students AND rest of commas denotes that no of students
                            */
                            noOfStudents = file.noOfStudents(className);
                            noOfStudents = noOfStudents - 3;

                            if (noOfStudents < 5) //maximum students for one class is 5
                            {
                                file.AddingStudent(className, studentName); // adding student name to cla
                            }

                            else
                            {
                                cout << "Sorry Clasroom \'" << className << "\' is full (maximum limit of students is 5)\n";
                            }
        
                        
                        break;
                    }

                    case 4:{
                        cout << "\n\t---------------------- Leave Class ----------------------\n";
                        cin.ignore();
                        cout << "Enter Class Name: ";
                        getline(cin, className);
                        enrolledObject.setClassName(className);
                        string st;
                        cout << "Enter Student Name: ";
                        getline(cin, st);

                        file.RemovingStudent(className, st); // removing student name to file classes.txt
                        break;
                    }


                    case 5:{
                        //view assignment details
                        // SHOWING THIS THROUGH THE DISPLAY FUNCTION OF ClassManager
                            cout << "\n\t---------------------- View Assignment Details ----------------------\n";
                            cout << "Enter Assignment Title: ";
                            cin.ignore();
                            getline(cin, assignmentTitle);
                            bool titleFound = false;

                            ifstream classFile("assignments.txt");
                                if (classFile.is_open())
                                {
                                    string line;

                                    
                                    while (getline(classFile, line))
                                    {
                                        stringstream ss(line);
                                        string token;

                                        /*this means that we will start reading entire string stream till endof lines but i have put a delimeter here which
                                        is comma means when I willreach to comma the string before comma will be stored in token variable . After that I
                                        have moved ext to comma and will read file till next comma and will extraxt the next string*/
                                        getline(ss, token, ',');
                                        if (token == assignmentTitle)
                                        {
                                            titleFound = true;
                                            string  description, deadline, attachedFile, totalMarks,teacherName;
                                            getline(ss, description, ',');
                                            getline(ss, deadline, ',');
                                            getline(ss, attachedFile, ',');
                                            getline(ss, totalMarks, ',');
                                            getline(ss, teacherName, ',');
                                            int pointValue = stoi(totalMarks);
                                            teacher.setUsername(teacherName);
                                            assignments = new AssignmentsManager(token, description, deadline, attachedFile, pointValue, teacher, student);
                                            assignments->displayAssignmentInfo();

                                        break;
                                        }
                                    }

                                    if (!titleFound)
                                    {
                                        cout << "\n\" Assignment not found \"\n";
                                    }
                                    classFile.close(); 

                                }
                                else
                                {
                                    cout << "\nError opening class file\n";
                                }


                    break;
                    }  


                    case 6:
                    {
                            cout << "\n\t---------------------- All Assignments ----------------------\n";
                            // Read all classes from the file and display them
                            file.readFromFile("assignments.txt");
                            break;
                    }

                    case 7:{
                        //upload assignment. 
                        /*
                        HERE BASCIALLY I WILL CREATE A NEW FILE uploadAssignment.txt AND I WILL WRITE ASSIGNMENT TITLE AS STUDENT NAME 
                        AND WILL WRITE REST OF THINGS BUT WILL CHANGE THE DEADLINE TO CURRENT TIME AND ATTCHED FILE TO STUDENT FILE
                        */
                        cout << "\n\t---------------------- Upload Assignment ----------------------\n";
                        cout << "Enter Assignment Title for Upload: ";
                        cin.ignore();
                        getline(cin, assignmentTitle);

                        
                       
                        bool check = file.ClassOrAssignExists(assignmentTitle, "assignments.txt");
                        if(check){
                           cout<<"\n Enter Your File Name to Upload: ";
                           getline(cin, attachedFileName); 

                           ifstream classFile("assignments.txt");
                            if (classFile.is_open())
                            {
                                string line;

                                
                                while (getline(classFile, line))
                                {
                                    stringstream ss(line);
                                    string studentName = student.getUsername();
                                    //getting current in format YYYY-MM-DD|HH:MM
                                    string currentTime = assignments->getCurrentTimeAsString();
                                    string  title,description, deadline, attachedFile, totalMarks,teacherName;
                                        getline(ss, title, ',');
                                        getline(ss, description, ',');
                                        getline(ss, deadline, ',');
                                        getline(ss, attachedFile, ',');
                                        getline(ss, totalMarks, ',');
                                        getline(ss, teacherName, ',');
                                        
                                        int pointValue =20;


                                        teacher.setUsername(teacherName);
                                        assignments = new AssignmentsManager(studentName, description, currentTime, attachedFileName, pointValue, teacher, student);
                                        assignments->displayStudentAssignmentInfo();
                                        // Save cassignment information to the file
                                        file.uploadAssignByStudent(assignments); // sending object classes manager to file handilng class
                                        break;
                                }
                                classFile.close(); 

                            }  
                                else
                            {
                                cout << "\nError opening class file\n";
                            }
                        }
                        else{
                            cout << "Assignment not found\n";
                        }


                        break;
                    }

                    case 8:
                    {
                        //change password here
                    break;
                    }

                    case 9:
                    {
                        cout << "\n\t---------------------- Password ----------------------\n\n";
                        cout<<"\nYour Password is : "<<student.getPassword()<<endl;

                        break;
                    }

                    case 10:{
                        cout << "\n\t----------------------Notificaton ----------------------\n\n";
                        cout<<"No Notifications..."<<endl;



                        break;
                     }

                    case 11:{
                        loggedInStudent.logout();  //fuction in User class
                        studentChoice = 0;
                        break;
                    }

                    case 0:{
                        exit(0);
                    }

                    default:{
                        cout << "Invalid choice\n";
                        break;
                    }    

                } //student menu wala switch ends here

               }while(studentChoice != 0);
            
            break;
            }

            case 2:
            {
                cout << "\n\t---------------------- Login ----------------------\n";
                cout << "\n\nEnter Username: ";
                cin.ignore();
                getline(cin, username);
                cout << "\nEnter Password: ";
                password = teacher.getHiddenPassword();
                
                teacher.setUsername(username);
                teacher.setPassword(password);
                login = teacher.loginTeacher();

                do
                {
                    if (login)
                    {
                        //For further file handling changing the indexs
                        cout << "\n\nSuccessful Login!\n\n";
                        for (int j = 0; j < 200; j++)  //because In file there are not more than 200 teachers
                        {
                            if ((teachers[j].getUsername()) == (teacher.getUsername()))
                            {
                                teacherIndex = j;
                                break;
                            }
                        }
                    
                        loggedIn = 2;
                        loggedInTeacher = teachers[teacherIndex];
                    }

                    else
                    {
                        cout << "\nLogin Failed!\nTry Again!\n\n";
                        system("pause");  //presss enter
                        system("cls");

                        cout << "\n\t---------------------- Login ----------------------\n";
                        cout << "\n\nEnter Username: ";
                        cin.ignore();
                        getline(cin, username);
                        cout << "\nEnter Password: ";
                        password = teacher.getHiddenPassword();

                        teacher.setUsername(username); //goes in user class because student class is a subclass of user class
                        teacher.setPassword(password);//goes in user class because student class is a subclass of user class
                        login = teacher.loginTeacher();
                    }

                } while (login != true);
               
                
                system("cls");

            //we will approach here only when teacher success to login    
                cout<<"WELCOME "<<teacher.getUsername()<<"\n\n";
              do{

                system("pause");
                system("cls");

                cout << "\n\t---------------------- ClassRoom ----------------------\n";
                cout<<"\n\n1.  Create Class";
                cout<<"\n2.  Update Class";
                cout<<"\n3.  Delete Class";
                cout<<"\n4.  View Class Details"; //here we can also see enrolled students in a class
                cout<<"\n5.  View All Classes";
                cout<<"\n6.  Add Student in a Class";
                cout<<"\n7.  Remove Student from Class";
                cout<<"\n8.  Create Assignment";
                cout<<"\n9.  Update Assignment";
                cout<<"\n10. Delete Assignment";
                cout<<"\n11. View Assignment Details";
                cout<<"\n12. View All Assignments";
                cout<<"\n13.  Change Password";
                cout<<"\n14.  See Password";
                cout<<"\n15.  See Notifications";
                cout<<"\n16. Logout";
                cout<<"\n0. Quit Program"; //to finish the program
                cout<<"\n\nChoice: ";
                cin>>teacherChoice;

                system("cls");

                switch(teacherChoice){
                    case 1:
                    {
                            cout << "\n\t---------------------- Create Class ----------------------\n";
                            cout << "\nEnter Class Name: ";
                            cin.ignore();
                            getline(cin, className);
                            cout << "\nEnter Subject: ";
                            getline(cin, subject);

                            currentTeacher = teacher.getUsername();

                            cout << "\nEnter Description: ";

                            getline(cin, description);

                            // Create a new class object
                            ClassesManager newClass(className, subject, currentTeacher, description);

                            // Save class information to the file
                            file.saveClassToFile(newClass); //sending object classes manager to file handilng class

                            cout << "\nClass Created Successfully!\n";
                            
                            break;
                    }

                    case 2:
                    {
                            cout << "\n\t---------------------- Update Class ----------------------\n";
                            cout << "Enter Class Name to Update: ";
                            cin.ignore();
                            getline(cin, className);

                            bool check = file.ClassOrAssignExists(className, "classes.txt");

                            if(check == false){
                                cout << "\nClass Not Found\n";
                            break;
                            }

                        int teacherChoice2;
                           
                            cout<<"\nWhat would you like to update?\n\n";
                            cout<<"\n1. Class Name";
                            cout<<"\n2. Subject Name";
                            cout<<"\n3. Teacher Name";
                            cout<<"\n4. Description";
                            cout<<"\n0. Go Back:\n";
                            cout<<"\nChoice: ";
                            cin>>teacherChoice2;

                            if(teacherChoice2 == 1){
                            string newClassName;    
                            cout<<"\nEnter New Class Name: ";
                            cin.ignore();
                            getline(cin, newClassName); 
                            enrolledObject.setClassName(newClassName); //saving new class name to ClassesManager class too
                            
                            /* CAN DO  ClassesManager newClass(className); 
                            then i have to make similar constructor un that class and will send the object to 
                            Classroom file class   */

                            /* CAN ALSO DO By saving new info to classes manager class
                            ClasseSManager newClass(newClassName, enrolledObject.getSubject(), enrolledObject.getTeacher(), enrolledObject.getDescription());
                            file.updateClass(newClass) //update class ki prototype bhi chnage karni paray gi
                            Now if you call Display function from ClassesManager class it will display the new info
                            */

                            // Call the updateClassSubject function to update the class subject
                            file.updateClass(className, newClassName, teacherChoice2);
                            break;
                            }

                            else if(teacherChoice2 == 2){
                                 // Ask for the new subject
                            string newSubject;
                            cout << "Enter new Subject Name: ";
                            cin.ignore();
                            getline(cin, newSubject);
                            enrolledObject.setSubject(newSubject);

                            // Call the updateClassSubject function to update the class subject
                            file.updateClass(className, newSubject, teacherChoice2);
                            break;
                            }


                            else if(teacherChoice2 == 3){
                             // Ask for the new subject
                            string newTeacher;
                            cout << "\nEnter new Teacher Name: ";
                            cin.ignore();
                            getline(cin, newTeacher);
                            enrolledObject.setTeacher(newTeacher);

                            // Call the updateClass function to update the class teacher
                            file.updateClass(className, newTeacher, teacherChoice2);
                            break;
                            }       
                            
                            else if(teacherChoice2 == 4){  
                            string newDescription;
                            cout << "\nEnter new Description: ";
                            cin.ignore();
                            getline(cin, newDescription);
                            enrolledObject.setDescription(newDescription);
                            
                            // Call the updateClassSubject function to update the class decsription
                            file.updateClass(className, newDescription, teacherChoice2);
                            break;

                            }
                            
                            else if(teacherChoice2 == 0){
                            break;    
                            }

                            else{
                                cout<<"\n\nInvalid Choice!\n\n";
                                break;
                            }

                    break;
                    }

                    case 3:
                    {
                            cout << "\n\t---------------------- Delete Class ----------------------\n";
                            cout << "Enter Class Name to Delete: ";
                            cin.ignore();
                            getline(cin, className);

                            if(file.ClassOrAssignExists(className, "classes.txt")){
                            file.deleteClass(className); // global function to delete class by seeing class name
                            }
                            else{
                                cout << "\nClass Not Found\n";
                            }
                    break;
                    }

                    case 4:
                    {
                            // SHOWING THIS THROUGH THE DISPLAY FUNCTION OF ClassManager
                            cout << "\n\t---------------------- View Class Details ----------------------\n";
                            cout << "Enter Class Name: ";
                            cin.ignore();
                            getline(cin, className);
                            bool classFound = false;

                            // THIS THING IS EXPLAINED ON PAPER WRITTEN PROJECT ON TOP
                            noOfStudents = file.noOfStudents(className);
                            noOfStudents = noOfStudents - 3;

                            string enrollStudents; // to store the line after description from classes.txt
                            // Search the class by its name in the file and display its details
                            {
                                ifstream classFile("classes.txt");
                                if (classFile.is_open())
                                {
                                    string line;

                                    
                                    while (getline(classFile, line))
                                    {
                                        stringstream ss(line);
                                        string token;

                                        /*this means that we will start reading entire string stream till endof lines but i have put a delimeter here which
                                        is comma means when I willreach to comma the string before comma will be stored in token variable . After that I
                                        have moved ext to comma and will read file till next comma and will extraxt the next string*/
                                        getline(ss, token, ',');
                                        if (token == className)
                                        {
                                            classFound = true;
                                            string subject, teacher, description;
                                            getline(ss, subject, ',');
                                            getline(ss, teacher, ',');
                                            getline(ss, description, ',');
                                            getline(ss, enrollStudents);
                                            ClassesManager foundClass(token, subject, teacher, description);
                                            foundClass.displayClassInfo();
                                            cout << "Number of Enrolled Students in " << className << " : " << noOfStudents << "\n";
                                            break;
                                        }
                                    }

                                    if (!classFound)
                                    {
                                        cout << "\n\" Class not found \"\n";
                                    }
                                    classFile.close();
                                }
                                else
                                {
                                    cout << "\nError opening class file\n";
                                }
                            }

                            if(classFound){
                            string choice;
                            cout << "Do you want to see Enrolled Students in " << className << "? (y/n) : ";
                            cin >> choice;
                            if (choice == "y" || choice == "Y" || choice == "yes" || choice == "Yes")
                            {
                                cout << "\n\t---------------------- View Enrolled Students ----------------------\n";
                                cout << enrollStudents << "\n\n";
                            }
                            }
                            break;
                    }

                    case 5:
                    {
                            cout << "\n\t---------------------- All Classes ----------------------\n";
                            // Read all classes from the file and display them
                            file.readFromFile("classes.txt");
                            break;
                    }

                    case 6:
                    {
                            cout << "\n\t---------------------- Add Student to Class ----------------------\n";
                            cin.ignore();
                            cout << "Enter Class Name: ";
                            getline(cin, className);
                            enrolledObject.setClassName(className);
                            string studentName;
                            cout << "Enter Student Name: ";
                            getline(cin, studentName);

                            /*  IMPORTANT ( EXPLAINED IN PAPER TOO )
                            Counting no of students on the basis of no of commas in a  spacific line. 4 names are fixed for classname , subject,
                            teacher and description and 4 names means 3 so if theer are only 4 names ina line that means there will be 3 commas
                            and none of them ae students AND rest of commas denotes that no of students
                            */
                            noOfStudents = file.noOfStudents(className);
                            noOfStudents = noOfStudents - 3;

                            if (noOfStudents < 5) //maximum students for one class is 5
                            {
                                file.AddingStudent(className, studentName); // adding student name to cla
                            }

                            else
                            {
                                cout << "Clasroom \'" << className << "\' is full (maximum limit of students is 5)\n";
                            }

                    break;
                    }

                    case 7:
                    {
                            cout << "\n\t---------------------- Remove Student from Class ----------------------\n";
                            cin.ignore();
                            cout << "Enter Class Name: ";
                            getline(cin, className);
                            enrolledObject.setClassName(className);
                            string st;
                            cout << "Enter Student Name: ";
                            getline(cin, st);

                            //  enrolledObject.removeStudent(st);

                            file.RemovingStudent(className, st); // removing student name to file classes.txt
                    break;
                    }

                    case 8:
                    {

                    cout << "\n\t---------------------- Create Assignment ----------------------\n";
                    cout << "\nEnter Assigment Title: ";
                    cin.ignore();
                    getline(cin, assignmentTitle);
                    cout << "\nEnter Assignment Description: ";
                    getline(cin, assignmentDescription);

                    while (true)
                    {
                        cout << "\nEnter Deadline Date (yyyy-mm-dd) : ";

                        getline(cin, deadlineDate);

                        cout << "\nEnter Deadline Time ( 24 hrs Formating HH-MM ): ";
                        getline(cin, deadlineTime);

                        assignmentDueDate = deadlineDate + "|" + deadlineTime;

                        AssignmentsManager deadline(teacher, student);

                        if (deadline.isValid(assignmentDueDate))
                        {
                        break;
                        }
                        cout << "Lets Try again\n";
                    }

                    cout << "\nEnter Attached File Name :";
                    getline(cin, attachedFileName);

                    cout << "\nSet Marks for Assignment : ";
                    cin >> setMarks;
                    cout << endl
                         << endl;

                    assignments = new AssignmentsManager(assignmentTitle, assignmentDescription, assignmentDueDate, attachedFileName, setMarks, teacher, student);
                    assignments->displayAssignmentInfo();
                    // Save cassignment information to the file
                    file.saveAssignToFile(assignments); // sending object classes manager to file handilng class

                    cout << "\nAssignment Created Successfully!\n";

                    break;
                    }

                    case 9:
                    {
                        cout << "\n\t---------------------- Update Assignment ----------------------\n";
                        cout << "Enter Assignment Title to Update: ";
                        cin.ignore();
                        getline(cin, assignmentTitle);

                        bool check = file.ClassOrAssignExists(assignmentTitle, "assignments.txt");

                        if (check == false)
                        {
                                    cout << "\nAssignment Not Found\n";
                                    break;
                        }

                        int teacherChoice2;

                        cout << "\nWhat would you like to update?\n\n";
                        cout << "\n1. Assignment Title";
                        cout << "\n2. Assignment Description";
                        cout << "\n3. Assignment Deadline";
                        cout << "\n4. Attached File";
                        cout << "\n5. Update Total Marks";
                        cout << "\n0. Go Back";
                        cout << "\nChoice: ";
                        cin >> teacherChoice2;

                        if (teacherChoice2 == 1)
                        {
                            string newAssignTitle;
                            cout << "\nEnter New AssignmentTitle: ";
                            cin.ignore();
                            getline(cin, newAssignTitle);
                            assignments->setTitle(newAssignTitle);

                            file.updateAssignment(assignmentTitle, newAssignTitle, teacherChoice2);
                            break;
                        }

                        else if (teacherChoice2 == 2)
                        {
                        
                            string newDescription;
                            cout << "Enter new Assignment Description: ";
                            cin.ignore();
                            getline(cin, newDescription);
                            assignments->setDescription(newDescription);

                            // Call the updateClassSubject function to update the class subject
                            file.updateAssignment(assignmentTitle, newDescription, teacherChoice2);
                            break;
                        }

                        else if (teacherChoice2 == 3)
                        {

                            string newAssignmentDueDate, newdeadlineDate, newdeadlineTime;
                            cin.ignore();

                            while (true)
                            {
                            cout << "\nEnter new Date: ";
                            getline(cin, newdeadlineDate);

                            cout << "\nEnter new Time ( Time 24 hrs Formating HH-MM ): ";
                            getline(cin, newdeadlineTime);

                            newAssignmentDueDate = newdeadlineDate + "|" + newdeadlineTime;

                            AssignmentsManager newdeadline(teacher, student);

                            if (newdeadline.isValid(newAssignmentDueDate))
                            {
                                    break;
                            }
                            cout << "Lets Try again\n";
                            }

                            assignments->setDeadline(newAssignmentDueDate);
                            // Call the updateClass function to update the class teacher
                            file.updateAssignment(assignmentTitle, newAssignmentDueDate, teacherChoice2);
                            break;
                        }

                        else if (teacherChoice2 == 4)
                        {
                            string newAttachedFile;
                            cout << "\nEnter new Attached File Name: ";
                            cin.ignore();
                            getline(cin, newAttachedFile);
                            assignments->setDescription(newAttachedFile);

                            file.updateAssignment(assignmentTitle, newAttachedFile, teacherChoice2);
                            break;
                        }

                        else if (teacherChoice2 == 5)
                        {
                            int newMarks;
                            cout << "\nEnter new Total Marks: ";
                            cin >> newMarks;
                            assignments->setPointValue(newMarks);
                            string number = to_string(newMarks);
                            file.updateAssignment(assignmentTitle, number, teacherChoice2);
                            break;
                        }

                        else if (teacherChoice2 == 0)
                        {
                            break;
                        }

                        else
                        {
                            cout << "\n\nInvalid Choice!\n\n";
                            break;
                        }

                    break;
                    }

                    case 10:{
                        //delete assignments
                        cout << "\n\t---------------------- Delete Assignment ----------------------\n";
                            cout << "Enter Assignment Title to Delete: ";
                            cin.ignore();
                            getline(cin, assignmentTitle);

                            if(file.ClassOrAssignExists(assignmentTitle, "assignments.txt")) { 
                                file.deleteAssignment(assignmentTitle); // global function to delete assignment by seeing assignment name

                            }
                            else{
                                cout << "\nAssignment Not Found\n";
                            }
                            
                    break;
                    }

                    case 11:{
                        //view assignment details
                        // SHOWING THIS THROUGH THE DISPLAY FUNCTION OF AssignmentsManager
                            cout << "\n\t---------------------- View Assignment Details ----------------------\n";
                            cout << "Enter Assignment Title: ";
                            cin.ignore();
                            getline(cin, assignmentTitle);
                            bool titleFound = false;

                            ifstream classFile("assignments.txt");
                                if (classFile.is_open())
                                {
                                    string line;

                                    
                                    while (getline(classFile, line))
                                    {
                                        stringstream ss(line);
                                        string token;

                                        /*this means that we will start reading entire string stream till endof lines but i have put a delimeter here which
                                        is comma means when I willreach to comma the string before comma will be stored in token variable . After that I
                                        have moved ext to comma and will read file till next comma and will extraxt the next string*/
                                        getline(ss, token, ',');
                                        if (token == assignmentTitle)
                                        {
                                            titleFound = true;
                                            string  description, deadline, attachedFile, totalMarks,teacherName;
                                            getline(ss, description, ',');
                                            getline(ss, deadline, ',');
                                            getline(ss, attachedFile, ',');
                                            getline(ss, totalMarks, ',');
                                            getline(ss, teacherName, ',');
                                            int pointValue = stoi(totalMarks);
                                            teacher.setUsername(teacherName);
                                            assignments = new AssignmentsManager(token, description, deadline, attachedFile, pointValue, teacher, student);
                                            assignments->displayAssignmentInfo();

                                        break;
                                        }
                                    }

                                    if (!titleFound)
                                    {
                                        cout << "\n\" Assignment not found \"\n";
                                    }
                                    classFile.close(); 

                                }
                                else
                                {
                                    cout << "\nError opening class file\n";
                                }


                    break;
                    }  

                    case 12:{
                    
                            cout << "\n\t---------------------- All Assignments ----------------------\n";
                            // Read all classes from the file and display them
                            file.readFromFile("assignments.txt");
                            break;
                    
                    }

                    case 13:
                    {
                        //change password here
                    break;
                    }

                    case 14:
                    {
                        cout << "\n\t---------------------- Password ----------------------\n\n";
                        cout<<"\nYour Password is : "<<teacher.getPassword()<<endl;

                        break;
                    }

                    case 15:{
                        cout << "\n\t----------------------Notificaton ----------------------\n\n";
                        cout<<"No Notifications..."<<endl;



                        break;
                     }

                    case 16:{
                        loggedInTeacher.logout();
                        teacherChoice=0;
                        break;
                    }

                    case 0:{
                        exit(0);
                    }

                    default:{
                        cout << "Invalid choice\n";
                        break;
                    }    

                } //teacher menu wala switch ends here
              
              }while(teacherChoice!=0);

            break;
            }  //loginAs teacher case ends here

            default:
            {
                cout << "Invalid Choice!\n\n";
                //goto again;
                break;
            }

          } //loginAs switch ends here

        break;
        } //main case 1 ends here which was of login 

        system("cls");


        case 2:
        {

           again2:
            cout << "\n\t---------------------- Registration As ----------------------\n";

            cout << "\n\n1.Student";
            cout << "\n2.Teacher\n";
            cout << "Choice: ";
            cin >> loginAs;

            system("cls");
            switch (loginAs)
            {
            case 1:
            {
                cout << "\n\t---------------------- Registration ----------------------\n";
                cout<<"\n\nEnter your full name : ";
                cin.ignore();
                getline(cin, name);
                cout<<"Enter Email Address : ";
                
                while(true){
                   
                getline(cin,emailAddress);
                bool b = student.validateEmail(emailAddress);
                if(b){
                    break;
                }
                cout<<"Please enter a valid email address : ";
                }
                cout <<"Enter Contact Number : ";
                while(true){
                getline(cin,contactNumber);
                bool d=student.validatePhone(contactNumber);
                if(d){
                break;    
                }
                cout<<"Please enter a valid contact number : ";
                }

                cout << "Enter Username (should be without spaces and uppercase letters) : ";
                
                while(true){
                        
                getline(cin, username);
                
                bool e = student.isValidUsername(username);
                if(e==true){
                    break;
                }
                cout<<"\nInvalid Username. Enter Again (should be without spaces and uppercase letters) : ";
                }

                cout << "\nEnter Password: ";
                while(true){
                
                getline(cin, password);
                bool a = student.checkPassword(password);
                if(a==true){
                    break;
                }
                cout<<"\n.Invalid Password Format. Passowrd Must contain :\n-> Atleast one UpperCase and"; 
                cout<<"LowerCase\n-> Atleats 6 characters Long\n-> Must not contain Spaces\n-> Atleast One digit\n";
                cout<<"Enter Again : ";
                }

                student.setName(name);
                student.setEmailAddress(emailAddress);
                student.setContact(contactNumber);
                student.setUsername(username);
                student.setPassword(password);
                
                regist = student.registerStudent();
                break;
            }

            case 2:
            {
                cout << "\n\t---------------------- Registration ----------------------\n";
                cout<<"\n\nEnter your full name : ";
                cin.ignore();
                getline(cin, name);
                cout<<"Enter Email Address : ";
                
                while(true){
                   
                getline(cin,emailAddress);
                bool b = teacher.validateEmail(emailAddress);
                if(b){
                    break;
                }
                cout<<"Please enter a valid email address : ";
                }
                
                cout <<"Enter Contact Number : ";
                
                while(true){
                
                getline(cin,contactNumber);
                bool d=teacher.validatePhone(contactNumber);
                if(d){
                break;    
                }
                cout<<"Please enter a valid contact number : ";
                }

                cout << "Enter Username (should be without spaces and uppercase letters) : ";
                
                while(true){
                        
                getline(cin, username);
                
                bool e = teacher.isValidUsername(username);
                if(e==true){
                    break;
                }
                cout<<"\nInvalid Username. Enter Again (should be without spaces and uppercase letters) : ";
                }

                cout << "\nEnter Password: ";
                while(true){
                
                getline(cin, password);
                bool a = teacher.checkPassword(password);
                if(a==true){
                    break;
                }
                cout<<"\n.Invalid Password Format. Passowrd Must contain :\n-> Atleast one UpperCase and"; 
                cout<<"LowerCase\n-> Atleats 6 characters Long\n-> Must not contain Spaces\n-> Atleast One digit\n";
                cout<<"Enter Again : ";
                }


                teacher.setName(name);
                teacher.setEmailAddress(emailAddress);
                teacher.setContact(contactNumber);
                teacher.setUsername(username);
                teacher.setPassword(password);
                regist = teacher.registerTeacher();
                break;
            }

            default:
            {
                cout << "Invalid Choice!\n\n";
                system("pause");
                system("cls");
                goto again2;
            }
            break;
            }

            if (regist)
            {
                cout << "\n\nSuccessful Registration!\n\n";
            }

            else
            {
                cout << "\n\nRegistration Failed!\n\n";
            }

            system("pause");
            break;
        }

        case 3:
        {
            quit = 'q';
            system("cls");
            break;
        }

        
        
        default:
        {
            cout << "Invalid Choice!\n\n";
            system("pause");
            system("cls");
            break;
        }
        break;
      }

    } while (quit != 'Q' && quit != 'q');

    return 0;
}