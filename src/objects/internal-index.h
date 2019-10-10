// Copyright 2019 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_OBJECTS_INTERNAL_INDEX_H_
#define V8_OBJECTS_INTERNAL_INDEX_H_

#include <stdint.h>

#include <limits>

#include "src/base/logging.h"

namespace v8 {
namespace internal {

// Simple wrapper around an entry (which is notably different from "index" for
// dictionary backing stores). Most code should treat this as an opaque
// wrapper: get it via GetEntryForIndex, pass it on to consumers.
class InternalIndex {
 public:
  explicit InternalIndex(size_t raw) : entry_(raw) {}
  static InternalIndex NotFound() { return InternalIndex(kNotFound); }

  InternalIndex adjust_down(size_t subtract) {
    DCHECK_GE(entry_, subtract);
    return InternalIndex(entry_ - subtract);
  }
  InternalIndex adjust_up(size_t add) {
    DCHECK_LT(entry_, std::numeric_limits<size_t>::max() - add);
    return InternalIndex(entry_ + add);
  }

  bool is_found() const { return entry_ != kNotFound; }
  bool is_not_found() const { return entry_ == kNotFound; }

  size_t raw_value() const { return entry_; }
  uint32_t as_uint32() const {
    DCHECK_LE(entry_, std::numeric_limits<uint32_t>::max());
    return static_cast<uint32_t>(entry_);
  }
  int as_int() const {
    DCHECK(entry_ >= 0 && entry_ <= std::numeric_limits<int>::max());
    return static_cast<int>(entry_);
  }

 private:
  static const size_t kNotFound = std::numeric_limits<size_t>::max();

  size_t entry_;
};

}  // namespace internal
}  // namespace v8

#endif  // V8_OBJECTS_INTERNAL_INDEX_H_
