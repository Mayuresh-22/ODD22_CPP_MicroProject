// ODD2022 CPP Microproject 2107003,2107004.
#include<iostream>
#include<cstdio>
#include<fstream>
#include<time.h>
using namespace std;

// Class for question selection
class QuestionPaper{
    public:
    int queno, quenolis[10], index=0;
    string line;

        // selecting unique question number
        int selectQueno(){
            int quenum;
            bool exist;
            do{
                quenum = rand() % 20 + 1;
                for(int i = 0; i <= 9; i++){
                    if(quenum == quenolis[i]){
                        exist = true;
                        break;
                    }
                    else{
                        exist = false;
                    }
                }
                if(exist == false){
                    quenolis[index] = quenum;
                    index++;
                    return quenum;
                }
            }while(exist == true);
        }

        // selecting questions
        string selectQues(int queno){
            string line;
            ifstream filein;
            filein.open("questionset.txt");
            // selecting questions
            for(int i = 1; i <= queno; i++){
                getline(filein, line);
                if(i == queno){
                    return line;
                }
            }
            filein.close();
        }
};

// Class for printing question paper in file
class PrintPaperInFile: public QuestionPaper{
    public:
        // printing questions in file
        void printPaper(string name, string div, int roll){
            ofstream fileout;
            fileout.open(name + "_Question_Paper.txt");
            fileout<<"Name: "<<name<<"\n";
            fileout<<"Div: "<<div<<"\n";
            fileout<<"Roll: "<<roll<<"\n";
            fileout<<"\n------ Question Paper ------\n";

            // printing questions in file and console
            srand(time(NULL));
            for(int i = 1; i <= 10; i++){
                queno = selectQueno();
                line = selectQues(queno);
                cout<<i<<" "<<line<<"\n";
                fileout<<i<<" "<<line<<"\n";
            }
            fileout.close();
        }
};

// Class for Login & Register and question paper generation for students
class Students: public PrintPaperInFile{
    string name, div, password;
    int roll;
    public:
        // Register & Login
        void header(){
            for(int i = 0; i < 67; i++){
                cout<<"-";
            }
            cout<<"\n";
            cout<<" ------ Welcome to Random Question Paper Generator software ------\n";
            cout<<"       ---- ODD2022 CPP Microproject by 2107003,2107004 ----\n";
            for(int i = 0; i < 67; i++){
                cout<<"-";
            }
            cout<<"\n";
            cout<<"1. Register\n";
            cout<<"2. Login\n";
            cout<<"3. Exit\n";
            int choice;
            cout<<"Enter your choice: ";
            cin>>choice;
            switch(choice){
                case 1:
                    regist();
                    break;
                case 2:
                    login();
                    break;
                case 3:
                    cout<<"\nExiting...\n";
                    exit(0);
                    break;
                default:
                    cout<<"Invalid Choice\n";
                    header();
            }
        }

        // Student Registration function
        void regist(){
            cout<<"\n------ Register ------\n";
            cout<<"Name: ";
            cin.ignore();
            getline(cin, name);
            cout<<"Password: ";
            getline(cin, password);

            //write to file
            // if user is already registered
            ifstream filein("users.txt");
            string line;
            bool exist = false;
            while(getline(filein, line)){
                if(line == name){
                    exist = true;
                    break;
                }
            }
            filein.close();
            if(exist == true){
                cout<<"User already registered\n\n";
                header();
            }
            else{
                ofstream file("users.txt", ios::app);
                file<<name<<"\n";
                file<<password<<"\n";
                file.close();
                cout<<"Registered successfully\n\n";
                getinfo();
                cout<<"\n------ Question Paper ------\n";

                printPaper(name, div, roll);
                cout<<"\n";
                header();
            }
        }

        // Student Login function
        void login(){
            cout<<"\n------ Login ------\n";
            cout<<"Name: ";
            cin.ignore();
            getline(cin, name);
            cout<<"Password: ";
            getline(cin, password);

            //read from file
            ifstream file("users.txt");
            string line;
            bool exist = false;
            while(getline(file, line)){
                if(line == name){
                    getline(file, line);
                    if(line == password){
                        exist = true;
                        break;
                    }
                }
            }
            file.close();
            if(exist == true){
                cout<<"Logged In successfully\n\n";
                getinfo();
                cout<<"\n------ Question Paper ------\n";
                printPaper(name, div, roll);
                cout<<"\n";
                header();
            }
            else{
                cout<<"Invalid Username or Password\n";
                header();
            }
        }

        // Student info
        void getinfo(){
            cout<<"------ Student Info ------\n";
            cout<<"Name: "<<name<<"\n";
            cout<<"Div: ";
            getline(cin, div);
            cout<<"Roll: ";
            cin>>roll;
        }

};

int main(){
    // creating object of class Students
    Students stud;
    // calling header function
    stud.header();
    
    return 0;
}