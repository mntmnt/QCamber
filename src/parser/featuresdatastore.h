/**
 * @file   featuresdatastore.h
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

#ifndef __FEATURES_DATASTORE_H__
#define __FEATURES_DATASTORE_H__

#include <QList>
#include <QMap>
#include <QString>
#include <QStringList>

#include "datastore.h"
#include "structuredtextdatastore.h"
#include "record.h"

class FeaturesDataStore: public DataStore {
public:
  FeaturesDataStore();
  virtual ~FeaturesDataStore();

  typedef QMap<int, QString> IDMapType;
  typedef QMap<QString, int> CountMapType;

  void setJobName(const QString& name);
  void setStepName(const QString& name);
  void setLayerName(const QString& name);

  void putAttrlistItem(const QString& key, const QString& value);
  void putSymbolName(int id, const QString& name);
  void putAttribName(int id, const QString& name);
  void putAttribText(int id, const QString& text);
  void putLine(LineRecord* rec);
  void putPad(PadRecord* rec);
  void putArc(ArcRecord* rec);
  void putText(TextRecord* rec);
  void putBarcode(BarcodeRecord* rec);
  void putSurfaceRecord(SurfaceRecord* rec);

  QString jobName() const { return m_jobName; }
  QString stepName() const { return m_stepName; }
  QString layerName() const { return m_layerName; }
  QString attrlist(QString name) { return m_attrlist[name]; }

  const IDMapType& symbolNameMap() const { return m_symbolNameMap; }
  const IDMapType& attribNameMap() const { return m_attribNameMap; }
  const IDMapType& attribTextMap() const { return m_attribTextMap; }
  const QList<Record*> & records() const { return m_records; }

  const CountMapType& posLineCountMap() const { return m_posLineCountMap; }
  const CountMapType& posPadCountMap() const { return m_posPadCountMap; }
  const CountMapType& posArcCountMap() const { return m_posArcCountMap; }
  int posSurfaceCount() const { return m_posSurfaceCount; }
  int posTextCount() const { return m_posTextCount; }
  int posBarcodeCount() const { return m_posBarcodeCount; }

  const CountMapType& negLineCountMap() const { return m_negLineCountMap; }
  const CountMapType& negPadCountMap() const { return m_negPadCountMap; }
  const CountMapType& negArcCountMap() const { return m_negArcCountMap; }

  int negSurfaceCount() const { return m_negSurfaceCount; }
  int negTextCount() const { return m_negTextCount; }
  int negBarcodeCount() const { return m_negBarcodeCount; }

  void dump() override;

private:
  QString m_jobName;
  QString m_stepName;
  QString m_layerName;

  QMap<QString, QString> m_attrlist;
  IDMapType m_symbolNameMap;
  IDMapType m_attribNameMap;
  IDMapType m_attribTextMap;

  CountMapType m_posLineCountMap;
  CountMapType m_posPadCountMap;
  CountMapType m_posArcCountMap;
  int m_posSurfaceCount;
  int m_posTextCount;
  int m_posBarcodeCount;

  CountMapType m_negLineCountMap;
  CountMapType m_negPadCountMap;
  CountMapType m_negArcCountMap;
  int m_negSurfaceCount;
  int m_negTextCount;
  int m_negBarcodeCount;

  QList<Record*> m_records;
};

#endif /* __FEATURES_DATASTORE_H__ */
