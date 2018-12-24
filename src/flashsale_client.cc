#include "flashsale.grpc.pb.h"
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include <iostream>
#include <memory>
#include <string>
//#include "Md5.h"
#include <pthread.h>


#define Random(x) (rand() % x)
#define MAX_THREAD_NUM 500

using grpc::Channel;
using grpc::ClientContext;
using grpc::CreateChannel;
using grpc::InsecureChannelCredentials;
using grpc::Status;
using flashsale::FlashsaleRequest;
using flashsale::FlashsaleResponse;
using flashsale::FlashsaleService;
using namespace std;

class FlashsaleClient {
  public:
    FlashsaleClient(shared_ptr<Channel> channel)
      :stub_(FlashsaleService::NewStub(channel)) {}

  string flashsale(const string &usr_name,const string &usr_key) {
    FlashsaleRequest req;
    req.set_usrname(usr_name);
    req.set_usrkey(usr_key);
    FlashsaleResponse res;
    ClientContext context;
    Status status = stub_->flashsale(&context, req, &res);
    if (status.ok()) {
      return res.result();
    } else {
      cout << status.error_code() << ": " << status.error_message()
                << endl;
      return "RPC failed";
    }
  }

private:
  unique_ptr<FlashsaleService::Stub> stub_;
};

void* onFlashsale(void* args) {
//TODO 考虑加密
//    MD5 iMD5;
//    iMD5.GenerateMD5((unsigned char *)prikey.c_str(), strlen(prikey.c_str()));
//    string md5_str(iMD5.ToString());
    int i = Random(330);
    string flag = to_string(i);
    string name = to_string(i) + to_string(i);
    FlashsaleClient client(CreateChannel("localhost:50051", InsecureChannelCredentials()));
    string resultStr = client.flashsale(name, flag);
    int result = atoi(resultStr.c_str());
    if (result == 1) {
        cout << "succ" <<endl;
    } else {
        cout << "fail" <<endl;
    }
    return ((void *)0);
}


int main(int argc, char *argv[]) {
  pthread_t threads[MAX_THREAD_NUM];
  for(int i = 0; i < MAX_THREAD_NUM; ++i) {
        //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
        int ret = pthread_create(&threads[i], NULL, onFlashsale, NULL);
        if (ret != 0) {
            cout << "pthread_create error: error_code=" << ret << endl;
        }
    }
    //等各个线程退出后，进程才结束，否则进程强制结束了，线程可能还没反应过来；
    pthread_exit(NULL);
    
  return 0;
}

