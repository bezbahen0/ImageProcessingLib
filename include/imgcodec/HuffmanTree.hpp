#ifndef HUFFMANTREE_HPP
#define HUFFMANTREE_HPP

#include <string>
#include <memory>

#include "include/types.hpp"

namespace imp
{

struct Node;
using NodePtr = std::shared_ptr<Node>;


struct Node
{

    Node() : right(nullptr), left(nullptr), parent(nullptr), value(0x0000), code("")
    {
    }
    
    Node(const uint16_t value, const std::string code) : 
        value(value), code(code), right(nullptr), left(nullptr), parent(nullptr)
    {
    }

    ~Node()
    {
    }

    bool isRoot()
    {
        return parent == nullptr;
    }

    bool isLeaf()
    {
        return right == nullptr && left == nullptr;
    }

    std::string code;
    uint16_t value; 

    NodePtr right;
    NodePtr left;
    NodePtr parent;
};


class HuffmanTree
{
public:
    HuffmanTree();
    HuffmanTree(const HuffmanTableType& table);
    ~HuffmanTree();
    
    NodePtr getRoot();
    void insert(NodePtr node, const uint16_t value);

    bool empty();
    void clear();

protected:
    NodePtr getRightLevelNode(NodePtr node);
    void createChilds(NodePtr node);

    NodePtr root_;
};

}


#endif /* HUFFMANTREE_HPP */
