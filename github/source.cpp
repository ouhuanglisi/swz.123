#include<iostream>
#include<iomanip>
#include<limits>
#include<exception>
#include<string>
#include<ctime>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;
class User {
protected:
    string username;
    string password;
    string role;

public:
    User(string u, string p, string r)
        : username(u), password(p), role(r) {}

    bool login(string pwd) {
        return password == pwd;
    }
    virtual ~User() {}
    string getRole() { return role; }
    string getUsername() { return username; }
};

class Admin : public User {
public:
    Admin(string u, string p) : User(u, p, "admin") {}
};
class RegularUser : public User {
private:
    vector<string> joinedClubs; 
public:
    RegularUser(string u, string p) : User(u, p, "user") {}

    void joinClub(string clubName) {
        for (string club : joinedClubs) {
            if (club == clubName) {
                cout << "���Ѽ�������ţ�" << endl;
                return;
            }
        }
        if (joinedClubs.size() >= 3) {
            cout << "���ֻ�ܼ���3�����ţ�" << endl;
            return;
        }

        joinedClubs.push_back(clubName);
        cout << "�ɹ���������: " << clubName << endl;
    }
    void leaveClub(string clubName) {
        for (auto it = joinedClubs.begin(); it != joinedClubs.end(); ++it) {
            if (*it == clubName) {
                joinedClubs.erase(it);
                cout << "���˳�����: " << clubName << endl;
                return;
            }
        }
        cout << "��δ��������ţ�" << endl;
    }

    vector<string> getJoinedClubs() {
        return joinedClubs;
    }
};
class Club {
private:
    string name;
    string type;
    string description;
    string leader;
    vector<string> members;
public:

};
class Activity {
private:
    string name;
    string creattime;
    string description;
    string belongclub;
    vector<string> partcipate;
public:

};
class system {

};
int main() {

}