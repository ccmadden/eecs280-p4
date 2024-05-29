#include <fstream>
#include <iostream>
#include <cassert>
#include "TextBuffer.hpp"
using namespace std;

  TextBuffer::TextBuffer(){
    cursor = data.end();
    row = 1;
    column = 0;
    index = 0;
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor one position forward and returns true,
  //          unless the cursor is already at the past-the-end position,
  //          in which case this does nothing and returns false.
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  bool TextBuffer::forward() {
      if (cursor == data.end()) {
          return false;
      }
      if (data_at_cursor() == '\n') {
          column = 0;
          ++row;
      } else {
          ++column;
      }
       ++cursor;
      ++index;
      return true;
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor one position backward and returns true,
  //          unless the cursor is is already at the first character in
  //          the buffer, in which case this does nothing and returns false.
  //HINT:     Implement and use the private compute_column() member
  //          function to compute the column when moving left from the
  //          beginning of a line to the end of the previous one.
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
    bool TextBuffer::backward() {
        if (cursor == data.begin()) {
            return false;
        } 
        else {
            --cursor;
            if (data_at_cursor() == '\n') {
              --row;
              column = compute_column();
            } 
            else {
                --column;
            }
            --index;
            return true;
        }
    }

  //MODIFIES: *this
  //EFFECTS:  Inserts a character in the buffer before the cursor position.
  //          If the cursor is at the past-the-end position, this means the
  //          inserted character is the last character in the buffer.
  //          The cursor remains in the same place as before the insertion.
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  void TextBuffer::insert(char c){ 
    cursor = data.insert(cursor, c);
    // edit: dont wanna call forward because the cursor is meant to stay in the sam
    // position you just want to increase the column count
    forward();
  }

  //MODIFIES: *this
  //EFFECTS:  Removes the character from the buffer that is at the cursor and
  //          returns true, unless the cursor is at the past-the-end position,
  //          in which case this does nothing and returns false.
  //          The cursor will now point to the character that was after the
  //          deleted character, or the past-the-end position if the deleted
  //          character was the last one in the buffer.
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  bool TextBuffer::remove(){
    if( cursor == data.end()){
      return false;
    }
    else{
      cursor = data.erase(cursor);
      //forward();
      return true;
    }
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the start of the current row (column 0).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  void TextBuffer::move_to_row_start(){
    while (column != 0){  
      backward();
    }
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the end of the current row (the
  //          newline character that ends the row, or the past-the-end
  //          position if the row is the last one in the buffer).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  void TextBuffer::move_to_row_end(){
 
    // need to change the index value also?
    while(cursor != data.end() && data_at_cursor() != '\n' ){
      forward();
    }
    // is this the correct way to move the index
  }

  //REQUIRES: new_column >= 0
  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the given column in the current row,
  //          if it exists. If the row does not have that many columns,
  //          moves to the end of the row (the newline character that
  //          ends the row, or the past-the-end position if the row is
  //          the last one in the buffer).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  void TextBuffer::move_to_column(int new_column){
    assert(new_column>= 0);
  // move it to the front of the row
    move_to_row_start();
    while (!is_at_end() && data_at_cursor() != '\n' && column != new_column){
      forward();
    }
    
   // try to think about what guarentees the other functions make for us
  }
  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the previous row, retaining the
  //          current column if possible. If the previous row is
  //          shorter than the current column, moves to the end of the
  //          previous row (the newline character that ends the row).
  //          Does nothing if the cursor is already in the first row.
  //          Returns true if the position changed, or false if it did
  //          not (i.e. if the cursor was already in the first row).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  bool TextBuffer::up(){
    if (row == 1){
      return false;
    }
    // move the cursor and index to the row above
    int col_val = column;
    move_to_row_start();
    backward();
    move_to_column(col_val);
    return true;
    // update index??
  }

  //MODIFIES: *this
  //EFFECTS:  Moves the cursor to the next row, retaining the current
  //          column if possible. If the next row is shorter than the
  //          current column, moves to the end of the next row (the
  //          newline character that ends the row, or the past-the-end
  //          position if the row is the last one in the buffer). Does
  //          nothing if the cursor is already in the last row.
  //          Returns true if the position changed, or false if it did
  //          not (i.e. if the cursor was already in the last row).
  //NOTE:     Your implementation must update the row, column, and index
  //          if appropriate to maintain all invariants.
  bool TextBuffer::down() {
    // need some sort of if statement checking for if u are already at the end
      
      // keep track of if the row change
      int col_val = column;
      move_to_row_end();
      forward();
      if (cursor == data.end()){
        return false;
      }
      move_to_column(col_val);

      // update index??
      return true;
  }

  //EFFECTS:  Returns whether the cursor is at the past-the-end position.
  bool TextBuffer::is_at_end() const{
    if (cursor == data.end()){
      return true;
    }
    else{
      return false;
    }
  }

  //REQUIRES: the cursor is not at the past-the-end position
  //EFFECTS:  Returns the character at the current cursor
  char TextBuffer::data_at_cursor() const{
    // what other arguments do you need to pass in 
   //assert(!is_at_end());
    return *cursor;
  }

  //EFFECTS:  Returns the row of the character at the current cursor.
  int TextBuffer::get_row() const{
    return row;
  }

  //EFFECTS:  Returns the column of the character at the current cursor.
  int TextBuffer::get_column() const{
    return column;
  }

  //EFFECTS:  Returns the index of the character at the current cursor
  //          with respect to the entire contents. If the cursor is at
  //          the past-the-end position, returns size() as the index.
  int TextBuffer::get_index() const{
    return index;
  }

  //EFFECTS:  Returns the number of characters in the buffer.
  int TextBuffer::size() const{
    return data.size();
  }

  //EFFECTS:  Returns the contents of the text buffer as a string.
  //HINT: Implement this using the string constructor that takes a
  //      begin and end iterator. You may use this implementation:
  //        return std::string(data.begin(), data.end());
  std::string TextBuffer::stringify() const{
    return std::string(data.begin(), data.end());
  }

  //EFFECTS: Computes the column of the cursor within the current row.
  //NOTE: This does not assume that the "column" member variable has
  //      a correct value (i.e. the row/column INVARIANT can be broken).
  int TextBuffer::compute_column() const{
    // know where cursor is
    // col = where u r in the list
  int count = 0;
  Iterator copy = cursor;
  for (Iterator i = copy; i != data.begin() && *(--i) != '\n'; ){
    count++;
  }
  return count;

  }