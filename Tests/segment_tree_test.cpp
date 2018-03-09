#include <boost/test/unit_test.hpp>
#include "../data-structures/segment_tree.hpp"
BOOST_AUTO_TEST_SUITE(segment_tree)

BOOST_AUTO_TEST_CASE(sum) {
  ds::SegmentTree<int> st(5);
  st.set(0, 5);
  st.set(1, 8);
  st.set(2, 6);
  st.set(3, 3);
  st.set(4, 2);
  st.set(5, 7);
  st.set(6, 2);
  st.set(7, 6);

  BOOST_CHECK(st.get_range(2, 7)==26);
  BOOST_CHECK(st.get_range(1, 3)==17);
  BOOST_CHECK(st.get_range(5, 7)==15);

}

BOOST_AUTO_TEST_CASE(min) {
  ds::SegmentTree<int> st(5, (~(1 << 31)),
                          [](int a, int b) -> int { return std::min<int>(a, b); });
  st.set(0, 5);
  st.set(1, 8);
  st.set(2, 6);
  st.set(3, 3);
  st.set(4, 1);
  st.set(5, 7);
  st.set(6, 2);
  st.set(7, 6);

  BOOST_CHECK(st.get_range(0, 7)==1);

  BOOST_CHECK(st.get_range(0, 3)==3);

  BOOST_CHECK(st.get_range(0, 2)==5);

  BOOST_CHECK(st.get_range(3, 6)==1);
}

BOOST_AUTO_TEST_CASE(make_tree) {
  std::vector<int> values({5, 8, 6, 3, 1, 7, 2, 6});

  auto st = ds::make_segment_tree(values.begin(), values.end(), (~(1 << 31)),
                                    [](int a, int b) -> int { return std::min<int>(a, b); });

  BOOST_CHECK(st.get_range(0, 7)==1);

  BOOST_CHECK(st.get_range(0, 3)==3);

  BOOST_CHECK(st.get_range(0, 2)==5);

  BOOST_CHECK(st.get_range(3, 6)==1);

}

BOOST_AUTO_TEST_SUITE_END()


