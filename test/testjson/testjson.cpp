#include "json.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;
using json = nlohmann::json;

//fun1fun2fun3为序列化的例子，将数据序列化为一个json对象，然后发送出去
void fun1(){
    json js;
    js["msg_tpye"] = 2;
    js["from"] = "zhangsan";
    js["to"] = "lisi";
    js["msg"] = "It's time to say";
    string sendBuf = js.dump();
    cout << sendBuf.c_str() <<endl;
}

void fun2(){
    json js;
    js["id"] = {1, 2, 3, 4, 5};
    js["name"] = "zhangsan";
    js["msg"]["zhangsan"] = "hello world";
    js["msg"]["lisi"] = "nihao";
    js["msg"] = {{"zhangsan", "hello world"}, {"lisi", "nihao"}};
    cout << js << endl;

}
//json序列化，可以直接序列化为数组
void fun3(){
    json js;
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);

    js["id"] = vec;
    map<int, string> m;
    m.insert({1, "qq"});
    m.insert({2, "ww"});
    m.insert({3, "ee"});
    js["path"] = m;

    string sendBuf = js.dump(); //json数据对象序列化为一个json字符串
    cout << js << endl;
}

//json反序列化
//从网络接收到json格式的数据之后，直接反序列化为数据甚至容器
string fun4(){
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhangsan";
    js["to"] = "lisi";
    js["msg"] = "It's time to say";
    string sendBuf = js.dump();
    return sendBuf;
}

json fun5(){
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhangsan";
    js["to"] = "lisi";
    js["msg"] = "It's time to say";
    return js;
}

string fun6(){
    json js;
    js["id"] = {1, 2, 3, 4, 5};
    js["name"] = "zhangsan";
    js["msg"]["zhangsan"] = "hello world";
    js["msg"]["lisi"] = "nihao";
    js["msg"] = {{"zhangsan", "hello world"}, {"lisi", "nihao"}};
    // cout << js << endl;
    return js.dump();
}
//直接容器反序列化
string fun7(){
    json js;
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);

    js["id"] = vec;
    map<int, string> m;
    m.insert({1, "qq"});
    m.insert({2, "ww"});
    m.insert({3, "ee"});
    js["path"] = m;

    string sendBuf = js.dump(); //json数据对象序列化为一个json字符串
    return sendBuf;
}

int main(){
    // fun1();
    // fun2();
    // fun3();
    // string recv = fun4();
    // json jsbuf = json::parse(recv);
    // cout << jsbuf["msg_type"] <<endl;
    // cout << jsbuf["from"] <<endl;
    // cout << jsbuf["to"] <<endl;
    // cout << jsbuf["msg"] <<endl;

    // string recv2 = fun6();
    // json jsbuf2 = json::parse(recv2);
    // cout<<jsbuf2["id"]<<endl;
    // vector<int> arry = jsbuf2["id"];
    // cout<< arry[2]<<endl;
    // string msgjs2 = jsbuf2["name"];
    // auto msg3js = jsbuf2["msg"];
    // cout<<msg3js<<endl;
    // // cout<<msg3js.type()<<endl;
    // cout<<msgjs2<<endl;

    string recv7 = fun7();
    json js7 = json::parse(recv7);

    vector<int> vec = js7["id"];  //js对象里的数组类型直接放入vector
    for(int v : vec){
        cout<< v << " ";
    }
    cout<<endl;

    map<int, string> m = js7["path"];
    // for(auto &p : m){
    //     cout<<p.first<<" "<<p.second<<" ";
    // }
    // cout<<endl;
    for(map<int, string>::iterator it = m.begin(); it != m.end(); it++){
        cout << it->first << " " << it->second << endl;
    }

    return 0;
}