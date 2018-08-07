#include <stdio.h>
#include <unistd.h>

#include "led_tasks.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

const static char http_html_hdr[] =
    "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
const static char http_index_hml_s[] = "<!DOCTYPE html>"
"<html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>ESP32</title>"
"<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css\"></head><body>"
"<div class=\"container\"><div class=\"row\"><div class=\"col\"><h1>LED MODE:</h1>";
const static char http_index_hml_b[] = "<a class=\"btn btn-primary btn-lg btn-block\" href=\"%s\" role=\"button\">%s</a><br/>";
const static char http_index_hml_bd[] = "<a class=\"btn btn-primary btn-lg btn-block disabled\" href=\"%s\" role=\"button\">%s</a><br/>";
const static char http_index_hml_e[] = "</div></div></div></body></html>";

static char html_format_buffer[100];

int http_server_serve(int sock)
{
  struct netbuf *inbuf;
  char *buf;
  int buflen;

  buf = (char*)malloc(1024);

  buflen = recv(sock, buf, 1024, 0);

    //printf("buffer = %s \n", buf);
    if (buflen>=5 &&
        buf[0]=='G' &&
        buf[1]=='E' &&
        buf[2]=='T' &&
        buf[3]==' ' &&
        buf[4]=='/' ) {
     //     printf("buf[5] = %c\n", buf[5]);
	   
	  if(buf[5]=='0') {
        switchScene(0);
      } else if(buf[5]=='1') {
        switchScene(1);
      } else if(buf[5]=='2') {
        switchScene(2);
      } else if(buf[5]=='3') {
        switchScene(3);
      } else if(buf[5]=='4') {
        switchScene(4);
      } else if(buf[5]=='5') {
        switchScene(5);
      } else if(buf[5]=='6') {
        switchScene(6);
      } else if(buf[5]=='7') {
        switchScene(7);
      } else if(buf[5]=='8') {
        switchScene(8);
      } else if(buf[5]=='9') {
        switchScene(9);
      } else if(buf[5]=='A') {
        switchScene(10);
      } else if(buf[5]=='B') {
        switchScene(11);
      }










	  int mode = getScene();
	  
          send(sock, http_html_hdr, sizeof(http_html_hdr)-1, 0);
	  send(sock, http_index_hml_s, sizeof(http_index_hml_s)-1, 0);
	  // OFF
	  if (mode == 3) {
		  sprintf(html_format_buffer, http_index_hml_bd, "/3", "OFF");
	  } else {
		  sprintf(html_format_buffer, http_index_hml_b, "/3", "OFF");
	  }
	  send(sock, html_format_buffer, strlen(html_format_buffer), 0);
	  // Main light
	  if (mode == 2) {
		  sprintf(html_format_buffer, http_index_hml_bd, "/2", "Main light");
	  } else {
		  sprintf(html_format_buffer, http_index_hml_b, "/2", "Main light");
	  }
	  send(sock, html_format_buffer, strlen(html_format_buffer), 0);
	  // Box light
	  if (mode == 11) {
		  sprintf(html_format_buffer, http_index_hml_bd, "/B", "Main light box");
	  } else {
		  sprintf(html_format_buffer, http_index_hml_b, "/B", "Main light box");
	  }
	  send(sock, html_format_buffer, strlen(html_format_buffer), 0);
	  // Artnet
	  if (mode == 1) {
		  sprintf(html_format_buffer, http_index_hml_bd, "/1", "Artnet");
	  } else {
		  sprintf(html_format_buffer, http_index_hml_b, "/1", "Artnet");
	  }
	  send(sock, html_format_buffer, strlen(html_format_buffer), 0);
	  // Test
	  if (mode == 0) {
		  sprintf(html_format_buffer, http_index_hml_bd, "/0", "Test");
	  } else {
		  sprintf(html_format_buffer, http_index_hml_b, "/0", "Test");
	  }
	  send(sock, html_format_buffer, strlen(html_format_buffer), 0);
	  // Perlin HSV
	  if (mode == 4) {
		  sprintf(html_format_buffer, http_index_hml_bd, "/4", "Perlin HSV");
	  } else {
		  sprintf(html_format_buffer, http_index_hml_b, "/4", "Perlin HSV");
	  }
	  send(sock, html_format_buffer, strlen(html_format_buffer), 0);
  	  // Perlin RGB
	  if (mode == 5) {
		  sprintf(html_format_buffer, http_index_hml_bd, "/5", "Perlin RGB");
	  } else {
		  sprintf(html_format_buffer, http_index_hml_b, "/5", "Perlin RGB");
	  }
	  send(sock, html_format_buffer, strlen(html_format_buffer), 0);
	  // Perlin G
	  if (mode == 6) {
		  sprintf(html_format_buffer, http_index_hml_bd, "/6", "Perlin Green");
	  } else {
		  sprintf(html_format_buffer, http_index_hml_b, "/6", "Perlin Green");
	  }
	  send(sock, html_format_buffer, strlen(html_format_buffer), 0);
	  // Perlin B
	  if (mode == 7) {
		  sprintf(html_format_buffer, http_index_hml_bd, "/7", "Perlin Blue");
	  } else {
		  sprintf(html_format_buffer, http_index_hml_b, "/7", "Perlin Blue");
	  }
	  send(sock, html_format_buffer, strlen(html_format_buffer), 0);
	  // Allight
	  if (mode == 8) {
		  sprintf(html_format_buffer, http_index_hml_bd, "/8", "Allight");
	  } else {
		  sprintf(html_format_buffer, http_index_hml_b, "/8", "Allight");
	  }
	  send(sock, html_format_buffer, strlen(html_format_buffer), 0);
	  // Night
	  if (mode == 9) {
		  sprintf(html_format_buffer, http_index_hml_bd, "/9", "Night");
	  } else {
		  sprintf(html_format_buffer, http_index_hml_b, "/9", "Night");
	  }
	  send(sock, html_format_buffer, strlen(html_format_buffer), 0);
	  // COLORBOX
	  if (mode == 10) {
		  sprintf(html_format_buffer, http_index_hml_bd, "/A", "Color Box");
	  } else {
		  sprintf(html_format_buffer, http_index_hml_b, "/A", "Color Box");
	  }
	  send(sock, html_format_buffer, strlen(html_format_buffer), 0);


	  send(sock, http_index_hml_e, sizeof(http_index_hml_e)-1, 0);
    }

  free(buf);
}

int listen_sock;

void* thread_http_server( void* vptr_args) {
	int SERVER_PORT = 80;

	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;

	server_address.sin_port = htons(SERVER_PORT);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((listen_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		printf("HTTP: could not create listen socket\n");
		return NULL;
	}

	if ((bind(listen_sock, (struct sockaddr *)&server_address,
	          sizeof(server_address))) < 0) {
		printf("HTTP: could not bind socket\n");
		return NULL;
	}

	int flags = fcntl(listen_sock, F_GETFL, 0);
	fcntl(listen_sock, F_SETFL, flags | O_NONBLOCK);

	int wait_size = 16;
	if (listen(listen_sock, wait_size) < 0) {
		printf("HTTP: could not open socket for listening\n");
		return NULL;
	}

	struct sockaddr_in client_address;
	int client_address_len = 0;

	while (running) {
		int sock;
		if ((sock =
		         accept(listen_sock, (struct sockaddr *)&client_address,
		                &client_address_len)) < 0) {
			usleep(100000);
		} else {

		int n = 0;
		int len = 0, maxlen = 100;
		char buffer[maxlen];
		char *pbuffer = buffer;

		printf("HTTP: client connected with ip address: %s\n",
		       inet_ntoa(client_address.sin_addr));
		
		http_server_serve(sock);

		// keep running as long as the client keeps the connection open
		
		close(sock);
		}
	}

	close(listen_sock);
	return NULL;
}

void http_server_stop() {
	close(listen_sock);
}
/*
void http_server(void *pvParameters)
{



  struct netconn *conn, *newconn;
  err_t err;
  conn = netconn_new(NETCONN_TCP);
  netconn_bind(conn, NULL, 80);
  netconn_listen(conn);
  do {
     err = netconn_accept(conn, &newconn);
     if (err == ERR_OK) {
       http_server_netconn_serve(newconn);
       netconn_delete(newconn);
     }
   } while(err == ERR_OK);
   netconn_close(conn);
   netconn_delete(conn);
}*/
