#include "huffman.hh"

namespace huffman {
	uint8_t EOF = 256 //lol idk what EOF I can safely use yet

	struct Huffman::Impl {
		Impl()
		addSymbol(symbol_t symbol)
		makeTree()
		bool editCheck = true; //this tells us if freqMap has been edited since the last time encode was run
		std::unordered_map<symbol_t, int> freqMap = {{EOF,1}}; //frequency map is to match the symbol to its frequency
		std::unordered_map<symbol_t, encoding_t> encMap = {{EOF,{}}}; //encoding map matches the symbol to its binary encoding
		for (unsigned i = 0; i < 256; ++i) {
			freqMap.insert({i, 0}); 
			encMap.insert({i,{}}); 
		}
	}


	Huffman::Impl::Impl() {
		...
	}

	Huffman::Impl::addSymbol(symbol_t symbol) {
		freqMap[symbol]++;
	}

	struct compareValues {
		bool operator()(std::pair a, std::pair b){
			return a.second > b.second;
		}
	}

	//I'm not really sure I can explain what happened here. I had a clever idea and then it got... out of hand.

	Huffman::Impl::makeTree(){
		std::priority_queue<std::pair<std::vector<symbol_t>, int>, std::vector<std::pair<std::vector<symbol_t>, int>>, compareValues> symbolSort;
		// Oh boy. symbolSort is a priority queue that accepts pairs, and then compares the values of each pair to 
		// sort them so the pair with the smallest value is on top. 
		// The pairs it accepts contain one vector of symbols, and an int. I swear there's a reason to make a vector of symbols

		std::unordered_map<symbol_t, int>::iterator it;
		for (it = freqMap.begin(); it = freqMap.end(); it++){
			std::pair <std::vector<symbol_t>, int> symbolList = {{it->first},it->second};
			symbolSort.push(symbolList);
			// We then take every element of freqMap and push it into symbolSort, after putting the symbol in another vector.
			//  Even though it's an unordered map, the fact that we're not retrieving a specific element, but instead are
			// just grabbing everything should mean it shouldn't take too long. I think that's how the pointer works, anyways.
		}

		while (symbolSort.size() != 1){ // We want to stop when the queue has only one element in it,
										// since we push each composite element back into the queue
			auto leftNode = symbolSort.top(); //reminder: firstNode is of the format pair{vector{},int}
			symbolSort.pop;
			auto rightNode = symbolSort.top(); 
			symbolSort.pop;
			for (int i = 0; i < firstNode.first.size(); ++i){
				symbol_t current = firstNode.first[i];
				encMap[current].insert(MyVector.begin(), 0) //instead of using a tree, I just prepend a 0 or 1 to the encoding of the symbol in that node and all children nodes
			}
			for (int i = 0; i < secondNode.first.size(); ++i){
				current = secondNode.first[i];
				encMap[current].insert(MyVector.begin(), 1);
			}
			auto newNode = {leftNode.first.insert(leftNode.first.end(), rightNode.first.begin(), rightNode.first.end()),(leftNode.second+rightNode.second)};
			// I'm using the vector inside the pair to keep track of which nodes are the children of this one. With regards to encoding, it doesn't matter
			// where they are on the tree. 
			symbolSort.push(newNode);
		}
	}

///////////////////////////////////////////////////////////////////////////////
	Huffman::Huffman()
	:pImpl_(new Impl)
	{}

///////////////////////////////////////////////////////////////////////////////
	Huffman::~Huffman()
	{}

///////////////////////////////////////////////////////////////////////////////
	Huffman::incFreq(symbol_t symbol)
	{
		pImpl_->addSymbol(symbol);
		pImpl_->editCheck = true;
	}


///////////////////////////////////////////////////////////////////////////////
	encoding_t
	Huffman::encode(symbol_t symbol)
	{
		if (pImpl_->editCheck = true){
			pImpl_->makeTree();
			pImpl_->editCheck = false;
		}
		return pImpl_->encMap[symbol];
	}

///////////////////////////////////////////////////////////////////////////////
	Huffman::decode(enc_iter_t& begin, const enc_iter_t& end)
	{}

///////////////////////////////////////////////////////////////////////////////
	Huffman::eofCode()
	{};
} //namespace finish




