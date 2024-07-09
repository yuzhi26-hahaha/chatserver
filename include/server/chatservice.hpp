#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include "muduo/net/TcpConnection.h"
#include<unordered_map>
#include<functional>
#include "json.hpp"
#include "usermodel.hpp"
#include<mutex>
#include "offlinemessagemodel.hpp"
#include "friendmodel.hpp"
#include "groupmodel.hpp"
# include "redis.hpp"

using namespace std;
using namespace muduo;
using namespace muduo::net;
using json = nlohmann::json;

//使用using来给一个已经存在的对象定义新的名称
//消息id对应的事件回调
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp)>;

//聊天服务器业务类
class ChatService
{
public:
    //单例模式，获取单例对象的接口函数
    static ChatService* instance();
    //处理登陆业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //处理注册业务
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 一对一聊天业务
    void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //添加好友业务
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 处理客户端异常断开
    void clientCloseException(const TcpConnectionPtr &conn);
    // 创建群组业务
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //加入群组业务
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 群聊业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    // 处理注销业务
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //服务器异常，业务重置的方法
    void reset();
    // 从redis消息队列中获取消息的订阅
    void handleRedisSubscribeMessage(int userid, string msg);
    //获取消息对应的处理器
    MsgHandler getHandler(int msgid);
private:
    ChatService();

    //映射事件回调，一个消息id映射一个事件处理，使用哈希表来完成
    unordered_map<int, MsgHandler> _msgHandlerMap;

    // 存储在线用户的通信连接，即，服务器需要将消息推送到某一个客户端，从这个哈希映射中去寻找
    //这个map需要考虑线程安全问题
    unordered_map<int, TcpConnectionPtr> _userConnMap;

    //定义互斥锁，保证—_userconnmap的线程安全
    mutex _connMutex;

    // 数据操作类对象
    UserModel _userModel;
    offlineMsgModel _offlineMsgModel;
    FriendModel _friendModel;
    GroupModel _groupModel;

    // redis操作对象
    Redis _redis;


};


#endif