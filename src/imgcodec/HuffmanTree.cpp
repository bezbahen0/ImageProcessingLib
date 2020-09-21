#include "include/imgcodec/HuffmanTree.hpp"

namespace imp
{

HuffmanTree::HuffmanTree()
{
}

HuffmanTree::HuffmanTree(const HuffmanTableType& table)
{
    root_ = std::make_shared<Node>();
    createChilds(root_);

    NodePtr leftn = root_ -> left;

    for(int i = 0; i < 16; ++i)
    {
        if(table[i].first == 0)
        {
            for(NodePtr ptr = leftn; ptr != nullptr; ptr = getRightLevelNode(ptr))
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

            NodePtr ptr = getRightLevelNode(leftn);
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

NodePtr HuffmanTree::getRoot()
{
    return root_;
}

std::string HuffmanTree::contains(std::string& huffmanCode)
{
    int i = 0;
    NodePtr nptr = root_;
    do
    {
        if(huffmanCode[i] == '0')
            nptr = nptr->left;
        else
            nptr = nptr->right;
        
        if(nptr != nullptr && nptr->isLeaf() && nptr->code == huffmanCode)
        {
            if(nptr->value == 0x0000)
                return "EOB";
            return std::to_string( nptr->value );
        }
        i++;
        
    } while(nptr != nullptr && i < huffmanCode.size());
    
    return "";
}

bool HuffmanTree::empty()
{
    return root_ == nullptr;
}

void HuffmanTree::clear()
{

}

NodePtr HuffmanTree::getRightLevelNode(NodePtr node)
{
    if(node == nullptr)
        return nullptr;

    if(node -> parent != nullptr && node -> parent -> left == node)
        return node -> parent -> right;

    int count = 0;
    NodePtr tempn = node;
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
        tempn = tempn -> left;
        count--;
    }

    return tempn;

}

void HuffmanTree::createChilds(NodePtr node)
{
    if(node -> left != nullptr || node -> right != nullptr || node == nullptr)
        return;

    NodePtr left = std::make_shared<Node>();
    node -> left = left;
    left -> parent = node;
    left -> code = node -> code + "0";

    NodePtr right = std::make_shared<Node>();
    node -> right = right;
    right -> parent = node;
    right -> code = node -> code + "1";
}

}
