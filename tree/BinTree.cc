#include"BinTree.h"
#include<iostream>
#include<queue>
#include<stack>
#include<vector>
#include<memory>
#include<stdexcept>
#include<cstdlib>

using namespace std;

void BinTree::RB_delete(BinTree **root, int data) {
  BinTree *parent = NULL;
  BinTree *pos = BST_find__(*root, data, &parent);
  if (!pos) {
    return;
  }

  /*
   * find the date actually be deleted
   */
  int actul_data;
  if (pos->lchild && pos->rchild) {// delete from the right child
      // get pos's next node
    BinTree *del;
    del = pos->rchild;
    while (del && del->lchild) {
      del = del->lchild;
    }
    actul_data = del->data;
  } else {
    actul_data = data;
  }
  pos->data = actul_data;
  /*
   * goto actul_data
   */
  vector<pair<BinTree *,bool> > path; // (parent, childIsLeft)
  path.push_back(pair<BinTree *, bool>(NULL, false)); // root has no parent
  BinTree *p = *root;
  while (p->data != actul_data) {
    path.push_back(pair<BinTree *, bool>(p, false));
    if (p->data > actul_data)
      p = p->lchild;
    else
      p = p->rchild;
    path.back().second = path.back().first->data > p->data;
  }
  std::auto_ptr<BinTree> auto_del(p);

  pair<BinTree *, bool> q;
  q = path.back();
  BinTree *nonLeaf = p->lchild ? p->lchild : p->rchild;

  if (p->rb_clr == RB_COLOR_RED)
  {
      // rb-tree's root is black, so p's parent must not null
      if(q.second) q.first->lchild = nonLeaf;
      else         q.first->rchild = nonLeaf;
      return;
  }

  // p is black
  if (nonLeaf && nonLeaf->rb_clr == RB_COLOR_RED)
  {
      nonLeaf->rb_clr = RB_COLOR_BLACK;
      if (q.first)
      {
          if (q.second) q.first->lchild = nonLeaf;
          else           q.first->rchild = nonLeaf;
      }
      else *root = nonLeaf;
      return;
  }

  adjust_tree(path, p, root);
}
void adjust_tree(std::vector<std::pair<BinTree *,bool> > &path,\
          BinTree *p, BinTree **root)
{
    // TODO
}

/*
 * 平衡二叉树之删除节点: https://blog.csdn.net/goodluckwhh/article/details/11786079
 */
void BinTree::AVL_delete(BinTree **root, int data) {
  BinTree *parent = NULL;
  BinTree *pos = BST_find__(*root, data, &parent);
  if (!pos) {
    return;
  }

  /*
   * find the date actually be deleted
   */
  int actul_data;
  bool delete_itself;
  if (pos->lchild && pos->rchild) {// delete from the higher child
    BinTree *del;
    if (pos->avl_bf != AVL_RH) {
       del = pos->lchild;
       while (del && del->rchild) {
         del = del->rchild;
       }
    } else {
       del = pos->rchild;
       while (del && del->lchild) {
         del = del->lchild;
       }
    }
    actul_data = del->data;
    delete_itself = false;
  } else {
    actul_data = data;
    delete_itself = true;
  }
  /*
   * goto actul_data
   */
  stack<BinTree *> path;
  path.push(NULL); // root's parent is NULL
  BinTree *p = *root;
  while (p->data != actul_data) {
    path.push(p);
    if (p->data > actul_data)
      p = p->lchild;
    else
      p = p->rchild;
  }

  /*
   * delete p
   * p is leaf or only has one child
   */
  parent = path.top();
  bool is_left_child;
  if (p->lchild == NULL && p->rchild == NULL) { // leaf
    if (parent == NULL) {
      *root = NULL;
    } else {
      if (p->data > parent->data) {
        is_left_child = false;
        parent->rchild = NULL;
      } else {
        is_left_child = true;
        parent->lchild = NULL;
      }
    }
  } else {
    if (parent == NULL) {
      *root = p->lchild ? p->lchild : p->rchild;
    } else {
      if (p->data > parent->data) {
        is_left_child = false;
        parent->rchild = p->lchild ? p->lchild : p->rchild;
      } else {
        is_left_child = true;
        parent->lchild = p->lchild ? p->lchild : p->rchild;
      }
    }
  }
  delete p;

  /*
   * adjusting
   */
  adjust_tree(path, is_left_child, root);

  if (!delete_itself) {
    pos->data = actul_data;
  }
}

void adjust_tree(stack<BinTree *> &path, bool delete_from_left, BinTree **root) {
  BinTree *parent;
  bool lower;

  while (path.size() > 1) {
    parent = path.top();
    path.pop();
    lower = true;

    //平衡因子为0，只需要调整平衡因子即可完成删除 
    if (parent->avl_bf == BinTree::AVL_EH) {
      if (delete_from_left) {
        parent->avl_bf = BinTree::AVL_RH;
      } else {
        parent->avl_bf = BinTree::AVL_LH;
      }
      break;
    }

    int parent_data = parent->data;

    /*
     * 从较高的子树删除，以parent为根的子树的高度降低，需要回溯往前继续处理高度降低的影响
     */
    if ((parent->avl_bf == BinTree::AVL_LH && delete_from_left == true) ||
        (parent->avl_bf == BinTree::AVL_RH && delete_from_left == false)
        ) {
      parent->avl_bf = BinTree::AVL_EH;
    } else if (delete_from_left && parent->avl_bf == BinTree::AVL_RH) {
      if (parent->rchild->avl_bf == BinTree::AVL_RH) {
        parent->avl_bf = BinTree::AVL_EH;
        parent->rchild->avl_bf = BinTree::AVL_EH;
        BinTree::AVL_l_rotate__s(&parent);
      } else if (parent->rchild->avl_bf == BinTree::AVL_EH) {
        parent->avl_bf = BinTree::AVL_RH;
        parent->rchild->avl_bf = BinTree::AVL_LH;
        BinTree::AVL_l_rotate__s(&parent);
        lower = false;
      } else {
        /*
         * BETTER STYLE, LESS TRAP.
         *
         *   if (BinTree::AVL_EH == parent->rchild->lchild->avl_bf)
        */
        if (parent->rchild->lchild->avl_bf == BinTree::AVL_EH) {
          parent->avl_bf = BinTree::AVL_EH;
          parent->rchild->avl_bf = BinTree::AVL_EH;
        } else if (parent->rchild->lchild->avl_bf == BinTree::AVL_LH) {
          parent->avl_bf = BinTree::AVL_EH;
          parent->rchild->avl_bf = BinTree::AVL_RH;
        } else {
          parent->avl_bf = BinTree::AVL_LH;
          parent->rchild->avl_bf = BinTree::AVL_EH;
        }
        parent->rchild->lchild->avl_bf = BinTree::AVL_EH;
        BinTree::AVL_r_rotate__s(&(parent->rchild));
        BinTree::AVL_l_rotate__s(&parent);
      }
    } else {
      if (parent->lchild->avl_bf == BinTree::AVL_LH) {
        parent->avl_bf = BinTree::AVL_EH;
        parent->lchild->avl_bf = BinTree::AVL_EH;
        BinTree::AVL_r_rotate__s(&parent);
      } else if (parent->lchild->avl_bf == BinTree::AVL_EH) {
        parent->avl_bf = BinTree::AVL_LH;
        parent->lchild->avl_bf = BinTree::AVL_RH;
        BinTree::AVL_r_rotate__s(&parent);
        lower = false;
      } else {
        if (parent->lchild->rchild->avl_bf == BinTree::AVL_EH) {
          parent->avl_bf = BinTree::AVL_EH;
          parent->lchild->avl_bf = BinTree::AVL_EH;
        } else if (parent->lchild->rchild->avl_bf == BinTree::AVL_RH) {
          parent->avl_bf = BinTree::AVL_EH;
          parent->lchild->avl_bf = BinTree::AVL_LH;
        } else {
          parent->avl_bf = BinTree::AVL_RH;
          parent->lchild->avl_bf = BinTree::AVL_EH;
        }
        parent->lchild->rchild->avl_bf = BinTree::AVL_EH;
        BinTree::AVL_l_rotate__s(&(parent->lchild));
        BinTree::AVL_r_rotate__s(&parent);
      }
    }

    if (path.top() == NULL) {
      *root = parent;
    } else {
      if (path.top()->data > parent_data) {
        delete_from_left = true;
        path.top()->lchild = parent;
      } else {
        delete_from_left = false;
        path.top()->rchild = parent;
      }
      if (!lower) {
        break;
      }
    }
  } // while loop
}

bool BinTree::RB_insert(BinTree **root, int data) {
  /*
   * case 1: data is the root node, i.e., first node of red–black tree
   */
  if (0 == *root) {
    BinTree *p = new BinTree(data);
    p->rb_clr = RB_COLOR_BLACK;
    *root = p;
    return true;
  }

  vector<BinTree *>path;
  path.push_back(0); // root has no parent
  BinTree *p = *root;
  while(p)
  {
      if (p->data == data) // already exist
          return false;
      path.push_back(p);
      if (p->data > data) p = p->lchild;
      else                p = p->rchild;
  }
  BinTree *node = new BinTree(data);
  node->rb_clr = RB_COLOR_RED;
  p = path.back();
  path.pop_back();
  if (p->data > data) p->lchild = node;
  else                p->rchild = node;

  BinTree *g; // grandparent
  BinTree *u; // uncle
  while (1)
  {
      // in case of case 3
      if (!p)
      {
          node->rb_clr = RB_COLOR_BLACK;
          break;
      }
      // case 2
      if (p->rb_clr == RB_COLOR_BLACK)
          break;

      g = path.back();
      path.pop_back();
      bool isLeft;
      u = getSibling(g, p, isLeft);

      // case 3
      if (u && u->rb_clr == RB_COLOR_RED)
      {
          p->rb_clr = RB_COLOR_BLACK;
          u->rb_clr = RB_COLOR_BLACK;
          g->rb_clr = RB_COLOR_RED;
          node = g;
          p = path.back();
          path.pop_back();
          continue;
      }

      // case 4
      if (g->lchild && node == g->lchild->rchild)
      {
          AVL_l_rotate__s(&p);
          g->lchild = p;
          node = p->lchild;
      } else if (g->rchild && node ==  g->rchild->lchild)
      {
          AVL_r_rotate__s(&p);
          g->rchild = p;
          node = p->rchild;
      }
      p->rb_clr = RB_COLOR_BLACK;
      g->rb_clr = RB_COLOR_RED;

      if (p->lchild == node) isLeft = true;
      else                   isLeft = false;

      p = path.back();
      path.pop_back();

      bool mount_to_left;
      if (p)
      {
          if (p->lchild == g) mount_to_left = true;
          else                mount_to_left = false;
      }

      if (isLeft)
      {
          AVL_r_rotate__s(&g);
      }
      else
      {
          AVL_l_rotate__s(&g);
      }
      if (!p)
      {
          *root = g;
      }
      else if(mount_to_left) p->lchild = g;
      else                   p->rchild = g;
      break;
  }

  return true;
}


BinTree *BinTree::getSibling(BinTree *parent, BinTree *me, bool &isLeft) {
  if (!parent || !me) {
    return 0;
  }
  if (parent->data > me->data) {
    isLeft = false;
    return parent->rchild;
  }
  else {
    isLeft = true;
    return parent->lchild;
  }
}

bool BinTree::AVL_insert(BinTree **root, int data) {
  bool no_used;
  return AVL_insert__(root, data, &no_used);
}

/*
 * references:1) https://blog.csdn.net/winder9898/article/details/51098211
 *            2) 严蔚敏《数据结构》
 */

bool BinTree::AVL_insert__(BinTree **root, int data, bool *taller) {
  BinTree *p;

  if (*root == NULL) {
    p = new BinTree(data);
    p->avl_bf = AVL_EH;
    *root = p;
    *taller = true;
    return true;
  }

  p = *root;

  if (p->data == data) {
    *taller = false;
    return false;
  }

  if (p->data > data) {
    if (!AVL_insert__(&(p->lchild), data, taller)) {
      return false;
    }
    if (*taller) {
      switch(p->avl_bf) {
        case AVL_EH:
          p->avl_bf = AVL_LH;
          break;
        case AVL_LH:
          if (p->lchild->data > data) { // LL
            AVL_r_rotate__(root);
          } else { // LR
            AVL_l_rotate__(&(p->lchild));
            AVL_r_rotate__(root);
          }
          *taller = false;
          break;
        case AVL_RH:
          p->avl_bf = AVL_EH;
          *taller = false;
          break;
      }
    }
  } else {
    if (!AVL_insert__(&(p->rchild), data, taller)) {
      return false;
    }
    if (*taller) {
      switch(p->avl_bf) {
        case AVL_EH:
          p->avl_bf = AVL_RH;
          break;
        case AVL_LH:
          p->avl_bf = AVL_EH;
          *taller = false;
          break;
        case AVL_RH:
          if (p->rchild->data < data) { // RR
            AVL_l_rotate__(root);
          } else { // RL
            AVL_r_rotate__(&(p->rchild));
            AVL_l_rotate__(root);
          }
          *taller = false;
          break;
      }
    }
  }
  return true;
}

void BinTree::AVL_l_rotate__s(BinTree **unblanced) {
  BinTree *p = (*unblanced)->rchild;
  (*unblanced)->rchild = p->lchild;
  p->lchild = *unblanced;
  *unblanced = p;
}

void BinTree::AVL_l_rotate__(BinTree **unblanced) {
  BinTree *p = (*unblanced)->rchild;
  (*unblanced)->rchild = p->lchild;
  p->lchild = *unblanced;
  int ldeepth = Deepth((*unblanced)->lchild);
  int rdeepth = Deepth((*unblanced)->rchild);
  //cout << "*** " << ldeepth << ", " << rdeepth << ", " << ldeepth - rdeepth << endl;
  (*unblanced)->avl_bf = (BF_TYPE)(ldeepth - rdeepth);
  ldeepth = ldeepth > rdeepth ? ldeepth : rdeepth;
  ldeepth += 1;
  rdeepth -= p->avl_bf;
  //cout << ldeepth << ", " << rdeepth << ", " << ldeepth - rdeepth << endl;
  p->avl_bf = (BF_TYPE)(ldeepth - rdeepth);
  *unblanced = p;
}

void BinTree::AVL_r_rotate__s(BinTree **unblanced) {
  BinTree *p = (*unblanced)->lchild;
  (*unblanced)->lchild = p->rchild;
  p->rchild = *unblanced;
  *unblanced = p;
}

void BinTree::AVL_r_rotate__(BinTree **unblanced) {
  BinTree *p = (*unblanced)->lchild;
  (*unblanced)->lchild = p->rchild;
  p->rchild = *unblanced;
  int ldeepth = Deepth((*unblanced)->lchild);
  int rdeepth = Deepth((*unblanced)->rchild);
  //cout << "*** " << ldeepth << ", " << rdeepth << ", " << ldeepth - rdeepth << endl;
  (*unblanced)->avl_bf = (BF_TYPE)(ldeepth - rdeepth);
  rdeepth = ldeepth > rdeepth ? ldeepth : rdeepth;
  rdeepth += 1;
  ldeepth += p->avl_bf;
  //cout << ldeepth << ", " << rdeepth << ", " << ldeepth - rdeepth << endl;
  p->avl_bf = (BF_TYPE)(ldeepth - rdeepth);
  *unblanced = p;
}

int BinTree::Deepth(const BinTree *root) {
  if (!root) {
    return 0;
  }
  int ldeepth = Deepth(root->lchild);
  int rdeepth = Deepth(root->rchild);
  int max = ldeepth > rdeepth ? ldeepth : rdeepth;
  return max + 1;
}

/*
 * 均衡性更好
 */
void BinTree::BST_delete_ex(BinTree **root, int data) {
  BinTree *parent = NULL;
  BinTree *del, *del_parent;
  BinTree *pos = BST_find__(*root, data, &parent);
  if (!pos) {
    return;
  }
  del_parent = pos;
  // find the nearest 'pre' in left first
  del = pos->lchild;
  while (del && del->rchild) {
    del_parent = del;
    del = del->rchild;
  }
  if (del) {
    pos->data = del->data;
    if (del_parent == pos) {
      pos->lchild = del->lchild;
    } else {
      del_parent->rchild = NULL;
    }
    delete del;
    return;
  }
  // no 'pre' in left, then find the nearest 'post' in right
  del = pos->rchild;
  while (del && del->lchild) {
    del_parent = del;
    del = del->lchild;
  }
  if (del) {
    pos->data = del->data;
    if (del_parent == pos) {
      pos->rchild = del->rchild;
    } else {
      del_parent->lchild = NULL;
    }
    delete del;
    return;
  }
  // pos is a leaf node or root itself
  if (parent) { // leaf
    if (parent->data > data) {
      parent->lchild = NULL;
    } else {
      parent->rchild = NULL;
    }
    delete pos;
  } else {
    *root = NULL; // root
    delete pos;
  }
}

void BinTree::BST_delete(BinTree **root, int data) {
  BinTree *parent = NULL;
  BinTree *pos = BST_find__(*root, data, &parent);
  if (!pos) {
    return;
  }
  if (!parent) { // delete root
    *root = pos->lchild ? pos->lchild : pos->rchild;
  } else {
    if (parent->data > data) {
      parent->lchild = pos->lchild ? pos->lchild : pos->rchild;
    } else {
      parent->rchild = pos->lchild ? pos->lchild : pos->rchild;
    }
  }
  /*
   * if lchild is null, do nothing;
   * if lchild is not null, but rchild is null, do nothing.
   */
  if (pos->lchild && pos->rchild) {
    BinTree *p = pos->lchild;
    while (p->rchild)
      p = p->rchild;
    p->rchild = pos->rchild;
  }

  delete pos;
}

void BinTree::LevelTraverse(const BinTree *root) {
  if (!root) {
    return;
  }
  queue<BinTree *> level;
  BinTree *p;
  BinTree *level_start;

  level.push(const_cast<BinTree *>(root));
  level_start = const_cast<BinTree *>(root);
  while (!level.empty()) {
    p = level.front();
    level.pop();
    if (p == level_start) {
      cout << endl;
      level_start = NULL;
    }
    cout << p->data << " ";
    //cout << (p->rb_clr == RB_COLOR_BLACK ? "black" : "red") << " ";
    if (p->lchild) {
      if (!level_start) {
        level_start = p->lchild;
      }
      level.push(p->lchild);
    }
    if (p->rchild) {
      if (!level_start) {
        level_start = p->rchild;
      }
      level.push(p->rchild);
    }
  }
}

bool BinTree::BST_insert(BinTree **root, int data) {
  BinTree *parent = NULL;
  if (BST_find__(*root, data, &parent)) {
    return false; // already exist
  } else {
    BinTree *node = new BinTree(data);
    if (!parent) { // an empty tree
      *root = node;
    } else {
      if (parent->data > data) {
        parent->lchild = node;
      } else {
        parent->rchild = node;
      }
    }
    return true;
  }
}

bool BinTree::Search(const BinTree *root, int data) {
  if (!root) {
    return false;
  }
  if (root->data == data) {
    return true;
  }
  if (Search(root->lchild, data)) {
    return true;
  }
  return Search(root->rchild, data);
}

void BinTree::PreTraverse(const BinTree *root) {
  if (root) {
    cout << root->data << endl;
    PreTraverse(root->lchild);
    PreTraverse(root->rchild);
  }
}

void BinTree::MiddleTraverse(const BinTree *root) {
  if (root) {
    MiddleTraverse(root->lchild);
    cout << root->data << " ";

    //property 5:Every path from a given node to any of its descendant NIL nodes contains the same number of black nodes.
    BinTree::check5__count = -1;
    vector<const BinTree*> path;
    int top = -1;
    if (!RB_check5__(root, path, top)) {
      cout << "houj rb error 1 ################## ";
      exit(-1);
    }
    // properpty 4:If a node is red, then both its children are black.
    if (root->rb_clr == RB_COLOR_RED) {
      if (root->lchild && root->lchild->rb_clr != RB_COLOR_BLACK) {
        cout << "houj rb error 2 ################## ";
        exit(-1);
      }
      if (root->rchild && root->rchild->rb_clr != RB_COLOR_BLACK) {
        cout << "houj rb error 3 ################## ";
        exit(-1);
      }
    }

    /*
    int l = Deepth(root->lchild);
    int r = Deepth(root->rchild);
    if (l - r != root->avl_bf) {
      cout << "houj bf error ################## ";
    }
    */
    MiddleTraverse(root->rchild);
  }
}

void BinTree::PostTraverse(const BinTree *root) {
  if (root) {
    PostTraverse(root->lchild);
    PostTraverse(root->rchild);
    cout << root->data << endl;
  }
}

BinTree::BinTree() {
  data = 0;
  lchild = NULL;
  rchild = NULL;
}

BinTree::BinTree(int data) {
  this->data = data;
  lchild = NULL;
  rchild = NULL;
}

BinTree::~BinTree() {
}

const BinTree * BinTree::BST_find(const BinTree *root, int data) {
  BinTree *parent = NULL;
  return BST_find__(const_cast<BinTree *>(root), data, &parent);
}

int BinTree::check5__count;

bool BinTree::RB_check5__(const BinTree *node, vector<const BinTree *> &path, int top) {
  if (node) {
    top++;
    try{
      path.at(top) = node;
    }catch(const std::out_of_range &ex) {
      path.push_back(node);
    }
    if (!RB_check5__(node->lchild, path, top))
      return false;
    return RB_check5__(node->rchild, path, top);
  } else {
    int count = 0;
    for (int i = 0; i <= top; i++) {
      if (path[i]->rb_clr == RB_COLOR_BLACK)
        count++;
    }
    if (check5__count == -1) {
      check5__count = count;
      return true;
    } else {
      return check5__count == count;
    }
  }
}


BinTree * BinTree::BST_find__(BinTree *root, int data, BinTree **parent) {
  if (!root) {
    return NULL;
  }
  if (root->data == data) {
    return root;
  } else if (root->data > data) {
    *parent = root;
    return BST_find__(root->lchild, data, parent);
  } else {
    *parent = root;
    return BST_find__(root->rchild, data, parent);
  }
}
