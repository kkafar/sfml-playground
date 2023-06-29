#ifndef __PIECE_VIEW_REGISTRY_HPP__
#define __PIECE_VIEW_REGISTRY_HPP__

#include <cstdint>
#include <functional>
#include <optional>
#include <unordered_map>
#include "View/PieceView.hpp"

/**
 * Registry does own the views
 */
class PieceViewRegistry {
public:
  using Tag = int32_t;

  void insert(const Tag tag, const PieceView &&view);
  std::optional<PieceView> remove(const Tag tag);
  std::optional<std::reference_wrapper<const PieceView>> viewForTag(const Tag tag);

private:
  std::unordered_map<Tag, PieceView> m_registry;

  using Iterator = decltype(m_registry)::iterator;
};

#endif // !__PIECE_VIEW_REGISTRY_HPP__
