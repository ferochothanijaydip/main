// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_DISPLAY_LIST_RTREE_H_
#define FLUTTER_DISPLAY_LIST_RTREE_H_

#include <list>
#include <map>

#include "third_party/skia/include/core/SkBBHFactory.h"
#include "third_party/skia/include/core/SkRect.h"

namespace flutter {

/**
 * An R-Tree implementation that forwards calls to an SkRTree. This is just
 * a copy of flow/rtree.h/cc until we can figure out where these utilities
 * can live with appropriate linking visibility.
 *
 * This implementation provides a searchNonOverlappingDrawnRects method,
 * which can be used to query the rects for the operations recorded in the tree.
 */
class DlRTree : public SkBBoxHierarchy {
 public:
  DlRTree();

  void insert(const SkRect[],
              const SkBBoxHierarchy::Metadata[],
              int N) override;
  void insert(const SkRect[], int N) override;
  void search(const SkRect& query, std::vector<int>* results) const override;
  size_t bytesUsed() const override;

  // Finds the rects in the tree that represent drawing operations and intersect
  // with the query rect.
  //
  // When two rects intersect with each other, they are joined into a single
  // rect which also intersects with the query rect. In other words, the bounds
  // of each rect in the result list are mutually exclusive.
  std::list<SkRect> searchNonOverlappingDrawnRects(const SkRect& query) const;

  // Insertion count (not overall node count, which may be greater).
  int getCount() const { return all_ops_count_; }

 private:
  // A map containing the draw operation rects keyed off the operation index
  // in the insert call.
  std::map<int, SkRect> draw_op_;
  sk_sp<SkBBoxHierarchy> bbh_;
  int all_ops_count_;
};

class DlRTreeFactory : public SkBBHFactory {
 public:
  DlRTreeFactory();

  // Gets the instance to the R-tree.
  sk_sp<DlRTree> getInstance();
  sk_sp<SkBBoxHierarchy> operator()() const override;

 private:
  sk_sp<DlRTree> r_tree_;
};

}  // namespace flutter

#endif  // FLUTTER_DISPLAY_LIST_RTREE_H_
