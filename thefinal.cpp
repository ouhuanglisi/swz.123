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
    void addParticipant(string username) {
        for (string p : participants) {
            if (p == username) {
                cout << username << " �Ѳ���û��" << endl;
                return;
            }
        }
        participants.push_back(username);
        cout << username << " �ɹ�����: " << name << endl;
    }
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
    // ������뻺����
    void clearInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    User* findUser(string username) {
        for (User* user : users) {
            if (user->getUsername() == username) {
                return user;
            }
        }
        return nullptr;
    }
    Club* findClub(string name) {
        for (Club& club : clubs) {
            if (club.getName() == name) {
                return &club;
            }
        }
        return nullptr;
    }
    Activity* findActivity(string name) {
        for (Activity& activity : activities) {
            if (activity.getName() == name) {
                return &activity;
            }
        }
        return nullptr;
    }

public:

    ~clubsystem() {
        for (User* user : users) {
            delete user;
        }
    }
    void mainMenu() {
        while (true) {
            cout << "\n=== ��У���Ź���ϵͳ ===" << endl;
            cout << "1. ��¼" << endl;
            cout << "2. ע��" << endl;
            cout << "3. �˳�ϵͳ" << endl;
            cout << "��ѡ��: ";

            int choice;
            cin >> choice;
            clearInput();

            switch (choice) {
            case 1: login(); break;
            case 2: registerUser(); break;
            case 3: return;
            default: cout << "��Чѡ�����������룡" << endl;
            }
        }
    }
    void login() {
        string username, password;
        cout << "\n�û���: ";
        getline(cin, username);
        cout << "����: ";
        getline(cin, password);

        User* user = findUser(username);
        if (user && user->login(password)) {
            currentUser = user;
            cout << "\n��¼�ɹ�����ӭ " << username << " (" << user->getRole() << ")" << endl;

            if (user->getRole() == "admin") {
                adminMenu();
            }
            else {
                userMenu();
            }
        }
        else {
            cout << "�û������������" << endl;
        }
    }
    void registerUser() {
        string username, password, role;
        cout << "\nע�����û�" << endl;
        cout << "�û���: ";
        getline(cin, username);

        if (findUser(username)) {
            cout << "�û����Ѵ��ڣ�" << endl;
            return;
        }
        cout << "����: ";
        getline(cin, password);
        cout << "��ɫ (admin/user): ";
        getline(cin, role);
        if (role == "admin") {
            users.push_back(new Admin(username, password));
        }
        else if (role == "user") {
            users.push_back(new RegularUser(username, password));
        }
        else {
            cout << "��Ч��ɫ��" << endl;
            return;
        }
        cout << "ע��ɹ���" << endl;
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
    void createClub() {
        string name, type, desc, leader;
        cout << "\n����������" << endl;
        cout << "��������: ";
        getline(cin, name);
        cout << "��������: ";
        getline(cin, type);
        cout << "���ż��: ";
        getline(cin, desc);
        cout << "������: ";
        getline(cin, leader);
        clubs.push_back(Club(name, type, desc, leader));
        cout << "���Ŵ����ɹ���" << endl;
    }
    void listClub() {
        if (clubs.empty()) {
            cout << "\n����������Ϣ" << endl;
            return;
        }
        cout << "\n=== �����б� ===" << endl;
        for (int i = 0; i < clubs.size(); i++) {
            cout << i + 1 << ". " << clubs[i].getName()
                << " (" << clubs[i].getType() << ")" << endl;
        }
        cout << "\n�����Ų鿴���� (0����): ";
        int choice;
        cin >> choice;
        clearInput();
        if (choice > 0 && choice <= clubs.size()) {
            clubs[choice - 1].printInfo();
        }
    }
    void createActivity() {
        string name, time, location, clubName;
        cout << "\n�����»" << endl;
        cout << "�����: ";
        getline(cin, name);
        cout << "�ʱ��: ";
        getline(cin, time);
        cout << "��ص�: ";
        getline(cin, location);
        cout << "��������: ";
        getline(cin, clubName);
        if (!findClub(clubName)) {
            cout << "���Ų����ڣ�" << endl;
            return;
        }
        activities.push_back(Activity(name, time, location, clubName));
        cout << "������ɹ���" << endl;
    }
    void listActivity() {
        if (activities.empty()) {
            cout << "\n���޻��Ϣ" << endl;
            return;
        }
        cout << "\n=== ��б� ===" << endl;
        for (int i = 0; i < activities.size(); i++) {
            cout << i + 1 << ". " << activities[i].getName()
                << " (" << activities[i].getTime() << ")" << endl;
        }
        cout << "\n�����Ų鿴���� (0����): ";
        int choice;
        cin >> choice;
        clearInput();
        if (choice > 0 && choice <= activities.size()) {
            activities[choice - 1].printInfo();
        }
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
    void joinClub(RegularUser* user) {
        if (clubs.empty()) {
            cout << "����������Ϣ" << endl;
            return;
        }
        cout << "\n�ɼ��������:" << endl;
        for (int i = 0; i < clubs.size(); i++) {
            cout << i + 1 << ". " << clubs[i].getName() << endl;
        }
        cout << "��ѡ�����ű��: ";
        int choice;
        cin >> choice;
        clearInput();

        if (choice < 1 || choice > clubs.size()) {
            cout << "��Чѡ��" << endl;
            return;
        }
        string clubName = clubs[choice - 1].getName();
        user->joinClub(clubName);
        clubs[choice - 1].addMember(user->getUsername());
    }
    void leaveClub(RegularUser* user) {
        vector<string> myClubs = user->getJoinedClubs();
        if (myClubs.empty()) {
            cout << "����δ�����κ����ţ�" << endl;
            return;
        }
        cout << "\n���Ѽ��������:" << endl;
        for (int i = 0; i < myClubs.size(); i++) {
            cout << i + 1 << ". " << myClubs[i] << endl;
        }
        cout << "��ѡ��Ҫ�˳������ű��: ";
        int choice;
        cin >> choice;
        clearInput();

        if (choice < 1 || choice > myClubs.size()) {
            cout << "��Чѡ��" << endl;
            return;
        }
        string clubName = myClubs[choice - 1];
        user->leaveClub(clubName);
        Club* club = findClub(clubName);
        if (club) {
            club->removeMember(user->getUsername());
        }
    }
    void showMyClub(RegularUser* user) {
        vector<string> myClubs = user->getJoinedClubs();
        if (myClubs.empty()) {
            cout << "����δ�����κ����ţ�" << endl;
            return;
        }
        cout << "\n���Ѽ��������:" << endl;
        for (string club : myClubs) {
            cout << "- " << club << endl;
        }
    }
    void joinActivity(RegularUser* user) {
        if (activities.empty()) {
            cout << "���޻��Ϣ" << endl;
            return;
        }
        cout << "\n�ɲ���Ļ:" << endl;
        for (int i = 0; i < activities.size(); i++) {
            cout << i + 1 << ". " << activities[i].getName()
                << " (" << activities[i].getTime() << ")" << endl;
        }
        cout << "��ѡ�����: ";
        int choice;
        cin >> choice;
        clearInput();
        if (choice < 1 || choice > activities.size()) {
            cout << "��Чѡ��" << endl;
            return;
        }
        Activity* activity = &activities[choice - 1];
        activity->addParticipant(user->getUsername());
    }
};
int main() {
    clubsystem system;
    system.mainMenu();
    cout << "��л��ʹ�ø�У����ϵͳ��" << endl;
    return 0;
}