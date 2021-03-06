/**
*    Copyright (C) 2013 Tokutek Inc.
*
*    This program is free software: you can redistribute it and/or  modify
*    it under the terms of the GNU Affero General Public License, version 3,
*    as published by the Free Software Foundation.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU Affero General Public License for more details.
*
*    You should have received a copy of the GNU Affero General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "mongo/pch.h"

#include "mongo/util/assert_util.h"

namespace mongo {

class RetryWithWriteLock : public DBException {
  public:
    RetryWithWriteLock() : DBException("Need to be write locked for this operation", 0) {}
    RetryWithWriteLock(const string &s) : DBException("Need to be write locked for this operation: " + s, 0) {}
};

} // namespace mongo
