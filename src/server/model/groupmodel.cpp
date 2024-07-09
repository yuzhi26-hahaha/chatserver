#include "groupmodel.hpp"
#include "db.h"

// 创建群组
bool GroupModel::createGroup(Group &group)
{
    char sql[1024] = {};
    sprintf(sql, "insert into allgroup(groupname, groupdesc) values ('%s', '%s')", group.getName().c_str(), group.getDesc().c_str());
    MySQL mysql;
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            group.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }
    return false;
}
// 加入群组
void GroupModel::addGroup(int userid, int groupid, string role)
{
    char sql[1024] = {0};
    sprintf(sql, "insert into groupuser values(%d, %d, '%s')", groupid, userid, role.c_str());
    MySQL mysql;
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}
// 查询用户所在群组信息
vector<Group> GroupModel::queryGroup(int userid)
{
    char sql[1024] = {0};
    sprintf(sql, "select a.id, a.groupname, a.groupdesc from allgroup as a inner join groupuser as b on a.id = b.groupid where b.userid = %d", userid);

    vector<Group> groupvec;
    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                Group group;
                // 此处查出群组信息，下边查出群组中的用户信息，即继承的父类的user信息
                group.setId(atoi(row[0]));
                group.setName(row[1]);
                group.setDesc(row[2]);
                groupvec.push_back(group);
            }
            mysql_free_result(res);
        }
    }
    for (Group &group : groupvec)
    {
        sprintf(sql, "select a.id, a.name, a.state, b.grouprole from user as a inner join groupuser as b on b.userid = a.id where b.groupid = %d", group.getId());
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                GroupUser user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setState(row[2]);
                user.setRole(row[3]);
                group.getUsers().push_back(user);
            }
            mysql_free_result(res);
        }
    }
    return groupvec;
}
// 根据群组id查询用户id列表，向除了自己以外的人发消息
vector<int> GroupModel::queryGroupUsers(int userid, int groupid)
{
    char sql[1024] = {0};
    sprintf(sql, "select userid from groupuser where groupid = %d and userid != %d", groupid, userid);
    vector<int> idvec;
    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                idvec.push_back(atoi(row[0]));
            }
            mysql_free_result(res);
        }
    }
    return idvec;
}