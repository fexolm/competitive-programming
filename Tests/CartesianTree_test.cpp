#include <boost/test/unit_test.hpp>
#include "../data-structures/CartesianTree.hpp"

BOOST_AUTO_TEST_SUITE(CartesianTree)

void print(std::ostream &out, ds::CartesianTree<int>::Node *node) {
  if (node->left) {
    print(out, node->left);
  }
  if (node->right) {
    print(out, node->right);
  }
  out << node->value;
}

BOOST_AUTO_TEST_CASE(sum) {
  ds::CartesianTree<int> tree;
  tree.insert(5);
  tree.insert(15);
  tree.insert(10);

  std::stringstream ss;

  print(ss, tree.root);

  BOOST_CHECK(ss.str()=="51015");
}
BOOST_AUTO_TEST_SUITE_END()


