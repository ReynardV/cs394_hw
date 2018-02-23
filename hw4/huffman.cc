#include "huffman.hh"

#include <unordered_map>
#include <queue>
#include <iostream>

namespace huffman {
	using symbol_t = Huffman::symbol_t;
	using encoding_t = Huffman::encoding_t;
	int end = 255+1; 

	struct Huffman::Impl {
		Impl();
		void addSymbol(symbol_t symbol);
		struct compareValues;
		void makeTree();
		std::unordered_map<symbol_t, int> freqMap; //frequency map is to match the symbol to its frequency
		std::unordered_map<symbol_t, encoding_t> encMap; //encoding map matches the symbol to its binary encoding
		bool edited = true;
	};

	Huffman::Impl::Impl() 
		:freqMap({{end,1}}), encMap({{end,{}}})
	{
		for (unsigned i = 0; i < 256; ++i) {
			freqMap.insert({i, 0}); 
			encMap.insert({i,{}}); 
		};
	}

	void
	Huffman::Impl::addSymbol(symbol_t symbol) {
		freqMap[symbol]++;
	}

	struct Huffman::Impl::compareValues {
		bool operator()(std::pair<std::vector<symbol_t>, int> a, std::pair<std::vector<symbol_t>, int>  b){
			return a.second > b.second;
		}
	};

	//I'm not really sure I can explain what happened here. I had a clever idea and then it got... out of hand.
	void
	Huffman::Impl::makeTree(){
		std::priority_queue<std::pair<std::vector<symbol_t>, int>, std::vector<std::pair<std::vector<symbol_t>, int>>, Huffman::Impl::compareValues> symbolSort;
		// Oh boy. symbolSort is a priority queue that accepts pairs, and sorts them so the pair with the smallest value is on top. 
		// The pairs it accepts contain one vector of symbols, and an int. 
		auto it = freqMap.begin();
		while (it != freqMap.end()){
			std::vector<symbol_t> vecList = {it->first};
			auto symbolList = std::make_pair(vecList,it->second);
			symbolSort.push(symbolList);
			// We then take every element of freqMap and push it into symbolSort, after adjusting its structure to make the pair <vector of symbols, int>
			// Even though it's an unordered map, the fact that we're not retrieving a specific element, but instead are
			// just grabbing everything should mean it shouldn't take too long. I think.
			it++;
		};
		for (unsigned i = 0; i < 256; ++i) {
			encMap[i].clear(); // clearing out the encoding so each maketree has a fresh start.
		};
		while (symbolSort.size() != 1){ // We want to stop when the queue has only one element in it,
			auto leftNode = symbolSort.top(); //reminder: left & right Nodes are of the format pair{vector{symbol_t},int}
			symbolSort.pop();
			auto rightNode = symbolSort.top(); 
			symbolSort.pop();
			for (unsigned long i = 0; i < leftNode.first.size(); ++i){
				symbol_t current = leftNode.first[i];
				encMap[current].insert(encMap[current].begin(), ZERO); // Instead of using a tree, I just prepend a 0 or 1 to the encoding of the symbol in that node and all children nodes
			}												// to represent the path that would have been taken in the actual tree. I have to prepend the number here, since I'm building the path backwards
			for (unsigned long i = 0; i < rightNode.first.size(); ++i){
				symbol_t current = rightNode.first[i];
				encMap[current].insert(encMap[current].begin(), ONE);
			}
			std::vector<symbol_t> childList = leftNode.first;
			childList.insert(childList.end(), rightNode.first.begin(), rightNode.first.end());
			std::pair<std::vector<symbol_t>, int> newNode = std::make_pair(childList,leftNode.second+rightNode.second);
			// I'm using the vector inside the pair to keep track of which nodes are the children of this one. With regards to encoding, it doesn't matter
			// where they are on the tree. In this way, we build up the path it would have taken without having to build the actual tree itself. 
			symbolSort.push(newNode);
		};
	};

///////////////////////////////////////////////////////////////////////////////
	Huffman::Huffman() noexcept
	:pImpl_(new Impl)
	{}

///////////////////////////////////////////////////////////////////////////////
	Huffman::~Huffman() noexcept
	{}

///////////////////////////////////////////////////////////////////////////////
	void
	Huffman::incFreq(symbol_t symbol)
	{
		pImpl_->addSymbol(symbol);
		pImpl_->edited = true;
	}


///////////////////////////////////////////////////////////////////////////////
	encoding_t
	Huffman::encode(symbol_t symbol) const
	{
		if (pImpl_->edited == true){
			pImpl_->makeTree();
			pImpl_->edited = false;
		};
		return pImpl_->encMap[symbol];
	}

///////////////////////////////////////////////////////////////////////////////
	symbol_t
	Huffman::decode(enc_iter_t& begin, const enc_iter_t& end) const
	{
		if (pImpl_->edited == true){
			pImpl_->makeTree();
			pImpl_->edited = false;
		};
		int output = 300;
		int bitCount = 1;
		while (output == 300){
			if (begin+bitCount > end){
				throw std::runtime_error("Symbol not found");
			};
			encoding_t input(begin, begin+bitCount); 
			std::unordered_map<symbol_t, encoding_t>::iterator it = pImpl_->encMap.begin(); 
			int count = 0;
			while (it != pImpl_->encMap.end()){
				if (it->second == input){ // it's not possible for a leaf to continue leading on to another branch, so
					output = it->first; // if the subvector is also an encoding in encMap, then we've found its symbol decoding. 
					break;
				};
				it++;
				count++;
			};
			bitCount++;			
		};
		begin += bitCount-1;
		symbol_t eightBitOutput = output;
		return eightBitOutput;
	}

///////////////////////////////////////////////////////////////////////////////
	encoding_t
	Huffman::eofCode() const
	{
		return (Huffman::encode(end));
	};
} 
//namespace finish




