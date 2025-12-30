#pragma once
#include <EpdFontFamily.h>
#include <FS.h>

#include <list>
#include <memory>
#include <string>

#include "Block.h"

// represents a block of words in the html document
class TextBlock final : public Block {
 public:
  enum BLOCK_STYLE : uint8_t {
    JUSTIFIED = 0,
    LEFT_ALIGN = 1,
    CENTER_ALIGN = 2,
    RIGHT_ALIGN = 3,
  };

 private:
  std::list<std::string> words;
  std::list<uint16_t> wordXpos;
  std::list<EpdFontStyle> wordStyles;
  BLOCK_STYLE style;
  int8_t letterSpacing;  // Letter spacing adjustment in pixels (negative = compression)

 public:
  explicit TextBlock(std::list<std::string> words, std::list<uint16_t> word_xpos, std::list<EpdFontStyle> word_styles,
                     const BLOCK_STYLE style, const int8_t letter_spacing = 0)
      : words(std::move(words)), wordXpos(std::move(word_xpos)), wordStyles(std::move(word_styles)), style(style),
        letterSpacing(letter_spacing) {}
  ~TextBlock() override = default;
  void setStyle(const BLOCK_STYLE style) { this->style = style; }
  BLOCK_STYLE getStyle() const { return style; }
  int8_t getLetterSpacing() const { return letterSpacing; }
  bool isEmpty() override { return words.empty(); }
  void layout(GfxRenderer& renderer) override {};
  // given a renderer works out where to break the words into lines
  void render(const GfxRenderer& renderer, int fontId, int x, int y) const;
  BlockType getType() override { return TEXT_BLOCK; }
  bool serialize(File& file) const;
  static std::unique_ptr<TextBlock> deserialize(File& file);
};
