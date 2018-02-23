#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "huffman.hh"

#include <limits.h>
#include <iostream>
#include <cstdlib>


using namespace huffman;

TEST_CASE("All symbols start with different codes", "[diff_codes]") {
  auto huff = Huffman();
  for (unsigned i = 0; i < 256; ++i) {
    for (unsigned j = 0; i < 256; ++i) {
      if (i != j) {
        REQUIRE(huff.encode(i) != huff.encode(j));
      }
    }
  }
}

TEST_CASE("Symbols always have different codes", "[diff_codes]") {
  for (int i = 0; i < 3; ++i) //three trials
  {
    auto huff = Huffman();
    int length = rand() % 50+50; //encode 50-100 characters
    for (int i = 0; i < length; ++i)
    {
      int digit = rand() % 256;
      huff.incFreq(digit);
    };
    for (unsigned i = 0; i < 256; ++i) {
      for (unsigned j = 0; i < 256; ++i) {
        if (i != j) {
          REQUIRE(huff.encode(i) != huff.encode(j));
        }
      }
    }
  }
}



TEST_CASE("Initial codes are always the same", "[const_codes]"){
  auto huff1 = Huffman();
  auto huff2 = Huffman();
  for (unsigned i = 0; i < 256; ++i) {
    REQUIRE(huff1.encode(i) == huff2.encode(i));
  }
}



TEST_CASE("Most frequent symbol encodes shortest", "[compression]") {
  auto huff = Huffman();
  huff.incFreq(0);
  huff.incFreq(0);
  const auto len0 = huff.encode(0).size();

  for (unsigned i = 1; i < 256; ++i) {
    REQUIRE(huff.encode(i).size() > len0);
  }
}



TEST_CASE("Most frequent symbol always encodes to single bit", "[compression]") {
  auto huff = Huffman();
  huff.incFreq(0);
  huff.incFreq(0);
  REQUIRE(huff.encode(0).size() == 1);
  REQUIRE(huff.encode(1).size() > 1);
  huff.incFreq(1);
  huff.incFreq(1);
  huff.incFreq(1);
  REQUIRE(huff.encode(0).size() > 1);
  REQUIRE(huff.encode(1).size() == 1);
}



TEST_CASE("Compressed data decompresses properly", "[compression/decompression]") {
  for (int i = 0; i < 3; ++i) //three trials
  {
    std::vector<int> originalData = {};
    auto huff1 = Huffman();
    int length = rand() % 50+50; //encode 50-100 characters
    Huffman::encoding_t compressedData = {};
    for (int i = 0; i < length; ++i){
      int digit = rand() % 256;
      originalData.push_back(digit);
      Huffman::encoding_t compressedDigit = huff1.encode(digit);
      compressedData.insert(compressedData.end(),compressedDigit.begin(), compressedDigit.end());
      huff1.incFreq(digit);
    };

    auto huff2 = Huffman();
    std::vector<int> decompressedData = {};
    auto b = compressedData.cbegin();
    auto e = compressedData.cend();
    while (b != e){
      const auto symbol = huff2.decode(b, e);

      assert(b <= e);
      if (!symbol && b==e) {
          break;
      } else {
          decompressedData.push_back(symbol);
          huff2.incFreq(symbol);
      };
    }
    REQUIRE(originalData == decompressedData);
  }
}


