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

private:
  int data;
  BinTree *lchild;
  BinTree *rchild;
  // avl
  int avl_bf;
  enum BF_TYPE{
    AVL_LH = +1,
    AVL_EH = 0,
    AVL_RH = -1
  };

  BinTree();
  BinTree(int data);
  ~BinTree();
  static BinTree *BST_find__(BinTree *root, int data, BinTree **parent);
  static bool AVL_insert__(BinTree **root, int data, bool *taller);
  static void AVL_l_rotate__(BinTree **unblanced);
  static void AVL_r_rotate__(BinTree **unblanced);
};


