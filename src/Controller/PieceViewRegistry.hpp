#ifndef __PIECE_VIEW_REGISTRY_HPP__
#define __PIECE_VIEW_REGISTRY_HPP__

#include <cstdint>
#include <functional>
#include <optional>
#include <unordered_map>
#include <vector>
#include "SFML/Config.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "View/PieceView.hpp"

/**
 * Registry does own the views
 */
class PieceViewRegistry : public sf::Drawable {
public:
  using Tag = sf::Uint32;
  using PieceViewOpt = std::optional<PieceView>;
  using PieceViewRefOpt = std::optional<std::reference_wrapper<PieceView>>;
  using PieceViewConstRefOpt = std::optional<std::reference_wrapper<const PieceView>>;

  void insert(const Tag tag, const PieceView &&view);
  std::optional<PieceView> remove(const Tag tag);
  PieceViewRefOpt viewForTag(const Tag tag);

protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  std::vector<PieceViewOpt> m_registry{32};
};

#endif // !__PIECE_VIEW_REGISTRY_HPP__
