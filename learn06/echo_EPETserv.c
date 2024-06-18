#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define BUF_SIZE 4          // 버퍼 크기를 4로 정의
#define EPOLL_SIZE 50       // epoll 이벤트의 최대 수를 50으로 정의

void setnonblockingmode(int fd);  // 파일 디스크립터를 논블로킹 모드로 설정하는 함수 선언
void error_handling(char *buf);   // 에러 메시지를 출력하고 프로그램을 종료하는 함수 선언

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t adr_sz;
	int str_len, i;
	char buf[BUF_SIZE];

	struct epoll_event *ep_events; // epoll 이벤트를 저장할 구조체 포인터
	struct epoll_event event;      // epoll 이벤트를 위한 구조체 변수
	int epfd, event_cnt;           // epoll 파일 디스크립터와 이벤트 개수

	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);  // 프로그램 사용법 출력 후 종료
	}

	// 서버 소켓 생성
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));
	
	// 소켓에 주소 할당
	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");
	// 연결 요청 대기 상태로 전환
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");

	// epoll 인스턴스 생성
	epfd=epoll_create(EPOLL_SIZE);
	ep_events=malloc(sizeof(struct epoll_event)*EPOLL_SIZE);  // epoll 이벤트 저장을 위한 메모리 할당

	setnonblockingmode(serv_sock);  // 서버 소켓을 논블로킹 모드로 설정
	event.events=EPOLLIN;
	event.data.fd=serv_sock;	
	epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);  // 서버 소켓을 epoll 인스턴스에 등록

	while(1)
	{
		// 이벤트 감지 대기
		event_cnt=epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
		if(event_cnt==-1)
		{
			puts("epoll_wait() error");
			break;
		}

		puts("return epoll_wait");
		for(i=0; i<event_cnt; i++)
		{
			if(ep_events[i].data.fd==serv_sock)  // 서버 소켓에 이벤트 발생 시
			{
				adr_sz=sizeof(clnt_adr);
				clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);  // 클라이언트 연결 수락
				setnonblockingmode(clnt_sock);  // 클라이언트 소켓을 논블로킹 모드로 설정
				event.events=EPOLLIN|EPOLLET;
				event.data.fd=clnt_sock;
				epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);  // 클라이언트 소켓을 epoll 인스턴스에 등록
				printf("connected client: %d \n", clnt_sock);
			}
			else
			{
				while(1)
				{
					str_len=read(ep_events[i].data.fd, buf, BUF_SIZE);
					if(str_len==0)  // 클라이언트 연결 종료 요청 시
					{
						epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);  // epoll 인스턴스에서 소켓 삭제
						close(ep_events[i].data.fd);
						printf("closed client: %d \n", ep_events[i].data.fd);
						break;
					}
					else if(str_len<0)
					{
						if(errno==EAGAIN)  // 더 이상 읽을 데이터가 없을 경우
							break;
					}
					else
					{
						write(ep_events[i].data.fd, buf, str_len);  // 받은 데이터를 클라이언트에게 에코
					}
				}
			}
		}
	}
	close(serv_sock);  // 서버 소켓 닫기
	close(epfd);       // epoll 인스턴스 닫기
	return 0;
}

// 파일 디스크립터를 논블로킹 모드로 설정하는 함수
void setnonblockingmode(int fd)
{
	int flag=fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flag|O_NONBLOCK);
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수
void error_handling(char *buf)
{
	fputs(buf, stderr);
	fputc('\n', stderr);
	exit(1);
}
