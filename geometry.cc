#include <cassert>
#include "geometry.h"

/*
 * Vector
 */

Vector::Vector(int32_t x, int32_t y)
   : _position(Position(x, y)) {}

int32_t Vector::x() const {
    return _position.x();
}

int32_t Vector::y() const {
    return _position.y();
}

bool Vector::operator==(const Vector& compared) const {
    return _position == compared._position;
}

Vector& Vector::operator+=(const Vector& reloc) {
    _position += reloc;
    return *this;
}

Vector Vector::reflection() const {
    return Vector(y(), x());
}

/*
 * Rectangle
 */

Rectangle::Rectangle(int32_t w, int32_t h)
    : _w(w), _h(h), _pos(Position::origin()) {
    assert(_w > 0);
    assert(_h > 0);
}

Rectangle::Rectangle(int32_t w, int32_t h, const Position& pos)
        : _w(w), _h(h), _pos(pos) {
    assert(_w > 0);
    assert(_h > 0);
}

bool Rectangle::operator==(const Rectangle& compared) const {
    return _w == compared._w &&
           _h == compared._h &&
           _pos == compared._pos;
}

int32_t Rectangle::width() const {
    return _w;
}

int32_t Rectangle::height() const {
    return _h;
}

Position Rectangle::pos() const {
    return _pos;
}

Rectangle Rectangle::reflection() const {
    return Rectangle(_h, _w, _pos.reflection());
}

Rectangle Rectangle::operator+=(const Vector& reloc) {
    _position += reloc;
    return *this;
}

int32_t Rectangle::area() const {
    return _w * _h;
}

//TODO 85 znaków, rozbić?
std::pair<Rectangle, Rectangle> Rectangle::split_horizontally(int32_t place) const {
    assert(place > 0 && place < _h);
    return std::pair<Rectangle, Rectangle>(
            Rectangle(_w, place, _pos),
            Rectangle(_w, _h - place, _pos + Vector(0, place)));
};

std::pair<Rectangle, Rectangle> Rectangle::split_vertically(int32_t place) const {
    assert(place > 0 && place < _w);
    return std::pair<Rectangle, Rectangle>(
            Rectangle(place, _h, _pos),
            Rectangle(_w - place, _h, _pos + Vector(place, 0)));
};

/*
 * Merges 2 rectangles, upper side of the first rectangle
 * must match lower side of the second rectangle
 */
Rectangle merge_horizontally(const Rectangle& rect1, const Rectangle& rect2) {
    assert(rect1.pos() + Vector(0, rect1.height()) == rect2.pos() &&
           rect1.width() == rect2.width());
    return Rectangle(
            rect1.width(), rect1.height() + rect2.height(), rect1.pos());
}

/*
 * Merges 2 rectangles, right side of the first rectangle
 * must match left side of the second rectangle
 */
Rectangle merge_vertically(const Rectangle& rect1, const Rectangle& rect2) {
    assert(rect1.pos() + Vector(rect1.width(), 0) == rect2.pos() &&
           rect1.height() == rect2.height());
    return Rectangle(
            rect1.width() + rect2.width, rect1.height(), rect1.pos());
}
