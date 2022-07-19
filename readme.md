
1. re-compile Binary after changing the skey.
2. Both binary take one argument as a filename (to encypt/decrypt).
3. if skey doesnt match in encrypt.cpp and decrypt.cpp, while decryption it will throw ERROR.
4. You can't make skey as a command line argument as it gets compiled while creating the binary.

5. Other usefull links
	5.1 https://stackoverflow.com/questions/12306956/example-of-aes-using-crypto
	5.2 https://stackoverflow.com/questions/33753293/using-stdstring-for-key-with-aes-encryption-in-crypto
	5.3 https://www.cplusplus.com/reference/istream/istream/read/
	5.4 https://www.cryptopp.com/
	5.5 https://github.com/weidai11/cryptopp

6.1 https://cristhianizaparedes.wordpress.com/2017/03/17/how-to-install-crypto-library-on-ubuntu/

6.2 To install the libray on centOS follow the below steps:
	6.2.0 on centos "yum install cryptopp cryptopp-devel cryptopp-progs" doesnt work need to compile and then install the required library as follows.
	6.2.1 git clone https://github.com/weidai11/cryptopp.git
	6.2.2 make && make dynamic 
	6.2.3 make install PREFIX=/usr && make install dynamic
