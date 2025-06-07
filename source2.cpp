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

    // 添加参与者
    void addParticipant(string username) {
        // 检查是否已参与
        for (string p : participants) {
            if (p == username) {
                cout << username << " 已参与该活动！" << endl;
                return;
            }
        }
        participants.push_back(username);
        cout << username << " 成功参与活动: " << name << endl;
    }

    // 移除参与者
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

    // 获取活动信息
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
public:
    void createClub() {

    }
    void listClub() {

    }
    void createActivity() {

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

};
int main() {
    clubsystem system;
    system.userMenu();
    cout << "感谢你使用高校社团系统！" << endl;
    return 0;
}