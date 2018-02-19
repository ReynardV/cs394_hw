/*
 * ptrtree.hh: API for a simple, non-mutating binary tree class.
 * A tree cannot be empty: it always has at least a root with a value.
 * See tree.hh for virtual API documentation.
 * Written by Eitan Frachtenberg.
 */

#pragma once

#include <string>
#include <memory>

#include "tree.hh"

namespace tree {

class PtrTree : public Tree {
  public:
    PtrTree(value_t value);
    ~PtrTree();
    PtrTree(value_t newroot, const PtrTree& left, const PtrTree& right);

    virtual unsigned size() const override;

    virtual std::string pathTo(value_t value) const override;

    value_t getByPath(const std::string& path) const override;

    const PtrTree* clone() const;  // Make a deep copy

  private:
    bool find(value_t) const;  // Is value in my tree?

    value_t value_;
    const PtrTree* left_;
    const PtrTree* right_;
};

} // namespace
