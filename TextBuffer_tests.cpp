#include "TextBuffer.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_down_last) {
  TextBuffer buffer;
  for(int i = 0; i<10; i++) {
    buffer.insert((char)('0'+i));
  }
  buffer.insert('\n');
  for(int i = 0; i<5; i++) {
    buffer.insert((char)('0'+i));
  }
  ASSERT_FALSE(buffer.down());

}

TEST_MAIN()
