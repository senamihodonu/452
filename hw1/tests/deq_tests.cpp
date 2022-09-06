#include "gtest/gtest.h"

extern "C" {
#include "../deq.h"
}

TEST(deq, initialize_empty_list) {
  Deq q=deq_new();
  ASSERT_EQ(0, deq_len(q));
}

TEST(deq, list_with_one_element) {
  Deq q=deq_new();
  Data data = (Data*)1;
  deq_head_put(q, data);
  ASSERT_EQ(1, deq_len(q));
}

TEST(deq, insert_to_head) {

}

TEST(deq, insert_to_tail) {

}

TEST(deq, return_index_value_from_head) {

}

TEST(deq, return_index_value_from_tail) {

}