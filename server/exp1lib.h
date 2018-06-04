
/**
 * prototype 
 */
int exp1_tcp_listen(int port);
int exp1_tcp_connect(const char *hostname, int port);
int exp1_udp_listen(int port);
int exp1_udp_connect(const char *hostname, int port);
double gettimeofday_sec();
int exp1_do_talk(int sock);
void exp1_init_clients();
void exp1_do_server(int sock_listen);
void exp1_add(int sock);
void exp1_remove(int id);
int exp1_get_max_sock();
void exp1_set_fds(fd_set* pfds, int accept_sock);

