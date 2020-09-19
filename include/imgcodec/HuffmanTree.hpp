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
    
    Node(const Uint16 value, const std::string code) : 
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
    Uint16 value; 

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
    std::string contains(std::string& huffmanCode);

    bool empty();
    void clear();

protected:
    NodePtr getRightLevelNode(NodePtr node);
    void createChilds(NodePtr node);

    NodePtr root_;
};

}


#endif /* HUFFMANTREE_HPP */
