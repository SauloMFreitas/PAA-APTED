#pragma once

#include <algorithm>
#include <iostream>

#include "Parser.hpp"
#include "StringNodeData.hpp"

using namespace std;
    
template<typename T>
inline string arratToString(vector<T>& array){
    stringstream ss;

    ss << "[";

    for (size_t i = 0; i < array.size(); i++)
    {
        if(i > 0){
            ss << ", ";
        }

        ss << array[i];
    }

    ss << "]";

    return ss.str();
    
}

template<>
inline string arratToString(vector<bool>& array){
    stringstream ss;

    ss << "[";

    for (size_t i = 0; i < array.size(); i++)
    {
        if(i > 0){
            ss << ", ";
        }

        if (array[i])
            ss << "true";
        
        else 
            ss << "false";
        
    }

    ss << "]";

    return ss.str();
}

template<typename T>
inline string arrayToString(vector<typename std::vector<T>>& nestedArray){

    stringstream ss;

    ss << "[";

    for (size_t i = 0; i < nestedArray.size(); i++)
    {
        if(i > 0){
            ss << ", ";
        }

        ss << arratToString(nestedArray[i]);
    }

    ss << "]";

    return ss.str();

} 

template<>
inline string arratToString(vector<Node<StringNodeData>*>& array){

    stringstream ss;

    ss << "[";

    for (size_t i = 0; i < array.size(); i++)
    {
        if(i > 0){
            ss << ", ";
        }

        ss << *array[i];
    }

    ss << "]";

    return ss.str();

}


template<typename T1, typename T2>
inline string arratToString(vector<pair<T1, T2>>& map){

    stringstream ss;

    ss << "[";

    for (size_t i = 0; i < map.size(); i++)
    {
        if(i > 0){
            ss << ", ";
        }

        ss << map[i].first << ":" << map[i].second;
    }

    ss << "]";

    
    return ss.str();

}