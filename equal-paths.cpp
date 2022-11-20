#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
int pathLengths(Node*);

int pathLengths(Node* root)
{
    if (!root->left && !root->right)
    {
        return 0;
    }
    else if (!root->left)
    {
        return 1 + pathLengths(root->right);
    }
    else if (!root->right)
    {
        return 1 + pathLengths(root->left);
    }
    else
    {
        int leftLen = pathLengths(root->left);
        int rightLen = pathLengths(root->right);
        if (leftLen == rightLen)
        {
            return 1 + leftLen;
        }
        else
        {
            return -1;
        }
    }
}

bool equalPaths(Node * root)
{
    // Add your code below
    return static_cast<bool>(pathLengths(root) != -1);
}

