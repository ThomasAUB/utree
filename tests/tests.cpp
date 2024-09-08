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

    ((MyNode::Content*) c[0].content())->a = 23;
    ((MyNode::Content*) c[0].content())->b = 42;

    CHECK(n1.mContent.a == 23);
    CHECK(n1.mContent.b == 42);

    CHECK(&((MyNode::Content*) c[0].content())->a == &n1.mContent.a);
    CHECK(&((MyNode::Content*) c[0].content())->b == &n1.mContent.b);

    CHECK(((char*) c[1].content()) == n2.str);

    CHECK(c[0].size() == sizeof(MyNode::Content));
    CHECK(c[1].size() == sizeof(MyNode2::str));


    uint8_t i = 0;

    for (auto& e : c) {

        switch (i++) {

            case 0:
                CHECK(((MyNode::Content*) e.content())->a == n1.mContent.a);
                CHECK(((MyNode::Content*) e.content())->b == n1.mContent.b);
                break;
            case 1:
                CHECK((char*) e.content() == n2.str);
                break;
            default:
                break;
        }

    }

}

