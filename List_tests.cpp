#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;


TEST(test_list_default_ctor) {
    List<int> empty_list;
    ASSERT_TRUE(empty_list.empty());
}

TEST(test_traversal_push_back) {
    List<int> list;
    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    int j = 0;
    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it, ++j) {
        ASSERT_EQUAL(*it, j);
    }
    ASSERT_EQUAL(j, list.size());
}
TEST(test_traversal_push_front) {
    List<int> list;
    for (int i = 4; i >= 0; --i) {
        list.push_front(i);
    }
    int j = 0;
    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it, ++j) {
        ASSERT_EQUAL(*it, j);
    }
    ASSERT_EQUAL(j, list.size());
}

TEST(test_insert_1){
    //insertng if its the first one 
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_front(4);
    list.push_front(5);

    List<int> list2;
    list2.push_front(1);
    list2.push_front(2);
    list2.push_front(3);
    list2.push_front(4);
    list2.push_front(6);
   
    // bc its in the List class, it needs to what its an Iterator for
    List<int>::Iterator i = list.begin();
    int datum = 6;
    list.insert(i, datum);

    ASSERT_EQUAL(list.size(), 6);
    List<int>::Iterator it = list.begin();
    List<int>::Iterator it2 = list2.begin();

    ASSERT_EQUAL(*it, *it2);
}
 // make a test case for just normally inserting somegthing


 TEST(test_insert_2){
    //insertng if its the first one 
    List<int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    list.push_front(4);
    list.push_front(5);
   
    // bc its in the List class, it needs to what its an Iterator for
    List<int>::Iterator i = list.begin();
    ++i;
    int datum = 6;
    List<int>::Iterator i2 = list.insert(i, datum);

    ASSERT_EQUAL(list.size(), 6);
    ASSERT_EQUAL(*i2, datum);
}


 TEST(test_pop_front_1){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    list.pop_front();
    int j = 2;
    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it, ++j) {
        ASSERT_EQUAL(*it, j);
    }
    ASSERT_EQUAL(4, list.size());
    
 }

//this one is causing an issue
 TEST(test_pop_back_1){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    list.pop_back();
    int j = 1;
    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it, ++j) {
        ASSERT_EQUAL(*it, j);
    }


    
 }


TEST(test_list_assigment_operator){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    list.push_back(5);

    List<int> list2;
    list2.push_back(6);
    list2.push_back(7);
    list2.push_back(8);
    list2.push_back(9);
    list2.push_back(10);

    list2 = list;
    List<int>::Iterator it2 = list2.begin();

    for (List<int>::Iterator it = list.begin(); it != list.end(); ++it) {
        ASSERT_EQUAL(*it, *it2);
        ++it2;
    }

}


TEST(test_dereference_operator){
    List<int> list;
    list.push_back(1);
    list.push_back(2);

    int datum = 1;
    List<int>::Iterator it = list.begin();

    ASSERT_EQUAL(*it, datum);
}

TEST(test_increment_operator){
     List<int> list;
    list.push_back(1);
    list.push_back(2);

    int datum = 2;
    List<int>::Iterator it = list.begin();
    it.operator++();

    ASSERT_EQUAL(*it, datum);
}

TEST(test_equals_operator){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
   
    List<int> list2;
    list2.push_back(1);
    list2.push_back(2);
    list2.push_back(3);
    List<int>::Iterator it = list.begin();
    List<int>::Iterator it2 = list2.begin();

    ASSERT_TRUE(*it == *it2);
    it++;
    it2++;
    ASSERT_TRUE(*it == *it2);
    it++;
    it2++;
    ASSERT_TRUE(*it == *it2);
    
}

TEST(test_not_equals_operator){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
   
    List<int> list2;
    list2.push_back(4);
    list2.push_back(5);
    list2.push_back(6);
    List<int>::Iterator it = list.begin();
    List<int>::Iterator it2 = list2.begin();

    ASSERT_TRUE(*it != *it2);
    it++;
    it2++;
    ASSERT_TRUE(*it != *it2);
    it++;
    it2++;
    ASSERT_TRUE(*it != *it2);
}

TEST(test_assignment_operator){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
   
    List<int> list2;
    list2.push_back(4);
    list2.push_back(5);
    list2.push_back(6);
 
    int j = 4;
    for (List<int>::Iterator it = list2.begin(); it != list2.end(); ++it, ++j) {
        ASSERT_EQUAL(*it, j);
    }

    list2 =list;
    
    j = 1;
    for (List<int>::Iterator it2 = list2.begin(); it2 != list2.end(); ++it2, ++j) {
        ASSERT_EQUAL(*it2, j);
    }

// how do we insert something like to the middle of the list, set it to the begining and
// just do plus plus 
}


    TEST(test_assignment_operator_diff_sizes){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
   
    List<int> list2;
    list2.push_back(4);
    list2.push_back(5);
    list2.push_back(6);
 
    int j = 4;
    for (List<int>::Iterator it = list2.begin(); it != list2.end(); ++it, ++j) {
        ASSERT_EQUAL(*it, j);
    }
    list2 =list;
    // try modifying the list after you use the assignment operator
    j = 1;
    for (List<int>::Iterator it2 = list2.begin(); it2 != list2.end(); ++it2, ++j) {
        ASSERT_EQUAL(*it2, j);
    }

    List<int>::Iterator it = list.begin();
    *it = 3;
    List<int>::Iterator it2 = list2.begin();
    ++it2;
    *it2 = 9;

    List<int>::Iterator it3 = list.begin();
    ASSERT_EQUAL(*it3, 3);
     List<int>::Iterator it4 = list2.begin();
    ++it4;
    ASSERT_EQUAL(*it4, 9);

}

TEST (test_empty_and_clear){
     List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    ASSERT_FALSE(list.empty());

    list.clear();
    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
}

TEST (test_copy_constructor){
  List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    List <int> list2 = list;
    ASSERT_EQUAL(list2.size(), list.size());
    
    int j = 1;
    for (List<int>::Iterator it2 = list2.begin(); it2 != list2.end(); ++it2, ++j) {
        ASSERT_EQUAL(*it2, j);
    }
    
}


TEST (test_front){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
   
   ASSERT_EQUAL(list.front(), 1);
   ASSERT_EQUAL(list.back(), 3);

}

TEST (test_begin_and_end){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);      

    List<int>::Iterator it = list.begin();
    ASSERT_EQUAL(list.begin(), it);
}

TEST (test_insert_last){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

     List<int>::Iterator it = list.begin();
     it++;
     it++;
     it++;

     List<int>::Iterator it2 = list.insert(it, 4);
     ASSERT_EQUAL(list.size(), 4);
     ASSERT_EQUAL(*it2, 4);

}

TEST(test_list_self_assigment) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    List<int> list2;
    list2.push_back(1);
    list2.push_back(2);
    list2.push_back(3);
   
    ASSERT_EQUAL(list.size(),list2.size());
    // try using diff numbers
    // try modifying the list in list 3 and list 2 after 359
    
   int j = 1;
    for (List<int>::Iterator it2 = list2.begin(); it2 != list2.end(); ++it2, ++j) {
        ASSERT_EQUAL(*it2, j);
    }
    list2 = list;
    List<int> *list3 = &list2;
    list2 = *list3;

    ASSERT_EQUAL(list2.size(),(*list3).size());
    ASSERT_EQUAL(list2.begin(), (*list3).begin());
    ASSERT_EQUAL(list2.end(), (*list3).end());
    List<int>::Iterator it2 = list2.begin();
    ++it2;
    *it2 = 7;

    List<int>::Iterator it3 = (*list3).begin();
    ++it3;
    ASSERT_EQUAL(*it3, 7);

}

TEST (test_front_and_back){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 3);
}

TEST (push_front_empty){
    List<int> list;
    ASSERT_TRUE(list.empty());
    list.push_front(1);
    ASSERT_FALSE(list.empty());
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 1);
}
TEST (push_back_empty){
    List<int> list;
    ASSERT_TRUE(list.empty());
    list.push_front(1);
    ASSERT_FALSE(list.empty());
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 1);
}

TEST(test_clear_empty){
    List<int> list;
    ASSERT_TRUE(list.empty());
    list.clear();
    ASSERT_TRUE(list.empty());
    ASSERT_EQUAL(list.size(), 0);
}

TEST (test_equals_operator_same_node){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    List<int> list2;
    list2.push_back(1);
    list2.push_back(2);
    list2.push_back(3);

    List<int>::Iterator it2 = list.begin();
    List<int>::Iterator it3 = list2.begin();
    ASSERT_FALSE( it2 == it3);
     ASSERT_TRUE (it2 != it3);
}

TEST (test_equals_operator_same_list){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    List<int>::Iterator it2 = list.begin();
    List<int>::Iterator it3 = list.begin();
    ++it3;
    ASSERT_FALSE( it2 == it3);
    ASSERT_TRUE (it2 != it3);
}

TEST (test_decrement_operator){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    List<int>::Iterator it2 = list.end();
    it2--;
    ASSERT_EQUAL(*it2, 3);
}

TEST (test_erase_first){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    List<int>::Iterator it2 = list.begin();
    List<int>::Iterator it = list.erase(it2);
    ASSERT_EQUAL(*it, 2);
}
TEST (test_erase_last){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    List<int>::Iterator it2 = list.end();
    --it2;
    List<int>::Iterator it = list.erase(it2);
    ASSERT_EQUAL(it, list.end());
}

TEST (test_erase){
     List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    List<int>::Iterator it2 = list.begin();
    ++it2;
    List<int>::Iterator it = list.erase(it2);
    ASSERT_EQUAL(*it, 3);
}

TEST(test_assignment_operator_2){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    List<int> list2 = list;
// how do we insert something like to the middle of the list, set it to the begining and
// just do plus plus 
}

TEST (test_pop_front_one_elemenet){
    List<int> list;
    list.push_back(1);

    list.pop_front();
    ASSERT_TRUE(list.empty());

}

TEST (test_pop_back_one_elemenet){
    List<int> list2;
    list2.push_back(1);

    list2.pop_back();
    ASSERT_TRUE(list2.empty());
}

TEST (test_clear_one_element){
    List<int> list2;
    list2.push_back(1);

    list2.clear();
     ASSERT_TRUE(list2.empty());

}

TEST (test_not_equals_same_list){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    List<int>::Iterator it = list.begin();
    List<int>::Iterator it2 = list.begin();
    ++it2;
    ASSERT_TRUE(*it != *it2);
}

TEST (test_copy_constructor_2){
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    List<int> list2;

    list2 = list;
    ASSERT_EQUAL(list2.size(), list.size());

    int j = 1;
    for (List<int>::Iterator it2 = list2.begin(); it2 != list2.end(); ++it2, ++j) {
        ASSERT_EQUAL(*it2, j);
    }
    

}





TEST_MAIN()
