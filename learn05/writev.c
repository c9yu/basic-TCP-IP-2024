#include <stdio.h>      // 표준 입출력 함수를 사용하기 위한 헤더 파일
#include <sys/uio.h>    // 벡터 입출력 함수를 사용하기 위한 헤더 파일

int main(int argc, char *argv[])
{
    struct iovec vec[2];       // 두 개의 iovec 구조체 배열을 선언
    char buf1[] = "ABCDEFG";   // 첫 번째 버퍼, 출력할 문자열
    char buf2[] = "1234567";   // 두 번째 버퍼, 출력할 문자열
    int str_len;               // 출력한 총 바이트 수를 저장할 변수

    // 첫 번째 iovec 구조체 초기화 (버퍼의 시작 주소와 길이)
    vec[0].iov_base = buf1;    // 버퍼1의 시작 주소
    vec[0].iov_len = 3;        // 버퍼1의 길이 (3바이트만 출력)

    // 두 번째 iovec 구조체 초기화 (버퍼의 시작 주소와 길이)
    vec[1].iov_base = buf2;    // 버퍼2의 시작 주소
    vec[1].iov_len = 4;        // 버퍼2의 길이 (4바이트만 출력)

    // 벡터 입출력을 사용하여 데이터를 출력 (표준 출력, 파일 디스크립터 1)
    str_len = writev(1, vec, 2);

    puts("");                  // 줄 바꿈을 출력하여 출력 결과를 보기 좋게 함
    printf("Write bytes: %d \n", str_len); // 총 출력한 바이트 수를 출력

    return 0;
}
