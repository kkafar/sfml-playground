#ifndef __PLAYER_PIECES_HPP__
#define __PLAYER_PIECES_HPP__

#include "PieceKind.hpp"
#include "PlayerKind.hpp"
#include "Resizable.hpp"
#include "SFML/Config.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "TextureStore.hpp"
#include <array>

class PlayerPieces : public sf::Drawable, public Resizable {
public:
  constexpr static sf::Uint32 PAWN_COUNT = 8;
  constexpr static sf::Uint32 BISHOP_COUNT = 2;
  constexpr static sf::Uint32 ROOK_COUNT = 2;
  constexpr static sf::Uint32 KNIGHT_COUNT = 2;
  constexpr static sf::Uint32 QUEEN_COUNT = 1;
  constexpr static sf::Uint32 KING_COUNT = 1;

  PlayerPieces(const PlayerKind player_kind, const sf::Uint32 tile_width_px,
               const sf::Uint32 tile_height_px,
               const TextureStore &texture_store)
      : m_player_kind(player_kind) {
    const sf::Texture &pawn_texture =
        texture_store.textureForPieceKind(PieceKind::Pawn);
    const sf::Texture &bishop_texture =
        texture_store.textureForPieceKind(PieceKind::Bishop);
    const sf::Texture &rook_texture =
        texture_store.textureForPieceKind(PieceKind::Rook);
    const sf::Texture &knight_texture =
        texture_store.textureForPieceKind(PieceKind::Knight);
    const sf::Texture &queen_texture =
        texture_store.textureForPieceKind(PieceKind::Queen);
    const sf::Texture &king_texture =
        texture_store.textureForPieceKind(PieceKind::King);

    for (sf::Uint32 i = 0; i < PAWN_COUNT; ++i) {
      m_pawns[i] = sf::Sprite(pawn_texture);
    }
    m_bishops[0] = sf::Sprite(bishop_texture);
    m_bishops[1] = sf::Sprite(bishop_texture);
    m_rooks[0] = sf::Sprite(rook_texture);
    m_rooks[1] = sf::Sprite(rook_texture);
    m_knights[0] = sf::Sprite(knight_texture);
    m_knights[1] = sf::Sprite(knight_texture);
    m_queen = sf::Sprite(queen_texture);
    m_king = sf::Sprite(king_texture);

    setInitialSpritePositions(tile_width_px, tile_height_px);
  }

  void resize(const sf::Uint32 width_px, const sf::Uint32 height_px) {
    setInitialSpritePositions(width_px / 8, height_px / 8);
  }

protected:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for (const auto &pawn : m_pawns) {
      target.draw(pawn);
    }
    target.draw(m_bishops[0]);
    target.draw(m_bishops[1]);
    target.draw(m_rooks[0]);
    target.draw(m_rooks[1]);
    target.draw(m_knights[0]);
    target.draw(m_knights[1]);
    target.draw(m_queen);
    target.draw(m_king);
  }

private:
  PlayerKind m_player_kind;
  std::array<sf::Sprite, PAWN_COUNT> m_pawns;
  std::array<sf::Sprite, BISHOP_COUNT> m_bishops;
  std::array<sf::Sprite, ROOK_COUNT> m_rooks;
  std::array<sf::Sprite, KNIGHT_COUNT> m_knights;
  sf::Sprite m_queen;
  sf::Sprite m_king;

  void setInitialSpritePositions(const sf::Uint32 tile_width_px,
                                 const sf::Uint32 tile_height_px) {
    int pawn_row_i;
    int figure_row_i;

    if (m_player_kind == PlayerKind::White) {
      pawn_row_i = 1;
      figure_row_i = 0;
    } else {
      pawn_row_i = 6;
      figure_row_i = 7;
    }

    placePawns(pawn_row_i, tile_width_px, tile_height_px);
    placeFigures(figure_row_i, tile_width_px, tile_height_px);
    scalePieces(tile_width_px, tile_height_px);
  }

  void placePawns(const int row, const sf::Uint32 tile_width_px,
                  const sf::Uint32 tile_height_px) {
    for (sf::Uint32 i = 0; i < 8; ++i) {
      sf::Sprite &pawn = m_pawns[i];
      pawn.setPosition(i * tile_width_px, row * tile_height_px);
    }
  }

  void placeFigures(const int row, const sf::Uint32 tile_width_px,
                    const sf::Uint32 tile_height_px) {
    sf::Uint32 row_offset = row * tile_height_px;
    m_rooks[0].setPosition(0 * tile_width_px, row_offset);
    m_knights[0].setPosition(1 * tile_width_px, row_offset);
    m_bishops[0].setPosition(2 * tile_width_px, row_offset);
    m_queen.setPosition(3 * tile_width_px, row_offset);
    m_king.setPosition(4 * tile_width_px, row_offset);
    m_bishops[1].setPosition(5 * tile_width_px, row_offset);
    m_knights[1].setPosition(6 * tile_width_px, row_offset);
    m_rooks[1].setPosition(7 * tile_width_px, row_offset);
  }

  void scalePieces(const sf::Uint32 tile_width_px, const sf::Uint32 tile_height_px) {
    float scale_x = static_cast<float>(tile_width_px) / m_pawns[0].getTexture()->getSize().x;
    float scale_y = static_cast<float>(tile_height_px) / m_pawns[0].getTexture()->getSize().y;
    for (sf::Uint32 i = 0; i < 8; ++i) {
      sf::Sprite &pawn = m_pawns[i];
      pawn.setScale(scale_x, scale_y);
    }

    scale_x = static_cast<float>(tile_width_px) / m_rooks[0].getTexture()->getSize().x;
    scale_y = static_cast<float>(tile_height_px) / m_rooks[0].getTexture()->getSize().y;
    m_rooks[0].setScale(scale_x, scale_y);
    m_rooks[1].setScale(scale_x, scale_y);

    scale_x = static_cast<float>(tile_width_px) / m_knights[0].getTexture()->getSize().x;
    scale_y = static_cast<float>(tile_height_px) / m_knights[0].getTexture()->getSize().y;
    m_knights[0].setScale(scale_x, scale_y);
    m_knights[1].setScale(scale_x, scale_y);

    scale_x = static_cast<float>(tile_width_px) / m_bishops[0].getTexture()->getSize().x;
    scale_y = static_cast<float>(tile_height_px) / m_bishops[0].getTexture()->getSize().y;
    m_bishops[0].setScale(scale_x, scale_y);
    m_bishops[1].setScale(scale_x, scale_y);

    scale_x = static_cast<float>(tile_width_px) / m_queen.getTexture()->getSize().x;
    scale_y = static_cast<float>(tile_height_px) / m_queen.getTexture()->getSize().y;
    m_queen.setScale(scale_x, scale_y);

    scale_x = static_cast<float>(tile_width_px) / m_king.getTexture()->getSize().x;
    scale_y = static_cast<float>(tile_height_px) / m_king.getTexture()->getSize().y;
    m_king.setScale(scale_x, scale_y);
  }
};

#endif // !__PLAYER_PIECES_HPP__
