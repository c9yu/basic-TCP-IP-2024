#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 30

int main(int argc, char *argv[])
{
    fd_set reads, temps;  // 파일 디스크립터 셋을 위한 변수
    int result, str_len;
    char buf[BUF_SIZE];
    struct timeval timeout;  // 타임아웃을 위한 구조체

    FD_ZERO(&reads);  // reads 셋 초기화
    FD_SET(0, &reads);  // 0(표준 입력)을 reads 셋에 추가

    /*
    timeout.tv_sec=5;
    timeout.tv_usec=5000;
    */

    while(1)
    {
        temps = reads;  // temps 셋을 reads 셋으로 초기화
        timeout.tv_sec = 5;  // 타임아웃을 5초로 설정
        timeout.tv_usec = 0;  // 타임아웃의 마이크로초 부분을 0으로 설정
        result = select(1, &temps, 0, 0, &timeout);  // 파일 디스크립터 감시

        if (result == -1)  // select 함수가 에러를 반환한 경우
        {
            puts("select() error!");
            break;
        }
        else if (result == 0)  // 타임아웃이 발생한 경우
        {
            puts("Time-out!");
        }
        else  // 입력이 발생한 경우
        {
            if (FD_ISSET(0, &temps))  // 표준 입력에 데이터가 있는지 확인
            {
                str_len = read(0, buf, BUF_SIZE);  // 표준 입력으로부터 데이터 읽기
                buf[str_len] = 0;  // 문자열의 끝에 null 문자 추가
                printf("message from console: %s", buf);  // 읽어온 메시지 출력
            }
        }
    }
    return 0;
}
