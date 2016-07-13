all: eb

eb: OpenSSL_ECDH.c
	gcc -o eb OpenSSL_ECDH.c -lssl -lcrypto -g -pg -I/usr/local/Cellar/openssl/1.0.2f/include




