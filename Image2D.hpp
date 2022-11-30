// file Image2D.hpp
#ifndef _IMAGE2D_HPP_
#define _IMAGE2D_HPP_
#include <vector>

/// Classe générique pour représenter des images 2D.
template <typename TValue>
class Image2D
{
public:
  typedef Image2D<TValue> Self;         // le type de *this
  typedef TValue Value;                 // le type pour la valeur des pixels
  typedef std::vector<Value> Container; // le type pour stocker les valeurs des pixels de l'image.

  // Constructeur par défaut
  Image2D();
  // Constructeur avec taille w x h. Remplit tout avec la valeur g
  // (par défaut celle donnée par le constructeur par défaut).
  Image2D(int w, int h, Value g = Value())
  {
    m_width = w;
    m_height = h;
    // resize remplit automatiquement de 0
    m_data.resize(w * h, g);
  }

  // Remplit l'image avec la valeur \a g.
  void fill(Value g)
  {
    m_data.assign(m_width * m_height, g);
  }

  /// @return la largeur de l'image.
  int w() const
  {
    return m_width;
  }
  /// @return la hauteur de l'image.
  int h() const
  {
    return m_height;
  }

  /// Accesseur read-only à la valeur d'un pixel.
  /// @return la valeur du pixel(i,j)
  Value at(int i, int j) const
  {
    return m_data[i + j * m_width];
  }

  /// Accesseur read-write à la valeur d'un pixel.
  /// @return une référence à la valeur du pixel(i,j)
  Value &at(int i, int j)
  {
    return m_data[i + j * m_width];
  }
  /// Un itérateur (non-constant) simple sur l'image.
  struct Iterator : public Container::iterator
  {
    Iterator(Self &image, int x, int y)
        : Container::iterator(image.m_data.begin() + image.index(x, y))
    {
    }
  };

  /// @return un itérateur pointant sur le début de l'image
  Iterator begin() { return start(0, 0); }
  /// @return un itérateur pointant après la fin de l'image
  Iterator end() { return start(0, h()); }
  /// @return un itérateur pointant sur le pixel (x,y).
  Iterator start(int x, int y) { return Iterator(*this, x, y); }

  // ---------------------/
  struct ConstIterator : public Container::iterator
  {
    ConstIterator(Self image, int x, int y)
        : Container::iterator(image.m_data.begin() + image.index(x, y))
    {
    }
  };

  //create cbegin
  ConstIterator cbegin() const { return cstart(0, 0); }
  //create cend
  ConstIterator cend() const { return cstart(0, h()); }
  //create cstart
  ConstIterator cstart(int x, int y) const { return ConstIterator(*this, x, y); }

private:
  Container m_data; // mes données; évitera de faire les allocations dynamiques
  int m_width;      // ma largeur
  int m_height;     // ma hauteur

  /// @return l'index du pixel (x,y) dans le tableau \red m_data.
  int index(int i, int j) const
  {
    return i + j * m_width;
  }
};
#endif // _IMAGE2D_HPP_