#include "stdafx.h"
#include "Pie.h"

template <class T>
void FreeMem (T* pt)
{
    if (pt)
    {
        delete pt;
        pt = nullptr;
    }
};

class Recursive
{
public:
    Recursive(const string &str) :_str(str)
    {
    }

    void Permutation()
    {
        int length = _str.length();

        char *pOut = new char[length+1];
        pOut[length] = '\0';

        bool *pUsed = new bool[length];
        memset(pUsed, false, sizeof(bool)*length);

        _DoPermutation(_str.c_str(), pOut, pUsed, length, 0);

        FreeMem(pOut);
        FreeMem(pUsed);
    }

    void Combination()
    {

    
    }

private:

    void _DoPermutation(const char in[], char out[], bool used[], int length, int currPos)
    {
        if (currPos == length)
        {
            printf("%s\n", out);
            return;
        }

        for (int i = 0; i < length; i++)
        {
            if (used[i]) continue;
            used[i] = true;
            out[currPos] = in[i];
            _DoPermutation(in, out, used, length, currPos+1);
            used[i] = false;
        }
    }

    void _DoCombination(const char in[], char out[], int length, int startPos, int currPos)
    {
        for (int i = startPos; i < length; i++)
        {
            out[currPos] = in[i];
            out[currPos+1] = '\0';
            printf("%s\n", out);

            if (startPos < (length -1))
                _DoCombination(in, out, length, startPos+1, currPos+1);
        }
    }

    string _str;
};

void TestRecursive::TestPermutation()
{
    Recursive r("abcd");
    r.Permutation();
}