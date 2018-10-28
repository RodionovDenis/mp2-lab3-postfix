#include "stack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}
TEST(TStack, stack_size_check)
{
	ASSERT_ANY_THROW(TStack<int> st(-1));
	ASSERT_ANY_THROW(TStack<int> st(MaxStackSize + 1));
}
TEST(TStack, two_different_stacks_have_different_memories)
{
	TStack<int> s1(2), s2(3);
	EXPECT_NE(&s1, &s2);
}
TEST(TStack, check_stack_for_empty)
{
	TStack<int> s1(5);
	EXPECT_EQ(true, s1.IsEmpty());
}
TEST(TStack, check_stack_for_full)
{
	TStack<int> s1(5);
	for (int i = 0; i < 5; i++)
		s1.push(i);
	EXPECT_EQ(true, s1.IsFull());
}
TEST(TStack, can_clear_stack)
{
	TStack<int> s1(5);
	for (int i = 0; i < 5; i++)
		s1.push(i);
	s1.clear();
	EXPECT_EQ(true, s1.IsEmpty());
}
TEST(TStack, can_erase_last_element_in_stack)
{
	TStack<int> s1(5);
	for (int i = 0; i < 5; i++)
		s1.push(i);
	s1.erase();
	EXPECT_EQ(false, s1.IsFull());
}
TEST(TStack, can_pop_element_in_stack)
{
	TStack<int> s1(5);
	for (int i = 0; i < 5; i++)
		s1.push(i);
	EXPECT_EQ(4, s1.pop());
	EXPECT_EQ(false, s1.IsFull());
}
TEST(TStack,can_view_last_element_in_stack_without_delete_him)
{
	TStack<int> s1(5);
	for (int i = 0; i < 5; i++)
		s1.push(i);
	EXPECT_EQ(4, s1.pop_nd());
	EXPECT_EQ(true, s1.IsFull());
}
TEST(TStack,can_push_element_in_stack)
{
	TStack<int> s1(5);
	s1.push(1);
	EXPECT_EQ(1, s1.pop_nd());
	EXPECT_EQ(false, s1.IsEmpty());
}
TEST(TStack,can_know_lenght_now )
{
	TStack<int>s1(5);
	s1.push(1);
	EXPECT_EQ(1, s1.lenght());
}