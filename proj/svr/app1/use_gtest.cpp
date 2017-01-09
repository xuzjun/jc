#include "gtest/gtest.h"
#include <memory>


class _TC{
public:
    _TC(int id):_id(id){printf("constructor: %d\n", _id);}
    ~_TC(){printf("destructor: %d\n", _id);}
private:
    int _id;
};
TEST(SharedPtrTest, create){
    auto ps = std::make_shared<_TC>(1);
    ASSERT_TRUE(ps.get() != NULL);

    std::shared_ptr<_TC> ps2(new _TC(2));
    ASSERT_TRUE(ps2.get() != NULL);
}
TEST(SharedPtrTest, reset){
    auto ps = std::make_shared<_TC>(1);
    ASSERT_TRUE(ps.get() != NULL);
    ps.reset();
    ASSERT_TRUE(ps.get() == NULL);
}

TEST(WeakPtrTest, create){
    auto sp = std::make_shared<_TC>(10);
    std::weak_ptr<_TC> w(sp);

    auto sp2 = w.lock();
    ASSERT_TRUE(sp == sp2);

    ASSERT_EQ(2, w.use_count());
    w.reset();
    ASSERT_EQ(0, w.use_count());
}

int main(int argc, char * argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


