/**
 * @file   structuredtextdatastore.h
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

#ifndef __STRUCTURED_TEXT_DATASTORE_H__
#define __STRUCTURED_TEXT_DATASTORE_H__

#include <map>
#include <string>

#include "datastore.h"

using std::string;
using std::map;
using std::multimap;
using std::pair;

class StructuredTextDataStore: public DataStore {
public:
  class InvalidKeyException: public std::exception {
  public:
    InvalidKeyException(const char* msg): m_msg(msg) {}
    virtual const char* what() const throw() { return m_msg; }

  private:
    const char* m_msg;
  };

  typedef enum { KEY_VALUE = 0, BLOCK } PutMode;

  typedef map<string, string> ValueType;
  typedef multimap<string, StructuredTextDataStore*> BlockType;
  typedef BlockType::iterator BlockIter;
  typedef pair<BlockIter, BlockIter> BlockIterPair;

  StructuredTextDataStore();
  void newElement(string name);
  bool commitElement();

  string get(string key);
  BlockIterPair getBlocksByKey(string key);
  const ValueType& getValueData() const;

  void put(string key, string value);
  void dump() override;

  static int dumpIndent;

private:
  PutMode m_mode;
  ValueType m_valueData;
  BlockType m_blockData;
  StructuredTextDataStore* m_currentBlock;
  string m_currentElementName;
};

#endif /* __STRUCTURED_TEXT_DATASTORE_H__ */
