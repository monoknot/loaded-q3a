/**
 * @brief		Loaded Q3A
 * @author		Kevin Fell <kevin@kevin-fell.co.uk>
 * @link		http://www.kevin-fell.co.uk/
 * @copyright	(C) 1999-2012 Kevin Fell.
 * 
 * Loaded Q3A
 *
 * Copyright (C) 1999-2012 Kevin Fell
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
 */

#include "q_shared.h"
#include "bg_public.h"

/**********
 * LOCALS *
 **********/
static uint s_uParseOpt				= 0;
static char	s_cParseDelimiterChr	= ',';

/** Sets the options to the parsing routes. */
void LQ3A_SetParseOptions(uint uOpt)
{
	s_uParseOpt = uOpt;
}

/** Sets the delimiter used for parsing with LQ3A_PARSE_BREAK_ON_DELIMITER. */
void LQ3A_SetParseDelimiter(char cChr)
{
	s_cParseDelimiterChr = cChr;
}

/** Parses the given path and ensures its valid. */
void LQ3A_ParsePath(pchar pFileName)
{
	size_t	uSize, i;
	
	uSize = strlen(pFileName);

	for (i=0; i<uSize; i++)
	{
		/* Ensure the path separators are suitable for the local system. */
		if ((pFileName[i] == '/') || (pFileName[i] == '\\'))
		{
			pFileName[i] = PATH_SEP;
		}
	}
}

/** Parses the given path to the next carriage return or
		line feed character and returns a parse return code. */
int LQ3A_ParseToCrLf(pchar *ppIn, size_t uIn)
{
	assert(ppIn && uIn);

	while (**ppIn && uIn)
	{
		if ((**ppIn == '\r') || (**ppIn == '\n'))
		{
			return LQ3A_PARSE_R_CRLF;
		}

		(*ppIn)++;
		uIn--;
	}

	return LQ3A_PARSE_R_COMPLETE;
}

/** Parses over a comment in the given string and returns qtrue if a comment was found. */
qboolean LQ3A_ParseComment(pchar *ppIn, size_t uIn)
{
	assert(ppIn && uIn);

	if ((uIn < 2) || (*(*ppIn) != '/') || ((*ppIn)[1] == 0))
	{
		return qfalse;
	}

	if ((*ppIn)[1] == '/')
	{
		*ppIn += 2;
		LQ3A_ParseToCrLf(ppIn, uIn);
		return qtrue;
	}

	if ((*ppIn)[1] == '*')
	{
		*ppIn += 2;
		uIn -= 2;

		while ((uIn >= 2) && **ppIn && (*ppIn)[1])
		{
			if ((**ppIn == '*') && ((*ppIn)[1] == '/'))
			{
				*ppIn += 2;
				return qtrue;
			}

			(*ppIn)++;
			uIn--;
		}

		return qtrue;
	}

	return qfalse;
}

/** Continues parsing the given string to assess if we are ready to break on delimiter.
		Returns LQ3A_PARSE_R_OK when a delimiters break criteria have no been met. */
static int LQ3A_ParseContinueDelimiter(pchar *ppIn, uint uIn, pchar pOut, uint uOut, puint puOutLen)
{
	uint uLen;

	assert(ppIn && pOut && puOutLen);

	uLen = *puOutLen;

	for (;;)
	{
		/* Exit once the in stream. */
		if ((**ppIn == 0) || (uIn == 0))
		{
			break;
		}

		if ((s_uParseOpt & LQ3A_PARSE_COMMENTS) && LQ3A_ParseComment(ppIn, uIn))
		{
			continue;
		}

		if (**ppIn == s_cParseDelimiterChr)
		{
			(*ppIn)++;
			return LQ3A_PARSE_R_DELIMITER;
		}

		if ((**ppIn != '\t') && (**ppIn != ' '))
		{
			*puOutLen = uLen;
			return LQ3A_PARSE_R_OK;
		}

		if (uLen < uOut)
		{
			pOut[uLen] = **ppIn;
		}

		uLen++;

		(*ppIn)++;
		uIn--;
	}

	return LQ3A_PARSE_R_COMPLETE;
}

/* Parses the next argument in the given string and returns the size of the argument parsed.
	If the return value is greater than the given size the given buffer is too small to receive all the data. */
int LQ3A_ParseArg(pchar *ppIn, uint uIn, pchar pOut, uint uOut, puint puOutLen)
{
	uint		uLen;
	qboolean	bQuote;
	int			iRtn;

	assert(ppIn && uIn && pOut && uOut);

	if (!puOutLen)
	{
		puOutLen = &uLen;
	}

	*puOutLen = 0;

	if (uIn == 0)
	{
		return LQ3A_PARSE_R_COMPLETE;
	}

	bQuote	= qfalse;
	iRtn	= LQ3A_PARSE_R_OK;

	for (;;)
	{
		/* Exit at end of stream. */
		if ((**ppIn == 0) || (uIn == 0))
		{
			iRtn = LQ3A_PARSE_R_COMPLETE;
			break;
		}

		/* Parse over comments. */
		if ((s_uParseOpt & LQ3A_PARSE_COMMENTS) && LQ3A_ParseComment(ppIn, uIn))
		{
			continue;
		}

		/* Delimiter. */
		if ((s_uParseOpt & LQ3A_PARSE_BREAK_ON_DELIMITER) && (**ppIn == s_cParseDelimiterChr))
		{
			iRtn = LQ3A_PARSE_R_DELIMITER;

			(*ppIn)++;
			break;
		}

		/* New line. */
		else if ((**ppIn == '\r') || (**ppIn == '\n'))
		{
			if (*puOutLen)
			{
				break;
			}

			/* Finish if we want to know about line breaks. */
			if (s_uParseOpt & LQ3A_PARSE_BREAK_ON_CRLF)
			{
				iRtn = LQ3A_PARSE_R_CRLF;

				(*ppIn)++;
				break;
			}

			/* Don't carry open quotes across lines. */
			bQuote = qfalse;
		}

		/* White space. */
		else if (!bQuote && ((**ppIn == '\t') || (**ppIn == ' ')))
		{
			if (*puOutLen)
			{
				if (s_uParseOpt & LQ3A_PARSE_BREAK_ON_DELIMITER)
				{
					/* Check if we should continue parsing. */
					iRtn = LQ3A_ParseContinueDelimiter(ppIn, uIn, pOut, uOut, puOutLen);

					if (iRtn == LQ3A_PARSE_R_OK)
					{
						/* There are still more characters to parse in this argument. */
						continue;
					}

					break;
				}

				(*ppIn)++;
				break;
			}
		}

		/* Track quotes. */
		else if (**ppIn == '\"')
		{
			if (bQuote)
			{
				/* Double quotes with no content can represent an empty argument. */
				if (s_uParseOpt & LQ3A_PARSE_BREAK_ON_EMPTY)
				{
					iRtn = LQ3A_PARSE_R_EMPTY;

					(*ppIn)++;
					break;
				}

				bQuote = qfalse;
			}
			else
			{
				bQuote = qtrue;
			}
		}

		else
		{
			if (*puOutLen < uOut)
			{
				pOut[*puOutLen] = **ppIn;
			}

			(*puOutLen)++;
		}

		(*ppIn)++;
		uIn--;
	}

	/* Terminate the string. */
	if (*puOutLen < uOut)
	{
		pOut[*puOutLen] = 0;
	}
	else
	{
		pOut[(*puOutLen)-1] = 0;
	}

	return iRtn;
}

/** Returns the given value with respect to the given bounding limits. */
int LQ3A_Clampi(int iValue, int iMin, int iMax)
{
	assert(iMin <= iMax);

	if (iValue < iMin)
	{
		return iMin;
	}

	if (iValue > iMax)
	{
		return iMax;
	}

	return iValue;
}

/** Returns the given value with respect to the given bounding limits. */
float LQ3A_Clampf(float fValue, float fMin, float fMax)
{
	assert(fMin <= fMax);

	if (fValue < fMin)
	{
		return fMin;
	}

	if (fValue > fMax)
	{
		return fMax;
	}

	return fValue;
}

/** Returns a pointer to the structure describing the item with the given classname, NULL is returned on error. */
struct gitem_s *LQ3A_FindItemByClassname(pcchar pcClassName)
{
	struct gitem_s *item;

	assert(pcClassName);
	
	for (item=bg_itemlist+1; item->classname != NULL; item++)
	{
		if (Q_stricmp(item->classname, pcClassName) == 0)
		{
			return item;
		}
	}

	return NULL;
}
