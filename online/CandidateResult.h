#ifndef __CANDIDATERESULT_H__
#define __CANDIDATERESULT_H__

#include <string>
using std::string;

class CandidateResult
{
public:
    CandidateResult();
    ~CandidateResult();
public:
    string _word;
    int _freq;
    int _dist;
};

#endif


