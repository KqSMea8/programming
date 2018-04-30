class BTree {
public:
  static void Traverse(const BTree *root);
  static bool Search(const BTree *root, int key);
  static bool Insert(BTree **root, int key);
  static void Delete(BTree **root, int key);

private:
  const static int m = 3;
  BTree *parent;
  int keynum;
  int keys[m-1];
  BTree *childs[m];
  BTree();
  virtual ~BTree();

  struct Result {
    bool found;
    int index;
    BTree *p;
    Result(bool found, int index, BTree *p) {
      this->found = found;
      this->index = index;
      this->p = p;
    }
  };

  static Result Search__(BTree *root, int key);
  // p is not full
  static void Insert_helper(BTree *p, int index, int key, BTree *q);
  static void print_node(const BTree *p);
  static void print_all_nodes(const BTree *p);
};

