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
                cout << "您已加入该社团！" << endl;
                return;
            }
        }
        if (joinedClubs.size() >= 3) {
            cout << "最多只能加入3个社团！" << endl;
            return;
        }

        joinedClubs.push_back(clubName);
        cout << "成功加入社团: " << clubName << endl;
    }
    void leaveClub(string clubName) {
        for (auto it = joinedClubs.begin(); it != joinedClubs.end(); ++it) {
            if (*it == clubName) {
                joinedClubs.erase(it);
                cout << "已退出社团: " << clubName << endl;
                return;
            }
        }
        cout << "您未加入该社团！" << endl;
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
                cout << username << " 已是社团成员！" << endl;
                return;
            }
        }
        members.push_back(username);
    }
    void removeMember(string username) {
        for (auto it = members.begin(); it != members.end(); ++it) {
            if (*it == username) {
                members.erase(it);
                cout << "已移除成员: " << username << endl;
                return;
            }
        }
        cout << username << " 不是社团成员！" << endl;
    }
    string getName() { return name; }
    string getType() { return type; }
    string getLeader() { return leader; }
    void printInfo() {
        cout << "\n=== 社团信息 ===" << endl;
        cout << "名称: " << name << endl;
        cout << "类型: " << type << endl;
        cout << "简介: " << description << endl;
        cout << "创建时间: " << createTime << endl;
        cout << "负责人: " << leader << endl;
        cout << "成员数: " << members.size() << endl;

        if (!members.empty()) {
            cout << "\n成员列表: ";
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
                cout << username << " 已参与该活动！" << endl;
                return;
            }
        }
        participants.push_back(username);
        cout << username << " 成功参与活动: " << name << endl;
    }
    void removeParticipant(string username) {
        for (auto it = participants.begin(); it != participants.end(); ++it) {
            if (*it == username) {
                participants.erase(it);
                cout << "已移除参与者: " << username << endl;
                return;
            }
        }
        cout << username << " 未参与该活动！" << endl;
    }
    string getName() { return name; }
    string getTime() { return time; }
    string getClubName() { return clubName; }
    void printInfo() {
        cout << "\n=== 活动信息 ===" << endl;
        cout << "活动名称: " << name << endl;
        cout << "时间: " << time << endl;
        cout << "地点: " << location << endl;
        cout << "所属社团: " << clubName << endl;
        cout << "参与人数: " << participants.size() << endl;

        if (!participants.empty()) {
            cout << "\n参与者: ";
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
    // 清除输入缓冲区
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
            cout << "\n=== 高校社团管理系统 ===" << endl;
            cout << "1. 登录" << endl;
            cout << "2. 注册" << endl;
            cout << "3. 退出系统" << endl;
            cout << "请选择: ";

            int choice;
            cin >> choice;
            clearInput();

            switch (choice) {
            case 1: login(); break;
            case 2: registerUser(); break;
            case 3: return;
            default: cout << "无效选择，请重新输入！" << endl;
            }
        }
    }
    void login() {
        string username, password;
        cout << "\n用户名: ";
        getline(cin, username);
        cout << "密码: ";
        getline(cin, password);

        User* user = findUser(username);
        if (user && user->login(password)) {
            currentUser = user;
            cout << "\n登录成功！欢迎 " << username << " (" << user->getRole() << ")" << endl;

            if (user->getRole() == "admin") {
                adminMenu();
            }
            else {
                userMenu();
            }
        }
        else {
            cout << "用户名或密码错误！" << endl;
        }
    }
    void registerUser() {
        string username, password, role;
        cout << "\n注册新用户" << endl;
        cout << "用户名: ";
        getline(cin, username);

        if (findUser(username)) {
            cout << "用户名已存在！" << endl;
            return;
        }
        cout << "密码: ";
        getline(cin, password);
        cout << "角色 (admin/user): ";
        getline(cin, role);
        if (role == "admin") {
            users.push_back(new Admin(username, password));
        }
        else if (role == "user") {
            users.push_back(new RegularUser(username, password));
        }
        else {
            cout << "无效角色！" << endl;
            return;
        }
        cout << "注册成功！" << endl;
    }
    void adminMenu() {
        while (currentUser) {
            cout << "\n=== 管理员菜单 ===" << endl;
            cout << "1. 创建社团" << endl;
            cout << "2. 查看所有社团" << endl;
            cout << "3. 创建活动" << endl;
            cout << "4. 查看所有活动" << endl;
            cout << "5. 退出登录" << endl;
            cout << "请选择: ";
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
                cout << "已退出登录" << endl;
                return;
            default: cout << "无效选择！" << endl;
            }
        }
    }
    void createClub() {
        string name, type, desc, leader;
        cout << "\n创建新社团" << endl;
        cout << "社团名称: ";
        getline(cin, name);
        cout << "社团类型: ";
        getline(cin, type);
        cout << "社团简介: ";
        getline(cin, desc);
        cout << "负责人: ";
        getline(cin, leader);
        clubs.push_back(Club(name, type, desc, leader));
        cout << "社团创建成功！" << endl;
    }
    void listClub() {
        if (clubs.empty()) {
            cout << "\n暂无社团信息" << endl;
            return;
        }
        cout << "\n=== 社团列表 ===" << endl;
        for (int i = 0; i < clubs.size(); i++) {
            cout << i + 1 << ". " << clubs[i].getName()
                << " (" << clubs[i].getType() << ")" << endl;
        }
        cout << "\n输入编号查看详情 (0返回): ";
        int choice;
        cin >> choice;
        clearInput();
        if (choice > 0 && choice <= clubs.size()) {
            clubs[choice - 1].printInfo();
        }
    }
    void createActivity() {
        string name, time, location, clubName;
        cout << "\n创建新活动" << endl;
        cout << "活动名称: ";
        getline(cin, name);
        cout << "活动时间: ";
        getline(cin, time);
        cout << "活动地点: ";
        getline(cin, location);
        cout << "所属社团: ";
        getline(cin, clubName);
        if (!findClub(clubName)) {
            cout << "社团不存在！" << endl;
            return;
        }
        activities.push_back(Activity(name, time, location, clubName));
        cout << "活动创建成功！" << endl;
    }
    void listActivity() {
        if (activities.empty()) {
            cout << "\n暂无活动信息" << endl;
            return;
        }
        cout << "\n=== 活动列表 ===" << endl;
        for (int i = 0; i < activities.size(); i++) {
            cout << i + 1 << ". " << activities[i].getName()
                << " (" << activities[i].getTime() << ")" << endl;
        }
        cout << "\n输入编号查看详情 (0返回): ";
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
            cout << "\n=== 用户菜单 ===" << endl;
            cout << "1. 查看所有社团" << endl;
            cout << "2. 加入社团" << endl;
            cout << "3. 退出社团" << endl;
            cout << "4. 查看我的社团" << endl;
            cout << "5. 查看所有活动" << endl;
            cout << "6. 参与活动" << endl;
            cout << "7. 退出登录" << endl;
            cout << "请选择: ";
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
                cout << "已退出登录" << endl;
                return;
            default: cout << "无效选择！" << endl;
            }
        }
    }
    void joinClub(RegularUser* user) {
        if (clubs.empty()) {
            cout << "暂无社团信息" << endl;
            return;
        }
        cout << "\n可加入的社团:" << endl;
        for (int i = 0; i < clubs.size(); i++) {
            cout << i + 1 << ". " << clubs[i].getName() << endl;
        }
        cout << "请选择社团编号: ";
        int choice;
        cin >> choice;
        clearInput();

        if (choice < 1 || choice > clubs.size()) {
            cout << "无效选择！" << endl;
            return;
        }
        string clubName = clubs[choice - 1].getName();
        user->joinClub(clubName);
        clubs[choice - 1].addMember(user->getUsername());
    }
    void leaveClub(RegularUser* user) {
        vector<string> myClubs = user->getJoinedClubs();
        if (myClubs.empty()) {
            cout << "您尚未加入任何社团！" << endl;
            return;
        }
        cout << "\n您已加入的社团:" << endl;
        for (int i = 0; i < myClubs.size(); i++) {
            cout << i + 1 << ". " << myClubs[i] << endl;
        }
        cout << "请选择要退出的社团编号: ";
        int choice;
        cin >> choice;
        clearInput();

        if (choice < 1 || choice > myClubs.size()) {
            cout << "无效选择！" << endl;
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
            cout << "您尚未加入任何社团！" << endl;
            return;
        }
        cout << "\n您已加入的社团:" << endl;
        for (string club : myClubs) {
            cout << "- " << club << endl;
        }
    }
    void joinActivity(RegularUser* user) {
        if (activities.empty()) {
            cout << "暂无活动信息" << endl;
            return;
        }
        cout << "\n可参与的活动:" << endl;
        for (int i = 0; i < activities.size(); i++) {
            cout << i + 1 << ". " << activities[i].getName()
                << " (" << activities[i].getTime() << ")" << endl;
        }
        cout << "请选择活动编号: ";
        int choice;
        cin >> choice;
        clearInput();
        if (choice < 1 || choice > activities.size()) {
            cout << "无效选择！" << endl;
            return;
        }
        Activity* activity = &activities[choice - 1];
        activity->addParticipant(user->getUsername());
    }
};
int main() {
    clubsystem system;
    system.mainMenu();
    cout << "感谢你使用高校社团系统！" << endl;
    return 0;
}