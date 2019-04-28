#include <vector>
#include <iostream>
#include <deque>
#include <sstream>
#include <iterator>
#include <algorithm> //std::replace


// returns a vector given a string of space separated elements
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


// reads a space separated vector of type T from input
template <typename T> 
std::vector<T> readVector() 
{

    std::string temp_line;
    std::getline(std::cin, temp_line);

    return parseToVector<T>(temp_line);
}

// overloads readVector(); reads a delim-separated vector of type T from input
template <typename T> 
std::vector<T> readVector(char delim) 
{

    std::string temp_line;
    std::getline(std::cin, temp_line);

    std::replace(temp_line.begin(),temp_line.end(),delim,' ');
    return parseToVector<int>(temp_line);
}


/* reads a vector of vectors from input,
 where each vector is separated by delim
 and within a vector, elements are separated by space */
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
std::vector< std::vector<T> >  readMatrix(int m, int n) {
    // given dimensions, matrix elements row by row

    std::cout<<"enter the rows of the matrix one-by-one: \n";

    std::string temp_line;

    std::vector< std::vector<T> > matrix;
    matrix.reserve(m);

    std::istringstream line_as_stream;

    for (int i=0; i<m; i++) {
        matrix.push_back(readVector<T>());
    }

    return matrix;    

}


// prints a vector of any type which can go into std::cout
template <typename T> 
void printVector(T &v) 
{ 
    for (const auto& x : v) {
        std::cout << x << " ";  
    }
    std::cout << "\n";
} 


template <typename T> 
void printMatrix(T &M) 
{ 
    for (const auto& row : M) {
        printVector(row);  
    }
    std::cout << "\n";
} 
