#include "exp1.h"
#include <poll.h>

#define MAX_CLIENTS 64

typedef struct
{
  char cmd[64];
  char path[256];
  char real_path[256];
  char type[64];
  int code;
  int size;
} exp1_info_type;


void exp1_send_file(int sock, char* filename)
{
  FILE *fp;
  int len;
  char buf[16384];

  fp = fopen(filename, "r");
  if(fp == NULL){
    shutdown(sock, SHUT_RDWR);
    close(sock);
    return;
  }

  len = fread(buf, sizeof(char), 16384, fp);
  while(len > 0){
    int ret = send(sock, buf, len, 0);
    if(ret < 0){
      shutdown(sock, SHUT_RDWR);
      close(sock);
      break;
    }
    len = fread(buf, sizeof(char), 1460, fp);
  }

  fclose(fp);
}

void exp1_send_404(int sock)
{
  char buf[16384];
  int ret;

  sprintf(buf, "HTTP/1.0 404 Not Found\r\n\r\n");
  printf("%s", buf);
  ret = send(sock, buf, strlen(buf), 0);

  if(ret < 0){
    shutdown(sock, SHUT_RDWR);
    close(sock);
  }
}

void exp1_http_reply(int sock, exp1_info_type *info)
{
  char buf[16384];
  int len;
  int ret;

  if(info->code == 404){
    exp1_send_404(sock);
    printf("404 not found %s\n", info->path);
    return;
  }

  len = sprintf(buf, "HTTP/1.0 200 OK\r\n");
  len += sprintf(buf + len, "Content-Length: %d\r\n", info->size);
  len += sprintf(buf + len, "Content-Type: %s\r\n", info->type);
  len += sprintf(buf + len, "\r\n");

  ret = send(sock, buf, len, 0);
  if(ret < 0){
    shutdown(sock, SHUT_RDWR);
    close(sock);
    return;
  }

  exp1_send_file(sock, info->real_path);
}

void exp1_check_file(exp1_info_type *info)

{
  struct stat s;
  int ret;
  char* pext;

  sprintf(info->real_path, "html%s", info->path);
  ret = stat(info->real_path, &s);

  if((s.st_mode & S_IFMT) == S_IFDIR){
    sprintf(info->real_path, "%s/index.html", info->real_path);
  }

  ret = stat(info->real_path, &s);

  if(ret == -1){
    info->code = 404;
  }else{
    info->code = 200;
    info->size = (int) s.st_size;
  }

  pext = strstr(info->path, ".");
  if(pext != NULL && strcmp(pext, ".html") == 0){
    strcpy(info->type, "text/html");
  }else if(pext != NULL && strcmp(pext, ".jpg") == 0){
    strcpy(info->type, "image/jpeg");
  }else if (pext != NULL && strcmp(pext, ".mp4") == 0){
    strcpy(info->type, "video/mp4");
  }else if (pext != NULL && strcmp(pext, ".mp3") == 0){
    strcpy(info->type, "audio/mp3");
  }
}

void exp1_parse_status(char* status, exp1_info_type *pinfo)
{
  char cmd[1024];
  char path[1024];
  char* pext;
  int i, j;

  enum state_type
  {
    SEARCH_CMD,
    SEARCH_PATH,
    SEARCH_END
  }state;

  state = SEARCH_CMD;
  j = 0;
  for(i = 0; i < strlen(status); i++){
    switch(state){
    case SEARCH_CMD:
      if(status[i] == ' '){
        cmd[j] = '\0';
        j = 0;
        state = SEARCH_PATH;
      }else{
        cmd[j] = status[i];
        j++;
      }
      break;
    case SEARCH_PATH:
      if(status[i] == ' '){
        path[j] = '\0';
        j = 0;
        state = SEARCH_END;
      }else{
        path[j] = status[i];
        j++;
      }
      break;
    }
  }

  strcpy(pinfo->cmd, cmd);
  strcpy(pinfo->path, path);
}

int exp1_parse_header(char* buf, int size, exp1_info_type* info)
{
  char status[1024];
  int i, j;

  enum state_type
  {
    PARSE_STATUS,
    PARSE_END
  }state;

  state = PARSE_STATUS;
  j = 0;
  for(i = 0; i < size; i++){
    switch(state){
    case PARSE_STATUS:
      if(buf[i] == '\r'){
        status[j] = '\0';
        j = 0;
        state = PARSE_END;
        exp1_parse_status(status, info);
        exp1_check_file(info);
      }else{
        status[j] = buf[i];
        j++;
      }
      break;
    }

    if(state == PARSE_END){
      return 1;
    }
  }

  return 0;
}

int exp1_http_session(int sock)
{
  char buf[2048];
  int recv_size = 0;
  exp1_info_type info;
  int ret = 0;

  while(ret == 0){
    int size = recv(sock, buf + recv_size, 2048, 0);

    if(size == -1){
      return -1;
    }

    recv_size += size;
    ret = exp1_parse_header(buf, recv_size, &info);
  }

  exp1_http_reply(sock, &info);

  return 0;
}



int exp1_tcp_listen(int port) {
	int sock;
	struct sockaddr_in addr;
	int yes = 1;
	int ret;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket");
		exit(1);
	}

	bzero((char *) &addr, sizeof(addr));
	addr.sin_family = PF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

	ret = bind(sock, (struct sockaddr *) &addr, sizeof(addr));
	if (ret < 0) {
		perror("bind");
		exit(1);
	}

	ret = listen(sock, 5);
	if (ret < 0) {
		perror("reader: listen");
		close(sock);
		exit(-1);
	}

	return sock;
}

int get_max_psock(struct pollfd* pfds){
	int i;
	int j;
	for(i=0; i<MAX_CLIENTS; i++){
		if(pfds[i].fd == 0){
			break;
		}
	}
	for(j=i; j<=0; j--){
		if(pfds[j-1].fd != -1){
			return j;
		}
	}
}

int get_free_psock(struct pollfd* pfds){
	int i;
	for(i=0; i<MAX_CLIENTS; i++){
		if(pfds[i].fd == 0 || pfds[i].fd == -1){
			return i;
		}
	}
}

int main(int argc, char **argv)
{
	int port;
	int max_sock;

	if(argc != 2){
		printf("usage:%s [portnumber]\n",argv[0]);
		return -1;
	}

	port = atoi(argv[1]);

  struct pollfd fds[MAX_CLIENTS];
  memset(&fds,0,sizeof(fds));
  fds[0].fd = exp1_tcp_listen(port);
	fds[0].events = POLLIN;	//読みだし可能データを監視

  while(1){
    struct sockaddr addr;
    int sock_client;
    socklen_t len = sizeof(addr);

    max_sock = get_max_psock(fds);

		switch(poll(fds, max_sock, 100*1000)){	//1.pollfd 2.要素数 3.タイムアウト時間（ミリ秒）
			case -1:
				perror("poll");
				break;
			case 0:
				break;	/*pollが0を返すときはタイムアウト*/
			default:
				if(fds[0].revents & POLLIN){
					int newfd = get_free_psock(fds);
					fds[newfd].fd = accept(fds[0].fd, &addr, (socklen_t*) &len);
					fds[newfd].events = POLLIN;
				}
				for(int i=1; i<max_sock; i++){
					if(fds[i].revents & POLLIN){
						exp1_http_session(fds[i].fd);
						shutdown(fds[i].fd, SHUT_RDWR);
						close(fds[i].fd);
						fds[i].fd = -1;
					}
				}
			break;
		}
  }
}
