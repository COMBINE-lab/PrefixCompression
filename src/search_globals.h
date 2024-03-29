/*
 * Copyright 2011, Ben Langmead <langmea@cs.jhu.edu>
 *
 * This file is part of Bowtie 2.
 *
 * Bowtie 2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Bowtie 2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Bowtie 2.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SEARCH_GLOBALS_H_
#define SEARCH_GLOBALS_H_

#include <stdint.h>
namespace prefixMatching{

// declared in ebwt_search.cpp
extern bool     gColor;

extern int      gVerbose;
extern int      gQuiet;
extern int      gTrim5;
extern int      gTrim3;

}//namespace prefixMatching
#endif /* SEARCH_GLOBALS_H_ */
