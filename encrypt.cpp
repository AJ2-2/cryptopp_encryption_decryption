#include <iostream>
#include <iomanip>
#include <fstream>
#include <cryptopp/modes.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
using namespace std;
using namespace CryptoPP;

string readEncryptedBinaryFile(string fname)
{
  string str="";
	std::ifstream is (fname, std::ifstream::binary);
  if (is) 
  {
    is.seekg (0, is.end);
    int length = is.tellg();
    is.seekg (0, is.beg);

    char * buffer = new char [length];
    is.read (buffer,length);

    if (!is)
    {
      std::cout<<"Error :couldn't open encypted file for reading\n";
      exit(-1);
    }
    is.close();

    for(int i=0;i<length;i++)                                                 // dont use t=buffer, because it automatically appends '\0' at the end
	    str+=buffer[i];
  
    delete[] buffer;
  }

	return str;
}


int main(int argc,char *argv[]) 
{
    string mode="1",fileName=argv[1],sKey="Password_key1234";

      //Key and IV setup
      //AES encryption uses a secret key of a variable length (128-bit, 196-bit or 256-   
      //bit). This key is secretly exchanged between two parties before communication   
      //begins. DEFAULT_KEYLENGTH= 16 bytes
      byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ], iv[ CryptoPP::AES::BLOCKSIZE ];
      //    memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
      memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

      if(CryptoPP::AES::DEFAULT_KEYLENGTH < sKey.size())
        sKey = sKey.substr(0, CryptoPP::AES::DEFAULT_KEYLENGTH); // chop if too long
      else if(CryptoPP::AES::DEFAULT_KEYLENGTH > sKey.size())
        sKey += std::string(CryptoPP::AES::DEFAULT_KEYLENGTH - sKey.size(), '*'); // pad
      memcpy(key, sKey.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);

    if(mode=="1")
    {
      // String and Sink setup
    
      string plaintext="";
      ifstream inFile;
      inFile.open(fileName);
      while(inFile.good())
      {
        string t;
        getline(inFile,t);
        plaintext+=t+"\n";
      }
      
      std::string ciphertext;

      //
      // Create Cipher Text
      //
      CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
      CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );

      CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( ciphertext ) );
      stfEncryptor.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length() );
      stfEncryptor.MessageEnd();

      ofstream oFile(fileName+".encrypt", ios::binary|ios::out);
      size_t len = ciphertext.size();
      oFile.write(ciphertext.c_str(), len);
      oFile.close();
      cout<<"AES encypted file: "<<fileName<<" -> "<<fileName<<".encrypt\n";
    }
    else if(mode=="2")
    {      
      string encryptedDataStr = readEncryptedBinaryFile(fileName);
      std::string decryptedtext;

      // Decrypt
      CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
      CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );

      CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedtext ) );
      stfDecryptor.Put( reinterpret_cast<const unsigned char*>( encryptedDataStr.c_str() ), encryptedDataStr.size() );
      stfDecryptor.MessageEnd();

      // Dump Decrypted Text
      ofstream outfile;
      outfile.open(fileName+".decrypt");
      outfile<<decryptedtext;
      outfile.close();
      std::cout<<" Decypted file: "<<fileName<<" -> "<<fileName<<".decrypt\n";
    }
    else
      cout<<" Invalid mode entered !!\n";

    return 0;
}
