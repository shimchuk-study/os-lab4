#pragma once

#ifndef FILENAMETREE_HPP
#define FILENAMETREE_HPP

#include "filename.hpp"
#include "btree.hpp"

using FileNameTree = BTree<FileName>;
using FileNameTreeIt = const FileNameTree::Iterator;

#endif // FILENAMETREE_HPP
