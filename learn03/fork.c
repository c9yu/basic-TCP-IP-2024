#include <stdio.h>
#include <unistd.h>

int gval = 10;  // 전역 변수

int main(int argc, char *argv[])
{
    pid_t pid;
    int lval = 20;  // 지역 변수
    gval++;  // 전역 변수 증가
    lval += 5;  // 지역 변수 증가
    
    pid = fork();  // 새로운 프로세스 생성
    if (pid == 0)  // 자식 프로세스인 경우
        gval += 2, lval += 2;  // 전역 변수와 지역 변수 모두 증가
    else  // 부모 프로세스인 경우
        gval -= 2, lval -= 2;  // 전역 변수와 지역 변수 모두 감소
    
    if (pid == 0)  // 자식 프로세스인 경우
        printf("Child Proc: [%d, %d] \n", gval, lval);  // 전역 변수와 지역 변수 출력
    else  // 부모 프로세스인 경우
        printf("Parent Proc: [%d, %d] \n", gval, lval);  // 전역 변수와 지역 변수 출력
    return 0;
}
