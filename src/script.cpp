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

#include "otpch.h"

#include "script.h"

void ScriptReader::nextToken()
{
	signed int v1; // esi@3
	int v4; // eax@5
	int v5; // eax@8
	int v6; // edi@8
	int v7; // eax@24
	int v9; // eax@32
	int v10; // eax@36
	int v11; // edi@36
	int v12; // eax@45
	int v13; // edi@45
	int v14; // eax@52
	int v15; // edi@52
	int v16; // eax@55
	int v17; // eax@62
	int v18; // eax@70
	int v19; // eax@78
	int v20; // edi@78
	int v21; // eax@86
	int v22; // eax@90
	int v23; // edi@90
	int v24; // eax@94
	int v25; // eax@98
	int v26; // edi@98
	int v27; // eax@102
	int v28; // eax@121
	int v29; // eax@127
	int v30; // eax@131
	int v31; // eax@136
	int v32; // eax@139
	std::string FileName; // [sp+1Ch] [bp-1Ch]@2
	int Sign; // [sp+20h] [bp-18h]@5
	FILE *f; // [sp+24h] [bp-14h]@5
	int pos; // [sp+28h] [bp-10h]@3

	if (this->RecursionDepth == -1)
	{
		error("ScriptReader::nextToken: Kein Skript zum Lesen ge÷ffnet.\n");
	LABEL_30:
		this->Token = ENDOFFILE;
		return;
	}
	FileName = String;
LABEL_3:
	pos = 0;
	v1 = 0;
	this->String = "";
	v4 = this->RecursionDepth;
	this->Number = 0;
	Sign = 1;
	f = this->File[v4];
	while (2)
	{
		if (pos == 3999)
			error("string too long");
		switch (v1)
		{
		case 0:
			v5 = getc(f);
			v6 = v5;
			if (v5 == -1)
				goto LABEL_24;
			if (v5 == 10)
			{
				++this->Line[this->RecursionDepth];
			} else if (!isspace(v5))
			{
				v1 = 1;
				if (v6 != 35)
				{
					v1 = 30;
					if (v6 != 64)
					{
						if (isalpha(v6))
						{
							v1 = 2;
							this->String += v6;
							pos++;
						} else if (IsDigit(v6))
						{
							this->Number = v6 - 48;
							v1 = 3;
						} else
						{
							v1 = 6;
							if (v6 != 34)
							{
								v1 = 11;
								if (v6 != 91)
								{
									v1 = 22;
									if (v6 != 60)
									{
										v1 = 25;
										if (v6 != 62)
										{
											v1 = 27;
											if (v6 != 45)
											{
												v1 = 10;
												this->Special = v6;
											}
										}
									}
								}
							}
						}
					}
				}
			}
			continue;
		case 1:
			v9 = getc(f);
			if (v9 != -1)
			{
				if (v9 == 10)
				{
					++this->Line[this->RecursionDepth];
				LABEL_35:
					v1 = 0;
				}
				continue;
			}
		LABEL_24:
			v7 = this->RecursionDepth;
			if (v7 <= 0)
				goto LABEL_30;
			if (v7 == -1)
			{
				printf("ScriptReader::close: Keine Datei offen.\n");
			} else
			{
				if (fclose(this->File[v7]))
				{
					printf("ScriptReader::close: Fehler %d beim Schlie¯en der Datei.\n", RecursionDepth);
				}
				--this->RecursionDepth;
			}
			goto LABEL_3;
		case 2:
			v10 = getc(f);
			v11 = v10;
			if (pos == 30)
				error("identifier too long");
			if (v10 == -1)
				goto LABEL_43;
			if (isalpha(v10) || IsDigit(v11) || v11 == 95)
				goto LABEL_39;
			ungetc(v11, f);
		LABEL_43:
			this->Token = IDENTIFIER;
			return;
		case 3:
			v12 = getc(f);
			v13 = v12;
			if (v12 == -1)
				goto LABEL_50;
			if (IsDigit(v12))
				goto LABEL_51;
			if (v13 == 45)
				goto LABEL_48;
			ungetc(v13, f);
		LABEL_50:
			this->Token = NUMBER;
			return;
		case 4:
			v14 = getc(f);
			v15 = v14;
			if (v14 == -1)
				error("unexpected end of file");
			if (!IsDigit(v14))
				error("syntax error");
			v1 = 5;
			this->Number = v15 - 48;
			continue;
		case 5:
			v16 = getc(f);
			v13 = v16;
			if (v16 == -1)
				goto LABEL_59;
			if (IsDigit(v16))
				goto LABEL_51;
			if (v13 != 45)
			{
				ungetc(v13, f);
			LABEL_59:
				this->Bytes[pos] = this->Number;
				this->Token = BYTES;
				return;
			}
		LABEL_48:
			this->Bytes[pos++] = this->Number;
			v1 = 4;
			continue;
		case 6:
			v17 = getc(f);
			v11 = v17;
			if (v17 == -1)
				error("unexpected end of file");
			if (v17 == 34)
			{
				v1 = 8;
			} else if (v17 == 92)
			{
				v1 = 7;
			} else
			{
				if (v17 == 10)
					++this->Line[this->RecursionDepth];
			LABEL_39:
				this->String += v11;
				pos++;
			}
			continue;
		case 7:
			v18 = getc(f);
			if (v18 == -1)
				error("unexpected end of file");
			if (v18 == 110) {
				this->String += 10;
				pos++;
			} else {
				this->String += v18;
				pos++;
			}
			v1 = 6;
			continue;
		case 8:
			this->Token = STRING;
			return;
		case 10:
			goto LABEL_77;
		case 11:
			v19 = getc(f);
			this->Special = 91;
			v20 = v19;
			if (v19 == -1)
				goto LABEL_77;
			if (IsDigit(v19))
			{
				Sign = 1;
				this->Number = v20 - 48;
			LABEL_82:
				v1 = 12;
				continue;
			}
			if (v20 == 45)
			{
				Sign = -1;
				this->Number = 0;
				goto LABEL_82;
			}
		LABEL_83:
			ungetc(v20, f);
		LABEL_77:
			this->Token = SPECIAL;
			return;
		case 12:
			v21 = getc(f);
			v13 = v21;
			if (v21 == -1)
				error("unexpected end of file");
			if (IsDigit(v21))
				goto LABEL_51;
			if (v13 != 44)
				error("syntax error");
			v1 = 13;
			this->CoordX = this->Number * Sign;
			continue;
		case 13:
			v22 = getc(f);
			v23 = v22;
			if (v22 == -1)
				error("unexpected end of file");
			if (IsDigit(v22))
			{
				Sign = 1;
				this->Number = v23 - 48;
			} else
			{
				if (v23 != 45)
					error("syntax error");
				Sign = -1;
				this->Number = 0;
			}
			v1 = 14;
			continue;
		case 14:
			v24 = getc(f);
			v13 = v24;
			if (v24 == -1)
				error("unexpected end of file");
			if (IsDigit(v24))
				goto LABEL_51;
			if (v13 != 44)
				error("syntax error");
			v1 = 15;
			this->CoordY = this->Number * Sign;
			continue;
		case 15:
			v25 = getc(f);
			v26 = v25;
			if (v25 == -1)
				error("unexpected end of file");
			if (IsDigit(v25))
			{
				Sign = 1;
				this->Number = v26 - 48;
			} else
			{
				if (v26 != 45)
					error("syntax error");
				Sign = -1;
				this->Number = 0;
			}
			v1 = 16;
			continue;
		case 16:
			v27 = getc(f);
			v13 = v27;
			if (v27 == -1)
				error("unexpected end of file");
			if (IsDigit(v27))
			{
			LABEL_51:
				this->Number = v13 + 10 * this->Number - 48;
			} else
			{
				if (v13 != 93)
					error("syntax error");
				v1 = 17;
				this->CoordZ = this->Number * Sign;
			}
			continue;
		case 17:
			this->Token = COORDINATE;
			return;
		case 22:
			v28 = getc(f);
			this->Special = 60;
			if (v28 == -1)
				goto LABEL_77;
			v1 = 23;
			if (v28 == 61)
				continue;
			v1 = 24;
			if (v28 == 62)
				continue;
			ungetc(v28, f);
			goto LABEL_77;
		case 23:
			this->Special = 76;
			goto LABEL_77;
		case 24:
			this->Special = 78;
			goto LABEL_77;
		case 25:
			v29 = getc(f);
			this->Special = 62;
			v20 = v29;
			if (v29 == -1)
				goto LABEL_77;
			v1 = 26;
			if (v29 != 61)
				goto LABEL_83;
			continue;
		case 26:
			this->Special = 71;
			goto LABEL_77;
		case 27:
			v30 = getc(f);
			this->Special = 45;
			if (v30 == -1)
				goto LABEL_77;
			v1 = 28;
			if (v30 == 62)
				continue;
			ungetc(v30, f);
			goto LABEL_77;
		case 28:
			this->Special = 73;
			goto LABEL_77;
		default:
			error("ScriptReader::nextToken: Ungnltiger Zustand.\n");
			goto LABEL_35;
		case 30:
			v31 = getc(f);
			if (v31 == -1)
				error("unexpected end of file");
			if (v31 != 34)
				error("syntax error");
			v1 = 31;
			continue;
		case 31:
			v32 = getc(f);
			v11 = v32;
			if (v32 == -1)
				error("unexpected end of file");
			if (v32 != 34)
				goto LABEL_39;
			v1 = 32;
			continue;
		case 32:
			open(CurrentDirectory + "/" + String);
			goto LABEL_3;
		}
	}
}
