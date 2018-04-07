#include"BinTree.h"
#include<iostream>
#include<queue>

using namespace std;

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

bool BinTree::search(int data) const {
  if (this->data == data) {
    return true;
  }
  bool ret = false;
  if (lchild) {
    ret = lchild->search(data);
  }
  if (ret) {
    return ret; // find in left
  }

  if (rchild) {
    ret = rchild->search(data);
  }

  return ret;
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
    PreTraverse(root->lchild);
    cout << root->data << endl;
    PreTraverse(root->rchild);
  }
}

void BinTree::PostTraverse(const BinTree *root) {
  if (root) {
    PreTraverse(root->lchild);
    PreTraverse(root->rchild);
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

