#define CATCH_CONFIG_MAIN
/*
 * Tree class unit tests
 * Written by Eitan Frachtenberg.
 */

#include "catch.hpp"
#include "tree.hh"
#include "ptrtree.hh"

using TreeType = tree::PtrTree;  // Change this to test other subclasses of Tree

TEST_CASE("size is computed correctly", "[ptrtree]") {
    const auto tree1 = new TreeType(15);

    SECTION("leaf case") {
        REQUIRE(tree1->size() == 1);
    }

    SECTION("compound tree") {
        const auto tree2 = new TreeType(10);
        const auto tree3 = new TreeType(7, *tree1, *tree2);
        REQUIRE(tree2->size() == 1);
        REQUIRE(tree3->size() == 3);

        delete tree3;
        delete tree2;
    }

    delete tree1;
}


TEST_CASE("Left path is computed correctly", "[ptrtree]") {
    const auto tree1 = new TreeType(15);
    const auto tree2 = new TreeType(10);
    const auto tree3 = new TreeType(7, *tree1, *tree2);

    REQUIRE(tree3->pathTo(15) == "L");
    REQUIRE_THROWS(tree3->pathTo(2));

    delete tree3;
    delete tree2;
    delete tree1;
}

TEST_CASE("Right path is computed correctly", "[ptrtree]") {
    const auto tree1 = new TreeType(15);
    const auto tree2 = new TreeType(10);
    const auto tree3 = new TreeType(7, *tree1, *tree2);

    REQUIRE(tree3->pathTo(10) == "R");
    REQUIRE_THROWS(tree3->pathTo(2));

    delete tree3;
    delete tree2;
    delete tree1;
}

TEST_CASE("Searching for a nonexistent element", "[ptrtree]") {
    const auto tree1 = new TreeType(15);
    const auto tree2 = new TreeType(10);
    const auto tree3 = new TreeType(7, *tree1, *tree2);


    REQUIRE_THROWS(tree3->pathTo(19));

    delete tree3;
    delete tree2;
    delete tree1;
}


TEST_CASE("Getting by path works", "[ptrtree]"){
    const auto tree1 = new TreeType(15);
    const auto tree2 = new TreeType(10);
    const auto tree3 = new TreeType(7, *tree1, *tree2);

    REQUIRE(tree3->getByPath("R") == 10);
    REQUIRE_THROWS(tree3->getByPath("LRL"));
    REQUIRE_THROWS(tree3->getByPath("X"));

    delete tree3;
    delete tree2;
    delete tree1;
}
