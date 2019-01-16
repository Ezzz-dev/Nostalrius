/**
* Tibia GIMUD Server - a free and open-source MMORPG server emulator
* Copyright (C) 2017  Alejandro Mujica <alejandrodemujica@gmail.com>
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
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef FS_SCRIPT_H_2905B3D5EAB34B4BA8830167262D2DC1
#define FS_SCRIPT_H_2905B3D5EAB34B4BA8830167262D2DC1

#include "tools.h"

enum TOKEN
{
	ENDOFFILE = 0,
	IDENTIFIER,
	NUMBER,
	STRING,
	BYTES,
	COORDINATE,
	SPECIAL
};

class ScriptReader
{
public:
	ScriptReader()
	{
		Token = ENDOFFILE;
		RecursionDepth = -1;
	}

	~ScriptReader()
	{
		if (RecursionDepth != -1)
		{
			std::cout << "ScriptReader::~ScriptReader: File is still open.\n";
			for (int i = RecursionDepth; i != -1; i = RecursionDepth)
			{
				if (fclose(File[i]))
				{
					std::cout << "ScriptReader::close: Error when closing the file.\n";
				}
				--RecursionDepth;
			}
		}
	}

	TOKEN Token;
	FILE* File[3];
	int RecursionDepth;
	char Filename[3][4096];
	std::string CurrentDirectory;
	std::string String;
	unsigned char Bytes[1000];
	int Line[3];
	int Number;
	uint16_t CoordX;
	uint16_t CoordY;
	uint8_t CoordZ;
	char Special;

	bool open(const std::string& FileName)
	{
		RecursionDepth++;
		if (RecursionDepth == 3)
		{
			error("ScriptReader::open: too big recursion.\n");
			error("Recursion depth too high.\n");
			return false;
		}

		if (RecursionDepth > -1)
		{
			CurrentDirectory = FileName;
			if (FileName.find('/') != std::string::npos) {
				int32_t end = FileName.find_last_of('/');
				CurrentDirectory = FileName.substr(0, end);
				strcpy(Filename[RecursionDepth], FileName.substr(end + 1, FileName.length() - end).c_str());
			} else {
				strcpy(Filename[RecursionDepth], FileName.c_str());
			}

			File[RecursionDepth] = fopen(FileName.c_str(), "rb");
			if (!File[RecursionDepth])
			{
				printf("ScriptReader::open: Can not open file %s.\n", FileName.c_str());
				RecursionDepth--;
				printf("Cannot open script-file\n");
				return false;
			}
		}

		Line[RecursionDepth] = 1;
		return true;
	}

	void close()
	{
		int depth; // eax@1

		depth = RecursionDepth;
		if (depth == -1)
		{
			std::cout << "ScriptReader::close: Invalid recursion depth.\n";
		} else
		{
			if (fclose(this->File[depth]))
			{
				std::cout << "ScriptReader::close: Error when closing file.\n";
			}
			--RecursionDepth;
		}
	}

	void error(const std::string& text)
	{
		int depth = this->RecursionDepth;
		if (depth != -1)
		{
			printf("error in script-file \"%s\", line %d: %s\n", Filename[this->RecursionDepth], this->Line[this->RecursionDepth], text.c_str());
			do
			{
				if (fclose(this->File[depth]))
				{
					std::cout << "ScriptReader::close: Error when closing file.\n";
				}
				--this->RecursionDepth;
				depth = this->RecursionDepth;
			} while (this->RecursionDepth != -1);
		}
	}

	void nextToken();

	std::string readIdentifier()
	{
		nextToken();
		if (this->Token != IDENTIFIER)
			error("identifier expected");
		if (this->Token != IDENTIFIER)
			error("identifier expected");
		String = asLowerCaseString(String);
		return std::string(this->String);
	}

	int readNumber()
	{
		TOKEN v1; // edx@1
		int v2; // esi@1

		nextToken();
		v1 = this->Token;
		v2 = 1;
		if (this->Token == SPECIAL && this->Special == 45)
		{
			v2 = -1;
			nextToken();
			v1 = this->Token;
		}
		if (v1 != NUMBER)
			error("number expected");
		if (this->Token != NUMBER)
			error("number expected");
		return this->Number * v2;
	}

	std::string readString()
	{
		nextToken();
		if (this->Token != STRING)
			error("string expected");
		if (this->Token != STRING)
			error("string expected");
		return this->String;
	}

	uint8_t* readBytesequence()
	{
		nextToken();
		if (this->Token != 4)
			error("byte-sequence expected");
		if (this->Token != 4)
			error("byte-sequence expected");
		return this->Bytes;
	}

	void readCoordinate(uint16_t& x, uint16_t& y, uint8_t& z)
	{
		nextToken();
		if (this->Token != COORDINATE)
			error("coordinates expected");
		if (this->Token != COORDINATE)
			error("coordinates expected");
		x = this->CoordX;
		y = this->CoordY;
		z = this->CoordZ;
	}

	int readSpecial()
	{
		nextToken();
		if (this->Token != SPECIAL)
			error("special-char expected");
		if (this->Token != SPECIAL)
			error("special-char expected");
		return this->Special;
	}

	void readSymbol(char Symbol)
	{
		nextToken();
		if (this->Token != SPECIAL)
			error("special-char expected");
		if (Symbol != this->Special)
			error("special-char expected");
	}

	std::string getIdentifier()
	{
		if (this->Token != IDENTIFIER)
			error("identifier expected");
		String = asLowerCaseString(String);
		return this->String;
	}

	int getNumber()
	{
		if (this->Token != NUMBER)
			error("number expected");
		return this->Number;
	}

	std::string getString()
	{
		if (this->Token != STRING)
			error("string expected");
		return this->String;
	}

	uint8_t* getBytesequence()
	{
		if (this->Token != BYTES)
			error("byte-sequence expected");
		return this->Bytes;
	}

	void getcoordinate(int32_t& x, int32_t& y, int32_t& z)
	{
		if (this->Token != COORDINATE)
			error("coordinates expected");
		x = this->CoordX;
		y = this->CoordY;
		z = this->CoordZ;
	}

	int getSpecial()
	{
		if (this->Token != SPECIAL)
			error("special-char expected");
		return this->Special;
	}
};

#endif
