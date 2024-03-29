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

#ifndef QUAL_H_
#define QUAL_H_

#include <stdexcept>
#include "search_globals.h"
#include "sstring.h"

namespace prefixMatching{

extern unsigned char qualRounds[];
extern unsigned char solToPhred[];

/// Translate a Phred-encoded ASCII character into a Phred quality
static inline UINT8 phredcToPhredq(char c) {
    return ((UINT8)c >= 33 ? ((UINT8)c - 33) : 0);
}

/**
 * Convert a Solexa-scaled quality value into a Phred-scale quality
 * value.
 *
 * p = probability that base is miscalled
 * Qphred = -10 * log10 (p)
 * Qsolexa = -10 * log10 (p / (1 - p))
 * See: http://en.wikipedia.org/wiki/FASTQ_format
 *
 */
static inline UINT8 solexaToPhred(int sol) {
	assert_lt(sol, 256);
	if(sol < -10) return 0;
	return solToPhred[sol+10];
}

class SimplePhredPenalty {
public:
    static UINT8 mmPenalty (UINT8 qual) {
		return qual;
	}
    static UINT8 delPenalty(UINT8 qual) {
		return qual;
	}
    static UINT8 insPenalty(UINT8 qual_left, UINT8 qual_right) {
		return std::max(qual_left, qual_right);
	}
};

class MaqPhredPenalty {
public:
    static UINT8 mmPenalty (UINT8 qual) {
		return qualRounds[qual];
	}
    static UINT8 delPenalty(UINT8 qual) {
		return qualRounds[qual];
	}
    static UINT8 insPenalty(UINT8 qual_left, UINT8 qual_right) {
		return qualRounds[std::max(qual_left, qual_right)];
	}
};

static inline UINT8 mmPenalty(bool maq, UINT8 qual) {
	if(maq) {
		return MaqPhredPenalty::mmPenalty(qual);
	} else {
		return SimplePhredPenalty::mmPenalty(qual);
	}
}

static inline UINT8 delPenalty(bool maq, UINT8 qual) {
	if(maq) {
		return MaqPhredPenalty::delPenalty(qual);
	} else {
		return SimplePhredPenalty::delPenalty(qual);
	}
}

static inline UINT8 insPenalty(bool maq, UINT8 qual_left, UINT8 qual_right) {
	if(maq) {
		return MaqPhredPenalty::insPenalty(qual_left, qual_right);
	} else {
		return SimplePhredPenalty::insPenalty(qual_left, qual_right);
	}
}

/**
 * Take an ASCII-encoded quality value and convert it to a Phred33
 * ASCII char.
 */
inline static char charToPhred33(char c, bool solQuals, bool phred64Quals) {
	using namespace std;
	if(c == ' ') {
		std::cerr << "Saw a space but expected an ASCII-encoded quality value." << endl
		          << "Are quality values formatted as integers?  If so, try --integer-quals." << endl;
		throw 1;
	}
	if (solQuals) {
		// Convert solexa-scaled chars to phred
		// http://maq.sourceforge.net/fastq.shtml
		char cc = solexaToPhred((int)c - 64) + 33;
		if (cc < 33) {
			std::cerr << "Saw ASCII character "
			          << ((int)c)
			          << " but expected 64-based Solexa qual (converts to " << (int)cc << ")." << endl
			          << "Try not specifying --solexa-quals." << endl;
			throw 1;
		}
		c = cc;
	}
	else if(phred64Quals) {
		if (c < 64) {
			cerr << "Saw ASCII character "
			     << ((int)c)
			     << " but expected 64-based Phred qual." << endl
			     << "Try not specifying --solexa1.3-quals/--phred64-quals." << endl;
			throw 1;
		}
		// Convert to 33-based phred
		c -= (64-33);
	}
	else {
		// Keep the phred quality
		if (c < 33) {
			cerr << "Saw ASCII character "
			     << ((int)c)
			     << " but expected 33-based Phred qual." << endl;
			throw 1;
		}
	}
	return c;
}

/**
 * Take an integer quality value and convert it to a Phred33 ASCII
 * char.
 */
inline static char intToPhred33(int iQ, bool solQuals) {
	using namespace std;
	int pQ;
	if (solQuals) {
		// Convert from solexa quality to phred
		// quality and translate to ASCII
		// http://maq.sourceforge.net/qual.shtml
		pQ = solexaToPhred((int)iQ) + 33;
	} else {
		// Keep the phred quality and translate
		// to ASCII
		pQ = (iQ <= 93 ? iQ : 93) + 33;
	}
	if (pQ < 33) {
		cerr << "Saw negative Phred quality " << ((int)pQ-33) << "." << endl;
		throw 1;
	}
	assert_geq(pQ, 0);
	return (int)pQ;
}

inline static UINT8 roundPenalty(UINT8 p) {
    //if(gNoMaqRound) return p;
	return qualRounds[p];
}

/**
 * Fill the q[] array with the penalties that are determined by
 * subtracting the quality values of the alternate basecalls from
 * the quality of the primary basecall.
 */
inline static UINT8 penaltiesAt(size_t off, UINT8 *q,
                                  int alts,
                                  const BTString&    qual,
                                  const BTDnaString *altQry,
                                  const BTString    *altQual)
{
    UINT8 primQ = qual[off]; // qual of primary call
    UINT8 bestPenalty = roundPenalty(phredcToPhredq(primQ));
	// By default, any mismatch incurs a penalty equal to the quality
	// of the called base
	q[0] = q[1] = q[2] = q[3] = bestPenalty;
	for(int i = 0; i < alts; i++) {
        UINT8 altQ = altQual[i][off]; // qual of alt call
		if(altQ == 33) break; // no alt call
		assert_leq(altQ, primQ);
        UINT8 pen = roundPenalty(primQ - altQ);
		if(pen < bestPenalty) {
			bestPenalty = pen;
		}
		// Get the base
		int altC = (int)altQry[i][off];
		assert_lt(altC, 4);
		q[altC] = pen;
	}
	// Return the best penalty so that the caller can evaluate whether
	// any of the penalties are within-budget
	return bestPenalty;
}
/**
 * Fill the q[] array with the penalties that are determined by
 * subtracting the quality values of the alternate basecalls from
 * the quality of the primary basecall.
 */
inline static UINT8 loPenaltyAt(size_t off, int alts,
                                  const BTString&    qual,
                                  const BTString    *altQual)
{
    UINT8 primQ = qual[off]; // qual of primary call
    UINT8 bestPenalty = roundPenalty(phredcToPhredq(primQ));
	for(int i = 0; i < alts; i++) {
        UINT8 altQ = altQual[i][off]; // qual of alt call
		if(altQ == 33) break; // no more alt calls at this position
		assert_leq(altQ, primQ);
        UINT8 pen = roundPenalty(primQ - altQ);
		if(pen < bestPenalty) {
			bestPenalty = pen;
		}
	}
	return bestPenalty;
}
} //namespace algn_ppbwt
#endif /*QUAL_H_*/
