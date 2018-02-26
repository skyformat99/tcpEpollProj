#include "cepollclient.h"  
  
int main(int argc, char *argv[])  
{  
        CEpollClient *pCEpollClient = new CEpollClient(100, "115.28.226.203", 8660);  
        if(NULL == pCEpollClient)  
        {  
                cout<<"[epollclient error]:main init"<<"Init CEpollClient fail"<<endl;  
        }  
  
        pCEpollClient->RunFun();  
  
        if(NULL != pCEpollClient)  
        {  
                delete pCEpollClient;  
                pCEpollClient = NULL;  
        }  
  
        return 0;  
}  


