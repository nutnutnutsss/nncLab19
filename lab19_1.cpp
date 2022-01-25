#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    char name[100];
    int a,b,c,total;
    ifstream data;
    data.open(filename);
    string text;
    while(getline(data,text)){
        const char *t = text.c_str();
        char format[] = "%[^:]: %d %d %d";
        sscanf(t, format, &name, &a, &b, &c);
        total = a+b+c;
        names.push_back(name);
        scores.push_back(total);
        grades.push_back(score2grade(total));
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    cin >> command;
    if(toUpperStr(command) == "NAME" || toUpperStr(command) == "GRADE"){
        cin.ignore();
        getline(cin,key);
    }
}

void searchName(vector<string> names,vector<int> scores,vector<char> grade,string key){
    bool check = false;
    cout << "---------------------------------\n";
    for(unsigned int i = 0; i < names.size(); i++){
        if(toUpperStr(key) == toUpperStr(names.at(i))){
        check = true;
        cout << names.at(i) << "'s " << "score = " << scores.at(i) << "\n";
        cout << names.at(i) << "'s " << "grade = " << grade.at(i) << "\n";
        }
    }
    if(check == false) cout << "Cannot found." << "\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
    const char *x = key.c_str();
    bool check = false;
    cout << "---------------------------------\n";
    for(unsigned int i =0; i < names.size(); i++){
        if(*x == grades.at(i)){
            check = true;
            cout << names.at(i) << " (" << scores.at(i) << ")" << "\n";
        }
    }
    if(check == false) cout << "Cannot found." << "\n";
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
