#include <iostream>
#include "tinystr.h"
#include "tinyxml.h"
#include <string>


int main() {
    std::cout << "Hello World!" << std::endl;
    TiXmlDocument doc( "example.xml" );
    doc.LoadFile();
    TiXmlElement * root = doc.FirstChildElement();
    TiXmlElement * w = root -> FirstChildElement();
    std::cout << "Hello, again!";

    return 0;
}
