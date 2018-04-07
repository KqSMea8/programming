struct BinTree {
  int data;
  struct BinTree *lchild;
  struct BinTree *rchild;

  static void PreTraverse(const BinTree *root);
  static void MiddleTraverse(const BinTree *root);
  static void PostTraverse(const BinTree *root);
  static void LevelTraverse(const BinTree *root);

  virtual bool search(int data)const;

  BinTree();
  BinTree(int data);
  virtual ~BinTree();
};


