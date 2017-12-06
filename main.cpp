#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include "Csv.h"

//#define TESTING
#ifdef TESTING
  #define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
  #include "catch.h"
#endif


//Write a vector<vector<class T> > to an output stream. Output is formatted as a matrix.
template < class T >
std::ostream& operator << (std::ostream& os, const std::vector<std::vector<T> >& v)
{
    for (typename std::vector<std::vector<T> >::const_iterator i = v.begin(); i != v.end(); ++i){
   // os << "[";
        for (typename std::vector<T>::const_iterator ii = i->begin(); ii != i->end(); ++ii)
        {
            if (ii!=i->begin()){
                os << ",";
            }
            os << *ii;
        }
        os << "\n";
    }
    return os;
}


template < class T >
std::ostream& operator << (std::ostream& os, const std::vector<T>& v)
{
    for (typename std::vector<T>::const_iterator i = v.begin(); i != v.end(); ++i)
    {
        if (i!=v.begin()){
            os << ",";
        }
        os << *i;
    }
    os << "\n";
    return os;
}


int day1_1(std::vector<int> &vec)
{
    int sum = 0;
    vec.push_back(vec.at(0));
    //int half = vec.size() / 2;

    for (auto it = begin(vec); it != end(vec); ++it){
        if (!(it+1==end(vec))){
            if (*it == *(it+1)){
                sum = sum + *it;
            }
        }
    }
    return sum;
}

int day1_2( std::vector<int> &vec){
                int sum = 0;
        int half = vec.size() / 2;
        for (auto it = begin(vec); it != begin(vec)+half; ++it){
            if (!(it+1==end(vec))){
                if (*it == *(it+half)){
                    sum = sum + *it;
                }
            }
        }
        return sum*2;
}

int day2_1(){
    std::vector<std::vector<int> > data;
    std::ifstream inFile("data.txt");
    Csv csv(inFile, "\t");
    csv.getall(data);
    int sum_diff = 0;
    for (auto it1 = begin(data); it1 != end(data); ++it1){
        int diff =  *std::max_element(it1->begin(), it1->end()) - *std::min_element(it1->begin(), it1->end());
        sum_diff += diff;
    }

    return sum_diff;
}

int day2_2(){
    std::vector<std::vector<int> > data;
    std::ifstream inFile("data.txt");
    Csv csv(inFile, "\t");
    csv.getall(data);
    int sum = 0;
    for (auto it1 = begin(data); it1 != end(data); ++it1){
       std::sort(it1->begin(), it1->end());
       std::reverse(it1->begin(), it1->end());

       auto it = it1->begin();
       while (it != it1->end()){
           for (auto it2 = it; it2 != it1->end(); ++it2){
               if (!(it2+1==it1->end())){

                   if(*it % *(it2+1)==0){
                      sum += *it / *(it2+1);
                   }
               }
           }
       ++it;
       }
    }

    return sum;
}

int side_length(int number){
    int side = std::ceil(std::sqrt(number));
    if (side % 2!=0) {
        ++side;
    }
    return side;
}

int day3_1(int number){
    //int number = 289326;
    int side = side_length(number);
    int steps = (side-1)/2;
    std::vector<int> axes;
    for (int i=0; i<4; ++i){
        axes.push_back(std::abs((side*side - ((side-1) * i)  - std::floor(side/2))-number));
    }
    return steps + *std::min_element(axes.begin(), axes.end());
}

int day4_1(){
    std::vector<std::vector<std::string> > data;
    std::ifstream inFile("data_day4.txt");
    Csv csv(inFile, " ");
    csv.getall(data);
    int sum = 0;
    for (auto it1 = begin(data); it1 != end(data); ++it1){
        bool good = true;
        auto it = it1->begin();
        while (it != it1->end()){
            for (auto it2 = it; it2 != it1->end(); ++it2){
                if (!(it2+1==it1->end())){
                    if (it->compare(*(it2+1))==0){
                        good = false;
                    }
                }
            }

        ++it;
        }
        if (good){
            ++sum;
        }
    }
    return sum;
}

bool is_anagram(std::string str1, std::string str2){
    if (str1.length() != str2.length()){
        return false;
    } else {
        std::sort(str1.begin(), str1.end());
        std::sort(str2.begin(), str2.end());
        return str1 == str2;
    }
}

int day4_2(){
    std::vector<std::vector<std::string> > data;
    std::ifstream inFile("data_day4.txt");
    Csv csv(inFile, " ");
    csv.getall(data);
    int sum = 0;
    for (auto it1 = begin(data); it1 != end(data); ++it1){
        bool good = true;
        auto it = it1->begin();
        while (it != it1->end()){
            for (auto it2 = it; it2 != it1->end(); ++it2){
                if (!(it2+1==it1->end())){
                    if (is_anagram(*it, *(it2+1))){
                        good = false;
                    }
                }
            }

        ++it;
        }
        if (good){
            ++sum;
        }
    }
    return sum;
}

int day5_1(){
    std::vector<int> data;
    std::ifstream inFile("data_day5.txt");
    Csv csv(inFile);
    csv.getall(data);
    //std::cout << data;
    int steps = 0;
    std::vector<int>::iterator it=data.begin();
    int jump = *it;
    //((it + jump) > data.begin()) ||
    while ((it+jump)<data.end()){
        auto it1 = it;
        it = it+jump;
        ++*it1;
        jump = *it;
        ++steps;
    }
    return steps+1;
}

int day5_2(){
    std::vector<int> data; //= {0,3,0,1,-3};
    std::ifstream inFile("data_day5.txt");
    Csv csv(inFile);
    csv.getall(data);
    //std::cout << data;
    int steps = 0;
    std::vector<int>::iterator it=data.begin();
    int jump = *it;
    //((it + jump) > data.begin()) ||
    while ((it+jump)<data.end()){
        auto it1 = it;
        it = it+jump;
        if (jump<3){
            ++*it1;
        } else {
            --*it1;
        }
        jump = *it;
        ++steps;
    }
    return steps+1;
}

#ifndef TESTING
int main(int argc, char *argv[])
{
    //std::cout << day3_1(1) << "\n";
    std::cout << day5_2() << "\n";
    //std::cout << day3_1(23) << "\n";
    //std::cout << day3_1(1024) << "\n";
    return 0;
}
#endif



#ifdef TESTING
TEST_CASE( "Factorials are computed", "[factorial]" ) {
    vector<int> vec = {1,2,1,2};
    REQUIRE( day1_2(vec) == 6 );
    vec = {1,2,2,1};
    REQUIRE( day1_2(vec) == 0 );
    vec = {1,2,3,4,2,5};
    REQUIRE( day1_2(vec) == 4 );
    vec = {1,2,3,1,2,3};
    REQUIRE( day1_2(vec) == 12 );
    vec = {1,2,1,3,1,4,1,5};
    REQUIRE( day1_2(vec) == 4 );
}
#endif
