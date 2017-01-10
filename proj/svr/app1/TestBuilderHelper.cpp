#include "BuilderHelper.h"
#include "gtest/gtest.h"

#include <string>
#include "TestCaseHelper.h"


class FRunner {
public:
    typedef BuilderHelper<FRunner> Builder;
    FRunner(){}
    FRunner(const _Base * c){printf("const _Base *\n");}
    FRunner(_Base * c) {printf("_Base *\n");}

    FRunner(const _Base & b){printf("const _Base &\n");}
    FRunner(_Base & c){printf("_Base & \n");}

    FRunner(int * p){};
    FRunner(const char * ptr){}
    FRunner(std::string ptr){}
    FRunner(const char * ptr, int ptr2){}
    FRunner(const char * ptr, int ptr2, double ptr3){}
    FRunner(const char * ptr, int ptr2, double ptr3, float ptr4){}
    ~FRunner(){}
};

TEST(BuilderHelperTest, easy){
    ASSERT_TRUE(FRunner::Builder::make());

    ASSERT_TRUE(FRunner::Builder::make("abc"));

    ASSERT_TRUE(FRunner::Builder::make("abc", 0));

    ASSERT_TRUE(FRunner::Builder::make("abc", 0, 0.2));

    ASSERT_TRUE(FRunner::Builder::make("abc", 0, 0.2, (float)0.2f));
}

TEST(BuilderHelperTest, ref_ptr){
    const _Base * cpBase = new _Base();
    ASSERT_TRUE(FRunner::Builder::make(cpBase));//for FRunner(const _Base *)

    ASSERT_TRUE(FRunner::Builder::make(new _Base()));//for FRunner(_Base *)

    ASSERT_TRUE(FRunner::Builder::make(_Base())); //for FRunner(const _Base &)

    _Base b;
    ASSERT_TRUE(new FRunner(b)); //for FRunner(_Base &)

    ASSERT_TRUE(FRunner::Builder::make(b)); //for FRunner(_Base &)
}

TEST(BuilderHelperTest, makeShared){

    ASSERT_TRUE(FRunner::Builder::make_shared(std::make_shared<int>(5)));

    std::shared_ptr<int> spint(new int(5));
    ASSERT_TRUE(FRunner::Builder::make_shared(spint));

    std::shared_ptr<_Base> spbase(new _Base());
    ASSERT_TRUE(FRunner::Builder::make_shared(spbase));
}

TEST(BuilderHelperTest, std_make_shared){
    ASSERT_TRUE(std::make_shared<FRunner>(_Base())); //FRunner(const _Base &)

    _Base b;
    ASSERT_TRUE(std::make_shared<FRunner>(b));  // FRunner(_Base &)
}

