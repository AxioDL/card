#pragma once

#include <array>
#include <cstdint>
#include "kabufuda/Constants.hpp"

namespace kabufuda {
class File {
  friend class IFileHandle;
  friend class Directory;
  friend class Card;
#pragma pack(push, 4)
  using RawData = std::array<uint8_t, 0x40>;
  union {
    struct {
      uint8_t m_game[4];
      uint8_t m_maker[2];
      uint8_t m_reserved;
      uint8_t m_bannerFlags;
#if __GNUC__ && !__clang__
      __attribute__((nonstring))
#endif
      char m_filename[0x20];
      uint32_t m_modifiedTime;
      uint32_t m_iconAddress;
      uint16_t m_iconFmt;
      uint16_t m_animSpeed;
      EPermissions m_permissions;
      int8_t m_copyCounter;
      uint16_t m_firstBlock;
      uint16_t m_blockCount;
      uint16_t m_reserved2;
      uint32_t m_commentAddr;
    };
    RawData raw;
  };
#pragma pack(pop)
  void swapEndian();

public:
  File();
  explicit File(const RawData& rawData);
  explicit File(const char* filename);
  ~File() = default;
};
} // namespace kabufuda
