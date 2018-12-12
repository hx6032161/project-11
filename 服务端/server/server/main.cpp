#include <cstdio>
#include "ServerOperation.h"
#include <sys/ipc.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <iostream>
using namespace std;

void createDeamon();

//class ServerInfo
//{
//public:
//	char			serverID[12];	// 服务器端编号
//	char			dbUse[24]; 		// 数据库用户名
//	char			dbPasswd[24]; 	// 数据库密码
//	char			dbSID[24]; 		// 数据库sid(192.168.10.145:1521/orcl)
//
//	unsigned short 	sPort;			// 服务器绑定的端口
//	int				maxnode;		// 共享内存最大网点数 客户端默认1个
//	int 			shmkey;			// 共享内存keyid 创建共享内存时使用	 
//};

int main()
{
	//createDeamon();
	// 启动服务器
	ServerInfo info;
	info.maxnode = 10;
	info.sPort = 9898;
	info.shmkey = ftok("/home", 'w');
	strcpy(info.serverID, "0001");
	
	ServerOperation op(&info);
	op.startWork();

	cout << "good bye..." << endl;

	return 0;
}

void createDeamon()
{
	// 1. 创建子进程, 杀死父进程
	pid_t pid = fork();
	// 父进程
	if (pid > 0)
	{
		exit(0);
	}
	// 子进程
	// 2. 子进程提升为会话
	setsid();
	// 3. 修改工作目录
	chdir("/home");
	// 4. 设置掩码
	umask(0022);
	// 5. 重定向文件描述符 - /dev/null
	int devfd = open("/dev/null", O_RDWR);
	dup2(devfd, 0);
	// dup2(devfd, 1); // 调试的时候需要看输出
	dup2(devfd, 2);
}