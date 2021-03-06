#include "http_client.hpp"

int HttpClient::m_exit_flag = 0;
reqCallback HttpClient::m_req_callback;

void HttpClient::sendReq(const string& url, reqCallback req_callback)
{
    m_req_callback = req_callback;
    mg_mgr mgr;
    mg_mgr_init(&mgr,nullptr);
    auto conn = mg_connect_http(&mgr, onHttpEvent, url.c_str(),nullptr,nullptr);
    mg_set_protocol_http_websocket(conn);
    cout<< "Send http request"<<url<<endl;
    while (m_exit_flag==0)
    {
        mg_mgr_poll(&mgr, 500);
    }
    mg_mgr_free(&mgr);
}

void HttpClient::onHttpEvent(mg_connection* conn, int event_type, void* event_data)
{
    http_message *hm = (struct http_message *)event_data;
    int connect_status;

    switch(event_type){
        case MG_EV_CONNECT:
            connect_status = *(int *)event_data;
            if(connect_status!=0){
                printf("Error connecting to server, error code: %d\n", connect_status);
			    m_exit_flag = 1;
            }
            break;
        case MG_EV_HTTP_REPLY:
            {
                printf("Got reply:\n%.*s\n", (int)hm->body.len, hm->body.p);
                std::string rsp = std::string(hm->body.p, hm->body.len);
                conn->flags |= MG_F_SEND_AND_CLOSE;
                m_exit_flag = 1; // 每次收到请求后关闭本次连接，重置标记
                m_req_callback(rsp);
            }
        	case MG_EV_CLOSE:
		if (m_exit_flag == 0) 
            {
                printf("Server closed connection\n");
                m_exit_flag = 1;
            };
            break;
        default:
            break;
    }
}