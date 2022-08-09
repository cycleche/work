#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define UDP_BUFFER_SIZE   12
#define SERV_PORT         8313

typedef struct LOCATIONINFO
{
  int   longitude;
  int   latitude;
  short numSV;
}LocationInfo;

int main()
{
  // sock_fd --- socket文件描述符 创建udp套接字
  int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sock_fd < 0)
  {
    perror("socket");
    exit(1);
  }

  // 将套接字和IP、端口绑定
  struct sockaddr_in addr_serv;
  int len;
  memset(&addr_serv, 0, sizeof(struct sockaddr_in));  //每个字节都用0填充
  addr_serv.sin_family = AF_INET;                     //使用IPV4地址
  addr_serv.sin_port = htons(SERV_PORT);              //端口
  // INADDR_ANY表示不管是哪个网卡接收到数据，只要目的端口是SERV_PORT，就会被该应用程序接收到
  addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);      //自动获取IP地址
  len = sizeof(addr_serv);

  // 绑定socket
  if(bind(sock_fd, (struct sockaddr *)&addr_serv, sizeof(addr_serv)) < 0)
  {
    perror("bind error:");
    exit(1);
  }

  int  recv_num;
  //为避免字节序问题，因此recvfrom按字节接收数据后，再将buf转换为LocationInfo
  char buf[UDP_BUFFER_SIZE] = {0};
  LocationInfo info;
  memset(&info, 0, sizeof(LocationInfo));
  struct sockaddr_in addr_client;

  while(true)
  {
    recv_num = recvfrom(sock_fd, buf, UDP_BUFFER_SIZE, 0, (struct sockaddr *)&addr_client, (socklen_t *)&len);
    if(recv_num < 0)
    {
      perror("recvfrom error:");
      continue ;
    }
    memcpy(&info, buf, sizeof(LocationInfo));

    printf("server receive %d bytes, lon = %.7f, lat = %.7f, numSV = %hd \n", recv_num, (1.0 * info.longitude) / 1e7, (1.0 * info.latitude) / 1e7, info.numSV);
    memset(&info, 0, sizeof(LocationInfo));
  }

  close(sock_fd);

  return 0;
}
