//moduo网络库提供了两个主要的类
//TcpServer用于编写服务器程序
//TCPClient用于编写客户端程序
//用网络库可以把网络代码和业务代码区分开来===》什么是业务代码？即用户的连接和断开，用户数据传输
//
//

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <functional>   //绑定器头文件
#include <string>

using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;

//
//1、组合TCPServer对象
//2、创建eventloop事件循环对象的指针
//3、明确TcpServer构造函数的的参数，构造函数
//4、构造函数中注册处理连接的回调函数和注册处理读写时间的回调函数
//5、设置合适的服务端线程数目，moduo库会自己分配IO线程和工作线程
//6、主要精力在两个回调函数上

class ChatServer{
public:
    ChatServer(EventLoop* loop,                     //事件循环
                const InetAddress& listenAddr,      //ip+port
                const string& nameArg)              //服务器name
                : _server(loop, listenAddr, nameArg), _loop(loop){
                    //给服务器注册用户连接的创建回调===》网络库监听的，然后上报
                    //回调==》当相应的事件发生后自动调用函数
                    _server.setConnectionCallback(bind(&ChatServer::onConnection, this, _1));

                    //给服务器注册用户读写事件回调
                    _server.setMessageCallback(bind(&ChatServer::onMessage, this, _1, _2, _3));     //_1是回调函数的占位符

                    //设置服务端的线程数量 1个IO线程，三个工作线程
                    _server.setThreadNum(4);
                }
    //开启事件循环
    void start(){
        _server.start();
    }
private:
    //处理用户的连接和断开
    void onConnection(const TcpConnectionPtr &conn){
        if(conn->connected()){
            cout << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() << " State : On" << endl; 
        }else{
            cout << conn->peerAddress().toIpPort() << " -> " << conn->localAddress().toIpPort() << " State : Off" << endl;
            conn->shutdown();
        }
    }
    //处理读写事件
    void onMessage(const TcpConnectionPtr &conn,    //连接
                            Buffer* buffer,            //缓冲区
                            Timestamp time)              //时间
    {             
        string buf = buffer->retrieveAllAsString();
        cout << "recv data: " << buf << "time: " << time.toString() << endl;
        conn->send(buf);        //回显echo
    }
    muduo::net::TcpServer _server;
    muduo::net::EventLoop *_loop;
};

int main(){
    EventLoop loop;
    InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "Chatserver");

    server.start();
    loop.loop();    
    return 0;
}