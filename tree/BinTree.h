class BinTree {
public:
  // basic bin tree
  static void PreTraverse(const BinTree *root);
  static void MiddleTraverse(const BinTree *root);
  static void PostTraverse(const BinTree *root);
  static void LevelTraverse(const BinTree *root);
  static bool Search(const BinTree *root, int data);

  // sorted bin tree
  static const BinTree *BST_find(const BinTree *root, int data);
  static bool BST_insert(BinTree **root, int data);
  static void BST_delete(BinTree **root, int data);
  static void BST_delete_ex(BinTree **root, int data);

private:
  int data;
  BinTree *lchild;
  BinTree *rchild;

  BinTree();
  BinTree(int data);
  ~BinTree();
  static BinTree *BST_find__(BinTree *root, int data, BinTree **parent);
};


