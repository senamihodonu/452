#include "gtest/gtest.h"
#include <string.h>

extern "C" {
#include "../deq.h"
}
/*empty list*/
TEST(deq, initialize_empty_list) {
  Deq q=deq_new();
  ASSERT_EQ(0, deq_len(q));
  deq_del(q,0);
}

/*list with one element*/
TEST(deq, list_with_one_element) {
  Deq q=deq_new();
  Data data = (Data*)1;
  deq_head_put(q, data);
  ASSERT_EQ(1, deq_len(q));
  deq_del(q,0);
}

TEST(deq, insert_to_head) {
  Deq q=deq_new();
  Data data = (Data*)1;
  deq_head_put(q, data);
}

