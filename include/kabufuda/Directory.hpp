#pragma once

#include <array>
#include <cstdint>
#include "kabufuda/File.hpp"

namespace kabufuda {
class Directory {
  friend class Card;
#pragma pack(push, 4)
  union {
    struct {
      std::array<File, MaxFiles> m_files;
      std::array<uint8_t, 0x3a> padding;
      uint16_t m_updateCounter;
      uint16_t m_checksum;
      uint16_t m_checksumInv;
    };
    std::array<uint8_t, BlockSize> raw;
  };
#pragma pack(pop)

  void swapEndian();
  void updateChecksum();
  bool valid() const;

public:
  Directory();
  Directory(uint8_t data[BlockSize]);
  ~Directory() = default;

  bool hasFreeFile() const;
  int32_t numFreeFiles() const;
  File* getFirstFreeFile(const char* game, const char* maker, const char* filename);
  File* getFirstNonFreeFile(uint32_t start, const char* game, const char* maker);
  File* getFile(const char* game, const char* maker, const char* filename);
  File* getFile(uint32_t idx);
  int32_t indexForFile(File* f);
};
} // namespace kabufuda
