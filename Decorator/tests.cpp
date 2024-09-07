#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

// Тесты для класса TextMessage
TEST(TextMessageTest, PrintLayer) {
    std::ostringstream oss;
    std::streambuf* original = std::cout.rdbuf(oss.rdbuf());

    TextMessage textMsg("Hello, World!");
    textMsg.PrintLayer();

    std::cout.rdbuf(original); // Восстанавливаем оригинальный буфер

    EXPECT_EQ(oss.str(), "Text Message : Hello, World!\n");
}

TEST(TextMessageTest, Serialize) {
    TextMessage textMsg("Hello, World!");
    EXPECT_EQ(textMsg.Serialize(), "Hello, World!");
}

// Тесты для класса ImageMessage
TEST(ImageMessageTest, PrintLayer) {
    std::ostringstream oss;
    std::streambuf* original = std::cout.rdbuf(oss.rdbuf());

    ImageMessage imageMsg("image.png");
    imageMsg.PrintLayer();

    std::cout.rdbuf(original); // Восстанавливаем оригинальный буфер

    EXPECT_EQ(oss.str(), "Image Message : image.png\n");
}

TEST(ImageMessageTest, Serialize) {
    ImageMessage imageMsg("image.png");
    EXPECT_EQ(imageMsg.Serialize(), "Binary Data Of image.png");
}

// Тесты для класса EncryptionMessageDecorator
TEST(EncryptionMessageDecoratorTest, PrintLayer) {
    std::ostringstream oss;
    std::streambuf* original = std::cout.rdbuf(oss.rdbuf());

    auto textMsg = std::make_unique<TextMessage>("Secret Message");
    EncryptionMessageDecorator encryptedMsg(std::move(textMsg));
    encryptedMsg.PrintLayer();

    std::cout.rdbuf(original); // Восстанавливаем оригинальный буфер

    EXPECT_EQ(oss.str(), "Text Message : Secret Message\nEncrypt Message\n");
}

TEST(EncryptionMessageDecoratorTest, Serialize) {
    auto textMsg = std::make_unique<TextMessage>("Secret Message");
    EncryptionMessageDecorator encryptedMsg(std::move(textMsg));

    std::string result = encryptedMsg.Serialize();
    EXPECT_EQ(result, "et MSGSecret aseM"); // Зависит от реализации ротации
}

// Тесты для класса CompressionMessageDecorator
TEST(CompressionMessageDecoratorTest, PrintLayer) {
    std::ostringstream oss;
    std::streambuf* original = std::cout.rdbuf(oss.rdbuf());

    auto textMsg = std::make_unique<TextMessage>("Hello World!");
    CompressionMessageDecorator compressedMsg(std::move(textMsg));
    compressedMsg.PrintLayer();
    std::cout.rdbuf(original); //Восстанавливаем оригинальный буфер

    EXPECT_EQ(oss.str(), "Text Message : Hello World!\nCompress Message\n");
}

TEST(CompressionMessageDecoratorTest, Serialize) {
    auto textMsg = std::make_unique<TextMessage>("aaaaaabbb");
    CompressionMessageDecorator compressedMsg(std::move(textMsg));

    std::string result = compressedMsg.Serialize();
    EXPECT_EQ(result, "ab"); // Зависит от реализации
}
int main() {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
