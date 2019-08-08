#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>

using namespace std;
struct Course {
    string key;
    string name;
    double hours;
    string grade;
    double pgrade;
};

double letterGrade(string grade){
    double pgrade;
    if(grade == "A"){
        pgrade = 4.00;
    }
    else if(grade == "A-"){
        pgrade = 3.67;
    }
    else if(grade == "B+"){
        pgrade = 3.33;
    }
    else if(grade == "B"){
        pgrade = 3.00;
    }
    else if(grade == "B-"){
        pgrade = 2.67;
    }
    else if(grade == "C+"){
        pgrade = 2.33;
    }
    else if(grade == "C"){
        pgrade = 2.00;
    }
    else if(grade == "D"){
        pgrade = 1.00;
    }
    else if(grade == "F"){
        pgrade = 0.00;
    }
    return pgrade;
}


int main(){
    int menuInput;
    int number = 0;
    string fileline;
    string key;
    string name;
    double hours;
    double shours = 0.00;
    string grade;
    double pgrade = 0.00;
    double points;
    double spoints = 0.00;
    double gpa;
    list<Course> semester;
    list<string> semesterload;

    do{
        cout << "\t-------------- Menu -------------\t" << "\n"
             << "1. Create A New Semester File\n"
             << "2. Load A Semester File\n"
             << "3. Exit Menu\n"
             << "Enter An Option: ";
        cin >> menuInput;
        if(menuInput == 1){
            cout << "\n\nCreating A New Semester File..." << endl;

            cout << "Enter the number of classes you're taking: ";
            cin >> number;
            cin.ignore(256, '\n');
            for(int i=0; i < number; i++){
                Course course;
                cout << "Enter course key: ";
                getline(cin, course.key);

                cout << "Enter course name: ";
                getline(cin, course.name);

                cout << "Enter course hours: ";
                cin >> course.hours;

                cout << "Enter course grade: ";
                cin.ignore(256, '\n');
                getline(cin, course.grade);
                course.pgrade = letterGrade(course.grade);

                semester.push_back(course);
                cout << "Course saved." << endl;
            }

            std::list<Course>::iterator it;
            cout << "\t-------------- Course -------------\t" << endl;
            for (it = semester.begin(); it != semester.end(); it++) {
                key = it->key;
                name = it->name;
                hours = it->hours;
                grade = it->grade;

                cout << key << "\t" << name << "\t\t" << hours << "\t" << grade << endl;
            }

            for (it = semester.begin(); it != semester.end(); it++) {
                hours = it->hours;
                grade = it->grade;
                pgrade = letterGrade(grade);
                points = hours*pgrade;
                shours += hours;
                spoints += points;
            }
            gpa = spoints / shours;
            cout << "Semester GPA: " << gpa << endl;

            cout << "Writing semester to text file..." << endl;
            ofstream file;
            file.open ("semester.txt");
            file << "\t-------------- Courses -------------\t" << endl;
            for (it = semester.begin(); it != semester.end(); it++) {
                key = it->key;
                name = it->name;
                hours = it->hours;
                grade = it->grade;

                file << key << "\t" << name << "\t\t" << hours << "\t" << grade << endl;
            }
            file.close();
            cout << "File saved." << endl;
        }
        else if(menuInput == 2){
            cout << "\n\nLoading A Semester File..." << endl;
            ifstream file;
            file.open("C:\\Users\\BMo\\Documents\\Personal Projects\\CPP\\GPACalculator\\semester.txt");
            if (!file) {
                cerr << "Unable to open file semester.txt";
                exit(1);   // call system to stop
            }
            file.ignore(10000,'\n');
            while (getline(file, fileline, '\n')) {
                Course course;
                stringstream iss(fileline);
                string tempStr;
                short cnt = 0;
                while (iss) {
                    iss >> tempStr;
                    if(cnt == 0)
                        course.key =tempStr;
                    else if(cnt == 1)
                        course.name = tempStr;
                    else if(cnt == 2)
                        course.hours = atof(tempStr.c_str());
                    else if(cnt == 3)
                        course.grade = tempStr;
                    ++cnt;
                    }
                semester.push_back(course);
            }
            file.close();


            std::list<Course>::iterator it;
            cout << "\t-------------- Course -------------\t" << endl;
            for (it = semester.begin(); it != semester.end(); it++) {
                key = it->key;
                name = it->name;
                hours = it->hours;
                grade = it->grade;

                cout << key << "\t" << name << "\t\t" << hours << "\t" << grade << endl;
            }

             for (it = semester.begin(); it != semester.end(); it++) {
                hours = it->hours;
                grade = it->grade;
                pgrade = letterGrade(grade);
                points = hours*pgrade;
                shours += hours;
                spoints += points;
            }
            gpa = spoints / shours;
            cout << "Semester GPA: " << gpa << endl;

            cout << "\n\n" << endl;
        }

        else if(menuInput == 3){
            return 0;
        }
        else{
            cout << "Please enter a valid menu option.\n" << endl;
        }
    } while ((menuInput != 1) || (menuInput != 2));

    return 0;
}
