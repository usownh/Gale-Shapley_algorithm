#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

vector<string> gen_boys(int number)
{
    vector<string> result;
    for(int i = 0; i < number; i++){
        string boy = "B";
        string s;
        stringstream ss;
        ss << i;
        ss >> s;
        boy.append(s);
        result.push_back(boy);
    }
    return result;
}

vector<string> gen_girls(int number)
{
    vector<string> result;
    for(int i = 0; i < number; i++){
        string boy = "G";
        string s;
        stringstream ss;
        ss << i;
        ss >> s;
        boy.append(s);
        result.push_back(boy);
    }
    return result;
}

vector<string> gen_ranking(vector<string> candidate)
{
    random_shuffle(candidate.begin(), candidate.end());
    return candidate;
}

void write_rankings(vector<string> people, vector<vector<string> > rankings, string out_file)
{
    ofstream ofs(out_file.c_str());
    if(ofs.fail()){
        cerr << "Error: " << out_file << endl;
        return;
    }
    for(int i = 0; i < people.size(); i++){
        ofs << people[i] << ":";
        for(int j = 0; j < rankings[i].size(); j++){
            ofs << " " << rankings.at(i).at(j);
        }
        ofs << endl;
    }
    ofs.close();
}

int main(int argc, char ** argv)
{
    srand(time(NULL));
    int n = 200;
    vector<string> boys = gen_boys(n);
    vector<string> girls = gen_girls(n);
    vector<vector<string> > boys_rankings;
    vector<vector<string> > girls_rankings;
    for(int i = 0; i < n; i++){
        boys_rankings.push_back(gen_ranking(girls));
        girls_rankings.push_back(gen_ranking(boys));
    }
    write_rankings(boys, boys_rankings, "boys_rankings.txt");
    write_rankings(girls, girls_rankings, "girls_rankings.txt");
    return 1;
}





