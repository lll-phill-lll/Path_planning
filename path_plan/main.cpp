#include <iostream>
#include "tinystr.h"
#include "tinyxml.h"
#include <string>


int main() {
    std::cout << "Hello World2!" << std::endl;
    // Make xml: <?xml ..><Hello>World</Hello>
        TiXmlDocument doc;
        TiXmlDeclaration * decl = new TiXmlDeclaration("1.0","","");
        TiXmlElement * element = new TiXmlElement("Hello");
        TiXmlText * text = new TiXmlText("World");
        element->LinkEndChild(text);
        doc.LinkEndChild(decl);
        doc.LinkEndChild(element);
        doc.SaveFile("madeByHand.xml");
        std::cout << "ttt";

    return 0;
}
