#ifndef GROUPMODEL_H
#define GROUPMODEL_H

#include "group.hpp"

class GroupModel{
public:
    //创建群组
    bool createGroup(Group &group);
    // 加入群组
    void addGroup(int userid, int groupid, string role);
    // 查询用户所在群组信息
    vector<Group> queryGroup(int userid);
    // 根据群组id查询用户id列表，向除了自己以外的人发消息
    vector<int> queryGroupUsers(int userid, int groupid);

};

#endif