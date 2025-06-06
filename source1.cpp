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
    string clubname;
    string type;
    string description;
    string creatTime;
    string leader;
    vector<string> members;
public:

};
class Activity {
private:
    string name;
    string time;
    string location;
    string clubName;
    vector<string> participants;
public:

};
class clubsystem {
private:
    vector<User*> users;
    vector<Club> clubs;
    vector<Activity> activities;
    User* currentUser = nullptr;
public:
    void mainmenu() {

    }
    void 
};
int main() {
    clubsystem system;
    system.mainmenu();
    cout << "��л��ʹ�ø�У����ϵͳ��" << endl;
    return 0;
}