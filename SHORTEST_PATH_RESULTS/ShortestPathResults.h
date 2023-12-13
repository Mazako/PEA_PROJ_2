#ifndef PEA_PROJ_1_SHORTESTPATHRESULTS_H
#define PEA_PROJ_1_SHORTESTPATHRESULTS_H
#include <string>

class ShortestPathResults {
    bool noTimeCause;
    unsigned long long int cost;
    int* path;
    int n;
    long long secondsTime;

public:
    ShortestPathResults(unsigned long long int cost, int n, int* path, long long secondsTime, bool noTimeCause);

    ~ShortestPathResults();

    std::string toString();

    bool isNoTimeCause() const;

    unsigned long long int getCost() const;

    int* getPath() const;

    int getN() const;

    long long int getSecondsTime() const;
};


#endif //PEA_PROJ_1_SHORTESTPATHRESULTS_H
