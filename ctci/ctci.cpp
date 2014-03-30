// ctci.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


/// 1.1 check if all char in a string is unique
// ask range of char
// 8 bit -> 0~255
bool AllUniqueChar(char *str)
{
    const int intLen = sizeof(int)*8;
    const int bitMapLen = 256/ intLen;
    int bitMap[bitMapLen];
    memset(bitMap, 0, sizeof(bitMap));

    bool bAllUnique = true;    
    char *p = str;
    
    while ((*p ) != '\0')
    {
        int idx = (*p)/intLen;
        int offset = (*p)%intLen;
        if (bitMap[idx] & (1 << offset)) 
        {    
            bAllUnique = false;
            break;
        }else
        {
            bitMap[idx] |= (1 << offset);
            p++;
        }
    }
    
    return bAllUnique;
}

bool AllUnique2(char *str)
{
    int iMap = 0;
    while (*str!='\0')
    {
        int imask = 1 << ((*str)%32);
        if ( iMap & imask)
        {
            return false;
        }else
        {
            iMap |= imask;
            str++;
        }
    }
    return true;
}


void TestAllUniqueChar()
{
    char *strList[6] = {"abc",  "a", "", "aa", "abcdee", "abccde"};

    for (int i = 0; i < 6; i++)
    {
        printf("%s\t Allunique=%s\n", strList[i], AllUnique2(strList[i]) ? "true" : "false");
    }
}

// 1.2 reverse a c string
void swap(char &s, char &t)
{
    s = s^t;
    t = s^t;
    s = s^t;
}

void reverse(char *str)
{
    if (!str)
    {
        return;
    }

    char *p = str;
    while ((*p) != '\0')
    {
        p++;
    }
    p--;

    char *q = str;
    while (q < p)
    {
        swap(*q, *p);
        q++;
        p--;
    }    
}

void TestReverse()
{
    // pay attention to the test case where you can't declar string literals that is immuatable
    // e.g. char *strList[6] = {"abc",  "a", "", "aa", "abcdee", "abccde"}; will AV when swap
   char strList[6][10] = {"abc",  "a", "", "aa", "abcdee", "abccde"};

   printf("\nOriginal strings\n");
   for (int i = 0 ; i < 6; i++)
   {    
        printf("%s\n", strList[i]);
   }

   printf("\nReversed strings\n");
   for (int i = 0 ; i < 6; i++)
   {
        reverse(strList[i]);
        printf("%s\n", strList[i]);
   }
    
}

// 1.3 
/*
Design an algorithm and write code to remove the duplicate characters in a string without using any additional buffer. 
NOTE: One or two additional variables are fine. An extra copy of the array is not. FOLLOW UP Write the test cases for this method.
*/

// O(n^2)
void RemoveDup(char *str)
{
    int strLen = strlen(str);
    // iterate over the string for each char, set the dup in the remaining part of the array as 0
    for (int i = 0; i < strLen; i++)
    {        
        // !!! pay attention to the initial value of j, should be j+1 not j
        for(int j = i+1; j < strLen; j++)
        {
            if (str[j] == str[i])
            {
                str[j] = '\0';
            }
        }
    }

    int idx = 0;
    for (int i = 0;  i < strLen; i++)
    {
       if (str[i] != '\0')
       {
           str[idx++] = str[i];        
       }
    }

    str[idx] = '\0';
    
}

// use a bitMap of bool to redce the time complexity from O(n^2) to O(n)
// extra space 256 bytes, if choose to use true bitmap, can be further reduced to 256/32 = 8 bytes
void RemoveDup2(char *str)
{
    if (!str)
        return;

    int strLen = strlen(str);
    if (strLen < 2)
        return;

    bool bMap[256];
    memset(bMap, 0, sizeof(bMap));

    int idx = 0;
    for (int i = 0; i < strLen; i++)
    {
        if (!bMap[str[i]])
        {
            str[idx++] = str[i];
            bMap[str[i]] = true;
        }    
    }
    str[idx] = '\0';
}

// Remove Dup with bitmap
void RemoveDup3(char *str)
{
    if (!str)
        return;
    int strLen = strlen(str);
    if (strLen < 2)
        return;

    int bitMap[8];
    memset(bitMap, 0, sizeof(bitMap));

    int idx = 0;
    for (int i = 0; i < strLen; i++)
    {
        if (!(bitMap[str[i]/32] & (1 << (str[i]%32))))
        {
            str[idx++] = str[i];
            bitMap[str[i]/32] |= (1 << (str[i]%32));
        }
    }
    str[idx] = '\0';
}

void TestRemoveDup()
{
    // pay attention to the test case where you can't declar string literals that is immuatable
    // e.g. char *strList[6] = {"abc",  "a", "", "aa", "abcdee", "abccde"}; will AV when swap
   char strList[6][30] = {"abc",  "a", "", "aa", "aabcccdeefffggghhhi", "abcdefghiabcdef"};

   printf("\nOriginal strings\n");
   for (int i = 0 ; i < 6; i++)
   {    
        printf("%s\n", strList[i]);
   }

   printf("\nDup removed strings\n");
   for (int i = 0 ; i < 6; i++)
   {
       RemoveDup(strList[i]);
        printf("%s\n", strList[i]);
   }
}

// 1.4 Write a method to decide if two strings are anagrams or not.
bool IsAnagramWrong(char *str)
{
    if (!str)
        return false;

    char *p = str;
    while (*p != '\0')
    {
        p++;
    }
    p--;

    char *q = str;
    while (q < p)
    {
        if (*q == *p)
        {
            q++;
            p--;
        }else
        {
            return false;
        }
    }
    return true;
}

// anagram can be any combination order which does not have to be the exact reverse
bool IsAnagram(char *s1, char *s2)
{
    // the idea is to sort both array and compared them one by one to decide if they are the same
    // complexity: O(nlogn) quick sort, and O(n) final compare
    // overvall: O(n)
    if ((!s1) && (!s2))
        return true;

    if ((!s1) || (!s2))
        return false;
    
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    if (len1 != len2)
        return false;

    std::sort(s1, s1+len1);
    std::sort(s2, s2+len2);

    for (int i = 0; i < len1; i++)
    {
        if (s1[i]!=s2[i])
            return false;
    }
    return true;
}

// O(n)
bool IsAnagram2(char *s1, char *s2)
{
    // the idea is to sort both array and compared them one by one to decide if they are the same
    // complexity: O(nlogn) quick sort, and O(n) final compare
    // overvall: O(n)
    if ((!s1) && (!s2))
        return true;

    if ((!s1) || (!s2))
        return false;
    
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    if (len1 != len2)
        return false;

    int countMap[256];

    // Note that sizeof return the number of bytes of the structure not the number of elements
    // if you want to get the number of element, you will need: sizeof(countMap)/sizeof(int)
    // int sizeofret =  sizeof(countMap);
    memset(countMap, 0, sizeof(countMap));

    for (int i = 0; i < len1; i++)
    {
        countMap[s1[i]]++;
        countMap[s2[i]]--;    
    }

    for (int i = 0; i < 256; i++)
    {
        if (countMap[i] != 0)
            return false;
    }

    return true;
}

void TestIsAnagram()
{
    char s1[64] = "hello";
    char s2[64] = "lloeh";

    printf("%s and %s is Anagram = %s\n", s1, s2, IsAnagram2(s1, s2) ? "true" : "false");
}

// 1.5 
// Write a method to replace all spaces in a string with ‘%20’.
// e.g. "Hello World XYZ"  "Hello%20World%20XYZ"
// assume original string str have enough space to do the in place update without resizing 
void ReplaceSpaceWithP20(char *str)
{
    if (!str)
        return;

    // get the new size by counting number of spaces in the original string
    int cSpaces = 0;
    char *p = str;
    while (*p != '\0')
    {
        if (*p == ' ')
            cSpaces++;
        p++;
    }

    // no space, short cut and return
    if (cSpaces == 0)
        return;

    int origStrlen = strlen(str);
    int newStrlen = origStrlen + cSpaces*2;
    str[newStrlen] = '\0';
    int idx = newStrlen - 1;

    for (int i = origStrlen-1; i >= 0; i--)
    {
        if (str[i] != ' ')
        {
            str[idx--] = str[i];
        }else
        {
            str[idx--] = '0';
            str[idx--] = '2';
            str[idx--] = '%';
        }
    }
}

void TestReplaceSpace()
{
    char s1[256] = "This is a small world! I love Coffee.";

    printf("original: %s  \n", s1);
    ReplaceSpaceWithP20(s1);
    printf("newstring: %s \n", s1);
    
}


/// 1.6
// Given an image represented by an NxN matrix, where each pixel in the image is 4 bytes, 
// write a method to rotate the image by 90 degrees. Can you do this in place?

// a common mistake while (i < n) ; , the extra ; will make program into a deadloop

void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}

void RotateNxNby90Degree(int a[][4], int N)
{
    // how to represent a matrix rotate
    // 1. swap the major diaganal
    // 2. swap a[i], a[N-i-1]
    for (int i = 0; i < N; i++)
        for (int j = i+1; j < N; j++)
            swap(a[i][j], a[j][i]);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            swap(a[i][j], a[N-i-1][j]);
    }
}

void PrintMatrix(int a[][4], int M, int N)
{
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void TestRotate()
{
    int a[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    PrintMatrix(a, 4, 4);

    printf("\n\n");

    RotateNxNby90Degree(a, 4);

    PrintMatrix(a, 4, 4);

    printf("\n\n");

}

// 1.7 Write an algorithm such that if an element in an MxN matrix is 0, its entire row and column is set to 0.
void ZeroRowColumn(int a[][4],  const int M,  const int N)
{
    bool *row = new bool[M];
    bool *col = new bool[N];

    memset(row, false, sizeof(row));
    memset(col, false, sizeof(col));

    for (int i = 0; i < M; i++)
        for (int j =0 ; j < N; j++)
        {
            if (a[i][j] == 0)
            {
                row[i] = true;
                col[j] = true;
            }
        }

     for (int i = 0; i < M; i++)
     {
         for (int j = 0; j < N; j++)
         {
            if ((row[i]) || (col[j]))
            {
                a[i][j] = 0;
            }
         }
     }

     delete row;
     delete col;
}

void TestZeroMatrix()
{
    int a[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9, 10, 11, 12},
        {0, 14, 15, 16}
    };

    PrintMatrix(a, 4, 4);

    printf("\n\n");

    ZeroRowColumn(a, 4, 4);

    PrintMatrix(a, 4, 4);

    printf("\n\n");
}


/// chapter 2
// 2.1 Write code to remove duplicates from an unsorted linked list. FOLLOW UP How would you solve this problem if a temporary buffer is not allowed? 
typedef struct Node
{
    int data;
    Node *next;

    Node(int data): data(data), next(nullptr) {}
}Note;

void RemoveDupLinklist(Node *pHead)
{
    // assume data range is 1~100 otherwise, you need to use the real hash funciton
    bool hash[100];
    memset(hash, false, sizeof(hash));

    Node *p = pHead;
    Node *pre = nullptr;
    
    while (p != nullptr)
    {
        if (hash[p->data])
        {
            // remove dup
            _ASSERT(pre != nullptr);
            _ASSERT(pre->next == p);            
            pre->next = p->next;
            delete p;
            p = pre->next; // !!! pay attention here as we have to move the pointer p appropriately to make sure the loop work correctly
        }else
        {
            hash[p->data] = true;
            pre = p;
            p=p->next;
        }
    }
}

void RemoveDupeLinklist2(Node *pHead)
{
    Node *p = pHead;

    while (p != nullptr)
    {
        Node *pre = p;
        Node *q = p->next;        
        while ( q!= nullptr)
        {
            if (q->data == p->data)
            {
                // remove dup
                pre->next = q->next;
                delete q;
                q = pre->next;
            }else
            {
                pre = q;
                q = q->next;
            }        
        }  
        p = p->next; // !!! don't forget to move the loop pointer
    }
}
 
Node *InitLinkList(int testdata[], int size)
{
    Node *pHead=nullptr;
    for (int i = 0; i < size; i++)
    {
        Node *p = new Node(testdata[i]);
        if (p)
        {
            p->next = pHead;
            pHead = p;
        }else
        {
            printf("memory alloc error \n");
            break;
        }
    }
    return pHead;
}


Node *InitLinkListOriginalOrder(int testdata[], int size)
{
    Node *pHead=nullptr;
    Node *pTail = nullptr;

    for (int i = 0; i < size; i++)
    {
        Node *p = new Node(testdata[i]);
        if (p)
        {
            if (!pHead)
            {
                pHead = p;
                pTail = p;
            }

            pTail->next = p;
            pTail = p;

        }else
        {
            printf("memory alloc error \n");
            break;
        }
    }
    return pHead;
}

void CleanupLinkList(Node **pHead)
{
    Node *p = *pHead;
    while (p != nullptr)
    {
        Node *temp = p; 
        p = p->next;
        delete temp;
    }

    *pHead = nullptr;
}

void PrintLinkList(Node *pHead, char *pCaption = nullptr)
{
    if (pCaption)
        printf("\n %s : ", pCaption);

    Node *p = pHead;    
    while (p!=nullptr)
    {
        printf("%d ", p->data);
        p=p->next;
    }

    printf("\n");
}

void TestRemoveDupLinklist()
{
    int testdata[6] = {1, 1, 2, 3, 3, 5};


    Node *pHead = InitLinkList(testdata, sizeof(testdata)/sizeof(int));
        
    PrintLinkList(pHead);

    // O(n) if additional storage is allowed for the hash table
    //RemoveDupLinklist(pHead);

    // O(n^2) complexity if no additional storage is allowed
    RemoveDupeLinklist2(pHead);

    printf("\n\n");

    PrintLinkList(pHead);

    CleanupLinkList(&pHead);
}


// 2.2 Implement an algorithm to find the nth to last element of a singly linked list.
Node *FindNthNodeLinkList(Node *pHead, int n)
{    
    Node *p = pHead;
    Node *q = nullptr;
    
    while (p && (n>0))
    {
        p = p->next;
        n--;
    }

    if (p != nullptr)
    {
        q = pHead;
        while (p != nullptr)
        {
            p = p->next;
            q = q->next;
        }
    }

    return q;
}

void reverseArray(int a[], int size)
{
    int i = 0;
    int j = size -1;

    while (i++ < j--)
    {
        swap(a[i], a[j]);
    }
}


void TestNToTheLast()
{

    int testdata[6] = {1, 2, 3, 4, 5, 6};

    reverseArray(testdata, 6);

    Node *pHead = InitLinkList(testdata, sizeof(testdata)/sizeof(int));
        
    PrintLinkList(pHead);

    Node *pN = FindNthNodeLinkList(pHead, 3);

    printf("\n\n pN = %d", pN? pN->data: -1);

    CleanupLinkList(&pHead);
}

// 2.3 implement an algorithm to delete a node in the middle of a single linked list, 
//given only access to that node. EXAMPLE Input: the node ‘c’ from the linked list a->b->c->d->e 
//Result: nothing is returned, but the new linked list looks like a->b->d->e
bool RemoveInMidLinklist(Node *pHead, Node *pRemove)
{
    Node *pNext = pRemove->next;

    if ((pNext == nullptr) || (pRemove == nullptr))
        return false;

    pRemove->data = pNext->data;

    pRemove->next = pNext->next;

    delete pNext;

    return true;
}

void TestRemoveLinklistInMiddle()
{
    int testdata[6] = {1, 2, 3, 4, 5, 6};

    reverseArray(testdata, 6);

    Node *pHead = InitLinkList(testdata, sizeof(testdata)/sizeof(int));
        
    PrintLinkList(pHead);

    Node *pN = FindNthNodeLinkList(pHead, 3);

    printf("\n\n pN = %d\n", pN? pN->data: -1);

    RemoveInMidLinklist(pHead, pN);

    PrintLinkList(pHead);

    CleanupLinkList(&pHead);
}

/*
2.4 You have two numbers represented by a linked list, where each node contains a single digit.
The digits are stored in reverse order, such that the 1’s digit is at the head of the list.
Write a function that adds the two numbers and returns the sum as a linked list. EXAMPLE Input: (3 -> 1 -> 5) + (5 -> 9 -> 2) Output: 8 -> 0 -> 8
*/

Node *LinkListAdd(Node *ph1, Node *ph2)
{
    Node *p1 = ph1;
    Node *p2 = ph2;
    Node *pRet = nullptr;
    Node *pLast = nullptr;

    bool bCarryOver = false;

    while ((p1 != nullptr) && (p2 != nullptr))
    {
        int sum = p1->data + p2->data + (bCarryOver? 1: 0);
        bCarryOver = (sum >= 10);

        Node *p = new Node(sum % 10);
        if (pRet == nullptr) // == vs. =
        {
            pRet = p;
            pLast = p;
        }else
        {
            pLast ->next = p;
            pLast = p;
        }   
        p1 = p1->next;
        p2 = p2->next;
    }

    while (p1 != nullptr)
    {
        int sum = p1->data + (bCarryOver ? 1: 0);
        Node *p = new Node (sum % 10);
        bCarryOver = (sum >= 10);
        if (pRet == nullptr)
        {
            pRet = p;
            pLast = p;
        }else
        {
            pLast ->next = p;
            pLast = p;
        }   
        p1 = p1->next;
    }

    while (p2 != nullptr)
    {
        int sum = p2->data + (bCarryOver ? 1: 0);
        Node *p = new Node (sum % 10);
        bCarryOver = (sum >= 10);
        if (pRet == nullptr)
        {
            pRet = p;
            pLast = p;
        }else
        {
            pLast ->next = p;
            pLast = p;
        }   
        p2 = p2->next;
    }

    // !!! the last carry over is the tricky part as we might hit 111+ 999
    if (bCarryOver)
    {
        Node *p = new Node(1);
        pLast->next = p;
        pLast = p; // still keep the pLast through it is not necessary
    }

    return pRet;
}

void TestLinkListSum()
{
    int testdata[6] = {1, 2, 3, 4, 5, 6};
    //reverseArray(testdata, 6);
    
    int testdata2[9] = {0, 0, 0, 0, 5, 3, 9, 9, 9} ;
    //reverseArray(testdata2, 9);

    Node *ph1 = InitLinkListOriginalOrder(testdata, sizeof(testdata)/sizeof(int));
    
    Node *ph2 = InitLinkListOriginalOrder(testdata, sizeof(testdata)/sizeof(int));
   
    Node *ph3 = InitLinkListOriginalOrder(testdata2, sizeof(testdata2)/sizeof(int));
   

    PrintLinkList(ph1, "List 1");

    PrintLinkList(ph2, "List 2");

    PrintLinkList(ph3, "List 3");

    Node *pSum = LinkListAdd(ph1, ph2);

    PrintLinkList(pSum, "List Sum");

    Node *pSum2 = LinkListAdd(ph1, nullptr);

    PrintLinkList(pSum2, "List Sum 2");

    Node *pSum3 = LinkListAdd(ph1, ph3);

    PrintLinkList(pSum3, "List Sum 3");

    CleanupLinkList(&ph1);
    CleanupLinkList(&ph2);
    CleanupLinkList(&pSum);
    CleanupLinkList(&pSum2);
    CleanupLinkList(&pSum3);
}
    
// 2.5 Given a circular linked list, implement an algorithm which returns node at the beginning of the loop. 
// DEFINITION Circular linked list: A (corrupt) linked list in which a node’s next pointer points to an earlier node, 
// so as to make a loop in the linked list. EXAMPLE input: A -> B -> C -> D -> E -> C (the same C as earlier) output: C

Node *FindLoopBeingLinklist(Node *pHead)
{
    // TODO: 
    return nullptr;
}


void TestFindLoopBeginLinklist()
{
    int testdata[6] = {1, 2, 3, 4, 5, 6};

    Node *ph1 = InitLinkListOriginalOrder(testdata, sizeof(testdata)/sizeof(int));
    
    PrintLinkList(ph1, "List 1");

    Node *p3 = FindNthNodeLinkList(ph1, 3);
    Node *p0 = FindNthNodeLinkList(ph1, 0);

    // make the fake loop
    p0->next = p3->next;

    Node *pLoopBegin = FindLoopBeingLinklist(ph1);

    printf("Loop begin at %d\n", pLoopBegin->data);

    CleanupLinkList(&ph1);

}

// chapter 3. stack and queue

// 3.1 Describe how you could use a single array to implement three stacks.
class ThreeStack_1
{
public:

    ThreeStack_1(int size) : _size(size)
    {
        _top[0]=_top[1]=_top[2] = -1;
        _pBuf = new int[size*3];
    }

    bool Push(int stackNum, int val)
    {
        int idx = ++_top[stackNum];
        bool ret = false;
        if (idx < _size)
        {            
            _pBuf[ stackNum * _size + idx ] = val;
            ret = true;
        }
        return ret;
    }

    bool Pop(int stackNum)
    {
        int idx = _top[stackNum];
        bool ret = false;
        if ( idx >= 0 )
        {
            _top[stackNum]--;
            ret = true;            
        }
        return ret;
    }

    int Top(int stackNum)
    {
        int idx = _top[stackNum];
        int ret = -1;
        if ( idx >= 0)
        {
            ret = _pBuf[stackNum *_size + _top[stackNum]];    // !!! size should time stackNum         
        }
        return ret;
    }

    ~ThreeStack_1()
    {
        if (_pBuf)
            delete []_pBuf;
    }

private:
    int _size;
    int *_pBuf;
    int _top[3];
};

void TestThreeStack()
{
    ThreeStack_1 ts1(20);

    for (int js = 0; js < 3; js++)
    {
        for (int i = 0; i < 4; i++)
        {
            ts1.Push(js, i);
        }
    }

    for (int js = 0; js < 3; js++)
    {
        printf("Stack %d:\n", js);
        for (int i = 0; i < 4; i++)
        {
            int v = ts1.Top(js);
            ts1.Pop(js);
            printf("%d ", v); 
        }
        printf("\n");
    }
}

typedef struct StackEntry
{
    int val;
    int iPrev;

    StackEntry() 
    {
        val = 0;
        iPrev = -1;
    };
}StackEntry;

class ThreeStack2
{
public:
    bool Init(int size)
    {
        _pEntries = new StackEntry[size]; 
        _curr = -1;
    }

    bool Push(int stackNum, int val)
    {        
        if (_curr >= _size)
        {
            return false;
        } 

        int top = ++_curr;
        _pEntries[top].val = val;
        _pEntries[top].iPrev = _top[stackNum];
        _top[stackNum] = top;
        return true;
    }

    // free space is not usable, needs to track the _curr free space list
    bool Pop(int stackNum)
    {
        if (_curr < 0)
        {
            return false;
        }

        _top[stackNum] = _pEntries[_top[stackNum]].iPrev;
        
        return true;
    }

    int Top(int stackNum)
    {
        if (_curr < 0)
        {
            return -1;
        }

        return _pEntries[_top[stackNum]].val;
    }


private:
    StackEntry *_pEntries;
    int _curr;
    int _top[3];
    int _size;
};

class MyStack{
    
public:
    MyStack()
    {
        _pBuf = nullptr;
    }

    bool Init(int size)
    {
        if (_pBuf != nullptr)
        {
            delete []_pBuf;
        }

        _size = size;
        _pBuf = new int[size];
        _top = -1;
    }

    bool Push(int val)
    {
        if (_top >= (_size -1))
        {
            return false;
        }
        _pBuf[++_top] = val;
    }

    bool Pop()
    {
        if (_top < 0)
        {
            return false;
        }
        _top--;
    }

    int Top()
    {
        if (_top < 0)
        {
            return -1;
        }
        return _pBuf[_top--];
    }

    bool Empty()
    {
        return (_top == -1);
    }

    ~MyStack()
    {
        if (_pBuf != nullptr)
        {
            delete []_pBuf;
        }
    }

private:
    int _size;
    int *_pBuf;
    int _top;
};
// 3.2 How would you design a stack which, in addition to push and pop, 
// also has a function min which returns the minimum element? Push, pop and min should all operate in O(1) time.
// 2 stacks, main stack and min stack
class MinStack{
public:
    bool push(int val)
    {
        bool ret = false;
        if (s1.Push(val))
        {
            if (s1.Top() < s2.Top())
            {
                if (s2.Push(val))
                {
                    ret = true;
                }
            }
            ret = true;
        }   
        return ret;
    }

    int pop()
    {
        int  ret = s1.Pop();

        if (s1.Top() == s2.Top())
        {
            s2.Pop();
        }
        return ret;
    }


    int min()
    {
        return s2.Top();
    }
private:
    MyStack s1, s2;
};

// 3.3
/*
Imagine a (literal) stack of plates. If the stack gets too high, it might topple. 
Therefore, in real life, we would likely start a new stack when the previous stack exceeds some threshold. 
Implement a data structure SetOfStacks that mimics this. SetOfStacks should be composed of several stacks, and 
should create a new stack once the previous one exceeds capacity. 
SetOfStacks.push() and SetOfStacks.pop() should behave identically to a single stack (that is, pop() should return the 
same values as it would if there were just a single stack). FOLLOW UP Implement a function popAt(int index) which performs
a pop operation on a specific sub-stack.
*/

// similar to the mutiple stack in a single array, maintain _curr stack number for push and pop

// 3.5 Implement a MyQueue class which implements a queue using two stacks.
class MyQueue{
public:
    bool Init()
    {
        s1.Init(30);
        s2.Init(30);
    }

    bool Enqueue(int val)
    {
        s1.Push(val);
    }

    int Dequeue()
    {
        int ret = -1;
        if (s2.Empty())
        {
            while (!s1.Empty())
            {
                s2.Push( s1.Top());
                s1.Pop();                
            }
        }

        if (!s2.Empty())
        {
            ret = s2.Top();
            s2.Pop();
        }

        return ret;
    }

private:
    MyStack s1;
    MyStack s2;
   
};


// 3.6 Write a program to sort a stack in ascending order. You should not make any assump- tions about how the stack is implemented.
// The following are the only functions that should be used to write this program: push | pop | peek | isEmpty.

template <class T>
class Stack
{
public:

    Stack(int iMaxSize): _max(iMaxSize), _curr(-1)
    {
        _buf = new T[iMaxSize];
    }
    
    ~Stack()
    {
        if (_buf)
            delete []_buf;
    }

    bool Push(T data)
    {
        bool bRet = false;
        if (!IsFull)
        {
            _buf[++_curr] = data;
        }
        return bRet;
    }

    bool Pop()
    {
        bool bRet = false;
        if (!IsEmpty())
        {
            _curr--;
        }
        return bRet;
    }

    T& Top()
    {
        if (!IsEmpty())
        {
            return _buf[_curr];
        }
    }

    bool IsEmpty()
    {
        return !(_curr >=0);
    }

    bool IsFull()
    {
        return !(_curr < _max);
    }

private:

    int _max;
    int _curr;
    T *_buf;
};

void TestCC150()
{
    ///
    /// array:
    ///

    //TestAllUniqueChar();
    //TestReverse();
    //TestRemoveDup();
    //TestIsAnagram();
    //TestReplaceSpace();
    //TestRotate();
    //TestZeroMatrix();

    ///
    /// Link list
    ///

    //TestRemoveDupLinklist();
    //TestNToTheLast();
    //TestRemoveLinklistInMiddle();
    //TestLinkListSum();
    // TODO:
    //TestFindLoopBeginLinklist();

    ///
    /// stack
    ///
    TestThreeStack();

    ///
    /// Queue
    ///

    ///
    /// TREE
    ///
    // Binary Search Tree

    // Binary Tree

    ///
    /// Graph
    /// 
    // BFS

    // DFS

    // TOPO Sort


    /// Recursion
    
    // Dynamic Programming

}

