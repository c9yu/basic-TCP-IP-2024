#include <stdio.h>   // 표준 입출력 함수를 사용하기 위한 헤더 파일
#include <unistd.h>  // UNIX 표준 함수들을 사용하기 위한 헤더 파일

int main(int argc, char *argv[])
{
    int cfd1, cfd2;                 // 복제된 파일 디스크립터를 저장할 변수
    char str1[] = "Hi~ \n";         // 첫 번째 문자열
    char str2[] = "It's nice day~ \n"; // 두 번째 문자열

    // 표준 출력(파일 디스크립터 1)을 복제하여 새로운 파일 디스크립터 cfd1 생성
    cfd1 = dup(1);
    // cfd1을 복제하여 파일 디스크립터 7에 할당 (이미 존재하면 덮어씌움)
    cfd2 = dup2(cfd1, 7);
    
    // 복제된 파일 디스크립터 번호 출력
    printf("fd1=%d, fd2=%d \n", cfd1, cfd2);
    // cfd1을 통해 str1 문자열 출력
    write(cfd1, str1, sizeof(str1));
    // cfd2를 통해 str2 문자열 출력
    write(cfd2, str2, sizeof(str2));
    
    // 파일 디스크립터 cfd1 닫기
    close(cfd1);
    // 파일 디스크립터 cfd2 닫기
    close(cfd2);
    // 표준 출력(파일 디스크립터 1)을 통해 str1 문자열 출력
    write(1, str1, sizeof(str1));
    // 표준 출력(파일 디스크립터 1) 닫기
    close(1);
    // 표준 출력이 닫혔으므로 아래 코드는 출력되지 않음
    write(1, str2, sizeof(str2));
    
    return 0;
}
