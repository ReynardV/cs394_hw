


#include "ptrtree.hh"

#include <algorithm>
#include <stdexcept>

namespace tree {

	PtrTree::PtrTree(value_t value) 
		: Tree(), nodeValue(value), leftNode(nullptr), rightNode(nullptr)
	{}

	unsigned
	PtrTree::size() const
	{
	    int count = 1;
	    if (leftNode!=nullptr){
	    	count += (leftNode->size());
	    } 
	    if (rightNode != nullptr){
	    	count += (rightNode->size());
	    }
	    return (count);

	}


	PtrTree::PtrTree(value_t value, const PtrTree* left, const PtrTree* right)
		: Tree(), nodeValue(value), leftNode(left), rightNode(right)
	{}



	std::string
	PtrTree::pathToHelper(value_t value) const
	{
	    if ((leftNode==nullptr) && (rightNode==nullptr)){
	    	if (nodeValue == value){
	    		return ("F");
	    	} else{
	    		return ("");
	    	}
	    }else if (leftNode!=nullptr){
	    	std::string leftPath = leftNode->pathTo(value);
		    if (leftPath!= "")
		    {
		    	// leftPath.erase(std::remove(str.begin(), str.end(), 'F'), leftPath.end());
		    	return (leftPath.insert(0, 1, "L"));
		    }
	    }
	    if (rightNode != nullptr){
	    	std::string rightPath = rightNode->pathTo(value);
	    	if (rightPath!= "")
		    {
		    	// rightPath.erase(std::remove(str.begin(), str.end(), 'F'), rightPath.end());
		    	return (rightPath.insert(0, 1, "R"));
		    }
	    }

	}

	std::string
	PtrTree::pathTo(value_t value) const
	{
		std::string finalPath = pathToHelper(value);

		if (finalPath == "")
		{
        	throw std::runtime_error("Value not found!");
		}
		finalPath.pop_back();
		return finalPath;
	}

	std::string
	PtrTree::value_t
	PtrTree::getByPath(const std::string& path) const
	{
		if (path.length() > size()){
			throw std::runtime_error("Path too long!");
		}
	    char fork = path.at(0);
	    std::string newPath = path.erase(0,1);
	    if (fork == "R"){
	    	return (rightNode->getByPath)
	    } else if (fork == "L"){
	    	return (leftNode->getByPath)
	    } else if (fork == ""){
	    	return nodeValue
	    } else{
	    	throw std::runtime_error("Invalid character in path: " + path);
	    }

	}

}








