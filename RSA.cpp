#include <iostream>
#include <string>
#include <time.h>

typedef unsigned int uint;
int Str_op();
int main()
{
    Str_op();
    int str2;
    std::cin >> str2;
    return 0;
}

int Nod(int x, int y)
{
    return y ? Nod(y, x%y) : x;
}

int Prime_number(int a)
{
    unsigned int i;
    if (a == 2)
        return 1;
    if (a == 0 || a == 1 || a % 2 == 0)
        return 0;
    for (i = 3; i*i <= a && a % i; i += 2);
    return i*i > a;
}

void encrypt(uint *message_not_en, uint *message_en, int length)
{
    int p, q;
    while (2)
    {
        std::cout << "Enter Prime Numbers " << std::endl;
        std::cin >> p;
        std::cin >> q;
        if (Prime_number(p) == 0 || Prime_number(q) == 0)
        {
            std::cout << "There are no prime numbers " << std::endl;
            continue;
        }
        break;
    }
    
    int n = p*q;
    int fi = (p - 1)*(q - 1);
    int e, e_1 = 0;
    srand(time(NULL));
    while (e_1 != 1)
    {
        e = rand() % 100;
        e_1 = Nod(e, fi);
    }
    std::cout << "Public key: {" << e << "," << n << "}" << std::endl;
    int d = 0;
    int d_1 = 0;
    while (d_1 != 1)
    {
        d += 1;
        d_1 = (e*d) % fi;
    }
    std::cout << "Private key: {" << d << "," << n << "}" << std::endl;
    
    for (int c = 0; c < length; c++)
    {
        int unsintel = 1;
        for (int k = 1; k <= e; k++)
        {
            unsintel = (unsintel*(*(message_not_en + c))) % n;
        }
        *(message_en + c) = unsintel;
    }
}

int decrypt(uint *message_en, int d, int n, uint *message_dec, int length)
{
    for (int c = 0; c < length; c++)
    {
        int unsintel = 1;
        for (int k = 1; k <= d; k++)
            
        {
            unsintel = (unsintel*(*(message_en + c))) % n;
        }
        *(message_dec + c) = unsintel;
    }
    return 0;
}

int Str_op()
{
    int p1, p2;
    int magic_number = 48;
    std::cout << "Enter message: " << std::endl;
    std::string inputstr;
    getline(std::cin, inputstr);
    int length = inputstr.size();
    uint *message_not_en = new uint[length];
    uint *message_en    = new uint[length];
    uint *message_dec    = new uint[length];
    std::cout << std::endl;
    for (int c = 0; c < length; c++)
    {
        *(message_not_en + c) = static_cast<int>(inputstr[c]) - magic_number;
        std::cout << *(message_not_en + c) << " ";
    }
    std::cout << std::endl;
    encrypt(message_not_en, message_en, length);
    
    if (message_en == NULL)
    {
        std::cerr << "Error" << std::endl;
        int str;
        std::cin >> str;
        return 0;
    }
    std::cout << "There is a crypted message: " << std::endl;
    for (int c = 0; c < length; c++)
    {
        std::cout << (*(message_en + c)) << " ";
    }
    std::cout << std::endl;
    std::cout << "Enter private key: " << std::endl;
    std::cin >> p1;
    std::cin >> p2;
    decrypt(message_en, p1, p2, message_dec, length);
    std::cout << "Result: " << std::endl;
    for (int c = 0; c < length; c++)
    {
        std::cout << (*(message_dec + c)) << " ";
    }
    std::cout << std::endl;
    return 0;
}