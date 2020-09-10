#ifndef HUFFMANTREE_HPP
#define HUFFMANTREE_HPP

#include <string>

#include "include/types.hpp"

namespace imp
{
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

    Node* right;
    Node* left;
    Node* parent;
};

class HuffmanTree
{
public:
    HuffmanTree(const HuffmatTableType& table);
    ~HuffmanTree();
    
    Node* getRoot();
    void insert(Node* node, const uint16_t value);

    bool empty();
    void clear();

private:
    Node* getRightLevelNode(const Node* node);
    void createNode(Node* node);

    Node* root_;
};

}


#endif /* HUFFMANTREE_HPP */
