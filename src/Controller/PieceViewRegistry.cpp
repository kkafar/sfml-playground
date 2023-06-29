#include "PieceViewRegistry.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include <functional>
#include <iterator>
#include <optional>
#include <glog/logging.h>


void PieceViewRegistry::insert(const Tag tag, const PieceView &&view) {
  m_registry[tag] = view;
}

std::optional<PieceView> PieceViewRegistry::remove(const Tag tag) {
  if (m_registry[tag]) {
    PieceView return_value = std::move(m_registry[tag].value());
    m_registry[tag].reset();
    return std::make_optional(return_value);
  }
  return std::nullopt;
}

std::optional<std::reference_wrapper<PieceView>> PieceViewRegistry::viewForTag(const Tag tag) {
  if (m_registry[tag]) {
    LOG(INFO) << "Request for view for tag " << tag;
    return std::make_optional(std::ref(m_registry.at(tag).value()));
  }
  LOG(WARNING) << "Missed request for view for tag " << tag;
  return std::nullopt;
}

void PieceViewRegistry::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (const PieceViewOpt &pv : m_registry) {
    if (pv) {
      target.draw(pv.value());
    }
  }
}
