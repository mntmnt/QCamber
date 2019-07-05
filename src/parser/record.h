/**
 * @file   record.h
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

#ifndef __RECORD_H__
#define __RECORD_H__

#include <QGraphicsScene>
#include <QMap>
#include <QPainterPath>
#include <QString>
#include <QStringList>

#include "symbol.h"

class Features;
class DataStore;
class FeaturesDataStore;
class FontDataStore;
class NotesDataStore;

struct Record {
  Record(DataStore* _ds, const AttribData& attr): ds(_ds), attrib(attr) {}
  virtual ~Record() { }
  virtual Symbol* createSymbol() const = 0;

  DataStore* ds;
  AttribData attrib;
};


struct LineRecord: public Record {
  LineRecord(FeaturesDataStore* ds, const QStringList& param,
      const AttribData& attr);
  Symbol* createSymbol() const override;

  qreal xs, ys;
  qreal xe, ye;
  int sym_num;
  Polarity polarity;
  int dcode;
};

struct PadRecord: public Record {
  PadRecord(FeaturesDataStore* ds, const QStringList& param,
      const AttribData& attr);
  Symbol* createSymbol() const override;

  qreal x, y;
  int sym_num;
  Polarity polarity;
  int dcode;
  Orient orient;
  QString sym_name;
};

struct ArcRecord: public Record {
  ArcRecord(FeaturesDataStore* ds, const QStringList& param,
      const AttribData& attr);
  Symbol* createSymbol() const override;

  qreal xs, ys;
  qreal xe, ye;
  qreal xc, yc;
  int sym_num;
  Polarity polarity;
  int dcode;
  bool cw;
};

struct TextRecord: public Record {
  TextRecord(FeaturesDataStore* ds, const QStringList& param,
      const AttribData& attr);
  Symbol* createSymbol() const override;

  void setTransform(Symbol* symbol) const;
  virtual QString dynamicText(QString);

  qreal x, y;
  QString font;
  Polarity polarity;
  Orient orient;
  qreal xsize, ysize;
  qreal width_factor;
  QString text;
  int version;
};

struct BarcodeRecord: public TextRecord {
  typedef enum { T = 0, B } AstrPos;

  BarcodeRecord(FeaturesDataStore* ds, const QStringList& param,
      const AttribData& attr);
  Symbol* createSymbol() const override;

  QString barcode;
  QString e;
  qreal w, h;
  bool fasc;
  bool cs;
  bool bg;
  bool astr;
  AstrPos astr_pos;
};

struct SurfaceOperation {
  typedef enum { SEGMENT = 0, CURVE } OpType;

  OpType type;
  qreal x, y;
  qreal xe, ye;
  qreal xc, yc;
  bool cw;
};

struct PolygonRecord {
  typedef enum { I = 0, H } PolyType;

  PolygonRecord(const QStringList& param);
  virtual ~PolygonRecord();
  virtual QPainterPath painterPath();

  qreal xbs, ybs;
  PolyType poly_type;
  QList<SurfaceOperation*> operations;
};

struct SurfaceRecord: public Record {
  SurfaceRecord(FeaturesDataStore* ds, const QStringList& param,
      const AttribData& attr);
  ~SurfaceRecord();
  Symbol* createSymbol() const override;

  Polarity polarity;
  int dcode;
  QList<PolygonRecord*> polygons;
  PolygonRecord* currentRecord;
};

struct CharLineRecord {
  typedef enum { R = 0, S } ShapeType;

  CharLineRecord(const QStringList& param);
  QPainterPath painterPath(qreal width_factor);

  qreal xs, ys;
  qreal xe, ye;
  Polarity polarity;
  ShapeType shape;
  qreal width;
};

struct CharRecord {
  CharRecord(FontDataStore* ds, const QStringList& param);
  virtual ~CharRecord();

  QPainterPath painterPath(qreal width_factor);

  FontDataStore* ds;
  char tchar;
  QList<CharLineRecord*> lines;
};

struct NoteRecord: public Record {
  NoteRecord(NotesDataStore* ds, const QStringList& param);
  Symbol* createSymbol() const override;

  int timestamp;
  QString user;
  qreal x, y;
  QString text;
};

#endif /* __RECORD_H__ */
