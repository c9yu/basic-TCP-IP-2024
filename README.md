# basic-TCP-IP-2024
IoT 개발자 TCP/IP 학습 리포지토리

- 리눅스 조작
	- 경로 지정 관련
		- mkdir : 폴더 생성
		- cd 폴더명 : 폴더로 들어가기
		- cd : 초기 폴더로 돌아간다.
        - cd.. : 이전 경로로 돌아가기
		- ls : 현재 폴더에 있는 파일들의 목록을 보여준다.

	- 파일 관리
        - rm -rf 파일명 : 파일 삭제
		- nano 파일명 : 파일을 생성
		- sudo nano 파일명 : 파일을 수정
        - gcc 파일명 -o 실행파일명 : 컴파일
        - ./파일명 : 파일 실행
        - ps : 현재 실행중인 프로세스 확인
	
	- 세부 설정 변경
		- sudo nano /etc/nanorc 를 통해 설정창을 열어준다.
		- 줄번호 추가
			- linenumber 행의 주석을 제거해 준다.
        - backtab 크기 지정
            - backtab 행을 찾아서 숫자를 지정 (2가 적당하다)

    - 단축키
        - 복사
            - Shift + Ctrl + C
        - 붙여넣기
            - Shift + Ctrl + V
            

## 1일차 (2024-06-11)
- 프로토콜이란?
    - 컴퓨터 상호간의 대화에 피룡한 통신 규약

- TCP/IP 프로토콜 스택 4계층
    - APPLICATION 계층
    - TCP 계층 / UDP 계층
    - IP 계층
    - LINK 계층

- 데이터 전송 특성에 따른 소켓 타입 분류
    - 연결 지향형 소켓
        - 중간에 데이터가 소멸되지 않고 목적지로 전송된다.
        - 전송 순서대로 데이터가 수신된다.
        - 전송되는 데이터의 경계가 존재하지 않는다.

    - 비 연결 지향형 소켓
        - 전송된 순서에 상관없이 가장 빠른 전송을 지향한다.
        - 전송된 데이터는 손실의 우려가 있고, 파손의 우려가 있다.
        - 전송되는 데이터의 경계(Boundary)가 존재한다.
        - 한번에 전송할 수 있는 데이터의 크기가 제한된다.

- TCP/IP
	- IP
		- IPv4 : 4개의 byte로 구성되어 있다.
		- IPv6 : 향후 IPv4를 대체할 예정
	
		- 기본 게이트웨이 : 내 컴퓨터로 들어오는 출입문

	- 전송 방식
		- TCP / UDP
			- 통신 선로상에서 데이터(정보)가 흐른다.
		
			- TCP : 누락되는 데이터 없이 정확한 데이터의 전송이 필요한 경우 ex. 압축파일 등
			- UDP : 대용량으로 데이터를 전송해 한 두 개 잃어버려도 괜찮은 데이터 ex. 영상 등

- 네트워크 프로그래밍
	- 소말리아
		- 소 : 소켓 (Socket) : 전화기
		- 말 : 바인드 (Bind) : 전화번호
		- 리 : 리슨 (Listen) : 개통이 완료된 상태
		- 아 : 엑셉트 (Accept) : 통화(개통이 완료된 후)
	
	- Socket : 소켓 생성
	- Bind   : IP 주소와 PORT 번호 할당
	- Listen : 연결요청 가능상태로 변경
	- Accept : 연결요청에 대한 수락
	
	- 웹 통신이 이루어지는 원리
		- 특정한 키워드(데이터, 정보)를 서버에 보내면 해당 키워드에 해당하는 화면을 서버에서 보내준다.

    - 디스크립터
        - 주로 int fd의 형태로 선언하며, 특정 작업의 성공 여부에 따라 반환되는 값(0(성공), 1(실패))이 달라진다
        - 반환되는 값에 따라 다른 코드를 실행한다.

    - IPv4 기반의 주소표현을 위한 구조체
    ```
    struct sockaddr_in
    {
        sa_faaminly_t   sin_family;   // 주소체계 (Address Family)
        uint16_t        sin fort;     // 16비트 TCP/UDP PORT 번호
        struct in_addr  sin_addr;     // 32비트 IP 주소
        char            sin_zero[8];  // 사용되지 않음
    };

    struct in_addr
    {
        in_addr_t       s_addr;       // 32비트 IPv4 인터넷 주소
    }
    ```

    - 주소 체계
        - AF_INET IPv4 인터넷 프로토콜에 적용하는 주소체계
        - AF_INET6 IPv6 인터넷 프로토콜에 적용하는 주소체계
        - AF_LOCAL 로컬 통신을 위한 유닉스 프로토콜의 주소체계
    
    - 바이트 순서와 네트워크 바이트 순서
        - 리틀 엔디안/빅 엔디안
            - 작은 번지에 하위 바이트 값 : 리틀 엔디안
            - 작은 번지에 상위 바이트 값: 빅 엔디안

        - ex. 정수 0x12345678와, 0x20, 0x21, 0x22, 0x23 번지가 존재하는 경우
            - 0x12 : 최상위 바이트
            - 0x78 : 최하위 바이트

            - 0x20 : 최하위 번지
            - 0x23 : 최상위 번지

            - 즉, 최상위 바이트(0x12)가 최하위 번지(0x20)에 저장 : 빅 엔디안
            - 최하위 바이트(0x78)가 최하위 번지(0x20)에 저장 : 리틀 엔디안
    
## 2일차(2024-06-12)
## 2일차
- 인터넷 주소의 초기화

    ```c
    struct sockaddr_in addr;
    char* serv_ip = "211.217.168.13";
    char* serv_port = "9190";
    memset(&addr, 0, sizeof(addr)); // 구조체 변수 addr의 모든 멤버 0으로 초기화!
    addr.sin_family = AF_INET;      // 주소 체계 지정
    addr.sin_addr.s_addr = inet_addr(serv_ip)       // 문자열 기반의 IP주소 초기화
    addr.sin_port.s_addr = htons(atoi(serv_port));  // 문자열 기반의 PORT번호 초기화
    ```

    - memset 함수는 동일한 값으로 바이트단위 초기화를 할 때 호출하는 함수
    - 이 함수를 호출해서 addr을 전부 0으로 초기화하는 이유는
    - 0으로 초기화해야 하는 sockaddr_in 구조체 멤버 sin_zero를 0으로 초기화하기 위해서임!
    
- 서버 프로그램
    - sockaddr_in 구조체 변수 선언 > 서버 소켓이 동작하는 컴퓨터의 IP와 소켓에 부여할 PORT 번호로 초기화 > bind 함수 호출
- 클라이언트 프로그램
    - sockaddr_in 구조체 변수 선언 > 이를 연결할 서버 소켓의 IP와 PORT번호로 초기화 > connect 함수 호출

- INADDR_ANY 상수로 서버의 IP주소 할당

    ```c
        struct sockaddr_in addr;
        char* serv_port = "9190";
        memset(&addr, 0, sizeof(addr)); 
        addr.sin_family = AF_INET;      
        addr.sin_addr.s_addr = htonl(INADDR_ANY); // 소켓의 IP주소를 INADDR_ANY로 초기화할 경우, 소켓이 동작하는 컴퓨터의 IP주소가 자동으로 할당됨!
        addr.sin_port.s_addr = htons(atoi(serv_port));  
    ```

    - 이러면 컴퓨터 내에 두 개 이상의 IP 할당 받아 사용하는 경우(ex: Router)
    - 할당 받은 IP중 어떤 주소를 통해서 데이터가 들어오더라도 PORT 번호만 일치하면 수신 가능

- 루프팩 주소 - 127.0.0.1, 컴퓨터 자신의 IP주소

- 소켓에 인터넷 주소 할당
    - 초기화된 주소 정보를 소켓에 할당하는 bind 함수!

    ```c
    int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
        // 성공 시 0, 실패 시 -1 반환
        // sockfd : 주소 정보를 (IP,PORT) 할당할 소켓의 파일 디스크립터
        // myaddr : 할당하고자 하는 주소정보를 지니는 구조체 변수의 주소 값
        // addrlen : 두 번째 인자로 전달된 구조체 변수의 길이 정보
    ```

- TCP/IP 프로토콜 스택
    1. LINK 계층
        - 물리적인 영역의 표준화에 대한 결과
        - LAN, WAN, MAN과 같은 네트워크 표준과 관련된 프로토콜을 정의하는 영역
    2. IP 계층
        - 목적지로 데이터를 전송하기 위해 어떤 경로를 거쳐갈 것인지 해결하는 계층이며,
        - 이 계층에서 사용하는 프로토콜이 IP(Internet Protocol)!
        - IP 자체는 비 연결지향적, 신뢰할 수 없는 프로토콜 => 데이터 전송할 때마다 경로 선택 But 일정하지 않은 경로
        - 데이터 전송 도중 경로상 문제 발생 시 다른 경로 선택 But 데이터 손실 or 오류 발생 등에 대한 해결X
        - 오류발생에 대한 대비가 되어있지 않은 프로토콜
    3. TCP/UDP 계층
        - IP 계층에서 알려준 경로 정보를 바탕으로 데이터의 실제 송수신 담당
        - 전송(Transport) 계층
        - **TCP는 신뢰성 있는 데이터의 전송 담당**
        - IP는 오로지 하나의 데이터 패킷(데이터 전송의 기본 단위)이 전송되는 과정에만 중심을 두고 설계됨
        - 여러 개의 데이터 패킷을 전송한다 해도 각각의 패킷이 전송되는 과정은 IP에 의해 진행되므로 전송 순서 및 전송 자체 신뢰X
        - TCP는 데이터의 송수신 확인, 분실된 데이터 재전송 해줌
        - **TCP는 확인 절차를 걸쳐 신뢰성이 없는 IP에 신뢰성을 부여한 프로토콜!**
        - IP 상위 계층에서 호스트 대 호스트의 데이터 송수진 방식을 약속하는 TCP/UDP
    4. APPLICATION 계층
        - 클라이언트와 서버간의 데이터 송수신에 대한 정해진 약속(규칙)들을 APPLICATION 프로토콜이라고 함


- TCP 서버구현을 위한 함수 호출 순서
    1. socket() : 소켓 생성
    2. bind() : 소켓에 주소 할당
    3. listen() : 연결 요청 대기 상태
    4. accept() : 연결 허용(데이터 입출력용 소켓 생성!!)
    5. read()/write() : 데이터 송수신
    6. close() : 연결 종료

- 연결 요청을 허락하는 서버 소켓, 연결 요청 허락되고 실질적으로 데이터를 주고 받을 수 있는 클라이언트 소켓 두 개의 소켓이 생성되어야 함!

- listen()
    - listen() 호출 되어야 클라이언트가 연결 요청 할 수 있는 상태가 됨!
    - listen() 호출 되어야 클라이언트는 연결 요청을 위해 connect() 호출 가능

    ```c
    int listen(int sock, int backlog);
        // 성공 시 0, 실패 시 -1 리턴
        // sock : "연결 요청 대기 상태"에 두고자 하는 소켓의 파일 디스크립터 전달,
        //      : 이 함수의 인자로 전달된 디스크립터의 소켓이 "서버 소켓(리스닝 소켓)"이 됨
        // backlog : 연결 요청 대키 큐의 크기 정보 전달, 5가 전달되면 큐의 크기가 5가 되어 클라이언트의 연결요청을 5개까지 대기시킬 수 있다!
    ```

    - 서버가 연결 요청 대기 상태에 있다. = 클라이언트가 연결 요청을 했을 때 연결이 수락될 때까지 연결 요청 자체를 대기시킬 수 있는 상태에 있다.
    - 서버 소켓 
        - 연결 요청을 맞이하는 일종의 문지기 역할!
        - 클라이언트의 연결요청을 연결 요청 대기실(연결 요청 대기 큐)로!
        - listen 함수 호출되면 문지기 역할을 하는 서버 소켓이 생성되고, listen 함수 두 번째 인자로 전달되는 정수 크기만큼의 대기실 생성됨
        - 이 대기실이 연결 요청 대기 큐!
        - 클라이언트의 연결 요청을 받아들일 수 있는 상태(서버소켓 & 연결요청 대기 큐 준비 완료)를 연결 요청 대기 상태!

- **accept()**
    - 연결 요청 대기 큐에서 대기 중인 클라이언트의 연결 요청을 수락하는 기능의 함수
    - 호출 성공 시 내부적으로 데이터 입출력에 사용할 **소켓 생성** 하고, 해당 소켓의 파일 디스크립터 반환
    - **accept 함수 호출에 의해 생성된 소켓은 연결 요청을 한 클라이언트 소켓과 자동으로 연결됨!**

    ```c
    int accept(int sock, struct sockaddr* addr, socklen_t* addrlen);
        // 성공 시 생성된 소켓의 파일 디스크립터, 실패 시 -1 리턴
        // sock : 서버 소켓의 파일 디스크립터 전달
        // addr : 연결 요청한 클라이언트의 주소 정보를 담을 변수의 주소 값 전달
        //      : 함수 호출이 완료되면 인자로 전달된 주소의 변수에 클라이언트의 주소 정보 채워짐
        // addrlen : 두 번째 매개변수 addr에 전달된 주소의 변수 크기를 바이트 단위로 전달
        //         : 단, 크기 정보를 변수에 저장한 다음 변수의 주소 값 전달
        //         : 함수 호출 완료 시, 크기 정보로 채워져있던 변수에 클라이언트의 주소 정보 길이가 바이트 단위로 계산되어 채워짐
    ```

    - TCP 클라이언트의 함수 호출 순서
    1. socket() : 소켓 생성
    2. connect() : 연결 요청
    3. read()/write() : 데이터 송수신
    4. close() : 연결 종료

    - **connect()**
        - 클라이언트 소켓 생성 후 서버로 연결을 요청
        - 서버는 listen 함수 호출 이후부터 연결요청 대기 큐 만들어놓으니 그 때부터 클라이언트의 연결 요청이 가능해짐!!

        ```c
        int connect(int sock, struct sockaddr* servaddr, socklen_t addrlen);
            // 성공 시 0, 실패 시 -1 반환
            // sock : 클라이언트 소켓의 파일 디스크립터 반환
            // servaddr :  연결 요청할 서버의 주소 정보를 담은 변수의 주소 값 전달
            // addrlen : 두 번째 매개변수 servaddr에 전달된 주소의 변수 크기를 바이트 단위로 전달
        ```

        - connect() 호출 시 둘 중 한 가지 상황이 되어야 함수 반환(호출 완료)됨!
            1. 서버에 의해 연결 요청이 접수되었다.
            2. 네트워크 단절 등 오류 상황 발생하여 연결요청이 중단되었다.

            - 연결 요청의 접수 = 클라이언트의 연결요청 정보가 서버의 연결요청 대기 큐에 등록된 상황
        

    ![TCP기반 서버,클라이언트의 함수 호출 관계](https://raw.githubusercontent.com/c9yu/basic-TCP-IP-2024/main/imgs/img001.png)

- echo_server.c / echo_client.c 팀별로 확인해보기
    - ipTIME 관리자 > NAT/라우터 관리 > 포트포워드 설정
        - 규칙이름 : pi
        - 내부 IP 주소 : 라즈베리파이 ip
        - 프로토콜 : TCP
        - 외부포트 : 18080
        - 내부포트 : 18080

        - ./eserver 18080
        - ./eclient 210.119.12.65(서버용 컴퓨터(내 컴)) 18080

- TCP 소켓의 입출력버퍼
    - TCP 소켓의 데이터 송수신에는 경계X
        - 서버가 한번의 write 함수 호출로 40바이트를 전송해도, 클라이언트는 네 번의 read 함수 호출을 통해 10바이트씩 데이터 수신이 가능함
    - write 함수가 호출되는 순간 데이터는 **출력버퍼**로 이동하고,
    - read 함수가 호출되는 순간 **입력버퍼**에 저장된 데이터를 읽어들임

    1. 입출력 버퍼는 TCP 소켓 각각에 대해 별도로 존재
    2. 입출력 버퍼는 소켓 생성 시 자동으로 생성
    3. **소켓을 닫아도 출력버퍼에 남아있는 데이터는 계속해서 전송이 이루어짐**
        - 내 코드에 상관없이 OS가 맡아서 하고 있기 때문에 계속 전송이 이루어짐
    4. **소켓을 닫으면 입력버퍼에 남아있는 데이터는 소멸되어버림**
        - 소켓을 닫으면 read 함수로 데이터를 수신할 수 없기 때문..

## 3일차 (2024-06-13)
- TCP/UDP
    - 공통점
        - 네트워크 통신: TCP 클라이언트와 UDP 클라이언트는 모두 네트워크를 통해 서버와 통신합니다.
        - 주소와 포트 사용: 두 클라이언트 모두 통신을 위해 서버의 IP 주소와 포트 번호를 사용합니다.
        - TCP,UDP 모두 양방향 통신이 가능하다.
            - 데이터 송수신: TCP 클라이언트와 UDP 클라이언트는 모두 서버로 데이터를 전송하고 서버로부터 데이터를 수신할 수 있습니다.
    - 차이점
        - TCP의 경우 항상 연결을 유지한 채 데이터를 송수신을 진행한다
        - UDP의 경우 기본적으로 필요한 경우에만 연결을 한 뒤 데이터 송수신을 진행하고, 다시 연결을 끊어준다.

        - 연결 방식의 차이
            - TCP 클라이언트는 연결 지향적입니다. 서버와의 연결을 설정하고 데이터를 전송한 뒤에 연결을 종료합니다. 이를 통해 신뢰성 있는 데이터 전송이 가능합니다.
            - UDP 클라이언트는 비연결 지향적입니다. 서버와의 연결을 설정하지 않고 데이터를 전송합니다. 따라서 신뢰성 있는 데이터 전송이 보장되지 않습니다.

        - 신뢰성의 차이
            - TCP 클라이언트는 데이터 전송의 신뢰성을 보장합니다. 데이터가 손실되지 않고 순서대로 전달됩니다.
            - UDP 클라이언트는 데이터 전송의 신뢰성을 보장하지 않습니다. 데이터가 손실될 수 있고, 전송된 순서와 수신된 순서가 다를 수 있습니다.

        - 통신 방식의 차이
            - TCP 클라이언트는 연결 지향적이므로 데이터를 전송하기 전에 연결을 설정해야 합니다. 또한 연결이 설정된 후에만 데이터를 전송할 수 있습니다.
            - UDP 클라이언트는 비연결 지향적이므로 연결 설정 없이 데이터를 전송할 수 있습니다. 따라서 속도가 빠르고 오버헤드가 적습니다.

        - 헤더 크기와 오버헤드의 차이
            - TCP 헤더에는 제어 정보가 포함되어 있어 오버헤드가 큽니다. 따라서 작은 데이터를 주고받을 때에도 상대적으로 많은 오버헤드가 발생할 수 있습니다.
            - UDP 헤더는 간단하고 경량화되어 있어 오버헤드가 작습니다. 작은 데이터를 주고받을 때에도 TCP보다 더 적은 오버헤드가 발생합니다.

        - 전송 방식의 차이
            - TCP 클라이언트는 전이중(full-duplex) 방식으로 데이터를 송수신합니다. 즉, 동시에 양방향으로 데이터를 전송할 수 있습니다.
            - UDP 클라이언트는 반이중(half-duplex) 방식으로 데이터를 송수신합니다. 즉, 동시에 양방향으로 데이터를 전송할 수 없습니다.

    - UDP
        - 목적지 정보가 등록된 경우 : Connected Socket
        - 목적지 정보가 등록되지 않은 경우 : Unconnected Socket

        - 기본적으로 Unconnected Socket, 이는 매우 비효율적이다.
            - 세 개의 데이터를 세 번의 sendto 함수호출을 통해서 전송하는 경우
                - 이 경우
                    1. UDP소켓에 목적지의 IP와 PORT번호 등록
                    2. 데이터 전송
                    3. UDP 소켓에 등록된 목적지 정보 삭제
                - 의 3단계를 총 3회 반복해야한다. (비효율적)
                - 따라서 Unconnected Socket 을 Connected Socket으로 변경하는 것으로 성능향상을 기대할 수 있다.
        - Connected UDP 소켓을 생성하는 방법
            - UDP 소켓을 대상으로 connect 함수만 호출해주면 된다.

    - Socket/Stream
        - Stream : 소켓을 통해서 두 호스트가 연결되면 그 다음부터는 상호간에 데이터의 송수신이 가능한 상태가 된다.
        - Stream은 물의 흐름을 의미, 물의 흐름은 한쪽 방향으로만 형성된다.
        - 소켓의 Stream 역시 한쪽 방향으로만 데이터의 이동이 가능하기 때문에 양방향 통신을 위해서는 두 개의 Stream이 필요

    - 도메인 이름
        - 기억하기도 표현하기도 좋은 도메인 이름이라는 것을 IP 주소에 부여해서 이것이 IP 주소를 대신하도록 한다.

    - DNS 서버
        - 1. 네이버의 IP 주소를 입력하여 네이버에 접속
        - 2. 네이버의 도메인 이름 (www.naver.com)를 입력하여 네이버에 접속
        - 1번과 2번은 결과적으로는 둘 다 네이버에 접속하므로 차이가 없다.

        - 그러나 그 과정에 있어 차이가 존재
            - 도메인 이름의 경우 가상의 주소이지 실제 주소가 아니다.
            - 따라서 가상의 주소를 실제 주소로 변환하는 과정을 거친 뒤 네이버에 접속해야 한다.

        - 그렇다면 어떻게 도메인 이름을 -> IP 주소로 변환하는가
            - DNS 서버에 변환을 요청한다. 
            - DNS 서버
                - 계층적으로 관리되는 일종의 분산 데이터베이스 시스템

    - 소켓의 다양한 옵션
        - 지금까지는 소켓을 생성한 뒤 별다른 조작이 필요하지 않았다.
        - 그러나 이는 간단한 내용이었기 때문

        - 따라서 특정한 경우에는 소켓의 특성을 변화시켜야 할 수도 있다.

    - 주소 할당 에러(Binding Error) 발생
        -  클라이언트 콘솔에서 Ctrl + C를 통해 서버 프로그램을 강제 종료하는 경우 발생
        - 이경우 Bind() error가 발생
            - 이는 3분가량 지난 뒤 재실행하면 정상적으로 동작함

    - 프로세스
        - 메모리 공간을 차지한 상태에서 실행중인 프로그램
        - 프로세스 ID
            - 모든 프로세스는 생성되는 형태에 상관없이 운영체제로부터 ID를 부여받는다.
            - ps : 현재 실행중인 프로세스를 확인 가능한 명령어
            - fork 함수를 통한 프로세스 생성
                - fork 함수는 함께 호출한 프로세스의 복사본을 생성한다.
                - 완전히 동일한 복사본을 만드는 것이기 때문에 반환 값을 기준으로 나뉘도록 프로그래밍 해야한다.
        
        - 부모 프로세스 : 원본 프로세스, 즉 fork 함수를 호출한 주체가 된다.
        - 자식 프로세스 : 부모 프로세스의 fork 함수 호출을 통해서 복사된 프로세스를 의미한다.
        
        - 좀비 프로세스 : 프로세스가 생성되고 나서 할 일을 다하면 사라져야 하는데 사라지지 않고 남아 중요한 리소스르르 차지하는 상태의 프로세스
            - 생성 이유
                - 1. 인자를 전달하면서 exit를 호출하는 경우
                - 2. main 함수에서 return문을 실행하면서 값을 반환하는 경우
            - 'ps au'를 통해 확인 가능하다.
        
        - 좀비 프로세스의 생성을 막는 방법
            - wait 함수 : 블로킹의 문제가 발생
            - waitpid 함수 : 블로킹의 문제 해결

## 4일차 (2024-06-14)
- 시그널 핸들링
    - 자식 프로세스가 언제 종료될 지 알고 계속 waitpid 함수를 호출하는가?
    - 자식 프로세스가 종료되면 부모프로세스에게 알려주는 프로그램의 구현
    - 시그널 핸들링을 통해 이러한 프로그램을 구현 가능

- 시그널과 signal 함수
    - 프로세스는 자식 프로세스의 종료라는 상황 발생시, 특정 함수의 호출을 운영체제에 요구하는 것 : 이것이 signal 함수를 통해 이뤄진다.

- sigaction 함수
    - signal 함수와 유사하지만 훨씬 안정적으로 동작하는 함수
        - 그 이유는 signal 함수는 유닉스 계열의 운영체제 별로 동작방식에 있어서 약간의 차이를 보일 수 있지만, sigaction 함수는 차이를 보이지 않기 때문이다.
        
- 프로세스 기반의 다중접속 서버의 모델 구현
    - 동시에 둘 이상의 클라이언트에게 서비스를 제공하는 형태의 에코 서버
    - 클라이언트의 서비스 요청(연결요청)이 있을 때마다 에코 서버는 자식 프로세스를 생성해서 서비스를제공한다.
    - 즉, 서비스를 요청하는 클라이언트의 수가 다섯이라면 에코 서버는 추가로 다섯 개의 자식 프로세스를 생성하여 제공한다.

- fork 함수호출을 통한 파일 디스크럽터의 복사

- 프로세스간 통신의 기본 개념
    - 두 프로세스가 동시에 접근 가능한 메모리 공간만 있다면 이 공간을 통해서 얼마든지 데이터를 주고 받을 수 있다.
        - 하지만 프로세스는 완전히 별개의 메모리 구조를 지닌다.
    - 따라서 fork 함수호출을 통해서 새성된 자식 프로세스 조차 부모 프로세스와 메모리 공간을 조금도 공유하지 않는다.
    - 그래서 프로세스간 통신은 별도로 마련된 방법을 통해서만 이루어질 수 있다.

- 파이프
    - 두 프로세스간 통신을 위해서는 파이프를 이용해야 한다.
    - 길이가 2인 int형 배열의 주소 값을 인자로 전달하면서 위의 함수를 호출하면 배열에는 두 개의 파일 디스크립터가 담긴다
        - 이들은 각각 파이프의 출구와 입구로 사용된다.
    - 프로세스 모두 입출력 경로에 접근이 가능하지만, 자식은 입력 경로에만 부모는 출력 경로에만 접근해서 통신을 진행한다.

    - 파이프 기반의 양방향 통신
        - 파이프에 데이터가 들어가면 이는 임자없는 데이터가 된다.
        - 즉, read 함수 호출을 통해서 먼저 데이터를 읽어들이는 프로세스에게 데이터가 전달된다.
            - 그것이 파이프에 데이터를 가져다 놓은 프로세스라 할지라도.
        - 이 경우 파이프를 두 개 설치하여 해결 가능하다.

## 5일차 (2024-06-17)
- 멀티캐스트
    - 멀티캐스트의 데이터 전송방식과 멀티캐스트 트래픽 이점
        - 멀티캐스트 서버는 특정 멀티캐스트 그룹을 대상으로 데이터를 딱 한번 전송한다.
        - 딱 한번 전송하더라도 그룹에 속하는 클라이언트는 모두 데이터를 수신한다.
        - 멀티캐스트 그룹의 수는 IP 주소 범위 내에서 얼마든지 추가가 가능하다.
        - 특정 멀티캐스트 그룹으로 전송되는 데이터를 수신하려면 해당 그룹에 가입하면 된다.

    - TTL (Time to Live) : 패킷을 얼마나 멀리 전달할 것인가를 결정하는 주 요소

    - 멀티캐스트 Sender와 Reciver의 구현
        - 멀티캐스트의 경우 기존 '서버','클라이언트' 라는 표현 대신에 전송자(sender) 수신자(reciver)라는 표현을 사용

- 브로드캐스트
    - 브로드캐스트는 동일한 네트워크에 연결되어 있는 모든 호스트에게 동시에 데이터를 전송하기 위한 방법이다.
    - 멀티캐스트와 마찬가지로 UDP를 기반으로 데이터를 송수신한다.
    - 데이터 전송시 사용되는 IP 주소의 형태에 따라서 두 가지 형태로 구분
        - 1. Directed 브로드캐스트
        - 2. Local 브로드캐스트

- 소켓 표준과 입출력
    - 표준 입출력 함수의 두가지 장점
        - 표준 입출력 함수는 이식성(Portability)이 좋다.
        - 표준 입출력 함수는 버퍼링을 통한 성능의 향상에 도움이 된다.

    - 그렇다면 버퍼링을 하면 성능이 무조건 좋아지는가?
        - 모든 상황에서 우월한 성능을 보이는 것은 아니다.
            - 전송할 데이터의 양이 많을수록 버퍼링의 유무에 따른 성능차이가 커진다.
        - 두 가지 관점에서 성능에 대해 논할 수 있다.
            - 1. 전송하는 데이터 양
            - 2. 출력버퍼로의 데이터 이동 횟수
    
    - 표준 입출력 함수의 단점
        - 양방향 통신이 쉽지 않다.
        - 상황에 따라서 fflush 함수의 호출이 빈번히 등장할 수 있다.
        - 파일 디스크립터를 FILE 구조체의 포인터로 변환해야 한다.
        
- 입출력 스트림의 분리
    - 스트림 분리의 목적
        - 입력루틴(코드)과 출력루틴의 독립을 통한 구현의 편의성 증대
        - 입력에 상관없이 출력이 가능하게 함으로 인해서 속도의 향상 기대
        - FILE 포인터는 읽기모드와 쓰기모드를 구분해야 함으로
        - 읽기모드와 쓰기모드의 구분을 통한 편의성 증대
        - 입력버퍼와 출력버퍼를 구분함으로 인한 버퍼링 기능의 향상

    - 파일 디스크립터의 복사와 Half-close
        - 파일 디스크립터를 복사하여 각각의 FILE 포인터를 생성
        - 프로세스의 복사를 동반하지 않는 원본과 복사본이 하나의 프로세스 내에 존재하는 상태

    - 디스크립터의 복사는 다음 두 함수 중 하나를 이용해 진행한다.
    ```c
    #include <unistd.h>

    int dub(int fildes);
    int dup2(int fildes, int fildes2);
    ```

## 6일차 (2024-06-18)
- select보다 나은 epoll
    - select 기반의 IO 멀티플렉싱이 느린 이유
        - select 함수호출 이후에 항상 등장하는, 모든 파일 디스크립터를 대상으로 하는 반복문
        - select 함수를 호출할 때마다 인자로 매번 전달해야 하는 관찰대상에 대한 정보들

    - epoll이 select보다 낫다면 select는 필요없는 것인가?
        - 다음과 같은 경우네 select가 유용하게 사용된다.
            - 서버의 접속자 수가 많지 않다.
            - 다양한 운영체제에서 운영이 가능해야 한다.

    - epoll의 구현에 필요한 함수와 구조체
        - 상태변화의 확인을 위한, 전체 파일 디스크립터를 대상으로 하는 반복문이 필요없다.
        - select 함수에 대응하는 epoll_wait 함수호출 시, 관찰대상의 정보를 매번 전달할 필요가 없다.

    - epoll_create : 리소스 생성
    - epoll_ctl : epoll 인스턴스 생성 이후 관찰대상이 되는 파일 디스크립터를 등록
    - epoll_wait : select 함수에 해당되며, 관련 함수 중 가장 마지막에 호출된다.

    - 레벨 트리거
        - 레벨 트리거 방식에서는 입력버퍼에 데이터가 남아있는 동안에 계속해서 이벤트가 등록된다.

    - 레벨 트리거의 이벤트 특성
        - 클라이언트로부터 데이터가 수신될 때, 딱 한번 문자열 "return epoll_wait"이 출력된다. 그리고 이는 이벤트가 딱 한번 등록됨을 의미한다.

    - 엣지 트리거 기반의 서버 구현을 위해서 알아야 할 것 두가지
        - 변수 errno을 이용한 오류의 원인을 확인하는 방법
        - 넌-블로킹(Non-blocking) IO를 위한 소켓의 특성을 변경하는 방법
    
    - 엣지 트리거 기반의 에코 서버 구현
        - 엣지 트리거 방식에서는 데이터가 수신되면 딱 한번 이벤트가 등록된다.
        - "read 함수가 -1을 반환하고, 변수 errno에 저장된 값이 EAGAIN이라면 더 이상 읽어 들일 데이터가 존재하지 않은 상황이다.

    - 레벨 트리거와 엣지 트리거 중 무엇이 더 좋은가
        - 엣지 트리거 : 데이터의 수신과, 데이터가 처리되는 시점을 분리 할 수 있다.
        - 구현 모델의 특성상 엣지 트리거가 좋은 성능을 발휘할 확률이 상대적으로 높은 것은 사실이나, 단순히 엣지 트리거를 적용했다고 해서 무조건 빨라진다고 할 수는 없다.

- 멀티쓰레드 기반의 서버구현
    - 쓰레드의 등장배경
        - 멀티 프로세스의 단점 
            - 프로세스 생성이라는 부담스러운 작업 과정을 거친다.
            - 두 프로세스 사이에서의 데이터 교환을 위해서는 별도의 IPC 기법을 적용해야 한다.
            - 초당 수십번 ~ 수천 번까지 일어나는 컨텍스트 스위칭에 따른 부담

        - 결국 멀티프로세스의 특징을 유지하며, 단점을 어느정도 극복하기 위해 쓰레드가 등장했다.
        
        - 쓰레드와 프로세스의 차이점
            - 쓰레드는 둘 이상의 실행흐름을 갖기 위해서 프로세스가 유지하는 메모리 영역을 통째로 복사하는것이 부담스러웠기에 등장했다.

            - 그런데 둘 이상의 실행흐름을 갖는 것이 목적이라면, 위 그림처럼 완전히 메모리 구조를 분리시킬 것이 아니라 스택영역만을 분리하여 몇가지 장점을 얻어낼 수 있다.
                - 컨텍스트 스위칭 시 데이터 영역과 힙은 올리고 내릴 필요가 없다.
                - 데이터 영역과 힙을 사용해서 데이터를 교환할 수 있다.

            - 프로세스 : 운영체제 관점에서 별도의 실행흐름을 구성하는 단위
            - 쓰레드 : 프로세스 관점에서 별도의 실행으름을 단위

    - 쓰레드의 임계영역의 문제와 관련해 함수를 두 가지 종류로 구분
        - 쓰레드에 안전한 함수
        - 쓰레드에 불안전한 함수

    - 워커 쓰레드 모델
        - 쓰레드가 main이 관리하는 일꾼의 형태를 갖는다.

    - 쓰레드의 문제점과 임계영역
        - 하나의 변수에 둘 이상의 쓰레드가 동시에 접근하는 것이 문제가 된다.
        - 문제가 발생하는 형태
            - 1. 두 쓰레드가 동시에 thread_inc 함수를 실행하는 경우
            - 2. 두 쓰레드가 동시에 thread_des 함수를 실행하는 경우
            - 3. 두 쓰레드가 각각 thread_inc 함수와 thread_des 함수를 동시에 실행하는 경우

        - 임계영역
            - 함수 내에 둘 이상의 쓰레드가 동시에 실행하면 문제를 일으키는 하나 이상의 문장으로 묶여있는 코드블록

    - 쓰레드의 동기화
        - 동기화의 두 가지 측면
            - 동이한 메모리 영역으로의 동시접근이 발생하는 상황
            - 동일한 메모리 영역에 접근하는 쓰레드의 실행순서를 지정해야 하는 상황

        - 뮤텍스
            - 동시 접근을 허용하지 않는다는 의미로 쓰레드의 동기접근에 대한 해결책

        - 세마포어
            - 세마포어는 뮤택스와 매우 유사하다

## 미니프로젝트


# 라즈베리 파이
## 1일차 (2024-06-20)
- 라즈베리 파이 핀의 역할
    - 1번, 17번 핀 : 3V
    - 2번, 3번 핀 : 5V (VCC)
    - 6번, 9번, 14번, 20번, 25번, 30번, 34번, 39번 핀 : 그라운드 (0V)

    - 핀 번호와 물리적 번호가 다르니 잘못 연결하지 않게 주의할 것

    - 전류 (I) : 전하의 흐름, 단위 시간 동안에 흐른 전하의 양
    - 전압 (V) : 전기장 안에서 전하가 갖는 전위의 차
    - 저항 (R) : 전류가 흐르는 것을 방해하는 정도

    - 옴의 법칙 : I = V/R 
        - 두 지점 사이의 도체에 일정한 전위차가 존재 할 때, 도체의 저항의 크기와 전류의 크기는 반비례한다.

    - 키르히호프
        - 전류 법칙 (KCL) : 특정 노드 혹은 닫힌 영역에 들어오는 전류의 대수적 합은 0이다.
        - 전압 법칙 (KVL) : 닫힌 경로 혹은 루프에서 모든 전압의 대수적 합은 0이다.

    - GPIO 설정함수
        - GPIO.setmode(GPIO.BOARD) - wpi
        - GPIO.setmode(GPIO.BCM) - BCM
        - GPIO.setup(channel, GPIO.mode)
        - -channel: 핀번호, mode: IN/OUT
        - GPIO.cleanup()
    - GPIO 출력함수
        - GPIO.output(channel, state)
        - -channel: 핀번호, state: HIGH/LOW or 1/0 or True/False
    - GPIO 입력함수
        - GPIO.input(channel)
        - -channel: 핀번호, 반환값: H/L or 1/0 or T/F
    - 시간지연 함수
        - time.sleep(secs)

    - 풀업 저항
        - input에 1이 들어간다
            - 스위치를 눌렀을 때 0이 된다.
            
    ![입력이VCC에연결된경우](https://raw.githubusercontent.com/c9yu/basic-TCP-IP-2024/main/imgs/img002.jpg)


    - 풀다운 저항
        - input에 0이 들어간다
            - 스위치를 눌렀을 때 1이 된다.

    ![입력이GND에연결된경우](https://raw.githubusercontent.com/c9yu/basic-TCP-IP-2024/main/imgs/img003.jpg)


    - interrupt

## 2일차 (2024-06-20)
- 가상환경 만들기
    - 파이썬 버전 확인 : python -V
    - 가상환경 만들기 : python -m venv env
    - 가상환경 실행하기 : source ./env/bin/activate
    - 가상환경 종료하기 : deactivate

- 가상환경을 사용하는 이유
    - 문제가 생기는 경우 가상환경 자체를 삭제하여 피해를 막을 수 있기 때문

- 가상환경에서 RPi를 못찾는 경우
    - 다운로드 해줘야 함
        - pip install RPi.GPIO

- 적외선 센서 동작이 잘 안되는 경우
    - 추가 프로그램을 다운로드 해줘야한다.
        - 1. sudo git clone https://github.com/WiringPi/WiringPi
        - 2. sudo ./build
        - 3. gpio readall
            - led가 계속 켜진다면 led를 연결해둔 핀에 1이 디폴트값으로 들어가 있어서 그런 것이다.


## 3일차 (2024-06-24)


- 웹서버 만들기
    - flask (가상환경에서 진행)
        - pip install flask
            - python flask01.py
                - 두번째 IP는 라즈베리 파이 내부의 인터넷에서 접속하는 경우
                - 세번째 IP는 기존 윈도우의 인터넷에서 접속하는 경우
        
    - 옵션이 추가된 가상환경 만들기
        - python -m venv --system-site-packages env
        - 이 경우 pip list를 통해 확인해보면 다양한 파일들이 가상환경 생성과 동시에 설치되어 있다.
            - 앞서 직접 설치해줬던 flask도 마찬가지

```C
from flask import Flask

app = Flask(__name__)  # name 이름을 통한 flask 객체 생성

@app.route("/") # 라우팅을 위한 함수 등록
def hello():
  return "Hello World" 

if __name__ == "__main__": # 터미널에서 직접 실행시켜야 실행파일의 이름이 main으로 바뀐다.
  app.run(host="0.0.0.0", port="10200", debug=True) # 실행을 위한 명령문으로 보면된다.
  # port = ~~~ : port번호를 지정 가능
  # debug = True : 디버깅을 가능하도록 함
```

- 정적 라우팅
    - flask 내부에 함수를 구현한다.
    - 서버를 열고 접속
    - 주소창 뒤에 함수를 입력 ex. 192.168.5.3:10200/age와 같이 입력시
    - 작성해둔 함수의 리턴값이 출력

- URL 접속을 통한 라즈베리 파이 동작
    - 함수를 활용

- 값을 보자
```C
from flask import Flask, request

app = Flask(__name__)

@app.route("/")
def get():
  value1 = request.args.get("이름", "user")
  value2 = request.args.get("주소", "부산")
  return value1 + ":" + value2

if __name__ == "__main__":
  app.run(host = "0.0.0.0", port = "10011", debug=True)
```
- 실행 후 http://192.168.5.3:10011/?이름=홍길동&주소=제주도
    - 위 형태로 값을 넣어준다.

## 4일차 (2024-06-25)

## 5일차 (2024-06-26)
- 세븐 세그먼트 활용
    - 1. 세그먼트 1의 자리(COM4)에서 0~9가 순차적으로 반복
    ```c
    #핵심 코드
    try:
        while True:
            if GPIO.input(btn) == True:
             i = 0
            for i in range(6):
                GPIO.output(leds[i], seg_patterns[count_1][i])
            count_1 = count_1 + 1
            print(count_1)
            time.sleep(1)

        if count_1 == 10:
            count_1 = 0
    ```
    - 변수 count를 선언하여 해당 변수를 증가시켜줘 count의 증가에 따라 세그먼트에 출력되는 숫자가 증가하게 함

    - 2. 세그먼트의 네자리 (COM1 ~ COM4)에 '1234'가 출력
    ```c
    #핵심 코드
    def display_digit(com, digit):
        for i in range(0, 4):
            if i == com:
                GPIO.output(digits[i], True)
            else:
                GPIO.output(digits[i], False)
        for j in range(0, 7):
            GPIO.output(segments[j], num[digit][j])

    def display_number(numbers):
        numbers_1 = numbers // 1000
        numbers_2 = (numbers % 1000) // 100
        numbers_3 = (numbers % 100) // 10
        numbers_4 = numbers % 10
        display_digit(0, numbers_1)
        time.sleep(0.001)
        display_digit(1, numbers_2)
        time.sleep(0.001)
        display_digit(2, numbers_3)
        time.sleep(0.001)
        display_digit(3, numbers_4)
        time.sleep(0.001)

    def main():
        setup()
        try:
            while True:
                display_number(1234) # 각 자리수에 출력할 숫자를 지정
        except KeyboardInterrupt:
            GPIO.cleanup()
    ```
    - 두 함수 'display_digit'과 'display_number'를 정의하여 사용한다. display_digit은 각 자리를 나타내는 역할을 수행, display_number는 각 자리의 값을 나타내는 역할을 수행한다.

    - 3. 세그먼트의 네자리에 0000 ~ 9999가 1초 단위로 출력
    ```c
    try:
        while True:
            count = 0
            for i in range(0, 9999):
                start_time = time.time()
                while time.time() - start_time < 1:
                    display_number(i)
                if i == 9999:
                i = 0
    ```
    - 2번과 소스코드 자체에 큰 차이는 없으나 count라는 변수를 선언하여 count값이 증가함에 따라 count값을 세그먼트에서 출력하게끔 하였다.
    - 방법 자체는 간단하나, time.time() 함수를 사용하지 않으면 1000, 100, 10의 자리의 값들이 매우 빠른속도로 넘어가 카운트의 기능 자체는 동작하지만 1의 자리만 육안으로 관찰되는 문제가 발생한다.
    - 따라서 time.time()함수를 사용해 1초의 시간동안 네 자리의 값들 모두가 동일하게 반복되는 형태를 취하여 문제를 해결할 수 있었다.