/**
 * @file   ellipsesymbol.h
 * @author Wei-Ning Huang (AZ) <aitjcize@gmail.com>
 *
 * Copyright (C) 2012 - 2014 Wei-Ning Huang (AZ) <aitjcize@gmail.com>
 * All Rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __ELLIPSESYMBOL_H__
#define __ELLIPSESYMBOL_H__

#include "symbol.h"

class EllipseSymbol: public Symbol {
public:

  EllipseSymbol(const QString& def, const Polarity& polarity,
      const AttribData& attrib);

  QPainterPath painterPath() override;

protected:

private:
  QString m_def;
  qreal m_w;
  qreal m_h;
};

#endif /* __ELLIPSESYMBOL_H__ */
