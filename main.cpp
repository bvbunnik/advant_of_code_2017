#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <istream>
#include <iterator>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_map>
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

int day6_1() {
    //{10,3,15,10,5,15,5,15,9,2,5,8,5,2,3,6}
    std::vector<int> data = {10,3,15,10,5,15,5,15,9,2,5,8,5,2,3,6};//{0,2,7,0};
    bool cont = true;
    int steps = 0;
    std::map<std::string, int> states;
    while (cont){
        auto bank = std::max_element(begin(data), end(data));
        int blocks = *bank;
        *bank = 0;
        for (int i=0; i<blocks; ++i){
            int start_bank = bank - begin(data)+1;
            ++data.at((i+start_bank) % data.size());
        }
        std::cout<<data << "\n";
        std::string state;
        for (int i=0; i<data.size(); ++i){
            state += std::to_string(data.at(i));
        }
        if (states.find(state)==states.end()){
            states[state] = 1;
            ++steps;
        } else {
            ++steps;
            cont = false;
        }
    }
    return steps;
}

int day6_2() {
    //{10,3,15,10,5,15,5,15,9,2,5,8,5,2,3,6}
    std::vector<int> data = {10,3,15,10,5,15,5,15,9,2,5,8,5,2,3,6};//{0,2,7,0};
    bool cont = true;
    int steps = 0;
    int loop_size = 0;
    std::map<std::string, int> states;
    while (cont){
        auto bank = std::max_element(begin(data), end(data));
        int blocks = *bank;
        *bank = 0;
        for (int i=0; i<blocks; ++i){
            int start_bank = bank - begin(data)+1;
            ++data.at((i+start_bank) % data.size());
        }

        std::string state;
        for (int i=0; i<data.size(); ++i){
            state += std::to_string(data.at(i));
        }
        if (states.find(state)==states.end()){
            states[state] = steps;
            ++steps;
        } else {
            loop_size = steps - states.find(state)->second;
            cont = false;
        }
    }
    return loop_size;
}

void create_tree(std::vector<std::vector<int> > &data){

}

int calculate_cumulative_weights(const std::string& root, std::unordered_map<std::string, int>  &cumulative_weights,std::unordered_map<std::string, std::vector<std::string>> &edges,std::unordered_map<std::string, int> &vertices)
{
    ;
    if (cumulative_weights[root] == 0)
    {
        cumulative_weights[root] = vertices[root] + std::accumulate(edges[root].begin(), edges[root].end(), 0,
                                        [&](int w, auto s){ return w + calculate_cumulative_weights(s,cumulative_weights,edges,vertices); });
    }
    return cumulative_weights[root];
}

int search(const std::string& root, std::unordered_map<std::string, bool> &searched, std::unordered_map<std::string, std::vector<std::string>> &edges,std::unordered_map<std::string, int> &cumulative_weights,std::unordered_map<std::string, int> &vertices)
{
    if (!searched[root])
    {
        searched[root] = true;
        std::unordered_map<int, int> weight_frequency;
        for (auto& c : edges[root])
            weight_frequency[cumulative_weights[c]]++;
        if (weight_frequency.size() > 1)
        {
            auto a = weight_frequency.begin(), b = std::next(weight_frequency.begin());
            if (b->second > a->second)
                std::swap(a, b);
            auto program = *std::find_if(edges[root].begin(), edges[root].end(),
                                        [&](const std::string& s){return cumulative_weights[s] == b->first;});
            int ret = search(program,searched, edges, cumulative_weights,vertices);
            return ret ? ret : vertices[program] + a->first - b->first;
        }
    }
    return 0;
}

int day7_2(){

    std::unordered_map<std::string, int>  vertices;
    std::unordered_map<std::string, std::vector<std::string>> edges;
    std::unordered_map<std::string, bool> searched;
    std::unordered_map<std::string, int>  cumulative_weights;
    std::vector<std::vector<int> > data;

    std::ifstream inFile("data_day7.txt");
    for (std::string line; std::getline(inFile, line); )
    {
        std::string program_name = line.substr(0, line.find(' '));
        vertices[program_name] = std::stoi(std::string{line.begin() + line.find('(') + 1, line.begin() + line.find(')')});
        searched[program_name] = false;
        auto idx = line.find("->");
        if ( idx != std::string::npos)
        {
            std::string children_str = line.substr(idx + 2);
            children_str.erase(std::remove(children_str.begin(), children_str.end(), ','), children_str.end());
            std::stringstream ss (children_str);
            edges.emplace(program_name, std::vector<std::string>{std::istream_iterator<std::string>{ss}, {}});
        }
    }

    for (auto& p : vertices)
    {
        calculate_cumulative_weights(p.first, cumulative_weights, edges, vertices);
        int r = search(p.first, searched, edges, cumulative_weights, vertices);
        if (r){
            return r;
        }
    }
    return 0;
}

bool compare(int amount1, std::string comparison, int amount2){
    if (comparison.compare("<")==0){
        return (amount1 < amount2);
    }
    if (comparison.compare(">")==0){
        return (amount1 > amount2);
    }
    if (comparison.compare("<=")==0){
        return (amount1 <= amount2);
    }
    if (comparison.compare(">=")==0){
        return (amount1 >= amount2);
    }
    if (comparison.compare("==")==0){
        return (amount1 == amount2);
    }
    if (comparison.compare("!=")==0){
        return (amount1 != amount2);
    }
    return -1;
}

template<typename KeyType, typename ValueType>
std::pair<KeyType,ValueType> get_max( const std::map<KeyType,ValueType>& x ) {
  using pairtype=std::pair<KeyType,ValueType>;
  return *std::max_element(x.begin(), x.end(), [] (const pairtype & p1, const pairtype & p2) {
        return p1.second < p2.second;
  });
}

int day8_1()
{
    std::ifstream inFile("data_day8.txt");
    Csv csv(inFile, " ");
    std::vector<std::vector<std::string> > data;
    csv.getall(data);
    //data consists of [0] reg1, [1] command, [2] amount, [3] "if", [4] reg2, [5] comparison, [6] amount
    std::map<std::string, int> registers;
    for (auto i=begin(data); i!=end(data); ++i){
        auto reg2 = registers.find(i->at(4));
        if (reg2 != end(registers)){
            if (compare(reg2->second, i->at(5), std::stoi(i->at(6)))){
                if (i->at(1).compare("inc")==0){
                    registers[i->at(0)] += std::stoi(i->at(2));
                } else {
                      registers[i->at(0)] -= std::stoi(i->at(2));
                }
            }
        } else {
            if (compare(0, i->at(5), std::stoi(i->at(6)))){
                if (i->at(1).compare("inc")==0){
                    registers[i->at(0)] += std::stoi(i->at(2));
                } else {
                    registers[i->at(0)] -= std::stoi(i->at(2));
                }
            }
        }
    }
    auto max = get_max(registers);
    return max.second;
}

int day8_2()
{
    std::ifstream inFile("data_day8.txt");
    Csv csv(inFile, " ");
    std::vector<std::vector<std::string> > data;
    csv.getall(data);
    int max = 0;
    //data consists of [0] reg1, [1] command, [2] amount, [3] "if", [4] reg2, [5] comparison, [6] amount
    std::map<std::string, int> registers;
    for (auto i=begin(data); i!=end(data); ++i){
        auto reg2 = registers.find(i->at(4));
        if (reg2 != end(registers)){
            if (compare(reg2->second, i->at(5), std::stoi(i->at(6)))){
                if (i->at(1).compare("inc")==0){
                    registers[i->at(0)] += std::stoi(i->at(2));

                } else {
                    registers[i->at(0)] -= std::stoi(i->at(2));
                }
            }
        } else {
            if (compare(0, i->at(5), std::stoi(i->at(6)))){
                if (i->at(1).compare("inc")==0){
                    registers[i->at(0)] += std::stoi(i->at(2));
                } else {
                    registers[i->at(0)] -= std::stoi(i->at(2));
                }
            }
        }
        if(registers[i->at(0)]>max){
            max = registers[i->at(0)];
        }
    }
    return max;
}

int day9_1(){
    int score = 0;
    int level = 0;
    int charCounter = 0;
    bool ignore = false;
    bool insideGarbage = false;
    std::ifstream inFile("data_day9.txt");
    char currentChar = inFile.get();
    while (inFile.good()){
        if (!ignore){
            if (currentChar == '!'){
                ignore = true;
            } else {
                if (insideGarbage){
                    if (currentChar == '>'){
                        insideGarbage = false;
                    } else {
                        charCounter++;
                    }
                } else {
                    switch (currentChar){
                        case '<':
                            insideGarbage = true;
                            break;
                        case '{':
                            level++;
                            break;
                        case '}':
                            score += level;
                            level--;
                            break;
                    }
                }
            }
        } else {
            ignore = false;
        }
        currentChar = inFile.get();
    }
    //return score; (day9_1)
    return charCounter; //(day9_2)
}

int day10_1()
{

}


#ifndef TESTING
int main(int argc, char *argv[])
{
    std::cout << day10_1() << "\n";
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
