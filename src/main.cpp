#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
//File-Based Vigenère Cipher
class FileEncrypter
{
    public:
    std::string unlengthedkey{};
    std::string AskKey()
    {
        std::string key;
        std::cout << "Key : " << key;
        std::getline(std::cin,key);
        unlengthedkey = key;
        return key;
    }
    void LengthenKey(std::string & key,int length)

    {
        if(key.empty())return;
        const int originallength = key.length();
        for(int index = 0;index < key.length();index++)
            {
                key += key[index];
                if(index == originallength - 1)
                {
                    index = 0;
                }
                if (key.length() >= length) 
                {
                break; 
                }
            }

    }
    void Encrypt(std::string& key)
    {
        std::string line;
        std::ifstream FileReader("data.txt");

        if (!FileReader || key.empty())
            return;

        std::getline(FileReader, line);
        FileReader.close();
        LengthenKey(key,line.length());

        for (int i = 0; i < line.length(); i++)
        {
            line[i] = static_cast<char>(
                (static_cast<unsigned char>(line[i])
                + static_cast<unsigned char>(key[i % key.length()]))
                % 256
            );
        }

        std::ofstream File("encrypted.txt");
        File << line;
    }
    void Decrypt()
    {
        std::ofstream file{"decrypted.txt"};

        std::string key;
        std::string txt;
        std::cout << "Enter the key of your encrypted file : ";
        std::cin >> key ;
        if(key != unlengthedkey)std::cout << "Fuck off!! if you dont know the actual key";
        else
        {
            std::ifstream filereader{"encrypted.txt"};
            std::getline(filereader,txt);
            filereader.close();
            std::ofstream filewriter{"decrypted.txt",std::ios::app};
            for (int i = 0; i < txt.length(); i++)
            {
                    txt[i] = static_cast<char>(
                    (static_cast<unsigned char>(txt[i])
                    - static_cast<unsigned char>(key[i % key.length()]))
                    % 256
                );
            }
            filewriter << txt << std::endl;
            filewriter.close();
        }
    }    
};


int main ()
{
    FileEncrypter Test;
    std::string key = Test.AskKey();
    Test.Encrypt(key);
    Test.Decrypt();
    std::cout << key << std::endl;
    return 0;
}