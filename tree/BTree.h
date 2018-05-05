/*
 *                  KISS: Keep it simple, stupid
 */
class BTree {
public:
  static void Traverse(const BTree *root, bool clear = false);
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
  static void get_siblings(BTree *p, BTree *&lsib, BTree *&rsib);
  /* remove K[index] and A[index + a].
   * if del is true, free A[index + a], otherwise not free it.
   * if a is 1, right child will be deleted, 0 left deleted.
   */
  static void remove_in_node(BTree *node, int index, int a, bool del = true);
  /*
   * merge key and right into left's tail
   */
  static void merge_nodes(BTree *left, int key, BTree *right);
};

