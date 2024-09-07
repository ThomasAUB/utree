#include <iostream>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "utree.hpp"


TEST_CASE("basic ull tests") {

    struct MyNode : utree::Node<MyNode> {

        struct Content {
            int a;
            int b;
        };

        Content mContent;
    };

    struct MyNode2 : utree::Node<MyNode2> {
        char str[16] = "Hello world";
    };

    MyNode n1;
    MyNode2 n2;
    utree::Container cc;

    utree::Container c;

    c.addChild(n1);
    c.addChild(n2);
    c.addChild(cc);

    n1.mContent.a = 55;
    n1.mContent.b = 89;

    ((MyNode::Content*) c[0].content())->a = 23;

    uint8_t i = 0;

    for (auto& e : c) {

        switch (i) {

            case 0:
                std::cout << ((MyNode::Content*) e.content())->a << " " << ((MyNode::Content*) e.content())->b << std::endl;
                break;

            case 1:
                std::cout << (char*) e.content() << std::endl;
                break;
            default:
                break;
        }

        i++;
    }

}

