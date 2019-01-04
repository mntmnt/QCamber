/**
 * @file   structuredtextdatastore.cpp
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

#include "structuredtextdatastore.h"

#include <cstdio>
#include <utility>
#include <iostream>

using std::cout;
using std::endl;

int StructuredTextDataStore::dumpIndent = 0;

StructuredTextDataStore::StructuredTextDataStore()
{
  m_mode = KEY_VALUE;
  m_currentBlock = nullptr;
}

void StructuredTextDataStore::put(string key, string value)
{
  switch (m_mode) {
  case KEY_VALUE:
    m_valueData[key] = value;
    break;
  case BLOCK:
    m_currentBlock->put(key, value);
    break;
  }
}

void StructuredTextDataStore::newElement(string name)
{
  if (m_currentBlock != nullptr) { // nested block
    m_currentBlock->newElement(name);
  } else {
    m_mode = BLOCK;
    m_currentElementName = name;
    m_currentBlock = new StructuredTextDataStore;
  }
}

bool StructuredTextDataStore::commitElement(void)
{
  if (!m_currentBlock) {
    return false;
  }

  if (m_currentBlock != nullptr) {
    if (!m_currentBlock->commitElement()) {
      m_mode = KEY_VALUE;
      m_blockData.insert(std::make_pair(m_currentElementName, m_currentBlock));
      m_currentBlock = nullptr;
      return true;
    }
  }
  return true;
}

string StructuredTextDataStore::get(string key)
{
  if (m_valueData.find(key) != m_valueData.end()) {
    return m_valueData[key];
  }
  throw InvalidKeyException(key.c_str());
}

StructuredTextDataStore::BlockIterPair
StructuredTextDataStore::getBlocksByKey(string key)
{
  return m_blockData.equal_range(key);
}

const StructuredTextDataStore::ValueType&
StructuredTextDataStore::getValueData(void) const
{
  return m_valueData;
}

void StructuredTextDataStore::dump(void)
{
  for (ValueType::const_iterator iter = m_valueData.begin();
      iter != m_valueData.end(); ++iter) {
    cout << string(dumpIndent * 2, ' ');
    cout << iter->first << " = " << iter->second << endl;
  }

  dumpIndent += 1;
  for (BlockType::const_iterator iter = m_blockData.begin();
      iter != m_blockData.end(); ++iter) {
    cout << string(dumpIndent * 2 - 2, ' ');
    cout << iter->first << " {" << endl;
    iter->second->dump();
    cout << string(dumpIndent * 2 - 2, ' ');
    cout << "}" << endl;
  }
  dumpIndent -= 1;
}

