all: client server

server: ftp_server.c
	gcc -o ftp_server ftp_server.c

client: ftp_client.c
	gcc -o ftp_client ftp_client.c

clean:
	rm -rf ftp_client ftp_server
