#include <stdio.h>      // 표준 입출력 함수를 사용하기 위한 헤더 파일
#include <fcntl.h>      // 파일 제어 옵션을 사용하기 위한 헤더 파일
#define BUF_SIZE 3      // 버퍼 크기를 3바이트로 정의

int main(int argc, char *argv[])
{
    int fd1, fd2, len;  // 파일 디스크립터와 읽어들인 바이트 수를 저장할 변수
    char buf[BUF_SIZE]; // 데이터를 저장할 버퍼

    // "news.txt" 파일을 읽기 전용으로 열기
    fd1 = open("news.txt", O_RDONLY);
    
    // "cpy.txt" 파일을 쓰기 전용으로 열기, 파일이 없으면 생성, 기존 파일이 있으면 내용 삭제
    fd2 = open("cpy.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    // "news.txt"에서 데이터를 읽어 "cpy.txt"에 쓰기
    while ((len = read(fd1, buf, sizeof(buf))) > 0)
        write(fd2, buf, len);

    // 파일 디스크립터 닫기
    close(fd1);
    close(fd2);

    return 0;
}

/*
이 프로그램은 "news.txt" 파일을 읽어서 "cpy.txt" 파일에 복사하는 기능을 수행합니다.
버퍼 크기는 3바이트로 정의되어 있으며, "news.txt"에서 읽어들인 데이터를 "cpy.txt"에 
쓸 때마다 최대 3바이트씩 처리합니다. `open` 함수는 파일을 열고, `read`와 `write` 
함수는 데이터를 읽고 쓰는 데 사용됩니다. 마지막으로 `close` 함수를 사용하여 
열었던 파일 디스크립터를 닫습니다.
*/
