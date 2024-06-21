#pragma once

#include <sstream>
#include <cassert>
#include <iostream>

#include "Parser.hpp"
#include "CostModel.hpp"

using namespace std;



class StringNodeData
{
private:
    
    string label;

public:

    friend ostream &operator<<(ostream &os, StringNodeData const &stringNode);

    StringNodeData(string label):label(label){}

    inline string getLabel() const {

        return label;

    }

};



inline ostream &operator<<(ostream &os, Node<StringNodeData> const &node){
    os << "{";
    os << *node.getData();
    for(Node<StringNodeData>* child : node.getChildren()){
        os << *child;
    }
    os << "}";

    return os;
}

inline ostream &operator<<(ostream &os, StringNodeData const &stringNode) {
    os << stringNode.getLabel();
    return os;
}

class stringCostModel : public CostModel<StringNodeData>{
    public:
        inline virtual float del(Node<StringNodeData>* n)const override{
            return 1.0f;
        }

        inline virtual float ins(Node<StringNodeData>* n) const override{
            return 1.0f;
        }

        inline virtual float ren(Node<StringNodeData>* n1, Node<StringNodeData>* n2)const override{
            return(n1->getData()->getLabel() == n2->getData()->getLabel()) ? 0.0f : 1.0f;                
        }
};

// --- SND Parser

class BracketStringParser : public Parser<StringNodeData>{
    private:
        const string inputString;

        inline static string getRootLabel(string s){
            size_t start = 1;
            size_t end   = s.find_first_of('{',1);
            if (end == string::npos)
            {
                end = s.find_first_of('}',1);
                assert(end != string::npos);
            }

            return s.substr(start, (end-2+1));
            
        }

        inline static vector<string> getChildrenString(string s){
            vector<string> children;
            
            size_t childrenStart = s.find_first_of('{',1);
            
            if (childrenStart == string::npos)
            {
                return children;
            }

            int depth = 0;

            stringstream currentChild;
            for (size_t i = childrenStart; i < s.size(); i++)
            {
                switch (s[i]){
                case '{':
                    depth++;
                    break;
                case '}':
                    depth--;
                    break;
                }

                if (depth == -1)
                {
                    break;
                }

                currentChild << s[i];
                if(depth == 0){
                    children.push_back(currentChild.str());
                    currentChild.str(string());
                }
                
            }

            return children;
            
            
        }

    public:

        BracketStringParser(string IS) : inputString(IS){}

        inline virtual Node<StringNodeData>* getRoot() override{
            
            string rootLabel = getRootLabel(inputString);
            vector<string> childrenString = getChildrenString(inputString);

            Node<StringNodeData>* node = new Node<StringNodeData>(new StringNodeData(rootLabel));
            for(string cs : childrenString){
                BracketStringParser Parser(cs);
                node->addChild(Parser.getRoot());
            }
            return node;
        }
};