//
//  main.cpp
//  Encoding and decoding
//
//  Created by 顏浩昀 on 2020/5/19.
//  Copyright © 2020 顏浩昀. All rights reserved.
//

#include <iostream>
#include "11014.h"

std::ostream& operator<<(std::ostream& os, Codec& data)
{
    data.show(os);
    return os;
}

void encode_decode(Codec & data)
{
    if (!data.is_encoded())
        data.encode();
    else
        data.decode();
}


int main()
{
    std::string input_string;
    std::cin >> input_string;

    DummyCodec dummy{input_string};
    encode_decode(dummy);
    std::cout << "Dummy encoding: ";
    std::cout << dummy << std::endl;
    encode_decode(dummy);
    std::cout << "Dummy decoding: ";
    std::cout << dummy << std::endl;

    RleCodec rle{input_string};
    encode_decode(rle);
    std::cout << "RLE encoding: ";
    std::cout << rle << std::endl;
    encode_decode(rle);
    std::cout << "RLE decoding: ";
    std::cout << rle << std::endl;
}