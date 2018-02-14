#pragma once

#include <ostream>
#include <string>
#include <vector>

#include "tree.hh"


namespace tree {

	class PtrTree : public Tree {
	public:
  		PtrTree(value_t value);
    	~PtrTree() = default;
    	PtrTree(value_t newroot, const PtrTree* left, const PtrTree* right);

    	virtual unsigned size() const override;
        virtual std::string pathToHelper (value_t value) const;
    	virtual std::string pathTo(value_t value) const override;
    	value_t getByPath(const std::string& path) const override;

    private:
        const value_t nodeValue;
    	const PtrTree* leftNode;
    	const PtrTree* rightNode;
	};

} 