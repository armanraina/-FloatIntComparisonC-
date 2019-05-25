/**
    Purpose: Compare speed of sorting of floats and ints in C++

    @author Arman Raina
*/
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
#include <math.h>
#include <numeric>      // std::accumulate

using namespace std;
#define ITERATIONS 10
#define SIZE 1000

int main()
{    
    vector<float> floats(ITERATIONS);
    vector<float> ints(ITERATIONS);
    for (int i = 0; i < ITERATIONS; i++){
        // First create an instance of an engine.
        random_device rnd_device;
        // Specify the engine and distribution.
        mt19937 mersenne_engine(rnd_device());
        uniform_real_distribution<float> distf(std::numeric_limits<int>::min(),
            std::numeric_limits<float>::max());
    
        auto genf = std::bind(distf, mersenne_engine);
        vector<float> vecf(SIZE);
        generate(begin(vecf), end(vecf), genf);
         
        clock_t tf;
        tf = clock();
        sort(vecf.begin(),vecf.end());
        tf = clock() - tf;
        floats[i] =((float)tf)/CLOCKS_PER_SEC;
        
        uniform_int_distribution<int> disti(std::numeric_limits<int>::min(),
            std::numeric_limits<int>::max());
    
        auto geni = std::bind(disti, mersenne_engine);
        vector<int> veci(SIZE);
        generate(begin(veci), end(veci), geni);
         
        clock_t ti;
        ti = clock();
        sort(veci.begin(),veci.end());
        ti = clock() - ti;
        ints[i] = ((float)ti)/CLOCKS_PER_SEC;
    }
    float meanf = accumulate(floats.begin(),floats.end(),0.0)/floats.size();
    float meani =  accumulate(ints.begin(),ints.end(),0.0)/ints.size();
    cout << "floats took " << meanf << " seconds"  << endl;
    cout << "ints took " << meani << " seconds"   << endl;
    
    float varf = 0.0;
    float vari = 0.0;
    for (int i = 0; i<ITERATIONS;i++){
        varf+=pow(floats[i]-meanf,2);
        vari+=pow(ints[i]-meani,2);
    }
    varf = sqrt(varf/ITERATIONS);
    vari = sqrt(vari/ITERATIONS);
    cout << "floats had var " << varf << " seconds"  << endl;
    cout << "ints had var " << vari << " seconds"   << endl;
}



