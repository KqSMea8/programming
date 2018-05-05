#include "BTree.h"
#include <iostream>
#include <string.h>
#include <assert.h>
#include <vector>
#include <cstdlib>

using namespace std;

void BTree::Delete(BTree **root, int key) {
  Result res = Search__(*root, key);
  // key does not exist
  if (false == res.found) {
    return;
  }
  if (res.p->childs[0]) { // 转化为删除终端节点
    BTree *right = res.p->childs[res.index + 1];
    while(right->childs[0])
      right = right->childs[0];
    res.p->keys[res.index] = right->keys[0];
    res.p = right;
    res.index = 0;
  }

  BTree *dnode = res.p;
  int index = res.index;
  int left_right = 1;
  bool del = false;
  while(1) {
    remove_in_node(dnode, index, left_right, del);
    if (dnode->keynum >= BTree::m / 2) { // case 1
      break; // deletion is over
    }

    BTree *lsib, *rsib;
    get_siblings(dnode, lsib, rsib);
    if (!lsib && !rsib) { // root
      if (dnode->keynum > 0) {
        break;
      } else {
        *root = dnode->childs[0]; // new root and btree is lower, or btree is empty now
        if (dnode->childs[0]) {
          dnode->childs[0]->parent = 0;
        }
        delete dnode;
        break;
      }
    }
    BTree *r = 0;
    // find the 'the rich'
    if (lsib && lsib->keynum > BTree::m / 2)
      r = lsib;
    if (!r && (rsib && rsib->keynum > BTree::m / 2))
      r = rsib;

    int dnode_index = 0;
    while (dnode != dnode->parent->childs[dnode_index])
      dnode_index++;

    if (r) { // case 2: 拆借
      if (r == rsib) {
        Insert_helper(dnode, dnode->keynum, dnode->parent->keys[dnode_index], r->childs[0]);
        dnode->parent->keys[dnode_index] = r->keys[0];
        index = 0;
        left_right = 0;
      } else {
        int i;
        for (i = dnode->keynum; i > 0; i--) {
          dnode->keys[i] = dnode->keys[i-1];
          dnode->childs[i + 1] = dnode->childs[i];
        }
        dnode->childs[1] = dnode->childs[0];
        dnode->keys[0] = dnode->parent->keys[dnode_index-1];
        dnode->childs[0] = r->childs[r->keynum];
        if (dnode->childs[0]) {
          dnode->childs[0]->parent = dnode;
        }
        dnode->keynum += 1;

        dnode->parent->keys[dnode_index-1] = r->keys[r->keynum-1];
        index = r->keynum - 1;
        left_right = 1;
      }
      dnode = r;
      del = false;
    } else { // case 3: 合并
      if ((BTree::m % 2 == 0) && (dnode->keynum == BTree::m / 2 - 1)) {
        /*
         * btree shall not support even m
         */
        break;
      }
      if (dnode_index) { // dnode must have left sibling
        merge_nodes(lsib, dnode->parent->keys[dnode_index-1], dnode);
        index = dnode_index - 1;
      } else {
        merge_nodes(dnode, dnode->parent->keys[dnode_index], rsib);
        index = dnode_index;
      }
      dnode = dnode->parent;
      del = true;
      left_right = 1;
    }
  }

}

void BTree::get_siblings(BTree *p, BTree *&lsib, BTree *&rsib) {
  int a;
  a = 0;
  BTree *parent = p->parent;
  if (0 == parent) { // root
    lsib = rsib = 0;
    return;
  }

  while (parent->childs[a] != p)
    a++;
  if (0 == a) { // no left sibling
    lsib = 0;
   } else {
     lsib = parent->childs[a-1];
   }
  if (parent->keynum == a) { // no right sibling
    rsib = 0;
  } else {
    rsib = parent->childs[a+1];
  }
}

bool BTree::Insert(BTree **root, int key) {
  Result res = Search__(*root, key);
  // key exists
  if (true == res.found) {
    return false;
  }

  if (0 == res.p) { // empty b-tree
    BTree *p = new BTree();
    p->parent = 0;
    p->keynum = 1;
    p->childs[0] = p->childs[1] = 0;
    p->keys[0] = key;
    *root = p;
    return true;
  }

  /*
   * node is not full
   */
  if (res.p->keynum < BTree::m - 1) {
    Insert_helper(res.p, res.index, key, 0);
    return true;
  }

  /*
   * node is full
   */
  BTree *p = res.p;
  BTree *q = 0;
  int index = res.index;

  int overflow_key;
  BTree *overflow_child;
  do {
    int i;

    // firstly insert 'key' and 'q'
    if (index == p->keynum) {
      overflow_key = key;
      overflow_child = q;
    } else {
      overflow_key = p->keys[p->keynum - 1];
      overflow_child = p->childs[p->keynum];
      p->keynum -= 1; // the two lasts is invalid now
      Insert_helper(p, index, key, q);
    }

    // begin split
    q = new BTree();
    q->parent = p->parent;
    q->keynum = (BTree::m - (BTree::m / 2 + 1));

    p->keynum = BTree::m - (1 + q->keynum); // pre part

    memcpy(q->keys, p->keys + (p->keynum + 1), (q->keynum - 1) * sizeof(int));
    memcpy(q->childs, p->childs + (p->keynum + 1), q->keynum * sizeof(BTree *));
    q->keys[q->keynum - 1] = overflow_key;
    q->childs[q->keynum] = overflow_child;

    key = p->keys[p->keynum];

    /*
     * this bug hurt me so baaaaaaaaaaaaaaaaaaaaaaaaaaaaaaadly!
     * remove the following FOR loop to see what's going to happen.
     */
    // 当节点分裂时，要正确地维护节点的父指针
    for (i = 0; i < q->keynum + 1; i++) {
      if (q->childs[i]) {
        q->childs[i]->parent = q;
      } else {
        break;
      }
    }

    // end split

    if (0 == p->parent) {
      BTree *new_root = new BTree();
      new_root->keynum = 1;
      new_root->keys[0] = key;
      new_root->childs[0] = p;
      new_root->childs[1] = q;
      p->parent = new_root;
      q->parent = new_root;
      *root = new_root;
      break;
    }
    // get index
    i = -1;
    while(p != p->parent->childs[++i])
      ;
    index = i;
    assert(i <= p->parent->keynum);

    p = p->parent;
    // p, index, key, q is already now
    if (p->keynum < BTree::m - 1) {
      Insert_helper(p, index, key, q);
      break;
    }
    // p is already full, it will be split
  } while (true);

  return true;
}

void BTree::merge_nodes(BTree *left, int key, BTree *right) {
  Insert_helper(left, left->keynum, key, right->childs[0]);
  int i;
  for (i = 0; i < right->keynum; i++) {
    Insert_helper(left, left->keynum, right->keys[i], right->childs[i+1]);
  }
}

void BTree::remove_in_node(BTree *node, int index, int a, bool del) {
  BTree *p = node->childs[index + a];
  int i,j;
  for (i = index, j = index + a; i < node->keynum - 1; i++, j++) {
    node->keys[i] = node->keys[i+1];
    node->childs[j] = node->childs[j+1];
  }
  if (0 == a) {
    node->childs[j] = node->childs[j+1];
  }
  node->keynum -= 1;
  if (del && p) {
    delete p;
  }
}

void BTree::Insert_helper(BTree *p, int index, int key, BTree *q) {
    assert(p->keynum < BTree::m - 1);
    int i;
    for (i = p->keynum; i > index; i--) {
      p->keys[i] = p->keys[i-1];
      p->childs[i + 1] = p->childs[i];
    }
    p->keys[index] = key;
    p->childs[index + 1] = q;
    p->keynum += 1;
    if (q) {
      q->parent = p;
    }
}

void BTree::print_node(const BTree *p) {
  if (0 == p) {
    return;
  }

  int i;
  cout << "[parent: " << p->parent << ", self: " << p << " | ";
  for (i = 0; i < p->keynum; i++) {
    cout << p->childs[i];
    cout << " " << p->keys[i] << " ";
  }
  cout << p->childs[i] << "]" << endl;
}

void BTree::Traverse(const BTree *root, bool clear) {
  static int v = -10000000;
  if (clear) {
    v = -10000000;
    clear = false;
  }


  if (0 == root) {
    return;
  }
  int i;
  vector<int> keys;
  if (root->keynum + 1 > BTree::m || root->keynum == 0) {
      cerr <<("###########   houjie errorrrrrrrrrrrrrrrrrrrrrrrrrrrrr line:") << __LINE__ << endl;
      print_node(root);
      exit(1);
  }
  if (root->parent) {
    if (root->keynum + 1 < BTree::m / 2 + 1 && (BTree::m % 2)) {
        cerr <<("###########   houjie errorrrrrrrrrrrrrrrrrrrrrrrrrrrrr line:") << __LINE__ << endl;
        print_node(root);
        exit(1);
  }
  } else {
    if (root->childs[0]) {
      if (root->keynum + 1 < 2) {
        cerr <<("###########   houjie errorrrrrrrrrrrrrrrrrrrrrrrrrrrrr line:") << __LINE__ << endl;
        print_node(root);
        exit(1);
  }
    }
  }

  for(i = 0; i < root->keynum; i++) {
    Traverse(root->childs[i]);
    cout << root->keys[i] << " " << endl;
    if (v >= root->keys[i]) {
      cout << v << " " << root->keys[i] << endl;
      cerr <<("###########   houjie errorrrrrrrrrrrrrrrrrrrrrrrrrrrrr line:") << __LINE__ << endl;
      exit(1);
    }
    v = root->keys[i];
    keys.push_back(v);
  }
  Traverse(root->childs[i]);
  cout << "     [";
  for (i = 0; i < keys.size(); i++) {
    cout << keys[i] << " ";
  }
  cout << "]" << endl;

}

void BTree::print_all_nodes(const BTree *root) {
  if (0 == root) {
    return;
  }
  int i;

  print_node(root);
  for(i = 0; i < root->keynum + 1; i++) {
    print_all_nodes(root->childs[i]);
  }
}

bool BTree::Search(const BTree *root, int key) {
  return Search__(const_cast<BTree *>(root), key).found;
}

BTree::Result BTree::Search__(BTree *root, int key) {
  if (!root) {
    return Result(false, -1, 0);
  }

  int i = 0;
  for (; i < root->keynum; i++) {
    if (key == root->keys[i]) {
      return Result(true, i, root);
    } else if (key < root->keys[i]) {
      if (0 != root->childs[i]) {
        return Search__(root->childs[i],key);
      } else {
        return Result(false, i,  root);
      }
    } else {
      continue;
    }
  }
  // i is already root->keynum
  if (0 != root->childs[i]) {
    return Search__(root->childs[i], key);
  } else {
    return Result(false, i, root);
  }
}

BTree::BTree() {
  parent = 0; // NULL pointer
  keynum = 0;
}

BTree::~BTree() {
}
