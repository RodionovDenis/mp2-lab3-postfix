#include "postfix.h"
#include "postfix.cpp"
#include <gtest.h>

TEST(TPostfix, can_create_postfix)
{
	ASSERT_NO_THROW(TPostfix p("0"));
}
TEST(TPostfix, can_change_infix)
{
	TPostfix p("a+b*c");
	p.ChangeInfix("a+0.5-1");
	EXPECT_EQ("a+0.5-1", p.GetInfix());
}
TEST(TPostfix, can_not_start_infix_the_operation)
{
	TPostfix p("+a+1");
	EXPECT_EQ(false, p.IsCorrect());
}
TEST(TPostfix, can_not_finish_infix_the_operation)
{
	TPostfix p("a+1+");
	EXPECT_EQ(false, p.IsCorrect());
}
TEST(TPostfix, infix_has_not_two_operation_in_a_row)
{
	TPostfix p("a+*1");
	EXPECT_EQ(false, p.IsCorrect());
}
TEST(TPostfix, parentheses_is_not_correct)
{
	TPostfix p("(a+1))");
	EXPECT_EQ(false, p.IsCorrect());
}
TEST(TPostfix, parentheses_is_correct)
{
	TPostfix p("(a+1)*(b+1)");
	EXPECT_EQ(false, p.IsCorrect());
}
TEST(TPostfix, transformation_infix_in_postfix_is_true)
{
	TPostfix p("(a+1)*(b+1)");
	p.ToPostfix();
	EXPECT_EQ("a 1 + b 1 + *", p.GetPostfix());
}
TEST(TPostfix, can_use_long_variables)
{
	TPostfix p("(alpha+1)*(betta+1)");
	p.ToPostfix();
	EXPECT_EQ("alpha 1 + betta 1 + *", p.GetPostfix());
}
TEST(TPostfix,can_calculate_expression)
{
	TPostfix p("(5+1)*(10+1)");
	p.ToPostfix();
	p.ReadArguments();
	EXPECT_EQ(66, p.Calculate());
}