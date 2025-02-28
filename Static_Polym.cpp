// Raw Program Example for Static Polymorphism in C++


// Points to keep in mind:
// 1. is-a relationship between base and derived class
// 2. Base class defines a "generic" algorithm using template method ex: parse_preorder
// 3. The "generic" algorithm is customized by derived class ex: EmployeeChart_Parser's process_node


#include <iostream>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int data): data(data), left(nullptr), right(nullptr) {}
};
// Base class
// Taking a example from Bo Qian video
template<typename T>
class Generic_Parser {
public:
    void parse_preorder (TreeNode* node) {
        if (node) {
            process_node(node);
            parse_preorder(node->left);
            parse_preorder(node->right);
        }
    }
    void process_node(TreeNode* node) {
        static_cast<T*>(this)->process_node(node);
    }
};

class EmployeeChart_Parser: public Generic_Parser<EmployeeChart_Parser> {
    public:
    void process_node(TreeNode* node) {
        cout << "EmployeeChart_Parser: " << node->data << endl;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    EmployeeChart_Parser ecp;
    ecp.parse_preorder(root);
    return 0;
}