#include "TestCaseHelper.h"

#include <memory>
#include "gtest/gtest.h"

TEST(SharedPtrTest, create){
    auto ps = std::make_shared<_Sub>(1);
    ASSERT_TRUE(ps.get() != NULL);
    ASSERT_EQ(1, ps.use_count());

    std::shared_ptr<_Sub> ps2(new _Sub(2));
    ASSERT_TRUE(ps2.get() != NULL);
    ASSERT_EQ(1, ps2.use_count());
}

TEST(SharedPtrTest, reset){
    auto ps = std::make_shared<_Sub>(1);
    ASSERT_TRUE(ps.get() != NULL);
    ASSERT_EQ(1, ps.use_count());

    ps.reset();

    ASSERT_TRUE(ps.get() == NULL);
    ASSERT_EQ(0, ps.use_count());
}

TEST(WeakPtrTest, create){
    auto sp = std::make_shared<_Sub>(10);
    ASSERT_EQ(1, sp.use_count());
    ASSERT_TRUE(NULL != sp.get());

    std::weak_ptr<_Sub> w(sp);
    ASSERT_EQ(1, w.use_count());
    ASSERT_EQ(1, sp.use_count());

    auto sp2 = w.lock();
    ASSERT_TRUE(sp == sp2);
    ASSERT_EQ(2, w.use_count());
    ASSERT_EQ(2, sp.use_count());

    w.reset();
    ASSERT_EQ(0, w.use_count());
    ASSERT_EQ(2, sp.use_count());
}
