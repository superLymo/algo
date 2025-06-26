#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <iterator>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution {
public:
    int maxDepth(TreeNode* root) {
        return root ? 0 : std::max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};