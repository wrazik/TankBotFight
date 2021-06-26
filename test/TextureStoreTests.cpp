#include <gtest/gtest.h>

#include <stdexcept>

#include "TextureStore.hpp"

struct TextureStoreTest : ::testing::Test {
  TextureStore mTextureStore;
};

TEST_F(TextureStoreTest, NonExistingSprite_ShouldThrowException) {
  EXPECT_THROW(mTextureStore.get_texture("not_existing"), std::runtime_error);
}

TEST_F(TextureStoreTest, GetSameTextureTwice_ShouldHaveTheSameAddress) {
  auto& first = mTextureStore.get_texture("tankBody_red.png");
  auto& second = mTextureStore.get_texture("tankBody_red.png");
  EXPECT_EQ(&first, &second);
}
