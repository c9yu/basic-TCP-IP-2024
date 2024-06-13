#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

// 에러를 처리하는 함수 프로토타입
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;  // 소켓 파일 디스크립터를 위한 변수
	int snd_buf, rcv_buf, state;  // 송신 버퍼, 수신 버퍼, 상태 변수를 선언
	socklen_t len;  // 옵션 길이를 저장할 변수
	
	sock = socket(PF_INET, SOCK_STREAM, 0);  // TCP 소켓을 생성
	
	// 송신 버퍼 크기를 가져오기 위한 코드
	len = sizeof(snd_buf);  // len 변수를 송신 버퍼 크기의 크기로 초기화
	state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, &len);  // 소켓 옵션을 가져옴
	if(state)  // getsockopt 함수가 실패하면 에러 처리
		error_handling("getsockopt() error");
	
	// 수신 버퍼 크기를 가져오기 위한 코드
	len = sizeof(rcv_buf);  // len 변수를 수신 버퍼 크기의 크기로 초기화
	state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void*)&rcv_buf, &len);  // 소켓 옵션을 가져옴
	if(state)  // getsockopt 함수가 실패하면 에러 처리
		error_handling("getsockopt() error");
	
	// 송신 버퍼와 수신 버퍼의 크기를 출력
	printf("Input buffer size: %d \n", rcv_buf);
	printf("Output buffer size: %d \n", snd_buf);
	
	return 0;
}

// 에러를 처리하는 함수 정의
void error_handling(char *message)
{
	fputs(message, stderr);  // 에러 메시지를 표준 에러 출력에 출력
	fputc('\n', stderr);  // 표준 에러 출력에 개행 문자 출력
	exit(1);  // 프로그램을 비정상 종료
}
