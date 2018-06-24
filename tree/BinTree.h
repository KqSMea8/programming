#include <stack>
#include <vector>

class BinTree {
public:
  // basic bin tree
  static void PreTraverse(const BinTree *root);
  static void MiddleTraverse(const BinTree *root);
  static void PostTraverse(const BinTree *root);
  static void LevelTraverse(const BinTree *root);
  static bool Search(const BinTree *root, int data);
  static int Deepth(const BinTree *root);

  // sorted bin tree
  static const BinTree *BST_find(const BinTree *root, int data);
  static bool BST_insert(BinTree **root, int data);
  static void BST_delete(BinTree **root, int data);
  static void BST_delete_ex(BinTree **root, int data);

  // balanced BST
  static bool AVL_insert(BinTree **root, int data);
  static void AVL_delete(BinTree **root, int data);

  // red-black BST
  static bool RB_insert(BinTree **root, int data);
  static void RB_delete(BinTree **root, int data);

private:
  int data;
  BinTree *lchild;
  BinTree *rchild;

  // avl
  enum BF_TYPE{
    AVL_LH = +1,
    AVL_EH = 0,
    AVL_RH = -1
  };
  BF_TYPE avl_bf;

  // red-black tree
  enum RB_COLOR {
    RB_COLOR_BLACK,
    RB_COLOR_RED
  };
  RB_COLOR rb_clr;

  BinTree();
  BinTree(int data);
  ~BinTree();
  static BinTree *BST_find__(BinTree *root, int data, BinTree **parent);
  static bool AVL_insert__(BinTree **root, int data, bool *taller);
  static void AVL_l_rotate__(BinTree **unblanced);
  static void AVL_l_rotate__s(BinTree **unblanced);
  static void AVL_r_rotate__(BinTree **unblanced);
  static void AVL_r_rotate__s(BinTree **unblanced);
  static BinTree *getSibling(BinTree *parent, BinTree *me, bool &isLeft);
  /*
   *(5) 对于任一结点而言，其到叶结点树尾端NIL指针的每一条路径都包含相同数目的黑结点。
   */
  static bool RB_check5__(const BinTree *node, std::vector<const BinTree *> &path, int top);
  static int check5__count;

  friend void adjust_tree(std::stack<BinTree *> &path, bool delete_from_left, BinTree **root);
  friend void adjust_tree(std::vector<std::pair<BinTree *,bool> > &path,\
          BinTree *p, BinTree **root);
};


