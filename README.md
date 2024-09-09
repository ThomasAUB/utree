# utree

Lightweight C++ tree structure for microcontrollers.

- single-header
- no heap allocation
- platform independent

## Example

```cpp
#include "utree.hpp"

struct MyNodeA : utree::Node<MyNode> {
    
    struct Content {
        int a;
        int b;
    };

    Content mContent;
};

struct MyNodeB : utree::Node<MyNode> {
    char mText[16] = "Hello world";
};

int main() {

    MyNodeA n1;
    MyNodeB n2;
    MyNodeA n3;
    utree::Container subContainer;

    utree::Container c;

    c.addChild(n1);
    c.addChild(n2);
    c.addChild(subContainer);
    subContainer.addChild(n3);

    // access node n1
    ((MyNodeA::Content*) c[0].content())->a = 23;
    ((MyNodeA::Content*) c[0].content())->b = 42;

    // prints "Hello world"
    std::cout << (char*) c[1].content() << std::endl;

    // container iterator
    for(auto& item : c) {
        std::cout << item.size() << std::endl;
    }

    return 0;
}


```


