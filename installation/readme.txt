
1. This is the git clone of https://github.com/weidai11/cryptopp.git
	(version 8.7 release)

2. During the installation it creates a ln and "ln -sf libcryptopp.so.8.7.0 libcryptopp.so.8" basically maps cryptopp++ 8.7 release version to libcrytopp.so.8 which is used by c++ in the 
runtime 

3. Always install same version of library on servers as this encryption/decryption is used across servers.

4. 	4.1 make && make dynamic 
	4.2 make install PREFIX=/usr && make install dynamic
		
	(here prefix /usr/ is the installation location for the library and at run time gcc will look for library in /usr/local/lib for the PREFIX=/usr/ added during runtime. 
