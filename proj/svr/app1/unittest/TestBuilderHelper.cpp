#include "Builder.h"
#include "gtest/gtest.h"

#include <string>
#include "TestCaseHelper.h"


class BuilderTarget {
public:
    typedef BuilderPtr<BuilderTarget> ptrBuilder;
    typedef BuilderSptr<BuilderTarget> sptrBuilder;
    typedef BuilderSptrSptr<BuilderTarget> sptrBuilderSptr;
    BuilderTarget(){}
    BuilderTarget(const _Base * c){printf("const _Base *\n");}
    BuilderTarget(_Base * c) {printf("_Base *\n");}

    BuilderTarget(const _Base & b){printf("const _Base &\n");}
    BuilderTarget(_Base & c){printf("_Base & \n");}

    BuilderTarget(int * p){};
    BuilderTarget(const char * ptr){}
    BuilderTarget(std::string ptr){}
    BuilderTarget(const char * ptr, int ptr2){}
    BuilderTarget(const char * ptr, int ptr2, double ptr3){}
    BuilderTarget(const char * ptr, int ptr2, double ptr3, float ptr4){}
    ~BuilderTarget(){}
};

TEST(BuilderPtrTest, use){
    {
        auto p = BuilderTarget::ptrBuilder::make();
        delete p;
        ASSERT_TRUE(BuilderTarget::sptrBuilder::make());
    }
    {
        auto p = BuilderTarget::ptrBuilder::make("abc");
        delete p;
        ASSERT_TRUE(BuilderTarget::sptrBuilder::make("abc"));
    }
    {
        auto p = BuilderTarget::ptrBuilder::make("abc", 0);
        delete p;
        ASSERT_TRUE(BuilderTarget::sptrBuilder::make("abc", 0));
    }
    {
        auto p = BuilderTarget::ptrBuilder::make("abc", 0, 0.2);
        delete p;
        ASSERT_TRUE(BuilderTarget::sptrBuilder::make("abc", 0, 0.2));
    }
    {
        auto p = BuilderTarget::ptrBuilder::make("abc", 0, 0.2, (float)0.2f);
        delete p;
        ASSERT_TRUE(BuilderTarget::sptrBuilder::make("abc", 0, 0.2, (float)0.2f));
    }
}

TEST(BuilderPtrTest, use_class){
    const _Base * cpBase = new _Base();
    {
        auto p = BuilderTarget::ptrBuilder::make(cpBase);//for BuilderTarget(const _Base *)
        delete p;
    }
    {
        auto p = BuilderTarget::ptrBuilder::make(new _Base());//for BuilderTarget(_Base *)
        delete p;
    }
    {
        auto p = BuilderTarget::ptrBuilder::make(_Base()); //for BuilderTarget(const _Base &)
        delete p;
    }
    _Base b;
    {
        auto p = new BuilderTarget(b); //for BuilderTarget(_Base &)
        delete p;
    }
    {
        auto p = BuilderTarget::ptrBuilder::make(b); //for BuilderTarget(_Base &)
        delete p;
    }
}
TEST(BuilderSptrTest, use){
    const _Base * cpBase = new _Base();
    ASSERT_TRUE(BuilderTarget::sptrBuilder::make(cpBase));//for BuilderTarget(const _Base *)

    ASSERT_TRUE(BuilderTarget::sptrBuilder::make(new _Base()));//for BuilderTarget(_Base *)

    ASSERT_TRUE(BuilderTarget::sptrBuilder::make(_Base())); //for BuilderTarget(const _Base &)
    _Base b;
    ASSERT_TRUE(BuilderTarget::sptrBuilder::make(b)); //for BuilderTarget(_Base &)
}

TEST(BuilderSptrSptrTest, use){

    ASSERT_TRUE(BuilderTarget::sptrBuilderSptr::make(std::make_shared<int>(5)));

    std::shared_ptr<int> spint(new int(5));
    ASSERT_TRUE(BuilderTarget::sptrBuilderSptr::make(spint));

    std::shared_ptr<_Base> spbase(new _Base());
    ASSERT_TRUE(BuilderTarget::sptrBuilderSptr::make(spbase));
}

TEST(StdMakeSharedTest, use){
    ASSERT_TRUE(std::make_shared<BuilderTarget>(_Base())); //BuilderTarget(const _Base &)
    _Base b;
    ASSERT_TRUE(std::make_shared<BuilderTarget>(b));  // BuilderTarget(_Base &)
}
