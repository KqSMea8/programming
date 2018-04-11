#include"BinTree.h"
#include<iostream>
#include<queue>

using namespace std;

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
  if (parent) {
    if (parent->data > data) {
      parent->lchild = NULL;
    } else {
      parent->rchild = NULL;
    }
    delete pos; // leaf
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
