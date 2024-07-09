#ifndef FRENDMODEL_H
#define FRENDMODEL_H

#include "user.hpp"
#include <vector>
using namespace std;

// 维护好友关系的操作接口方法
class FriendModel{
public:
    // 添加好友关系
    void insert(int userid, int friendid);

    // 返回用户好友列表 通过friendid-》username
    vector<User> query(int userid);

};

#endif