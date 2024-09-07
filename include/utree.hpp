/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * MIT License                                                                     *
 *                                                                                 *
 * Copyright (c) 2024 Thomas AUBERT                                                *
 *                                                                                 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy    *
 * of this software and associated documentation files (the "Software"), to deal   *
 * in the Software without restriction, including without limitation the rights    *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the Software is           *
 * furnished to do so, subject to the following conditions:                        *
 *                                                                                 *
 * The above copyright notice and this permission notice shall be included in all  *
 * copies or substantial portions of the Software.                                 *
 *                                                                                 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   *
 * SOFTWARE.                                                                       *
 *                                                                                 *
 * github : https://github.com/ThomasAUB/utree                                     *
 *                                                                                 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once

#include "ulink.hpp"
#include <cstddef>

namespace utree {

    struct NodeBase : ulink::Node<NodeBase> {

        NodeBase(std::size_t inSize) :
            kContentSize(inSize - sizeof(NodeBase)) {}

        const void* content() const {
            return reinterpret_cast<const uint8_t*>(this) + sizeof(NodeBase);
        }

        void* content() {
            return reinterpret_cast<uint8_t*>(this) + sizeof(NodeBase);
        }

        std::size_t size() const {
            return kContentSize;
        }

    private:
        const std::size_t kContentSize;
    };

    template<typename derived_t>
    struct Node : NodeBase { Node() : NodeBase(sizeof(derived_t)) {} };

    struct Container : Node<Container>, ulink::List<NodeBase> {

        void addChild(NodeBase& n) {
            this->push_back(n);
        }

        NodeBase& operator [](std::size_t i) {
            std::size_t c = 0;
            for (auto& e : *this) {
                if (c++ == i) {
                    return e;
                }
            }
            std::raise(SIGSEGV);
            return *this->end();
        }

    };

}
