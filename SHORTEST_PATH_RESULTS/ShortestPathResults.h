#ifndef PEA_PROJ_1_SHORTESTPATHRESULTS_H
#define PEA_PROJ_1_SHORTESTPATHRESULTS_H
#include <string>

class ShortestPathResults {
    bool noTimeCause;
    unsigned long long int cost;
    int* path;
    int n;
    long long nanoTime;

public:
    ShortestPathResults(unsigned long long int cost, int n, int* path, long long nanoTime, bool noTimeCause);

    ~ShortestPathResults();

    std::string toString();

    bool isNoTimeCause() const;

    unsigned long long int getCost() const;

    int* getPath() const;

    int getN() const;

    long long int getNanoTime() const;
};


#endif //PEA_PROJ_1_SHORTESTPATHRESULTS_H
