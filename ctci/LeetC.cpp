#include "stdafx.h"
#include "LeetC.h"

class TwoSum {
public:    
    static vector<int> GetTwoSum(vector<int> &numbers, int target) {
        int i = 0;
        int j = numbers.size()-1;
        vector<int> ret;
        
        while (i < j)
        {
            if ((numbers[i]+numbers[j])== target)
            {
                ret.push_back(i);
                ret.push_back(j);
                i++;
                j--;
            }else if ((numbers[i]+numbers[j]) < target)
            {
                i++;
            }else
            {
                j--;
            }
        }
        return ret;
    }
};

void TestTwoSum::Test()
{
    int iTestdata[4] = {0, 4, 3, 0}; 
    vector<int> testdata;
    for (int i = 0; i < sizeof(iTestdata)/sizeof(int); i++)
        testdata.push_back(iTestdata[i]);

    vector<int> ret = TwoSum::GetTwoSum(testdata, 0);

    for (vector<int>::iterator it = testdata.begin(); it != testdata.end(); it++)
    {
        cout << *it << " " <<endl;
    }

}

