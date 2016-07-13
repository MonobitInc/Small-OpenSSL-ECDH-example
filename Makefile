all: eb

eb: OpenSSL_ECDH.cpp
	g++ -o eb OpenSSL_ECDH.cpp cumino.cpp -lssl -lcrypto -g -pg -I/usr/local/Cellar/openssl/1.0.2f/include -I.




