#include "PieceViewRegistry.hpp"
#include <functional>
#include <iterator>
#include <optional>


void PieceViewRegistry::insert(const Tag tag, const PieceView &&view) {
  m_registry.insert({tag, view});
}

std::optional<PieceView> PieceViewRegistry::remove(const Tag tag) {
  Iterator it = m_registry.find(tag);

  if (it != std::end(m_registry)) {
    PieceView return_value = std::move(it->second);
    m_registry.erase(it);
    return std::make_optional(return_value);
  }
  return std::nullopt;
}

std::optional<std::reference_wrapper<const PieceView>> PieceViewRegistry::viewForTag(const Tag tag) {
  Iterator it = m_registry.find(tag);
  if (it != std::end(m_registry)) {
    return std::make_optional(std::cref(it->second));
  }
  return std::nullopt;
}
