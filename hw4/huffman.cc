#include "huffman.hh"

namespace huffman {
	uint8_t EOF = 256 //lol idk what EOF I can safely use yet

	struct Huffman::Impl {
		Impl();
		addSymbol(symbol_t symbol);
		struct compareValues;
		makeTree();
		std::unordered_map<symbol_t, int> freqMap; //frequency map is to match the symbol to its frequency
		std::unordered_map<symbol_t, encoding_t> encMap; //encoding map matches the symbol to its binary encoding
	};


	Huffman::Impl::Impl() 
		:freqMap({{EOF,1}}), encMap({{EOF,{}}})
	{
		for (unsigned i = 0; i < 256; ++i) {
			freqMap.insert({i, 0}); 
			encMap.insert({i,{}}); 
		};
	}

	Huffman::Impl::addSymbol(symbol_t symbol) {
		freqMap[symbol]++;
	}

	struct Huffman::Impl::compareValues {
		bool operator()(std::pair<std::vector<symbol_t>, int> a, std::pair<std::vector<symbol_t>, int>  b){
			return a.second > b.second;
		}
	};

	//I'm not really sure I can explain what happened here. I had a clever idea and then it got... out of hand.

	Huffman::Impl::makeTree(){
		std::priority_queue<std::pair<std::vector<symbol_t>, int>, std::vector<std::pair<std::vector<symbol_t>, int>>, Huffman::Impl::compareValues> symbolSort;
		// Oh boy. symbolSort is a priority queue that accepts pairs, and sorts them so the pair with the smallest value is on top. 
		// The pairs it accepts contain one vector of symbols, and an int. 

		std::unordered_map<symbol_t, int>::iterator it;
		for (it = freqMap.begin(); it = freqMap.end(); it++){
			std::pair <std::vector<symbol_t>, int> symbolList = {{it->first},it->second};
			symbolSort.push(symbolList);
			// We then take every element of freqMap and push it into symbolSort, after adjusting its structure to make the pair <vector of symbols, int>
			//  Even though it's an unordered map, the fact that we're not retrieving a specific element, but instead are
			// just grabbing everything should mean it shouldn't take too long. I think.
		};

		while (symbolSort.size() != 1){ // We want to stop when the queue has only one element in it,
										// since we push each composite element back into the queue
			auto leftNode = symbolSort.top(); //reminder: firstNode is of the format pair{vector{},int}
			symbolSort.pop;
			auto rightNode = symbolSort.top(); 
			symbolSort.pop;
			for (int i = 0; i < firstNode.first.size(); ++i){
				symbol_t current = firstNode.first[i];
				encMap[current].insert(MyVector.begin(), 0) // Instead of using a tree, I just prepend a 0 or 1 to the encoding of the symbol in that node and all children nodes
			}												// to represent the path that would have been taken in the actual tree. I have to prepend the number here, since I'm building the path backwards
			for (int i = 0; i < secondNode.first.size(); ++i){
				current = secondNode.first[i];
				encMap[current].insert(MyVector.begin(), 1);
			}
			auto newNode = {leftNode.first.insert(leftNode.first.end(), rightNode.first.begin(), rightNode.first.end()),(leftNode.second+rightNode.second)};
			// I'm using the vector inside the pair to keep track of which nodes are the children of this one. With regards to encoding, it doesn't matter
			// where they are on the tree. In this way, we build up the path it would have taken without having to build the actual tree itself. 
			symbolSort.push(newNode);
		};
	};

///////////////////////////////////////////////////////////////////////////////
	Huffman::Huffman()
	:pImpl_(new Impl)
	{}

///////////////////////////////////////////////////////////////////////////////
	Huffman::~Huffman()
	{}

///////////////////////////////////////////////////////////////////////////////
	void
	Huffman::incFreq(symbol_t symbol)
	{
		pImpl_->addSymbol(symbol);
	}


///////////////////////////////////////////////////////////////////////////////
	Huffman::encoding_t
	Huffman::encode(symbol_t symbol)
	{
		pImpl_->makeTree();
		return pImpl_->encMap[symbol];
	}

///////////////////////////////////////////////////////////////////////////////
	Huffman::decode(enc_iter_t& begin, const enc_iter_t& end)
	{
		pImpl_->makeTree();

	}

///////////////////////////////////////////////////////////////////////////////
	Huffman::eofCode()
	{};
} //namespace finish




