#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <iostream>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <sio_client.h>

#define BIND_EVENT(IO,EV,FN) \
IO->on(EV,FN)
using namespace sio;

class SocketClient : public QObject
{
    Q_OBJECT

public:
    explicit SocketClient(QObject *parent = nullptr) :
        QObject(parent),
        io(new client())
    {
        using std::placeholders::_1;
        using std::placeholders::_2;
        using std::placeholders::_3;
        using std::placeholders::_4;
        // "mappingstart" 이벤트 핸들러 설정

        // io.socket()->on("mappingstart", sio::socket::event_listener_aux([this](std::string const& name, sio::message::ptr const& data, bool isAck, sio::message::list &ack_resp) {
        //                         onMappingStart(data);
        //                     }));
        sio::socket::ptr sock = io->socket();
        BIND_EVENT(sock,"mapping",std::bind(&SocketClient::onMapping,this,_1,_2,_3,_4));
        BIND_EVENT(sock,"localization",std::bind(&SocketClient::onLocalization,this,_1,_2,_3,_4));

        // WebSocket 클라이언트 설정 및 연결
        io->set_open_listener(std::bind(&SocketClient::onConnected, this));
        io->set_close_listener(std::bind(&SocketClient::onDisconnected, this, std::placeholders::_1));
        io->set_fail_listener(std::bind(&SocketClient::onError, this));

        // WebSocket 서버에 연결
        io->connect("ws://localhost:11337");
    }

    QString getJson(sio::message::ptr const& data,QString key){
        return QString::fromStdString(data->get_map()[key.toStdString()]->get_string());
    }

    void sendMapping(){
        // JSON 객체 생성 및 데이터 설정
        QJsonArray json;
        QJsonArray t;
        t.append(0.1);
        t.append(0.2);
        t.append(0.3);
        t.append(0.4);
        json.append(t);
        json.append(t);
        json.append(t);
        sio::message::ptr response = sio::string_message::create(QJsonDocument(json).toJson().toStdString());
        io->socket()->emit("mapping_cloud",response);
    }
private Q_SLOTS:
    // 연결 성공 시 호출될 슬롯
    void onConnected()
    {
        std::cout << "WebSocket connected" << std::endl;
    }

    // 연결 종료 시 호출될 슬롯
    void onDisconnected(sio::client::close_reason const& reason)
    {
        std::cout << "WebSocket disconnected" << std::endl;
    }

    // 연결 오류 시 호출될 슬롯
    void onError()
    {
        std::cout << "WebSocket error" << std::endl;
    }

    void onLocalization(std::string const& name,message::ptr const& data,bool hasAck,message::list &ack_resp)
    {

        std::cout << "Received onLocalization command" << std::endl;
        if(data->get_flag() == message::flag_object){
            QString command = getJson(data,"command");

            // JSON 객체 생성 및 데이터 설정
            QJsonObject json;
            json["time"] = "3234234234243";
            json["command"] = command;

            if(command == "init"){
                json["result"] = "fail";
            }else if(command == "autoinit"){
                json["result"] = "success";
            }else if(command == "start"){
                json["result"] = "success";
            }else if(command == "stop"){
                json["result"] = "success";
            }

            // JSON 데이터를 문자열 메시지로 변환하여 전송
            sio::message::ptr response = sio::string_message::create(QJsonDocument(json).toJson().toStdString());
            io->socket()->emit("localization", response);

            std::cout << "Sent onLocalization response" << std::endl;
        }
    }

    void onMapping(std::string const& name,message::ptr const& data,bool hasAck,message::list &ack_resp)
    {
        std::cout << "Received onMapping command" << std::endl;
        if(data->get_flag() == message::flag_object){
            QString command = getJson(data,"command");

            // JSON 객체 생성 및 데이터 설정
            QJsonObject json;
            json["time"] = "3234234234243";
            json["command"] = command;

            if(command == "start"){
                json["result"] = "success";
            }else if(command == "stop"){
                json["result"] = "success";
            }else if(command == "save"){
                json["result"] = "success";
                json["name"] = getJson(data,"name");
            }

            // JSON 데이터를 문자열 메시지로 변환하여 전송
            sio::message::ptr response = sio::string_message::create(QJsonDocument(json).toJson().toStdString());
            io->socket()->emit("mapping", response);

            std::cout << "Sent onMapping response" << std::endl;
        }
    }



private:
    std::unique_ptr<client> io;
};

#endif // SOCKET_H
