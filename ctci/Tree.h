#pragma once

typedef struct _TreeNode
{
    int data;
    _TreeNode *left;
    _TreeNode *right;  
} TreeNode;

typedef struct _TreeNodewParent
{
    int data;
    _TreeNodewParent *left;
    _TreeNodewParent *right;  
    _TreeNodewParent *parent;
} TreeNodewParent;