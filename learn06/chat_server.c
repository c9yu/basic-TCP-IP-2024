#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUF_SIZE 100       // 버퍼 크기를 정의
#define MAX_CLNT 256       // 최대 클라이언트 수를 정의

void * handle_clnt(void * arg);      // 클라이언트 요청을 처리할 함수 선언
void send_msg(char * msg, int len);  // 메시지를 모든 클라이언트에 전송할 함수 선언
void error_handling(char * msg);     // 에러 메시지를 출력하고 프로그램을 종료하는 함수 선언

int clnt_cnt = 0;                    // 현재 접속 중인 클라이언트 수
int clnt_socks[MAX_CLNT];            // 클라이언트 소켓을 저장할 배열
pthread_mutex_t mutx;                // 뮤텍스 변수 선언

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	int clnt_adr_sz;
	pthread_t t_id;

	if(argc != 2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
  
	pthread_mutex_init(&mutx, NULL);  // 뮤텍스 초기화
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);  // 서버 소켓 생성

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET; 
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));
	
	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");  // 소켓에 주소 할당
	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");  // 연결 요청 대기 상태로 전환
	
	while(1)
	{
		clnt_adr_sz = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);  // 클라이언트 연결 수락
		
		pthread_mutex_lock(&mutx);
		clnt_socks[clnt_cnt++] = clnt_sock;  // 클라이언트 소켓을 배열에 저장
		pthread_mutex_unlock(&mutx);
	
		pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);  // 클라이언트 요청을 처리할 스레드 생성
		pthread_detach(t_id);  // 스레드 분리
		printf("Connected client IP: %s \n", inet_ntoa(clnt_adr.sin_addr));  // 클라이언트 IP 출력
	}
	close(serv_sock);  // 서버 소켓 닫기
	return 0;
}
	
// 클라이언트 요청을 처리할 함수 정의
void * handle_clnt(void * arg)
{
	int clnt_sock = *((int*)arg);  // 클라이언트 소켓 가져오기
	int str_len = 0, i;
	char msg[BUF_SIZE];
	
	while((str_len = read(clnt_sock, msg, sizeof(msg))) != 0)  // 클라이언트로부터 메시지 읽기
		send_msg(msg, str_len);  // 읽은 메시지를 모든 클라이언트에 전송
	
	pthread_mutex_lock(&mutx);
	for(i = 0; i < clnt_cnt; i++)  // 연결이 끊긴 클라이언트를 배열에서 제거
	{
		if(clnt_sock == clnt_socks[i])
		{
			while(i++ < clnt_cnt - 1)
				clnt_socks[i] = clnt_socks[i + 1];
			break;
		}
	}
	clnt_cnt--;
	pthread_mutex_unlock(&mutx);
	close(clnt_sock);  // 클라이언트 소켓 닫기
	return NULL;
}

// 메시지를 모든 클라이언트에 전송하는 함수 정의
void send_msg(char * msg, int len)
{
	int i;
	pthread_mutex_lock(&mutx);  // 뮤텍스 잠금
	for(i = 0; i < clnt_cnt; i++)
		write(clnt_socks[i], msg, len);  // 모든 클라이언트에 메시지 전송
	pthread_mutex_unlock(&mutx);  // 뮤텍스 잠금 해제
}

// 에러 메시지를 출력하고 프로그램을 종료하는 함수 정의
void error_handling(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
