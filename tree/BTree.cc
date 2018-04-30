#include "BTree.h"
#include <iostream>
#include <string.h>
#include <assert.h>

using namespace std;

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

void BTree::Insert_helper(BTree *p, int index, int key, BTree *q) {
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

void BTree::Traverse(const BTree *root) {
  if (0 == root) {
    return;
  }
  int i;

  for(i = 0; i < root->keynum; i++) {
    Traverse(root->childs[i]);
    cout << root->keys[i] << " ";
  }
  Traverse(root->childs[i]);
}

void BTree::print_all_nodes(const BTree *root) {
  if (0 == root) {
    return;
  }
  int i;

  print_node(root);
  for(i = 0; i < root->keynum + 1; i++) {
    Traverse(root->childs[i]);
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
