#include<iostream>
#include<iomanip>
#include<limits>
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
    string createTime;
    string leader;
    vector<string> members;
public:
    Club(string n, string t, string d, string l) :name(n),type(t),description(d),leader(l){
        time_t now = time(0);
        tm timeinfo;
        localtime_s(&timeinfo, &now);
        char timestr[80];
        strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", &timeinfo);
        createTime = timestr;
    }
    void addMember(string username) {
        for (string member : members) {
            if (member == username) {
                cout << username << " �������ų�Ա��" << endl;
                return;
            }
        }
        members.push_back(username);
    }
    void removeMember(string username) {
        for (auto it = members.begin(); it != members.end(); ++it) {
            if (*it == username) {
                members.erase(it);
                cout << "���Ƴ���Ա: " << username << endl;
                return;
            }
        }
        cout << username << " �������ų�Ա��" << endl;
    }

    string getName() { return name; }
    string getType() { return type; }
    string getLeader() { return leader; }

    void printInfo() {
        cout << "\n=== ������Ϣ ===" << endl;
        cout << "����: " << name << endl;
        cout << "����: " << type << endl;
        cout << "���: " << description << endl;
        cout << "����ʱ��: " << createTime << endl;
        cout << "������: " << leader << endl;
        cout << "��Ա��: " << members.size() << endl;

        if (!members.empty()) {
            cout << "\n��Ա�б�: ";
            for (string member : members) {
                cout << member << " ";
            }
            cout << endl;
        }
    }
};
class Activity {
private:
    string name;
    string time;
    string location;
    string clubName;
    vector<string> participants;
public:
    Activity(string n, string t, string l, string cn)
        : name(n), time(t), location(l), clubName(cn) {}

    // ��Ӳ�����
    void addParticipant(string username) {
        // ����Ƿ��Ѳ���
        for (string p : participants) {
            if (p == username) {
                cout << username << " �Ѳ���û��" << endl;
                return;
            }
        }
        participants.push_back(username);
        cout << username << " �ɹ�����: " << name << endl;
    }

    // �Ƴ�������
    void removeParticipant(string username) {
        for (auto it = participants.begin(); it != participants.end(); ++it) {
            if (*it == username) {
                participants.erase(it);
                cout << "���Ƴ�������: " << username << endl;
                return;
            }
        }
        cout << username << " δ����û��" << endl;
    }

    string getName() { return name; }
    string getTime() { return time; }
    string getClubName() { return clubName; }

    // ��ȡ���Ϣ
    void printInfo() {
        cout << "\n=== ���Ϣ ===" << endl;
        cout << "�����: " << name << endl;
        cout << "ʱ��: " << time << endl;
        cout << "�ص�: " << location << endl;
        cout << "��������: " << clubName << endl;
        cout << "��������: " << participants.size() << endl;

        if (!participants.empty()) {
            cout << "\n������: ";
            for (string p : participants) {
                cout << p << " ";
            }
            cout << endl;
        }
    }
};
class clubsystem {
private:
    vector<User*> users;
    vector<Club> clubs;
    vector<Activity> activities;
    User* currentUser = nullptr;
public:
    void createClub() {

    }
    void listClub() {

    }
    void createActivity() {

    }
    void adminMenu() {

        while (currentUser) {
            cout << "\n=== ����Ա�˵� ===" << endl;
            cout << "1. ��������" << endl;
            cout << "2. �鿴��������" << endl;
            cout << "3. �����" << endl;
            cout << "4. �鿴���л" << endl;
            cout << "5. �˳���¼" << endl;
            cout << "��ѡ��: ";

            int choice;
            cin >> choice;
            clearInput();

            switch (choice) {
            case 1: createClub(); break;
            case 2: listClub(); break;
            case 3: createActivity(); break;
            case 4: listActivity(); break;
            case 5:
                currentUser = nullptr;
                cout << "���˳���¼" << endl;
                return;
            default: cout << "��Чѡ��" << endl;
            }
        }
    }
    void clearInput() {

    }
    void listClub() {

    }
    void joinClub() {

    }
    void leaveClub() {

    }
    void showMyClub(){

    }
    void listActivity() {

    }
    void joinActivity() {

    }
    void userMenu() {
        RegularUser* user = dynamic_cast<RegularUser*>(currentUser);
        if (!user) return;

        while (currentUser) {
            cout << "\n=== �û��˵� ===" << endl;
            cout << "1. �鿴��������" << endl;
            cout << "2. ��������" << endl;
            cout << "3. �˳�����" << endl;
            cout << "4. �鿴�ҵ�����" << endl;
            cout << "5. �鿴���л" << endl;
            cout << "6. ����" << endl;
            cout << "7. �˳���¼" << endl;
            cout << "��ѡ��: ";

            int choice;
            cin >> choice;
            clearInput();

            switch (choice) {
            case 1: listClub(); break;
            case 2: joinClub(user); break;
            case 3: leaveClub(user); break;
            case 4: showMyClub(user); break;
            case 5: listActivity(); break;
            case 6: joinActivity(user); break;
            case 7:
                currentUser = nullptr;
                cout << "���˳���¼" << endl;
                return;
            default: cout << "��Чѡ��" << endl;
            }
        }
    }

};
int main() {
    clubsystem system;
    system.userMenu();
    cout << "��л��ʹ�ø�У����ϵͳ��" << endl;
    return 0;
}