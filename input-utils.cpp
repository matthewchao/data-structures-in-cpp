#include <vector>
#include <iostream>
#include <deque>


template <typename T> 
std::vector<T> parseToVector(std::string input_string)
{
    std::istringstream string_as_stream;
    std::vector<T> v;
    string_as_stream.str(input_string);

    std::copy(std::istream_iterator<T>(string_as_stream),
        std::istream_iterator<T>(),
        std::back_inserter(v));

    return v;        
}

template <typename T> 
std::deque<T> parseToDeque(std::string input_string)
{
    std::istringstream string_as_stream;
    std::deque<T> v;
    string_as_stream.str(input_string);

    std::copy(std::istream_iterator<T>(string_as_stream),
        std::istream_iterator<T>(),
        std::back_inserter(v));

    return v;        
}


template <typename T> 
std::vector<T> readVector() 
{

    std::string temp_line;
    std::vector<T> v;
    std::istringstream line_as_stream;
    std::getline(std::cin, temp_line);
    line_as_stream.str(temp_line);
    
    std::copy(std::istream_iterator<T>(line_as_stream),
        std::istream_iterator<T>(),
        std::back_inserter(v));

    return v;    
}

template <typename T>
std::vector<std::vector<T>> readGroupedVectors(char delim)
{

    std::string whole_line;
    std::getline(std::cin, whole_line);
    std::istringstream line_as_stream;
    line_as_stream.str(whole_line);
    std::string group;
    std::vector<T> v;
    std::vector<std::vector<T>> vect_of_vects;
    
    while (std::getline(line_as_stream,group,delim))
    {
        v = parseToVector<int>(group);  
        vect_of_vects.push_back(v);
    }      
    return vect_of_vects;

}

template <typename T>
std::vector<std::deque<T>> readGroupedDeques(char delim)
{

    std::string whole_line;
    std::getline(std::cin, whole_line);
    std::istringstream line_as_stream;
    line_as_stream.str(whole_line);
    std::string group;
    std::deque<T> v;
    std::vector<std::deque<T>> vect_of_vects;
    
    while (std::getline(line_as_stream,group,delim))
    {
        v = parseToDeque<int>(group);  
        vect_of_vects.push_back(v);
    }      
    return vect_of_vects;

}


template <typename T> 
void printVector(T &v) 
{ 
    for (const auto& x : v) {
        std::cout << x << " ";  
    }
    std::cout << "\n";
} 