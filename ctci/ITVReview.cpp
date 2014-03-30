
#include "stdafx.h"


#include "ITVReview.h"

using namespace std;

struct CharFrequency{
    char _ch;
    int _frequency;

    CharFrequency(char ch, int frequency): _ch(ch), _frequency(frequency)
    {}

    void Print()
    {
        cout << _ch << ": " << _frequency <<endl;
    }
};

class MyString{
public:
    MyString(string const&str):_str(str)
    {
    }

    void Compress(vector<CharFrequency> &ret)
    {
        int len = _str.length();
        int countMap[256] = {0};
        for (int i = 0; i < len; i++)
        {
            countMap[_str[i]]++;
        }

        for (int i = 0; i < len; i++)
        {
            if (countMap[_str[i]] != 0)
            {
                CharFrequency cf(_str[i], countMap[_str[i]]);
                ret.push_back(cf);
                countMap[_str[i]] = 0;
            }
        }    
    }

private:
    string _str;
};

void TestMyString::Test()
{
    string st("This is a test string that I do not want to use");
    MyString teststr(st);

    vector<CharFrequency> ret;
    teststr.Compress(ret);
    for (vector<CharFrequency>::iterator it = ret.begin(); it!=ret.end(); it++)
    {
        (*it).Print();
    }
}

#include <windows.h>

class Image{

public:

    Image(const byte *buf, int n, int m)
    {
        if ((!buf) || (n <=0) || (m<=0))
            return;

        _buf = new byte[n*m];
        _n = n;
        _m = m;
        memcpy(_buf, buf, n*m);
    }

    ~Image()
    {
        if (_buf)
            delete []_buf;
    }

    bool IsValid(int i, int j)
    {
        return ((i>=0) && (i <_n) && (j >=0) && (j < _m));
    }

    byte Average(int i, int j)
    {
        int count = 0;
        int sum = 0;
        for (int k = i-1; k <= i+1; k++)
            for (int p = j-1; p <= j+1; p++)
            {
                if (IsValid(k,p))
                {
                    sum+=_buf[k*_m + p];   // pay attention to the index scheme here
                    count++;
                }
            }
        return sum/count;
    }

    byte *Smooth()
    {
        int size = _n * _m;
        byte *ret = new byte[size];
        if (ret)
        {
            memset(ret, 0, size);
            for (int i = 0; i < _n; i++)
                for (int j = 0; j < _m; j++)
                {
                    ret[i*_m +j] = Average(i, j);
                }
        }
        return ret;
    }

    void swap( byte*& pa, byte*& pb)
    {
        byte *pt = pa;
        pa = pb;
        pb =pt;

    }

    byte Average2(byte *prev, byte *curr, byte *next, int i, int j)
    {
        int count = 0;
        int sum = 0;
        for (int k = i-1; k <= i+1; k++)
            for (int p = j-1; p <= j+1; p++)
            {
                if (IsValid(k,p))
                {
                    byte *buf = nullptr;
                    if (k == (i-1))
                        buf = prev;
                    else if (k== i)
                        buf = curr;
                    else if (k==(i+1))
                        buf = next;
                    else
                        assert(false);

                    assert(buf!=nullptr);
                    sum+=buf[p];   // pay attention to the index scheme here
                    count++;
                }
            }

        return sum/count;
    }

    void Smooth2()
    {
        if (_n < 2) return;

        byte *temp = new byte[_m*2];
        memcpy(temp, &_buf, _m*2);

        byte *prev = temp;
        byte *curr = temp+_m;
        byte *next = nullptr;

        for (int i = 0; i < _n; i++)
        {
            memcpy(curr, &_buf[i*_m], _m);

            next = ((i+1) <_n) ? &_buf[(i+1)*_m] : nullptr;

            for (int j = 0; j < _m; j++)
            {
                _buf[i*_m+j] = Average2(prev, curr, next, i, j);
                
            }

            swap(prev, curr);
                        
        }    
    }

    void Print()
    {
        for (int i = 0; i < _n; i++)
        {   
            for (int j = 0; j < _m; j++)
            {
                printf("%d ", _buf[i*_m+j]);
            }
            printf("\n");
        }
    }

private:

    int _n;
    int _m;
    byte *_buf;
};

void TestImage::Test()
{
    byte TestData[9] = {1, 2, 3,    4, 5, 5,    6, 7, 9};
    Image img(TestData, 3, 3);

    img.Print();
    
    printf("\n\n");
    Image smoothImage(img.Smooth(), 3, 3);
        
    smoothImage.Print();
    printf("\n\n");
    
    img.Smooth2();
    img.Print();
}

#include "Tree.h"

TreeNodewParent *InOrderNext(TreeNodewParent *r)
{
    if (r == nullptr) return nullptr;

    if (r->right) return r->right;

    TreeNodewParent *p = r->parent;
    TreeNodewParent *c = r;
    while ( p && (p->right == c))
    {
        c = p;
        p =  p->parent;
    }
    return p;
}

void TestTree::InOrderNextTest()
{
    // TODO common binary tree construction
    // e.g. BST from preorder
    // BT from preorder + inorder
    // BT from postorder + inorder

}

char GetMostUsedChar(char *pStr)
{
    if (!pStr) return '\0';

    // assume all ascii
    int countMap[256]={0};
    
    int len = strlen(pStr);
    for (int i = 0; i < len; i++)
    {
        countMap[pStr[i]]++;
    }

    CharFrequency maxfreq('\0', 0);
    for (int i = 0; i < 256; i++)
    {
        if (countMap[i]> maxfreq._frequency)
        {
            maxfreq._ch = i; 
            maxfreq._frequency = countMap[i];
        }
    }

    return maxfreq._ch;
}


vector<char> GetOddChars(char *pStr)
{
    vector<char> ret;

    int charMap[256]={0};

    for (size_t i = 0; i < strlen(pStr); i++)
    {
        charMap[pStr[i]] ^=1;
    }

    for (int i = 0; i < 256; i++)
    {
        if (charMap[i]!=0)
            ret.push_back(i);
    }
    return ret;
}
/*
void swap(char &a, char &b)
{
    char temp = a;
    a = b;
    b = temp;
}
*/
// "123" + "456" = "579"
// "89" + "132" = "221"
// "89" + "12" = "101"
string StringAdd(string &a, string &b)
{
    int la = a.length();
    int lb = b.length();

    int ia = la-1;
    int ib = lb -1;

    bool bCarry = 0;
    string ret;
    ret.resize(max(la, lb)+1);

    int idx = 0;
    while ((ia >=0) && (ib>=0))
    {
        int sumDigit = a[ia]-'0' + b[ib]- '0' + bCarry ? 1: 0;
        bCarry = (sumDigit > 10) ? true : false;
        ret[idx++] = sumDigit%10;
        ia--;
        ib--;
    }

    while (ia >=0)
    {
        int sumDigit = a[ia] - '0' +  bCarry ? 1: 0;
        bCarry = (sumDigit > 10) ? true : false;
        ret[idx++] = sumDigit%10;
        ia--;        
    }

    while (ib >=0)
    {
        int sumDigit = a[ib] - '0' +  bCarry ? 1: 0;
        bCarry = (sumDigit > 10) ? true : false;
        ret[idx++] = sumDigit%10;
        ib--;        
    }

    for (int i = 0, j = idx -1; i < j; i++, j--)
    {
        swap(ret[i], ret[j]);
    }

    return ret;
   
}