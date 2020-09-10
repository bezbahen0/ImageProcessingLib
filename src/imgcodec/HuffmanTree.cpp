#include "include/imgcodec/HuffmanTree.hpp"

namespace imp
{

HuffmanTree::HuffmanTree()
{
}

HuffmanTree::HuffmanTree(const HuffmanTableType& table)
{
    root_ = new Node(0x0000, "");
    Node* leftn = root_ -> left;

    for(int i = 0; i < table.size(); ++i)
    {
        if(table[i].first == 0)
        {
            for(Node* ptr = leftn; ptr != nullptr; ptr = getRightLevelNode(leftn))
            {
                createChilds(ptr);
            }
            leftn = leftn -> left;
        }
        else
        {
            for(auto&& codeValue : table[i].second)
            {
                leftn -> value = codeValue; 
                leftn = getRightLevelNode(leftn);
            }

            createChilds(leftn);

            Node* ptr = getRightLevelNode(leftn);
            leftn = leftn -> left;

            while(ptr != nullptr)
            {
                createChilds(ptr);
                ptr = getRightLevelNode(ptr);
            }
        }
    }
}

HuffmanTree::~HuffmanTree()
{
    clear();
}

Node* HuffmanTree::getRoot()
{
    return root_;
}

void insert(Node* node, const uint16_t value)
{

}

bool HuffmanTree::empty()
{
    return root_ == nullptr;
}

void HuffmanTree::clear()
{

}

Node* HuffmanTree::getRightLevelNode(Node* node)
{
    if(node == nullptr)
        return nullptr;

    if(node -> parent != nullptr && node -> parent -> left == node)
        return node -> parent -> right;

    int count = 0;
    Node* tempn = node;
    while(tempn -> parent != nullptr && tempn -> parent -> right == tempn)
    {
        tempn = tempn -> parent;
        count++;
    }

    if(tempn -> isRoot())
        return nullptr;
    
    tempn = tempn -> parent -> right;

    while(count > 0)
    {
        tempn = tempn -> right;
        count--;
    }

    return tempn;

}

void HuffmanTree::createChilds(Node* node)
{
    if(node -> left != nullptr || node -> right != nullptr || node == nullptr)
        return;

    Node* left = new Node();
    node -> left = left;
    left -> parent = node;
    left -> code = node -> code + "0";

    Node* right = new Node();
    node -> right = right;
    right -> parent = node;
    right -> code = node -> code + "1";
}

}
