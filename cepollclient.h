#ifndef _DEFINE_EPOLLCLIENT_H_  
#define _DEFINE_EPOLLCLIENT_H_  
#define _MAX_SOCKFD_COUNT 65535  
  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>  
#include <sys/epoll.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <fcntl.h>  
#include <arpa/inet.h>  
#include <errno.h>  
#include <sys/ioctl.h>  
#include <sys/time.h>  
#include <string>  
#include <unistd.h>
  
using namespace std;  
  
/** 
 * @brief 用户状态 
 */  
typedef enum _EPOLL_USER_STATUS_EM  
{  
        FREE = 0,  
        CONNECT_OK = 1,//连接成功  
        SEND_OK = 2,//发送成功  
        RECV_OK = 3,//接收成功  
}EPOLL_USER_STATUS_EM;  
  
/*@brief 
 *@CEpollClient class 用户状态结构体 
 */  
struct UserStatus  
{  
        EPOLL_USER_STATUS_EM iUserStatus;//用户状态  
        int iSockFd;//用户状态关联的socketfd  
        char cSendbuff[1024];//发送的数据内容  
        int iBuffLen;//发送数据内容的长度  
        unsigned int uEpollEvents;//Epoll events  
};  
  
class CEpollClient  
{  
        public:  
  
                /** 
                 * @brief 
                 * 函数名:CEpollClient 
                 * 描述:构造函数 
                 * @param [in] iUserCount  
                 * @param [in] pIP IP地址 
                 * @param [in] iPort 端口号 
                 * @return 无返回 
                 */  
                CEpollClient(int iUserCount, const char* pIP, int iPort);  
  
/** 
                 * @brief 
                 * 函数名:CEpollClient 
                 * 描述:析构函数 
                 * @return 无返回 
                 */  
                ~CEpollClient();  
  
                /** 
                 * @brief 
                 * 函数名:RunFun 
                 * 描述:对外提供的接口，运行epoll类 
                 * @return 无返回值 
                 */  
                int RunFun();  
  
        private:  
  
                /** 
                 * @brief 
                 * 函数名:ConnectToServer 
                 * 描述:连接到服务器 
                 * @param [in] iUserId 用户ID 
                 * @param [in] pServerIp 连接的服务器IP 
                 * @param [in] uServerPort 连接的服务器端口号 
                 * @return 成功返回socketfd,失败返回的socketfd为-1 
                 */  
                int ConnectToServer(int iUserId,const char *pServerIp,unsigned short uServerPort);  
  
/** 
                 * @brief 
                 * 函数名:SendToServerData 
                 * 描述:给服务器发送用户(iUserId)的数据 
                 * @param [in] iUserId 用户ID 
                 * @return 成功返回发送数据长度 
                 */  
                int SendToServerData(int iUserId);  
  
                /** 
                 * @brief 
                 * 函数名:RecvFromServer 
                 * 描述:接收用户回复消息 
                 * @param [in] iUserId 用户ID 
                 * @param [in] pRecvBuff 接收的数据内容 
                 * @param [in] iBuffLen 接收的数据长度 
                 * @return 成功返回接收的数据长度，失败返回长度为-1 
                 */  
                int RecvFromServer(int iUserid,char *pRecvBuff,int iBuffLen);  
  
                /** 
                 * @brief 
                 * 函数名:CloseUser 
                 * 描述:关闭用户 
                 * @param [in] iUserId 用户ID 
                 * @return 成功返回true 
                 */  
                bool CloseUser(int iUserId);  
  
/** 
                 * @brief 
                 * 函数名:DelEpoll 
                 * 描述:删除epoll事件 
                 * @param [in] iSockFd socket FD 
                 * @return 成功返回true 
                 */  
                bool DelEpoll(int iSockFd);  
        private:  
  
                int    m_iUserCount;//用户数量；  
                struct UserStatus *m_pAllUserStatus;//用户状态数组  
                int    m_iEpollFd;//需要创建epollfd  
                int    m_iSockFd_UserId[_MAX_SOCKFD_COUNT];//将用户ID和socketid关联起来  
                int    m_iPort;//端口号  
                char   m_ip[100];//IP地址  
};  
  
#endif  



