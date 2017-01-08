#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Message.h"
#include "UseMessage.h"

class MockMessage : public Message
{  
public:  
    MOCK_METHOD0(getMessage, std::string());  
};  



static void test(){
	std::string value = "Hello World!";
	MockMessage message;
	EXPECT_CALL(message, getMessage()).Times(1).
			WillOnce(::testing::Return(value));
	std::string returnValue = message.getMessage();
	std::cout << "Returned Value: " << returnValue << std::endl;
}

void test2(){

    MockMessage message;  
    std::string msg = "Hello World";  
    EXPECT_CALL(message, getMessage()).WillRepeatedly(::testing::Return(::testing::ByRef(msg)));  
  
    UseMessage usemsg;  
    EXPECT_EQ("Hello World", usemsg.getMessage(&message));  
    EXPECT_EQ("Hello World", usemsg.getMessage(&message));  
    EXPECT_EQ("Hello World", usemsg.getMessage(&message));  
}

int main(int argc, char * argv[]){
	::testing::InitGoogleMock(&argc, argv);

    test();

    test2();

	return 0;
}
